/** @file
 *
 * @date 01.03.2020
 * @author domohuhn
 * @copyright This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "gtest/gtest.h"
#include "hashes/hashed_string.hpp"
#include "hashes/fnv1a.hpp"

using namespace HASHES_NAMESPACE;


TEST(HashedStringView,FNV1A_32){
    using HString = HashedStringView<uint32_t,FNV1A_32>;
    constexpr auto s1 = HString("test_string");
    ASSERT_EQ(s1.hash(),0x8162e7ff);
    ASSERT_EQ(s1.string_view(),"test_string");
    
    constexpr auto s2 = HString("test_string2");
    ASSERT_EQ(s2.hash(),0x7bb2e7b7);
    ASSERT_EQ(s2.string_view(),"test_string2");

    constexpr auto s3 = HString("another");
    ASSERT_EQ(s3.hash(),0x23176214);
    ASSERT_EQ(s3.string_view(),"another");
    
    constexpr auto s4 = HString(nullptr);
    ASSERT_EQ(s4.hash(),2166136261U);
    ASSERT_EQ(s4.string_view(),"");

    
    constexpr auto s5 = HString("test_string");
    constexpr auto s6{s5};

    ASSERT_EQ(s1,s1);
    ASSERT_NE(s1,s2);
    ASSERT_NE(s1,s3);
    ASSERT_NE(s1,s4);
    ASSERT_EQ(s1,s5);
    ASSERT_EQ(s1,s6);
    ASSERT_EQ(s5,s6);

    std::cout<<sizeof(HString)<<"\n";
}

TEST(HashedString,FNV1A_64){
    using HString = HashedStringView<uint64_t,FNV1A_64>;
    constexpr auto s1 = HString("test_string");
    ASSERT_EQ(s1.hash(),0xa74a9df432a5ae3fULL);
    ASSERT_EQ(s1.string_view(),"test_string");
    
    constexpr auto s2 = HString("test_string2");
    ASSERT_EQ(s2.hash(),0xe97872f20f86c017ULL);
    ASSERT_EQ(s2.string_view(),"test_string2");

    constexpr auto s3 = HString("another");
    ASSERT_EQ(s3.hash(),0xb08377e5e235fd94ULL);
    ASSERT_EQ(s3.string_view(),"another");
    
    constexpr auto s4 = HString(nullptr);
    ASSERT_EQ(s4.hash(),14695981039346656037ULL);
    ASSERT_EQ(s4.string_view(),"");

    
    constexpr auto s5 = HString("test_string");
    constexpr auto s6{s5};

    ASSERT_EQ(s1,s1);
    ASSERT_NE(s1,s2);
    ASSERT_NE(s1,s3);
    ASSERT_NE(s1,s4);
    ASSERT_EQ(s1,s5);
    ASSERT_EQ(s1,s6);
    ASSERT_EQ(s5,s6);

    std::cout<<sizeof(HString)<<"\n";
}