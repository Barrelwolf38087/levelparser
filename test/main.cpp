#include <levelparser.hpp>

#include <iostream>

int main() {
    lp::Level level{"test.level"};

    std::cout << "Level Version:\t"  << level.version() << std::endl;
    std::cout << "Level Name:\t\t" << level.name() << std::endl;
    std::cout << "Chunks:\t\t\t" << level.size() << std::endl;

    auto chunk = level.chunk({0, 0});

    std::cout << "Chunk 0, 0:" << std::endl;
    std::cout << "\tOffset:\t\t" << level.chunkTable().find({0, 0})->second << std::endl;
    std::cout << "\tFirst Tile:\t" << chunk[0] << std::endl;

    return 0;
}
