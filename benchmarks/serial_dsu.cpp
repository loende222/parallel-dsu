#include <benchmark/benchmark.h>
#include <parallel-dsu-lib/serial_dsu.h>

bool Check(uint64_t value) {
    DSUSerial dsu(value);
    for (size_t i = 0; i != value; ++i) {
        dsu.unite(0, i);
    }
    return true;
}

static void BM_SerialDSU(benchmark::State& state) {
    uint64_t value = state.range(0);
    for (auto _ : state) {
        benchmark::DoNotOptimize(Check(value));
    }
}

BENCHMARK(BM_SerialDSU)
        ->Args({65536 * 1024 / 4});

BENCHMARK_MAIN();