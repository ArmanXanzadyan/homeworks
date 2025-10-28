#include <benchmark/benchmark.h>
#include "headers/Sudoku.hpp"

static void BM_GenerateRandomSudoku(benchmark::State& state)
{
    while (state.KeepRunning())
    {
        Sudoku sudoku;
        sudoku.generateRandomSudoku();
    }
}
BENCHMARK(BM_GenerateRandomSudoku);

static void BM_GenerateRandomSudoku1(benchmark::State& state)
{
    const int percent = 50;
    while (state.KeepRunning())
    {
        Sudoku sudoku;
        sudoku.generateRandomSudoku1(percent);
    }
}
BENCHMARK(BM_GenerateRandomSudoku1);

static void BM_GenerateRandomSudoku2(benchmark::State& state)
{
    const int percent = 50;
    while (state.KeepRunning())
    {
        Sudoku sudoku;
        sudoku.generateRandomSudoku2(percent);
    }
}
BENCHMARK(BM_GenerateRandomSudoku2);

static void BM_SolveSudoko(benchmark::State& state)
{
    Sudoku sudoku;
    sudoku.generateRandomSudoku();
    while (state.KeepRunning())
    {
        Sudoku copy = sudoku;
        copy.solveSudoko();
    }
}
BENCHMARK(BM_SolveSudoko);

BENCHMARK_MAIN();

