#include "filter.h"


Filter::Filter() {
	width = height = 1;
	kernel = {1.f};
}

Filter::Filter(const std::string& filename) {
	read(filename);
}

void Filter::read(std::string filename) {
	// todo
}

void Filter::normalize() {
	// todo	
}

const float& Filter::at(int x, int y) const {
	// todo
}