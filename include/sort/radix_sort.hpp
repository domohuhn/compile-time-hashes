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
#include <iostream>
#include <bitset>

HASHES_NAMESPACE_BEGIN

struct RadixTraits2 {
static constexpr size_t insertion_sort_limit = 64;
static constexpr size_t bits_per_pass = 2;
};

struct RadixTraits4 {
static constexpr size_t insertion_sort_limit = 64;
static constexpr size_t bits_per_pass = 4;
};

struct RadixTraits8 {
static constexpr size_t insertion_sort_limit = 64;
static constexpr size_t bits_per_pass = 8;
};

template<typename UIntegral>
constexpr inline size_t apply_mask(UIntegral value, UIntegral mask, size_t shift) noexcept
{
    return (value&mask)>>shift;
}

template<size_t buckets,typename Iterator, typename UIntegral>
constexpr inline std::array<size_t , buckets> count_entries_in_buckets(Iterator begin, Iterator end, UIntegral mask, size_t shift) noexcept
{
    std::array<size_t , buckets> counts{};
    while(begin!=end){
        const size_t index=apply_mask(*begin++,mask,shift);
        ++counts[index];
    }
    return counts;
}

template<size_t buckets,typename Iterator, typename Iterator2>
constexpr inline std::array<Iterator , buckets> find_bucket_positions(Iterator begin, Iterator end, Iterator2 count_begin) noexcept
{
    std::array<Iterator , buckets> rv{};
    auto oitr = rv.begin();
    auto oitr_end = rv.end();
    size_t running_sum=0;
    while(oitr!=oitr_end){
        *oitr=std::next(begin,running_sum);
        running_sum+=*count_begin;
        ++count_begin;
        ++oitr;
    }
    return rv;
}

template<typename Iterator, class RadixTraits>
constexpr void radix_sort_impl(Iterator begin, Iterator end, size_t pass)
{
    // doing a "simple" radix sort will require x recusrions for a n bit value
    // this is only as fast as std::sort
    // we need to do multiple bits in a single pass to beat std::sort!
    // do one byte at a time for smaller sorts (smaller than 200'000'000 elements).
    // for larger arrays, using only 4 bits speeds up the sort.
    constexpr size_t bits_in_one_pass = RadixTraits::bits_per_pass;
    constexpr size_t number_of_buckets = size_t(1)<<bits_in_one_pass;
    using value_type = typename std::decay<decltype(*begin)>::type;
    constexpr size_t max_passes = sizeof(value_type)*CHAR_BIT/bits_in_one_pass;
    if (pass+1>max_passes)
        return;
        
    if (begin==end)
        return;

    const size_t shift = (max_passes-1-pass)*bits_in_one_pass;
    const value_type mask = static_cast<value_type>(number_of_buckets-1)<<shift;

    auto counts = count_entries_in_buckets<number_of_buckets>(begin,end,mask,shift);
    auto bucket_positions = find_bucket_positions<number_of_buckets>(begin,end,counts.begin());

    for(size_t i=0;i<bucket_positions.size();++i){
        auto bucket_begin=bucket_positions[i];

        while(counts[i]!=0){
            const auto to_bucket = apply_mask(*bucket_begin,mask,shift);
            swap(*bucket_begin,*bucket_positions[to_bucket]);
            ++bucket_positions[to_bucket];
            --counts[to_bucket];
            bucket_begin+=(to_bucket==i);
        }
    }

    auto istart = begin;
    auto iend = bucket_positions[0];
    const bool recurse = ((pass+1)<(max_passes));
    if(recurse){
        for(size_t i=1;i<bucket_positions.size();++i){
            auto dist = std::distance(istart,iend);
            if(dist>RadixTraits::insertion_sort_limit){
                radix_sort_impl<Iterator,RadixTraits>(istart,iend,pass+1);
            }
            else if(dist>1){
                insertion_sort(istart,iend);
            }
            istart=iend;
            iend=bucket_positions[i];
        }
    }
}

template<typename Iterator, class RadixTraits=RadixTraits8>
constexpr void radix_sort(Iterator begin, Iterator end)
{
    const auto size = std::distance(begin,end);
    if(size>RadixTraits::insertion_sort_limit)
        radix_sort_impl<Iterator,RadixTraits>(begin,end,0);
    else
        insertion_sort(begin,end);
}

template<typename Range, class RadixTraits=RadixTraits8>
constexpr auto radix_sort(Range&& range)
{
    using Iterator=decltype(std::begin(range));
    if(range.size()>RadixTraits::insertion_sort_limit)
        radix_sort_impl<Iterator,RadixTraits>(std::begin(range),std::end(range),0);
    else
        insertion_sort(std::begin(range),std::end(range));
    return range;
}

HASHES_NAMESPACE_END

#endif /* RADIX_SORT_INCLUDED */