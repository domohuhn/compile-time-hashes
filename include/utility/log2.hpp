/** @file
 *
 * @date 08.03.2020
 * @author domohuhn
 * @copyright This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef LOG2_INCLUDED
#define LOG2_INCLUDED

#include "hashes/config.hpp"

HASHES_NAMESPACE_BEGIN


template<typename UIntegral>
constexpr UIntegral is_power_of_two(UIntegral i) {
    return i & (i-1) == 0;
}

template<typename UIntegral>
constexpr UIntegral log_largest_power_of_two_smaller_than(UIntegral n) 
{ 
    for (UIntegral i=0; i<8*sizeof(UIntegral)-1; ++i) 
    {
        if (UIntegral(1)<<(i+1) > n)
        { 
            return i;
        }
    }
    return 0; 
}


template<typename UIntegral>
constexpr UIntegral log_smallest_power_of_two_larger_than(UIntegral n) 
{ 
    for (UIntegral i=8*sizeof(UIntegral)-1; i>=1; --i) 
    {
        if (UIntegral(1)<<(i-1) < n)
        {
            return i;
        }
    }
    return 1; 
}


HASHES_NAMESPACE_END


#endif /* LOG2_INCLUDED */