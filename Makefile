.PHONY: all clean

INC := inc
SRC := src/algo_extractor.cpp src/main.cpp

all: build
	g++ -m32 -I$(INC) $(SRC) -o build/extractor.out

clean:
	rm -r build

build:
	mkdir build