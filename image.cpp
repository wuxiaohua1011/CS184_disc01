#include "image.h"
#include "lodepng.h"


Image::Image() {
	width = height = 0;
}

Image::Image(const std::string& filename) {
	read(filename);
}

Image::Image(const unsigned& w, const unsigned& h)
: width(w), height(h), data(4 * w * h) {

}

void Image::read(std::string filename) {
	// todo
}

void Image::write(std::string filename) const {
	// todo
}

uint8_t* Image::at(int x, int y) {
	// todo
}

Image Image::operator*(const Filter& filter) {
	// todo
}





