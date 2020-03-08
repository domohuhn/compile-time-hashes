/** @file
 *
 * @date 01.03.2020
 * @author domohuhn
 * @copyright This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include <benchmark/benchmark.h>
#include <random>
#include <vector>
#include "hashes/perfect_compressed_hash.hpp"
#include "hashes/fast_perfect_compressed_hash.hpp"

using namespace HASHES_NAMESPACE;
namespace {
    constexpr auto lamb = [](){return std::array<size_t,20>{
        9009107ULL, 66953935ULL, 138552752ULL, 157259760ULL,
        164757529ULL, 172519852ULL, 314271695ULL, 394122013ULL,
        465773819ULL, 515399088ULL, 529643005ULL, 582139926ULL,
        592724763ULL, 742685716ULL, 824480906ULL, 828633710ULL,
        841710459ULL, 846727684ULL, 946181757ULL, 953936015ULL};};
    constexpr auto hash =create_perfect_compressed_hash<size_t>(lamb);
    constexpr auto fast_hash =create_fast_perfect_compressed_hash<size_t>(lamb);
}

volatile size_t result=0;

void BM_baseline_compressed_hash(benchmark::State& state) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<size_t> dis(0, 953936015ULL);
    std::vector<size_t> vec;
    vec.reserve(1024);
    constexpr size_t max=8*1024;
    for(size_t i=0;i<max;++i){
        vec.emplace_back(dis(gen));
    }
    size_t i=0;
    for (auto _ : state){
        result+=vec[i];
        ++i;
        i=i&(max-1);
    }
}
BENCHMARK(BM_baseline_compressed_hash);

void BM_Fast_compressed_hash(benchmark::State& state) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<size_t> dis(0, 953936015ULL);
    std::vector<size_t> vec;
    vec.reserve(1024);
    constexpr size_t max=8*1024;
    for(size_t i=0;i<max;++i){
        vec.emplace_back(dis(gen));
    }
    size_t i=0;
    for (auto _ : state){
        result-=fast_hash(vec[i]);
        ++i;
        i=i&(max-1);
    }
}
BENCHMARK(BM_Fast_compressed_hash);


void BM_Compressed_hash(benchmark::State& state) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<size_t> dis(0, 953936015ULL);
    std::vector<size_t> vec;
    vec.reserve(1024);
    constexpr size_t max=8*1024;
    for(size_t i=0;i<max;++i){
        vec.emplace_back(dis(gen));
    }
    size_t i=0;
    for (auto _ : state){
        result-=hash(vec[i]);
        ++i;
        i=i&(max-1);
    }
}
BENCHMARK(BM_Compressed_hash);

