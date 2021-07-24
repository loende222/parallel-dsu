#include <gtest/gtest.h>
#include <parallel-dsu-lib/parallel_dsu.h>
#include <parallel-dsu-lib/parallel_dsu.cpp>

#include <thread>
#include <vector>
#include <atomic>


TEST(ParallelDSU, Simple) {
    DSUParallel dsu(3);
    ASSERT_EQ(1, dsu.find_set(1));
    ASSERT_FALSE(dsu.same(1, 2));
    dsu.unite(1, 2);
    ASSERT_TRUE(dsu.same(1, 2));
    ASSERT_FALSE(dsu.same(0, 1));
}

TEST(ParallelDSU, MultipleThreads) {
    DSUParallel dsu(1024);
    std::vector<std::thread> threads;
    for (size_t i = 0; i != 512; ++i) {
        threads.emplace_back([&dsu, i] {
            dsu.unite(2 * i, 2 * i + 1);
        });
    }
    for (auto& thread : threads) {
        thread.join();
    }
    ASSERT_TRUE(dsu.same(4, 5));
    ASSERT_FALSE(dsu.same(3, 4));
    threads.clear();
    for (size_t i = 0; i != 1023; ++i) {
        threads.emplace_back([&dsu, i] {
            if (i % 2 == 0) {
                ASSERT_TRUE(dsu.same(i, i + 1));
            } else {
                ASSERT_FALSE(dsu.same(i, i + 1));
            }
        });
    }
    for (auto& thread : threads) {
        thread.join();
    }
}

TEST(ParallelDSU, SetSize) {
    DSUParallel dsu(100);
    std::vector<std::thread> threads;
    for (size_t i = 1; i < 100; ++i) {
        threads.emplace_back([i, &dsu] {
            dsu.unite(0, i);
        });
    }
    for (auto& thread : threads) {
        thread.join();
    }
    threads.clear();
    std::atomic<int> counter;
    counter.store(0);
    for (size_t i = 0; i < 100; ++i) {
        threads.emplace_back([i, &dsu, &counter] {
            if (dsu.same(99, i)) {
                ++counter;
            }
        });
    }
    for (auto& thread : threads) {
        thread.join();
    }
    ASSERT_EQ(counter.load(), 100);
}

TEST(ParallelDSU, SetSizes) {
    DSUParallel dsu(100);
    std::vector<std::thread> threads;
    for (size_t i = 1; i < 50; ++i) {
        threads.emplace_back([i, &dsu] {
            dsu.unite(0, i);
        });
    }
    for (size_t i = 51; i < 100; ++i) {
        threads.emplace_back([i, &dsu] {
            dsu.unite(50, i);
        });
    }
    for (auto& thread : threads) {
        thread.join();
    }
    threads.clear();

    std::atomic<int> counter;
    counter.store(0);
    for (size_t i = 0; i < 100; ++i) {
        threads.emplace_back([i, &dsu, &counter] {
            if (dsu.same(0, i)) {
                ++counter;
            }
        });
    }
    for (auto& thread : threads) {
        thread.join();
    }
    threads.clear();
    ASSERT_EQ(counter.load(), 50);

    dsu.unite(20, 80);
    counter.store(0);
    for (size_t i = 0; i < 100; ++i) {
        threads.emplace_back([i, &dsu, &counter] {
            if (dsu.same(0, i)) {
                ++counter;
            }
        });
    }
    for (auto& thread : threads) {
        thread.join();
    }
    ASSERT_EQ(counter.load(), 100);
}