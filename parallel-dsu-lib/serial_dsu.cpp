#include "serial_dsu.h"

DSUSerial::DSUSerial(uint64_t size) : parents_(size), ranks_(size) {
    for (size_t i = 0; i != size; ++i) {
        parents_[i] = i;
        ranks_[i] = 0;
    }
}

uint64_t DSUSerial::find_set(uint64_t id) {
    if (id == parents_[id]) {
        return id;
    }
    return parents_[id] = find_set(parents_[id]);
}

uint64_t DSUSerial::unite(uint64_t id1, uint64_t id2) {
    id1 = find_set(id1);
    id2 = find_set(id2);
    if (id1 != id2) {
        if (ranks_[id1] < ranks_[id2]) {
            std::swap(id1, id2);
        }
        parents_[id2] = id1;
        if (ranks_[id1] == ranks_[id2]) {
            ++ranks_[id1];
        }
    }
    return id1;
}

bool DSUSerial::same(uint64_t id1, uint64_t id2) {
    id1 = find_set(id1);
    id2 = find_set(id2);
    if (id1 == id2) {
        return true;
    }
    return false;
}