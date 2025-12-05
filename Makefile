SRC = src/*.c 
END = build/nisse.bin 
END_D = build/nisse_debug.bin
END_O = build/nisse_optimal.bin

COMP = gcc
FLAGS = -I include

all: $(END)

$(END): $(SRC)
	$(COMP) $(SRC) -o $(END) $(FLAGS)

debug: $(END_D)

$(END_D): $(SRC)
	$(COMP) $(SRC) -o $(END_D) $(FLAGS) -g

optimal: $(END_O)

$(END_O): $(SRC)
	$(COMP) $(SRC) -o $(END_O) $(FLAGS) -g -O3

clean:
	rm -rf $(END) $(END_D) $(END_O)

.PHONY: all clean
