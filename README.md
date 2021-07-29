# Wait-free DSU

Это wait-free реализация системы непересекающихся множеств (disjoint-set-union, DSU) с эвристикой сжатия пути и ранговой эвристикой (на основе глубины деревьев).

# Сборка проекта. Запуск тестов и бенчмарков

## Сборка
```
$ git clone git@github.com:loende222/parallel-dsu.git
$ cd parallel-dsu
$ mkdir build
$ cd build
$ cmake ..
$ make
```


## Запуск тестов

Из директории `build`:
```
$./tests/bin/all_tests
```

## Запуск бенчмарков
Из директории `build`:
```
$ ./benchmarks/bin/parallel_dsu
$ ./benchmarks/bin/serial_dsu
```
