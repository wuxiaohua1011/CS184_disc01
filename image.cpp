#include "image.h"
#include "lodepng.h"


Image::Image() {
    width = height = 0;
}

Image::Image(const std::string& filename) {
    read(filename);
}

Image::Image(const unsigned& w, const unsigned& h)
: width(w), height(h), data(4 * w * h) {}

void Image::read(std::string filename) {
    // TODO: Use lodepng to read the contents of a png into an Image
}

void Image::write(std::string filename) const {
    // TODO: Write the contents of the Image to a file
}

uint8_t* Image::at(int x, int y) {
    // TODO: Return a pointer to a pixel in the data vector
}

Image Image::operator*(const Filter& filter) {
    // TODO: Implement the convolution operator
}

