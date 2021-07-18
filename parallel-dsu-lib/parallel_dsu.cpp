#include "parallel_dsu.h"

DSUParallel::DSUParallel(uint64_t size) {
    for (uint64_t i = 0; i < size; ++i) {
        parents_[i].store(i);
        ranks_[i].store(0);
    }
}

uint64_t DSUParallel::find_set(uint64_t id) {
    while (id != parents_[id].load()) {
        uint64_t parent = parents_[id].load();
        uint64_t grandparent = parents_[parent].load();
        parents_[id].compare_exchange_weak(parent, grandparent);
        id = grandparent;
    }
    return id;
}

bool DSUParallel::same(uint64_t id1, uint64_t id2) {
    for (;;) {
        id1 = find_set(id1);
        id2 = find_set(id2);
        if (id1 == id2) {
            return true;
        }
        if (parents_[id1] == id1) {
            return false;
        }
    }
}

uint64_t DSUParallel::unite(uint64_t id1, uint64_t id2) {
    for (;;) {
        id1 = find_set(id1);
        id2 = find_set(id2);

        if (id1 == id2)
            return id1;

        uint64_t rank1 = ranks_[id1].load();
        uint64_t rank2 = ranks_[id2].load();

        if (rank1 > rank2 || (rank1 == rank2 && id1 < id2)) {
            std::swap(rank1, rank2);
            std::swap(id1, id2);
        }

        if (!parents_[id1].compare_exchange_strong(id1, id2))
            continue;

        if (rank1 == rank2) {
            ranks_[id2].compare_exchange_weak(rank2, rank2 + 1);
        }
        break;
    }
    return id2;
}
