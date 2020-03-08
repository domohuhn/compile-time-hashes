/** @file
 *
 * @date 08.03.2020
 * @author domohuhn
 * @copyright This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef IS_UNIQUE_INCLUDED
#define IS_UNIQUE_INCLUDED

#include "hashes/config.hpp"

HASHES_NAMESPACE_BEGIN


template<typename Iterator,typename BinaryPred>
constexpr bool is_unique_sorted (Iterator begin,Iterator end,BinaryPred op) 
{
    if(begin==end)
        return true;
    auto current = std::next(begin);
    while(current!=end){
        if(op(*current,*begin)){
                return false;
        }
        ++current;
        ++begin;
    }
    return true;
}

template<typename Iterator,typename BinaryPred>
constexpr bool is_unique_unsorted (Iterator begin,Iterator end,BinaryPred op) 
{
    if(begin==end)
        return true;
    auto current = std::next(begin);
    while(current!=end){
        auto compare = begin;
        while(compare!=end){
            if(current!=compare&&op(*current,*compare)){
                return false;
            }
            ++compare;
        }
        ++current;
    }
    return true;
}

HASHES_NAMESPACE_END


#endif /* IS_UNIQUE_INCLUDED */