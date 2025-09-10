#include <optional>
#include <vector>
#include <span>
#include <cstdint>
#include <cassert>

#include "Parameters.hpp"

std::vector<std::byte> build_idx(std::span<const uint32_t> data, Parameters config){
    assert(false && "Implement me!");
}

std::optional<size_t> query_idx(uint32_t predicate, const std::vector<std::byte>& index){
    assert(false && "Implement me!");
}