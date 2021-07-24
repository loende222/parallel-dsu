#pragma once

#include <cstdint>
#include <vector>

struct DSUSerial {
private:
    std::vector<uint64_t> parents_;
    std::vector<uint64_t> ranks_;

public:
    DSUSerial(uint64_t size);
    uint64_t find_set (uint64_t id);
    bool same(uint64_t id1, uint64_t id2);
    uint64_t unite(uint64_t id1, uint64_t id2);
};

