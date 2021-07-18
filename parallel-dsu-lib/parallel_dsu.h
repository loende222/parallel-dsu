#pragma once

#include <cstdint>
#include <atomic>
#include <vector>

struct DSUParallel {
private:
    mutable std::vector<std::atomic<uint64_t>> parents_;
    mutable std::vector<std::atomic<uint64_t>> ranks_;

public:
    DSUParallel(uint64_t size);
    uint64_t find_set (uint64_t id);
    bool same(uint64_t id1, uint64_t id2);
    uint64_t unite(uint64_t id1, uint64_t id2);
};

