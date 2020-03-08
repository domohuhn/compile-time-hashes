/** @file
 *
 * @date 01.03.2020
 * @author domohuhn
 * @copyright This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "gtest/gtest.h"
#include "hashes/fast_perfect_compressed_hash.hpp"
#include <array>
#include <algorithm>

using namespace HASHES_NAMESPACE;

TEST(Fast_compressed_hash,FewNumbers){
    constexpr auto fun =create_fast_perfect_compressed_hash<size_t>([](){return std::array<size_t,5>{14,1,3,0,2};});
    ASSERT_EQ(fun.size(),8);
    ASSERT_EQ(fun.max(),7);
    ASSERT_EQ(fun.modulo(),8);
    ASSERT_EQ(fun.division(),1);
    ASSERT_EQ(fun.density(),5.0/8.0);
    
    ASSERT_EQ(fun(0),0);
    ASSERT_EQ(fun(1),1);
    ASSERT_EQ(fun(2),2);
    ASSERT_EQ(fun(3),3);
    ASSERT_EQ(fun(14),6);
}


TEST(Fast_compressed_hash,MoreNumbers){
    constexpr auto lamb = [](){return std::array<size_t,8>{4000424237ULL,1000237ULL,0ULL,1ULL,2ULL,3ULL,14ULL,8004000424232ULL,};};
    constexpr auto fun =create_fast_perfect_compressed_hash<size_t>(lamb);
    ASSERT_EQ(fun.division(),1);
    ASSERT_LT(fun.size(),1025);
    ASSERT_LT(fun.max(),1024);
    ASSERT_GT(fun.density(),7.0/1024.0);
    auto arr = lamb();
    
    std::cout<<"hash.size() = "<<fun.size()<<"\n";
    std::cout<<"hash.division() = "<<fun.division()<<"\n";
    std::cout<<"hash.modulo() = "<<fun.modulo()<<"\n";
    std::cout<<"hash.density() = "<<fun.density()<<"\n";
    std::array<size_t,8> hashes;
    auto otr=hashes.begin();
    for(auto itr : arr){
        std::cout<<"hash("<<itr<<") = "<<fun(itr)<<"\n";
        *otr=fun(itr);
        ++otr;
    }

    std::sort( hashes.begin(), hashes.end() );
    auto newend=std::unique(hashes.begin(), hashes.end() );
    ASSERT_EQ( hashes.end() ,newend);
}


TEST(Fast_compressed_hash,EvenDistribution){
    /* even distribution from random org */
    constexpr auto lamb = [](){return std::array<size_t,20>{
        9009107ULL, 66953935ULL, 138552752ULL, 157259760ULL,
        164757529ULL, 172519852ULL, 314271695ULL, 394122013ULL,
        465773819ULL, 515399088ULL, 529643005ULL, 582139926ULL,
        592724763ULL, 742685716ULL, 824480906ULL, 828633710ULL,
        841710459ULL, 846727684ULL, 946181757ULL, 953936015ULL};};
    constexpr auto fun =create_fast_perfect_compressed_hash<size_t>(lamb);
    ASSERT_LT(fun.size(),257);
    ASSERT_LT(fun.max(),256);
    ASSERT_GT(fun.density(),19.0/256.0);
    auto arr = lamb();
    
    std::cout<<"hash.size() = "<<fun.size()<<"\n";
    std::cout<<"hash.division() = "<<fun.division()<<"\n";
    std::cout<<"hash.modulo1() = "<<fun.modulo()<<"\n";
    std::cout<<"hash.density() = "<<fun.density()<<"\n";
    std::array<size_t,20> hashes;
    auto otr=hashes.begin();
    for(auto itr : arr){
        std::cout<<"hash("<<itr<<") = "<<fun(itr)<<"\n";
        *otr=fun(itr);
        ++otr;
    }

    std::sort( hashes.begin(), hashes.end() );
    auto newend=std::unique(hashes.begin(), hashes.end() );
    ASSERT_EQ( hashes.end() ,newend);
}
