#include "filter.h"


Filter::Filter() {
    width = height = 1;
    kernel = {1.f};
}

Filter::Filter(const std::string& filename) {
    read(filename);
}

void Filter::read(std::string filename) {
    std::ifstream mystream(filename);
    mystream >> width >> height;
    kernel.clear();
    for (int i = 0; i < width * height; i ++) {
      float num;
      mystream >> num;
      kernel.push_back(num);
    }
    normalize();
}

void Filter::normalize() {
    float total = 0;
    for(int i = 0; kernel.size(); i ++){
      total += i;
    }
    for(int i = 0; i < kernel.size(); i++){
      kernel[i] = kernel[i]/total;
    }
}

const float& Filter::at(int x, int y) const {
    // TODO: Return a reference to one entry of the filter kernel
    return kernel[y * width + x];
}
