#PROJECTS = ozw-power-on-off     \
           ozw-pir-power-switch \
           ozw-pir-active
PROJECTS = ozw-power-on-off
OUT      = $(addsuffix .out,$(PROJECTS))
OBJ      = $(addsuffix .o,$(PROJECTS))
OZWAY    = ozway
CC       = g++
IFLAGS   = -I $(OZWAY)/cpp/src                \
           -I $(OZWAY)/cpp/src/command_classes \
           -I $(OZWAY)/cpp/src/platform        \
           -I $(OZWAY)/cpp/src/value_classes   \
           -I $(OZWAY)/libzway
LIBS     = -lzway \
	   -lzcommons \
	   -lzs2 \
           -lpthread \
           -lxml2 \
           -larchive \
           -lcrypto \
           -lopenzwave
LDFLAGS  += -Lozway
LDFLAGS  += -Wl,-R/usr/local/lib
LDFLAGS  += '-Wl,-R$$ORIGIN'
LDFLAGS  += -L./$(OZWAY)
#LDFLAGS  += -L./$(OZWAY)/libzway/
CFLAGS   = -std=c++11

all: ozway_lib $(OUT)

$(OUT): %.out: %.o
	echo "making out"
	$(CC) $(LDFLAGS) $< $(LIBS) -o run_$@

$(OBJ): %.o: %/Main.cpp
	echo "making obj"
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

ozway_lib:
	echo "making lib"
	$(MAKE) -C $(OZWAY)

clean:
	rm -rf *.o *.out
	rm -f $(LIBFILE)
	$(MAKE) -C $(OZWAY) clean

re: clean all
