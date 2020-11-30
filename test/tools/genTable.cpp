#include <cstdint>
#include <fstream>
#include <iostream>

struct ChunkTableEntry {
	int16_t x;
	int16_t y;
	uint32_t ptr;
};

int main() {
	std::ofstream f{"table.dat", std::ios::binary | std::ios::app};

	ChunkTableEntry e{0, 0, 0};

	f.write(reinterpret_cast<const char *>(&e), sizeof(e));

	return 0;
}
