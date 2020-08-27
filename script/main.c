#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define READ_BUFF 1000

_Static_assert(READ_BUFF > 0, "READ_BUFF cannot be less than or equal to zero");

typedef struct		s_list			t_list;
typedef struct		s_list_elem		t_list_elem;

struct				s_list
{
	t_list_elem		*first;
	t_list_elem		*last;
};

struct				s_list_elem
{
	t_list_elem		*next;
	ssize_t			start;
	ssize_t			end;
};

void list_add(t_list *list, t_list_elem *elem)
{
	if (list->last)
		list->last->next = elem;
	else
		list->first = elem;
	list->last = elem;
}

t_list_elem *list_new_elem(ssize_t start, ssize_t end)
{
	t_list_elem *tmp;

	if ((tmp = (t_list_elem *)malloc(sizeof(t_list_elem))))
	{
		tmp->next = NULL;
		tmp->start = start;
		tmp->end = end;
	}
	return (tmp);
}

ssize_t read_text(int fd, char **dst)
{
	char buf[READ_BUFF];
	char *str = NULL;
	char *tmp;
	ssize_t len = 0;
	ssize_t n;

	while ((n = read(fd, buf, READ_BUFF)) > 0)
	{
		tmp = str;
		if (!(str = (char *)malloc(sizeof(char) * (len + n))))
			exit(1);
		memcpy(str, tmp, len);
		memcpy(str + len, buf, n);
		free(tmp);
		len += n;
	}
	if (n < 0)
	{
		free(str);
		return -1;
	}
	*dst = str;
	return len;
}

void file_search(char *file, ssize_t len, t_list *list)
{
	/* 
	 * 0: ()
	 * 1: []
	 * 2: {}
	 */
	int counter[3] = {0, 0, 0};
	char brackets[3][2] =
		{
			{'(', ')'},
			{'[', ']'},
			{'{', '}'}
		};
	char last_o = -1;
	char last_c = -1;
	char in_func = 0;
	char potential_func = 0;
	int bracket_nbr;
	ssize_t i;
	t_list_elem *tmp = NULL;
	i = 0;
	while (i < len)
	{
		if (!isspace(file[i]) && file[i] != brackets[2][0])
		{
			potential_func = 0;
		}
		for (int a = 0; a < 3; ++a)
			for (int b = 0; b < 2; ++b)
				if (file[i] == brackets[a][b])
				{
					counter[a] += b ? -1 : 1;
					if (b)
					{
						if (counter[a] < 0)
							exit(1);
						last_c = a;
						if (last_c == 0)
							potential_func = 1;
						else if (tmp && last_c == 2 && counter[last_c] == bracket_nbr)
						{
							tmp->end = i;
							list_add(list, tmp);
							tmp = NULL;
							in_func = 0;
						//printf("%c %c\n", brackets[last_o][0], brackets[last_c][1]);
						}
					}
					else
					{
						last_o = a;
						if (potential_func && !in_func && last_o == 2)
						{
							tmp = list_new_elem(i + 1, -1);
							in_func = 1;
							bracket_nbr = counter[2] - 1;
							potential_func = 0;
						//printf("%c %c\n", brackets[last_o][0], brackets[last_c][1]);
						}
					}
				}
		++i;
	}
	if (tmp)
		exit(1);
}

//TODO скипать комментарии и между круглыми и фигурными скобками функции только пробелы!
//TODO скипать ZSA функции
//TODO сделать обязательный флаг перед строкой которая добавляется в каждую функцию

#define MAIN_COMMENT "/* zway not implemented */"
#define PRE_COMMENT "/* OZW code *"
#define POST_COMMENT "* OZW code */"

void file_treatment(int fd, char *file, ssize_t len, t_list *list, char *code)
{
	const size_t main_len = strlen(MAIN_COMMENT);
	const size_t code_len = strlen(code);
	const size_t pre_len = strlen(PRE_COMMENT);
	const size_t post_len = strlen(POST_COMMENT);

	lseek(fd, SEEK_SET, 0);
	if (!list->first)
		return;
	t_list_elem *tmp = list->first;
	t_list_elem *prev;
	ssize_t n = 0;
	ssize_t from;
	ssize_t to;
	while (tmp)
	{
		write(fd, file + n, tmp->start - n);
		write(fd, "\n", 1);
		write(fd, MAIN_COMMENT, main_len);
		write(fd, code, code_len);
		write(fd, MAIN_COMMENT, main_len);
		//write(fd, PRE_COMMENT, pre_len);
		from = tmp->start;
		if (file[from] != '\n')
		{
			write(fd, "\n", 1);
			write(fd, "//", 2);
		}
		for (to = tmp->start; to < tmp->end; ++to)
		{
			if (file[to] == '\n')
			{
				write(fd, file + from, to - from + 1);
				if (to + 1 < tmp->end)
					write(fd, "//", 2);
				from = to + 1;
			}
		}
		if (file[to - 1] != '\n')
		{
			write(fd, file + from, to - from);
			write(fd, "\n", 1);
		}
		//write(fd, POST_COMMENT, post_len);
		n = tmp->end;
		prev = tmp;
		tmp = tmp->next;
		free(prev);
	}
	write(fd, file + n, len - n);
}

int main(int ac, char *av[])
{
	if (ac < 3)
	{
		printf("usage: %s <string> <file1> [<file2> ...]\n", *av);
		return 0;
	}
	int fd;
	char *file;
	ssize_t len;
	char *code = av[1];
	t_list list;
	int i = 1;
	while (++i < ac)
	{
		fd = open(av[i], O_RDWR);
		if ((len = read_text(fd, &file)))
		printf("begin\n");
		file_search(file, len, &list);
		printf("end\n");
		file_treatment(fd, file, len, &list, code);
		free(file);
		close(fd);
	}
	return 0;
}
