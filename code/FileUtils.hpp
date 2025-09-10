#pragma once

#include <fstream>
#include <vector>

struct DataFile {
    uint64_t num_chunks;
    uint64_t chunk_size;
    uint32_t values[];

    std::span<const uint32_t> getChunk(size_t chunk) const {
        return {values + chunk * chunk_size, chunk_size};
    }
};

struct QueryFile {
    uint64_t num_queries;
    uint32_t values[];
};

class InMemoryFile {
private:
    std::vector<char> buffer;

public:
    explicit InMemoryFile(const std::string& fileName) {
        std::ifstream file(fileName, std::ios::binary | std::ios::ate);
        if (!file) {
            std::cerr << "Failed to open file: " << fileName << std::endl;
            exit(2);
        }

        std::streamsize size = file.tellg();
        file.seekg(0, std::ios::beg);

        buffer.resize(size);
        if (!file.read(buffer.data(), size)) {
            std::cerr << "Failed to read file: " << fileName << std::endl;
            exit(3);
        }
    }

    const char* begin() const {
        return buffer.data();
    }

    const char* end() const {
        return buffer.data() + buffer.size();
    }

    uintptr_t size() const {
        return buffer.size();
    }
};
