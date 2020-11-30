#include "../include/levelparser.hpp"

using namespace lp;

constexpr size_t kVersionWidth = 2;
constexpr size_t kSizeWidth = 5;

Level::Level(const std::string &file)
        : _version{0}, _numChunks{0} {
    _file.open(file, std::ios::binary);

    // Read version
    _file.read(reinterpret_cast<char *>(&_version), kVersionWidth);

    char b;
    while ((b = _file.get()) != '\0') {
        _levelName.push_back(b);
    }

    _file.read(reinterpret_cast<char *>(&_numChunks), kSizeWidth);

    _chunkData.reserve(_numChunks);

    for (uint64_t i = 0; i < _numChunks; i++) {
        ChunkTableEntry tableEntry{};
        _file.read(reinterpret_cast<char *>(&tableEntry), sizeof(ChunkTableEntry));

        _chunkTable.insert(std::pair{std::pair{tableEntry.x, tableEntry.y}, tableEntry.ptr});
    }

    for (uint64_t i = 0; i < _numChunks; i++) {
        _chunkData.emplace_back();

        _file.read(reinterpret_cast<char *>(&_chunkData.back().data), sizeof(Chunk));
    }

}
