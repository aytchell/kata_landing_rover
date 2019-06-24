all: rover

H_FILES = position.h planet.h read_input.h map_printer.h
CXX_FILES = main.cpp position.cpp planet.cpp read_input.cpp map_printer.cpp

rover: $(H_FILES) $(CXX_FILES)
	g++ -std=c++11 -Wall -Wextra -pedantic -o rover $(CXX_FILES)
