/** @file
 *
 * @date 08.03.2020
 * @author domohuhn
 * @copyright This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef SMALLEST_DIFFERENCE_INCLUDED
#define SMALLEST_DIFFERENCE_INCLUDED

#include "hashes/config.hpp"

HASHES_NAMESPACE_BEGIN


template<typename UIntegral,typename Iterator>
constexpr UIntegral find_smallest_difference_sorted (Iterator begin,Iterator end) 
{
    UIntegral rv=std::numeric_limits<UIntegral>::max();
    if(begin==end)
        return rv;

    auto next = std::next(begin);
    while(next!=end){
        if(*next-*begin<rv){
            rv =  *next-*begin;
        }
        ++next;
        ++begin;
    }
    return rv;
}

template<typename UIntegral,typename Iterator>
constexpr UIntegral find_smallest_difference_unsorted (Iterator begin,Iterator end) 
{
    UIntegral rv=std::numeric_limits<UIntegral>::max();
    while(begin!=end){
        auto next = std::next(begin);
        while(next!=end){
            if(*begin< *next){
                rv =  rv>*next-*begin ? *next-*begin : rv;
            }
            else{
                rv =  rv>*begin-*next ? *begin-*next : rv;
            }
            ++next;
        }
        ++begin;
    }
    return rv;
}


HASHES_NAMESPACE_END


#endif /* SMALLEST_DIFFERENCE_INCLUDED */