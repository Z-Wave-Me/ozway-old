PROJECTS = ozw-power-on-off     \
           ozw-pir-power-switch \
           ozw-pir-active
OUT      = $(addsuffix .out,$(PROJECTS))
OBJ      = $(addsuffix .o,$(PROJECTS))
OZWAY    = ozway
CC       = g++
IFLAGS   = -I $(OZWAY)/cpp/src                \
           -I $(OZWAY)/cpp/src/command_classes \
           -I $(OZWAY)/cpp/src/platform        \
           -I $(OZWAY)/cpp/src/value_classes   \
           -I $(OZWAY)/libzway
LIBS     = -lopenzwave \
	   -lzway \
	   -lzcommons \
	   -lzs2 \
           -lpthread
LDFLAGS  = -L/usr/local/lib -Wl,-R/usr/local/lib '-Wl,-R$$ORIGIN' -L./$(OZWAY) -L./$(OZWAY)/libzway/
CFLAGS   = -std=c++11
LIBFILE  = libopenzwave.so.1.6

all: ozway_lib $(OUT)

$(OUT): %.out: %.o
	echo "making out"
	$(CC) $(LDFLAGS) $< $(LIBS) -o $@

$(OBJ): %.o: %/Main.cpp
	echo "making obj"
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

ozway_lib:
	echo "making lib"
	$(MAKE) -C $(OZWAY)
	cp $(OZWAY)/$(LIBFILE) ./

clean:
	rm -rf *.o *.out
	rm -f $(LIBFILE)
	$(MAKE) -C $(OZWAY) clean

re: clean all
