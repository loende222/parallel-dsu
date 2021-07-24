#include <benchmark/benchmark.h>
#include <parallel-dsu-lib/parallel_dsu.h>

#include <thread>


bool Check(uint64_t n_threads) {
    const size_t len = 65536 * 1024 / 4;
    DSUParallel dsu(len);
    size_t step = len / n_threads;
    std::vector<std::thread> threads;
    for (size_t i = 0; i != n_threads; ++i) {
        threads.emplace_back([&dsu, i, step] {
            for (size_t j = i * step; j < std::min((i + 1) * step, len - 1); ++j) {
                dsu.unite(i * step, j + 1);
            }
        });
    }
    for (auto& thread : threads) {
        thread.join();
    }
    return true;
}

static void BM_ParallelDSU(benchmark::State& state) {
    uint64_t value = state.range(0);
    for (auto _ : state) {
        benchmark::DoNotOptimize(Check(value));
    }
}

BENCHMARK(BM_ParallelDSU)
        ->Args({1})
        ->Args({2})
        ->Args({4})
        ->Args({8})
        ->Args({16})
        ->Args({32});

BENCHMARK_MAIN();