/** @file
 *
 * @date 01.03.2020
 * @author domohuhn
 * @copyright This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "gtest/gtest.h"
#include "hashes/murmur2.hpp"

using namespace HASHES_NAMESPACE;

TEST(Murmur2,A32Bit){
    constexpr auto hash1 = Murmur2_32::hash("test_string");
    EXPECT_EQ(hash1,1127032369);
    
    
    constexpr auto hash2 = Murmur2_32::hash("test_string2");
    ASSERT_EQ(hash2,3707599750);

    constexpr auto hash3 = Murmur2_32::hash("another");
    ASSERT_EQ(hash3,2740398393);
    
    constexpr auto hash4 = Murmur2_32::hash(nullptr);
    ASSERT_EQ(hash4,2056242848);
}

TEST(Murmur2,64A){
    constexpr auto hash1 = Murmur2_64::hash("test_string");
    ASSERT_EQ(hash1,10539208293966230372ULL);
    
    constexpr auto hash2 = Murmur2_64::hash("test_string2");
    ASSERT_EQ(hash2,3421406597264743844ULL);

    constexpr auto hash3 = Murmur2_64::hash("another");
    ASSERT_EQ(hash3,10438627398352920670ULL);
    
    constexpr auto hash4 = Murmur2_64::hash(nullptr);
    ASSERT_EQ(hash4,353297822103685302ULL);
}
