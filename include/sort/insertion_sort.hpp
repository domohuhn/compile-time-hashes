/** @file
 *
 * @date 08.03.2020
 * @author domohuhn
 * @copyright This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef INSERTION_SORT_INCLUDED
#define INSERTION_SORT_INCLUDED


#include "hashes/config.hpp"
#include "hashes/swap.hpp"

HASHES_NAMESPACE_BEGIN

template<typename Iterator>
constexpr void insertion_sort(Iterator begin, Iterator end)
{
    if(begin==end)
        return;
    const auto begin_copy = begin;
    std::advance(begin,1);
    while(begin!=end){
        auto itr=begin;
        auto itr2=std::next(begin,-1);
        while(itr!=begin_copy && *itr<*itr2){
            swap(*itr,*itr2);
            std::advance(itr,-1);
            std::advance(itr2,-1);
        }
        std::advance(begin,1);
    }
}

template<typename Range>
constexpr auto insertion_sort(Range&& range)
{
    insertion_sort(std::begin(range),std::end(range));
    return range;
}

HASHES_NAMESPACE_END

#endif /* INSERTION_SORT_INCLUDED */