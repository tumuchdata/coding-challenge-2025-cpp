#include <iostream>
#include <vector>

#include "User.hpp"
#include "Parameters.hpp"
#include "FileUtils.hpp"
#include <cassert>

size_t eval(std::span<const uint32_t> values, uint32_t predicate){
    size_t result = 0;
    for (const auto val : values){
        result += val == predicate;
    }
    return result;
}

int main(int argc, char** argv){
    if (argc != 4){
        std::cout << "Usage: ./main <f_a> <f_s> <filename>" << std::endl;
        return 1;
    }
    Parameters p(argv[1], argv[2], argv[3]);
    InMemoryFile dataFile(p.filename + ".data");
    InMemoryFile queryFile(p.filename + ".query");
    
    const auto* data = reinterpret_cast<const DataFile*>(dataFile.begin());
    const auto* queries = reinterpret_cast<const QueryFile*>(queryFile.begin());

    std::vector<std::vector<std::byte>> indexes(data->num_chunks);
    size_t storage_size = 0;
    for (size_t i=0; i!=data->num_chunks; i++){
        indexes[i] = build_idx(data->getChunk(i), p);
        storage_size += indexes[i].size();
    }
    storage_size = (storage_size + 1023) / 1024;

    size_t num_skips = 0;
    for (size_t i=0; i!=queries->num_queries; i++){
        uint32_t predicate = queries->values[i];
        for (size_t j=0; j!=data->num_chunks; j++){
            auto user_result = query_idx(predicate, indexes[j]);
            if (user_result.has_value()){
                assert(user_result.value() == eval(data->getChunk(j), predicate));
                num_skips++;
            }
        }
    }

    double normalizer = p.f_a * data->num_chunks * queries->num_queries ;
    int64_t score = (int64_t) num_skips * (int64_t) p.f_a - (int64_t) storage_size * (int64_t) p.f_s;

    std::cout << "storage size: " << storage_size << " " << storage_size * p.f_a << std::endl; 
    std::cout << "num skips: " << num_skips << " " << num_skips * p.f_s << std::endl;
    std::cout << "total score:" << score * 100.0 / normalizer << std::endl;

    return 0; 
}
