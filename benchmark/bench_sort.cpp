/** @file
 *
 * @date 08.03.2020
 * @author domohuhn
 * @copyright This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include <benchmark/benchmark.h>
#include <random>
#include <vector>
#include <limits>
#include "sort/radix_sort.hpp"

extern volatile size_t result;
using namespace HASHES_NAMESPACE;

static std::vector<size_t> vec_sort{};
constexpr size_t max_sorting_size = 1024*1024*1024;

static bool init_data()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<size_t> dis(0, std::numeric_limits<size_t>::max());
    size_t generate_numbers=max_sorting_size;
    vec_sort.reserve(generate_numbers);
    for(size_t i=0;i<generate_numbers;++i){
        vec_sort.push_back(dis(gen));
    }
}

static bool is_init = init_data();

void BM_Sort_radix(benchmark::State& state) {
    std::random_device rd;
    std::mt19937 gen(rd());
    auto begin = vec_sort.begin();
    size_t dist=state.range(0);
    if(dist>vec_sort.size())
        std::terminate();
    auto end = std::next(vec_sort.begin(),dist);
    for (auto _ : state){
        state.PauseTiming(); // Stop timers. They will not count until they are resumed.
        std::shuffle( begin, end, gen );
        state.ResumeTiming();
        radix_sort(begin,end);
    }
}
BENCHMARK(BM_Sort_radix)->RangeMultiplier(8)->Range(4, max_sorting_size)->Complexity();


void BM_Sort(benchmark::State& state) {
    std::random_device rd;
    std::mt19937 gen(rd());
    auto begin = vec_sort.begin();
    size_t dist=state.range(0);
    if(dist>vec_sort.size())
        std::terminate();
    auto end = std::next(vec_sort.begin(),dist);
    for (auto _ : state){
        state.PauseTiming(); // Stop timers. They will not count until they are resumed.
        std::shuffle( begin, end, gen );
        state.ResumeTiming();
        std::sort(begin,end);
    }
}
BENCHMARK(BM_Sort)->RangeMultiplier(8)->Range(4, max_sorting_size)->Complexity();
