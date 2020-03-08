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
#include <limits>
#include "hashes/perfect_compressed_hash.hpp"
#include "hashes/fast_perfect_compressed_hash.hpp"

extern volatile size_t result;

static std::vector<size_t> vec{};

bool init_data()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<size_t> dis(0, std::numeric_limits<size_t>::max());
    size_t generate_numbers=64*2048*2; // generating twice as needed so that possible collisions are handled.
    vec.reserve(generate_numbers);
    for(size_t i=0;i<generate_numbers;++i){
        vec.push_back(dis(gen));
    }
    std::sort(vec.begin(),vec.end());
    vec.erase( std::unique( vec.begin(), vec.end() ), vec.end() );
    std::shuffle( vec.begin(), vec.end(), gen );
}

static bool is_init = init_data();

void BM_Create_fast_perfect_hash(benchmark::State& state) {
    auto begin = vec.begin();
    size_t dist=state.range(0);
    if(dist>=vec.size())
        std::terminate();
    auto end = std::next(vec.begin(),dist);
    size_t i=0;
    constexpr size_t max=64*2048;
    for (auto _ : state){
        auto fast_hash= hashes::create_fast_perfect_compressed_hash<size_t>(begin,end);
        result-=fast_hash(vec[i]);
        ++i;
        i=i&(max-1);
        ++begin;
        ++end;
        if(end==vec.end()){
            begin = vec.begin();
            end = std::next(vec.begin(),dist);
        }
    }
}
BENCHMARK(BM_Create_fast_perfect_hash)->RangeMultiplier(2)->Range(4, 8*2048)->Complexity();


void BM_Create_perfect_hash(benchmark::State& state) {
    auto begin = vec.begin();
    size_t dist=state.range(0);
    if(dist>=vec.size())
        std::terminate();
    auto end = std::next(vec.begin(),dist);
    size_t i=0;
    constexpr size_t max=64*2048;
    for (auto _ : state){
        auto hash= hashes::create_perfect_compressed_hash<size_t>(begin,end);
        result-=hash(vec[i]);
        ++i;
        i=i&(max-1);
        ++begin;
        ++end;
        if(end==vec.end()){
            begin = vec.begin();
            end = std::next(vec.begin(),dist);
        }
    }
}
BENCHMARK(BM_Create_perfect_hash)->RangeMultiplier(2)->Range(4, 1024)->Complexity();

