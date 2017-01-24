all: main.cpp lodepng.cpp lodepng.h image.cpp image.h filter.cpp filter.h
	g++ main.cpp lodepng.cpp image.cpp filter.cpp -o convolve -std=c++11