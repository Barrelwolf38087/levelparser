#include <cstdint>
#include <fstream>
#include <iostream>

const uint16_t kTile = 1;

int main() {
	std::cout << sizeof(kTile) << std::endl;

	std::ofstream f{"chunk.dat", std::ios::binary | std::ios::app};
	
	for (int i = 0; i < 256; i++) {
		f.write(reinterpret_cast<const char *>(&kTile), sizeof(kTile));
	}

	return 0;
}
