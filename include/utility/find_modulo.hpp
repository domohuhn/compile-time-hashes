/** @file
 *
 * @date 08.03.2020
 * @author domohuhn
 * @copyright This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef FIND_MODULO_INCLUDED
#define FIND_MODULO_INCLUDED

#include "hashes/config.hpp"
#include "sort/radix_sort.hpp"
#include "utility/is_unique.hpp"
#include "utility/log2.hpp"
#include <vector>

HASHES_NAMESPACE_BEGIN

template<typename UIntegral, typename Iterator>
constexpr UIntegral find_modulo_pow2_sorted(Iterator begin,Iterator end,size_t bitshift) 
{
    UIntegral log_modulo = log_smallest_power_of_two_larger_than(std::distance(begin,end));
    size_t distance = std::distance(begin,end);
    std::vector<UIntegral> vec(distance,0);
    while(true){
        auto mod = UIntegral(1)<<log_modulo;
        auto mask = mod-1;
        std::transform( begin,end, vec.begin(),
                    [bitshift,mask](UIntegral l){return ((l>>bitshift)&mask);} );
        radix_sort(vec.begin(),vec.end());
        if(is_unique_sorted(vec.begin(),vec.end(),[](UIntegral l,UIntegral r){return l==r;}))
            return mod;
        else
            ++log_modulo;
    }
}

template<typename UIntegral, typename Iterator,typename UnaryPred>
constexpr UIntegral find_modulo_pow2(Iterator begin,Iterator end,UnaryPred op) 
{
    UIntegral log_modulo = log_smallest_power_of_two_larger_than(std::distance(begin,end));
    while(true){
        auto mod = UIntegral(1)<<log_modulo;
        if(is_unique_unsorted(begin,end,[mod,op](UIntegral l,UIntegral r){return op(l)%mod==op(r)%mod;}))
            return mod;
        else
            ++log_modulo;
    }
}


template<typename UIntegral, typename Iterator>
constexpr UIntegral find_modulo_sorted(Iterator begin,Iterator end,size_t division) 
{
    UIntegral modulo = std::distance(begin,end);
    size_t distance = std::distance(begin,end);
    std::vector<UIntegral> vec(distance,0);
    while(true){
        std::transform( begin,end, vec.begin(),
                    [division,modulo](UIntegral l){return ((l/division)%modulo);} );
        radix_sort(vec.begin(),vec.end());
        if(is_unique_sorted(vec.begin(),vec.end(),[](UIntegral l,UIntegral r){return l==r;}))
            return modulo;
        else
            ++modulo;
    }
}

template<typename UIntegral, typename Iterator,typename UnaryPred>
constexpr UIntegral find_modulo(Iterator begin,Iterator end,UnaryPred op) 
{
    UIntegral modulo = std::distance(begin,end);
    while(true){
        if(is_unique_unsorted(begin,end,[modulo,op](UIntegral l,UIntegral r){return op(l)%modulo==op(r)%modulo;}))
            return modulo;
        else
            ++modulo;
    }
}

HASHES_NAMESPACE_END

#endif /* FIND_MODULO_INCLUDED */