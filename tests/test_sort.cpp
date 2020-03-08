/** @file
 *
 * @date 08.03.2020
 * @author domohuhn
 * @copyright This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "gtest/gtest.h"
#include "sort/insertion_sort.hpp"
#include "sort/radix_sort.hpp"
#include <array>

using namespace HASHES_NAMESPACE;

constexpr bool test_sorted_array_insertion_sort(){
    auto sorted_arr=insertion_sort(std::array<uint64_t,10>{0,1,2,3,4,5,6,7,8,9});
    bool rv = true;
    for(size_t i=0;i<10;++i){
        if(i!=sorted_arr[i])
            rv=false;
    }
    return rv;
}

constexpr bool test_reversed_array_insertion_sort(){
    auto sorted_arr=insertion_sort(std::array<uint64_t,10>{9,8,7,6,5,4,3,2,1,0});
    bool rv = true;
    for(size_t i=0;i<10;++i){
        if(i!=sorted_arr[i])
            rv=false;
    }
    return rv;
}

constexpr bool test_random_array_insertion_sort(){
    auto sorted_arr=insertion_sort(std::array<uint64_t,10>{5,3,9,2,0,7,1,6,4,8});
    bool rv = true;
    for(size_t i=0;i<10;++i){
        if(i!=sorted_arr[i])
            rv=false;
    }
    return rv;
}

constexpr bool test_sorted_array_radix_sort(){
    auto sorted_arr=radix_sort(std::array<uint64_t,100>{0,1,2,3,4,5,6,7,8,9,
    10,11,12,13,14,15,16,17,18,19,
    20,21,22,23,24,25,26,27,28,29,
    30,31,32,33,34,35,36,37,38,39,
    40,41,42,43,44,45,46,47,48,49,    
    50,51,52,53,54,55,56,57,58,59,
    60,61,62,63,64,65,66,67,68,69,
    70,71,72,73,74,75,76,77,78,79,
    80,81,82,83,84,85,86,87,88,89,
    90,91,92,93,94,95,96,97,98,99
    });
    bool rv = true;
    for(size_t i=0;i<10;++i){
        if(i!=sorted_arr[i])
            rv=false;
    }
    return rv;
}

constexpr bool test_reversed_array_radix_sort(){
    auto sorted_arr=radix_sort(std::array<uint64_t,100>{
        90,91,92,93,94,95,96,97,98,99,
        80,81,82,83,84,85,86,87,88,89,
        70,71,72,73,74,75,76,77,78,79,
        60,61,62,63,64,65,66,67,68,69, 
        50,51,52,53,54,55,56,57,58,59,
        40,41,42,43,44,45,46,47,48,49, 
        30,31,32,33,34,35,36,37,38,39,
        20,21,22,23,24,25,26,27,28,29,
        10,11,12,13,14,15,16,17,18,19,
        9,8,7,6,5,4,3,2,1,0});
    bool rv = true;
    for(size_t i=0;i<10;++i){
        if(i!=sorted_arr[i])
            rv=false;
    }
    return rv;
}

constexpr bool test_random_array_radix_sort(){
    auto sorted_arr=radix_sort(std::array<uint64_t,100>{
    20,28,29,24,25,61,62,63,21,27,
    10,18,19,14,15,81,82,83,11,17,
    90,98,99,94,95,31,32,33,91,97,
    50,58,59,54,55,41,42,43,51,57,  
    70,78,79,74,75,71,72,73,76,77,
    60,68,69,64,65,66,67,22,23,26,
    80,88,89,84,85,86,87,12,13,16,
    30,38,39,34,35,36,37,92,93,96,
    40,48,49,44,45,46,47,52,53,56,  
    0,1,6,7,8,2,3,4,5,9
    });
    bool rv = true;
    for(size_t i=0;i<10;++i){
        if(i!=sorted_arr[i]){
            rv=false;
        }
    }
    return rv;
}

TEST(Sort,Insertionsort){
    constexpr bool test1 = test_sorted_array_insertion_sort();
    ASSERT_TRUE(test1);

    constexpr bool test2 = test_reversed_array_insertion_sort();
    ASSERT_TRUE(test2);

    constexpr bool test3 = test_random_array_insertion_sort();
    ASSERT_TRUE(test3);

}

TEST(Sort,Radixsort){
    constexpr bool test1 = test_sorted_array_radix_sort();
    ASSERT_TRUE(test1);

    constexpr bool test2 = test_reversed_array_radix_sort();
    ASSERT_TRUE(test2);

    constexpr bool test3 = test_random_array_radix_sort();
    ASSERT_TRUE(test3);

}