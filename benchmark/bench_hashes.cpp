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
#include <string>
#include "hashes/murmur2.hpp"
#include "hashes/fnv1a.hpp"

using namespace HASHES_NAMESPACE;

extern volatile size_t result;

static size_t current_stringlen=0;
static std::vector<std::string> data;
const size_t num_strings=131072;

void init_strings(size_t string_len)
{
    if(current_stringlen==string_len)
        return;
    data.clear();
    data.resize(num_strings);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<char> dis(1, 255);

    for(size_t i=0;i<num_strings;++i){
       data[i].resize(string_len);
        for(size_t k=0;k<string_len;++k){
            data[i][k]=dis(gen);
        }
    }
    current_stringlen=string_len;
}

void Murmur2A_32(benchmark::State& state) {
    auto len=state.range(0);
    init_strings(len);
    size_t i=0;
    for (auto _ : state){
        result+=Murmur2_32::hash(data[i]);
        ++i;
        i=i&(num_strings-1);
    }
}
BENCHMARK(Murmur2A_32)->RangeMultiplier(2)->Range(4, 2048)->Complexity();



void Murmur2_64A(benchmark::State& state) {
    auto len=state.range(0);
    init_strings(len);
    size_t i=0;
    for (auto _ : state){
        result+=Murmur2_64::hash(data[i]);
        ++i;
        i=i&(num_strings-1);
    }
}
BENCHMARK(Murmur2_64A)->RangeMultiplier(2)->Range(4, 2048)->Complexity();


void B_FNV1A_32(benchmark::State& state) {
    auto len=state.range(0);
    init_strings(len);
    size_t i=0;
    for (auto _ : state){
        result+=FNV1A_32::hash(data[i]);
        ++i;
        i=i&(num_strings-1);
    }
}
BENCHMARK(B_FNV1A_32)->RangeMultiplier(2)->Range(4, 2048)->Complexity();



void B_FNV1A_64(benchmark::State& state) {
    auto len=state.range(0);
    init_strings(len);
    size_t i=0;
    for (auto _ : state){
        result+=FNV1A_64::hash(data[i]);
        ++i;
        i=i&(num_strings-1);
    }
}
BENCHMARK(B_FNV1A_64)->RangeMultiplier(2)->Range(4, 2048)->Complexity();
