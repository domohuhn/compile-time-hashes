/** @file
 *
 * @date 08.03.2020
 * @author domohuhn
 * @copyright This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef RADIX_SORT_INCLUDED
#define RADIX_SORT_INCLUDED


#include "hashes/config.hpp"
#include "sort/insertion_sort.hpp"

HASHES_NAMESPACE_BEGIN

template<typename Iterator>
constexpr void radix_sort_impl(Iterator begin, Iterator end, size_t bit)
{
    using value_type = typename std::decay<decltype(*begin)>::type;
    constexpr auto max_bit = sizeof(value_type)*8;
    if (bit+1>max_bit)
        return;
    auto front=begin;
    auto back=end;
    const value_type mask = static_cast<value_type>(1)<<(max_bit-bit-1);
    while(front!=back){
        if(((*front)&mask)==0){
            std::advance(front,1);
        }
        else{
            std::advance(back,-1);
            swap(*front,*back);
        }
    }
    if(std::distance(begin,front)>64)
        radix_sort_impl(begin,front,bit+1);
    else
        insertion_sort(begin,front);
    if(std::distance(back,end)>64)
        radix_sort_impl(back,end,bit+1);
    else
        insertion_sort(back,end);
}

template<typename Iterator>
constexpr void radix_sort(Iterator begin, Iterator end)
{
    radix_sort_impl(begin,end,0);
}

template<typename Range>
constexpr auto radix_sort(Range&& range)
{
    radix_sort_impl(std::begin(range),std::end(range),0);
    return range;
}

HASHES_NAMESPACE_END

#endif /* RADIX_SORT_INCLUDED */