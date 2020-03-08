/** @file
 *
 * @date 01.03.2020
 * @author domohuhn
 * @copyright This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "gtest/gtest.h"
#include "hashes/perfect_compressed_hash.hpp"
#include <array>
#include <algorithm>

using namespace HASHES_NAMESPACE;

TEST(Compressed_hash,FewNumbers){
    constexpr auto fun =create_perfect_compressed_hash<size_t>([](){return std::array<size_t,5>{14,1,3,0,2};});
    ASSERT_EQ(fun.size(),5);
    ASSERT_EQ(fun.max(),4);
    ASSERT_EQ(fun.division(),1);
    ASSERT_EQ(fun.modulo1(),5);
    ASSERT_EQ(fun.modulo2(),5);
    ASSERT_EQ(fun.density(),1);
    
    ASSERT_EQ(fun(0),0);
    ASSERT_EQ(fun(1),1);
    ASSERT_EQ(fun(2),2);
    ASSERT_EQ(fun(3),3);
    ASSERT_EQ(fun(14),4);

    std::array<size_t,5> arr{14,1,3,0,2};
    auto fun_rt =create_perfect_compressed_hash<size_t>(arr.begin(),arr.end());
    ASSERT_EQ(fun_rt.size(),5);
    ASSERT_EQ(fun_rt.max(),4);
    ASSERT_EQ(fun_rt.division(),1);
    ASSERT_EQ(fun_rt.modulo1(),5);
    ASSERT_EQ(fun_rt.modulo2(),5);
    ASSERT_EQ(fun_rt.density(),1);
    for(auto itr : arr){
        ASSERT_EQ(fun(itr),fun_rt(itr));
    }
}


TEST(Compressed_hash,MoreNumbers){
    constexpr auto lamb = [](){return std::array<size_t,8>{4000424237ULL,1000237ULL,0ULL,1ULL,2ULL,3ULL,14ULL,8004000424232ULL,};};
    constexpr auto fun =create_perfect_compressed_hash<size_t>(lamb);
    ASSERT_LT(fun.size(),16);
    ASSERT_LT(fun.max(),15);
    ASSERT_GT(fun.density(),7.0/15.0);
    ASSERT_EQ(fun.division(),1);
    auto arr = lamb();
    
    std::cout<<"hash.size() = "<<fun.size()<<"\n";
    std::cout<<"hash.division() = "<<fun.division()<<"\n";
    std::cout<<"hash.modulo1() = "<<fun.modulo1()<<"\n";
    std::cout<<"hash.modulo2() = "<<fun.modulo2()<<"\n";
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

    auto fun_rt =create_perfect_compressed_hash<size_t>(arr.begin(),arr.end());

    otr=hashes.begin();
    for(auto itr : arr){
        *otr=fun_rt(itr);
        ++otr;
    }
    std::sort( hashes.begin(), hashes.end() );
    newend=std::unique(hashes.begin(), hashes.end() );
    ASSERT_EQ( hashes.end() ,newend);
}


TEST(Compressed_hash,EvenDistribution){
    /* even distribution from random org */
    constexpr auto lamb = [](){return std::array<size_t,20>{
        9009107ULL, 66953935ULL, 138552752ULL, 157259760ULL,
        164757529ULL, 172519852ULL, 314271695ULL, 394122013ULL,
        465773819ULL, 515399088ULL, 529643005ULL, 582139926ULL,
        592724763ULL, 742685716ULL, 824480906ULL, 828633710ULL,
        841710459ULL, 846727684ULL, 946181757ULL, 953936015ULL};};
    constexpr auto fun =create_perfect_compressed_hash<size_t>(lamb);
    ASSERT_LT(fun.size(),46);
    ASSERT_LT(fun.max(),45);
    ASSERT_GT(fun.density(),19.0/45.0);
    auto arr = lamb();
    
    std::cout<<"hash.size() = "<<fun.size()<<"\n";
    std::cout<<"hash.division() = "<<fun.division()<<"\n";
    std::cout<<"hash.modulo1() = "<<fun.modulo1()<<"\n";
    std::cout<<"hash.modulo2() = "<<fun.modulo2()<<"\n";
    std::cout<<"hash.density() = "<<fun.density()<<"\n";
    std::array<size_t,20> hashes;
    auto otr=hashes.begin();
    for(auto itr : arr){
       // std::cout<<"hash("<<itr<<") = "<<fun(itr)<<"\n";
        *otr=fun(itr);
        ++otr;
    }

    std::sort( hashes.begin(), hashes.end() );
    auto newend=std::unique(hashes.begin(), hashes.end() );
    ASSERT_EQ( hashes.end() ,newend);

    auto fun_rt =create_perfect_compressed_hash<size_t>(arr.begin(),arr.end());

    std::cout<<"RT hash.size() = "<<fun_rt.size()<<"\n";
    std::cout<<"RT hash.division() = "<<fun_rt.division()<<"\n";
    std::cout<<"RT hash.modulo1() = "<<fun_rt.modulo1()<<"\n";
    std::cout<<"RT hash.modulo2() = "<<fun_rt.modulo2()<<"\n";
    std::cout<<"RT hash.density() = "<<fun_rt.density()<<"\n";
    otr=hashes.begin();
    for(auto itr : arr){
        *otr=fun_rt(itr);
        ++otr;
    }
    std::sort( hashes.begin(), hashes.end() );
    newend=std::unique(hashes.begin(), hashes.end() );
    ASSERT_EQ( hashes.end() ,newend);
}