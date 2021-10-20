#include <iostream>
#include <fstream>
#include "save.hpp"

int convert(float val) {
	return (char)(255 * std::max(0.f, std::min(1.f, val))); 
}

void save(Matrix<Vec3> buf) {
	std::ofstream ofs;
	ofs.open("./out.ppm");
	ofs << "P6\n" << buf.width << " " << buf.height << "\n255\n";

	//Write each channel to the file
	for (size_t i = 0; i < buf.height * buf.width; i++) {
		for (size_t j = 0; j < 3; j++) {
			ofs << (char)convert(buf(i)[j]);
		}
	}
	ofs.close();
}

