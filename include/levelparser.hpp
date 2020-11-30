#ifndef LEVELPARSER_H
#define LEVELPARSER_H

#include <cstdint>
#include <vector>
#include <map>
#include <utility>
#include <string>
#include <fstream>


namespace lp {
    typedef uint16_t Version;

    class Level {

        struct Chunk {
            typedef int16_t TileID;
            constexpr static size_t size = 256;
            TileID data[256];
        };

        using ChunkTableKey = std::pair<int16_t, int16_t>;
        using ChunkPtr = uint32_t;
        using ChunkTable = std::map<ChunkTableKey, ChunkPtr>;
        using ChunkRef = const Chunk::TileID*;

        struct ChunkTableEntry {
            // Not a std::pair so we can simply reinterpret_cast the raw data.
            // Looking at its definition, it might actually work, but I'll figure it out later.
            int16_t x;
            int16_t y;
            ChunkPtr ptr;
        };

        std::ifstream _file;

        Version _version;
        std::string _levelName;
        uint64_t _numChunks;
        ChunkTable _chunkTable;
        std::vector<Chunk> _chunkData;

    public:

        /**
         * Get the version of the level format
         * @return The format version
         */
        [[nodiscard]] Version version() const {
            return _version;
        }

        /**
         * Get the level name
         * @return The level name
         */
        [[nodiscard]] const std::string& name() const {
            return _levelName;
        }

        /**
         * Get the size of the level
         * @return The number of chunks in the level
         */
        [[nodiscard]] uint64_t size() const {
            return _numChunks;
        }

        /**
         * Get the data for a chunk
         * @param index The index of the chunk to get
         * @return A pointer to the chunk data
         */
        ChunkRef operator[](ChunkPtr index) const {
            return _chunkData[index].data;
        }

        /**
         * Get the chunk table
         * @return A map of chunk coordinates to indexes
         */
        const ChunkTable& chunkTable() const {
            return _chunkTable;
        }

        /**
         * Convenience function to get a chunk from its coordinates
         * @return A pointer to the data of the chunk at the given coordinates
         */
        ChunkRef chunk(ChunkTableKey coords) const {
            auto c = _chunkTable.find(coords);

            if (c == _chunkTable.end()) {
                return nullptr;
            } else {
                return operator[](c->second);
            }
        }

        /**
         * Read a level from a file
         * @param file The level file to read
         */
        explicit Level(const std::string& file);

        ~Level() = default;

        // Prevent copying, since having two references to the same std::ifstream would cause problems
        Level(const Level& other) = delete;
        Level& operator=(const Level& other) = delete;
    };

}

#endif // LEVELPARSER_H
