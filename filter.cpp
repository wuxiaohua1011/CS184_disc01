#include "filter.h"


Filter::Filter() {
    width = height = 1;
    kernel = {1.f};
}

Filter::Filter(const std::string& filename) {
    read(filename);
}

void Filter::read(std::string filename) {
    int x, y;
    std::ifstream mystream(filename);
    mystream >> x >> y;
}

void Filter::normalize() {
    // TODO: Ensure that all elements of the filter add up to 1
}

const float& Filter::at(int x, int y) const {
    // TODO: Return a reference to one entry of the filter kernel
}
