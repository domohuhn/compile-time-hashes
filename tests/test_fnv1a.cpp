/** @file
 *
 * @date 01.03.2020
 * @author domohuhn
 * @copyright This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "gtest/gtest.h"
#include "hashes/fnv1a.hpp"

using namespace HASHES_NAMESPACE;

TEST(FNV1A,32Bit){
    constexpr auto hash1 = FNV1A_32::hash("test_string");
    ASSERT_EQ(hash1,0x8162e7ff);
    
    constexpr auto hash2 = FNV1A_32::hash("test_string2");
    ASSERT_EQ(hash2,0x7bb2e7b7);

    constexpr auto hash3 = FNV1A_32::hash("another");
    ASSERT_EQ(hash3,0x23176214);
    
    
    constexpr auto hash4 = FNV1A_32::hash(nullptr);
    ASSERT_EQ(hash4,2166136261U);
}

TEST(FNV1A,64Bit){
    constexpr auto hash1 = FNV1A_64::hash("test_string");
    ASSERT_EQ(hash1,0xa74a9df432a5ae3fULL);
    
    constexpr auto hash2 = FNV1A_64::hash("test_string2");
    ASSERT_EQ(hash2,0xe97872f20f86c017ULL);

    constexpr auto hash3 = FNV1A_64::hash("another");
    ASSERT_EQ(hash3,0xb08377e5e235fd94ULL);
    
    constexpr auto hash4 = FNV1A_64::hash(nullptr);
    ASSERT_EQ(hash4,14695981039346656037ULL);
}
