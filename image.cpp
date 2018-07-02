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
    data.clear();
    //decode
    unsigned error = lodepng::decode(data, width, height, filename);

    //if there's an error, display it
    if(error) std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;

    //the pixels are now in the vector "image", 4 bytes per pixel, ordered RGBARGBA..., use it as texture, draw it, ...
}

void Image::write(std::string filename) const {
    // TODO: Write the contents of the Image to a file
    //Encode the image
    unsigned error = lodepng::encode(filename, data, width, height);

    //if there's an error, display it
    if(error) std::cout << "encoder error " << error << ": "<< lodepng_error_text(error) << std::endl;
}

uint8_t* Image::at(int x, int y) {
    // TODO: Return a pointer to a pixel in the data vector
    return &data[0] + 4 * (y * width + x);
}

Image Image::operator*(const Filter& filter) {
    // TODO: Implement the convolution operator
    Image newImg(width, height);
    for (int y = 0; y < height; ++y) {
    for (int x = 0; x < width; ++x) {

        float temp[] = {0,0,0,0};
        for (int j = 0; j < filter.height; ++j) {
            for (int i = 0; i < filter.width; ++i) {
                int xi = x + i - filter.width/2, yi = y + j - filter.height/2;
                if (xi < 0 || xi >= width || yi < 0 || yi >= height) {
                    continue;
                } else {
                    for (int k = 0; k < 4; ++k)
                        temp[k] += at(xi,yi)[k] * filter.at(i,j);
                }
            }
        }

        for (int k = 0; k < 4; ++k) {
            newImg.at(x,y)[k] = temp[k];
            }
        }
    }
    return newImg;
}
