/** @file
 *
 * @date 01.03.2020
 * @author domohuhn
 * @copyright This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef FAST_PERFECT_COMPRESSED_HASH_INCLUDED
#define FAST_PERFECT_COMPRESSED_HASH_INCLUDED

#include "hashes/config.hpp"
#include "hashes/perfect_compressed_hash.hpp"

HASHES_NAMESPACE_BEGIN

template<typename UIntegral>
class FastCompressedHash {
public:
    constexpr FastCompressedHash(UIntegral div, UIntegral mod, UIntegral size) noexcept : m_division{div}, m_modulo{mod}, m_size{size} {};
    FastCompressedHash()=delete;
    ~FastCompressedHash()=default;
    FastCompressedHash(const FastCompressedHash&)=default;
    FastCompressedHash(FastCompressedHash&&)=default;
    FastCompressedHash& operator=(const FastCompressedHash&)=default;
    FastCompressedHash& operator=(FastCompressedHash&&)=default;

    constexpr UIntegral operator()(UIntegral in) const noexcept
    {
        return (in>>m_division)&m_modulo;
    }

    constexpr UIntegral max() const noexcept
    {
        return m_modulo;
    }

    constexpr UIntegral size() const noexcept
    {
        return m_modulo+1;
    }

    
    constexpr UIntegral modulo() const noexcept
    {
        return m_modulo+1;
    }

    constexpr UIntegral division() const noexcept
    {
        return UIntegral(1)<<m_division;
    }

    
    constexpr double density() const noexcept
    {
        return static_cast<double>(m_size)/static_cast<double>(m_modulo+1);
    }

private:
    UIntegral m_division{1};
    UIntegral m_modulo{1};
    UIntegral m_size{1};
};


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
constexpr FastCompressedHash<UIntegral> create_fast_perfect_compressed_hash(Iterator begin, Iterator end) 
{
    constexpr auto comp = [](UIntegral lhs,UIntegral rhs){return lhs==rhs;};

    if(!is_unique_unsorted(begin,end,comp)) // O(n2)
        throw std::runtime_error("You have to give a list of unique numbers to create_compressed_hash()");

    UIntegral division_value = find_smallest_difference_unsorted<UIntegral> (begin,end); // O(n2)
    UIntegral fast_division_value = log_largest_power_of_two_smaller_than(division_value); // const
    UIntegral modulo = find_modulo_pow2<UIntegral>(begin,end,[fast_division_value](UIntegral l){return l>>fast_division_value;}); // O(k*n2)
    // benchmark gives O(n2)
    // changes: sort vector to get O(nlog(n)),O(n),O(n)
    // create copy in find modulo, assign value, sort, unique -> (O(n),  O(nlog(n)), O(n))*O(1)
    return FastCompressedHash<UIntegral>{fast_division_value,modulo-1,static_cast<UIntegral>(std::distance(begin,end))};
}

template<typename UIntegral, typename X> 
constexpr FastCompressedHash<UIntegral> create_fast_perfect_compressed_hash(X arg) 
{
    constexpr auto arr= arg();
    constexpr auto comp = [](UIntegral lhs,UIntegral rhs){return lhs==rhs;};
    static_assert(is_unique_unsorted(arr.begin(),arr.end(),comp),"You have to give a list of unique numbers to create_compressed_hash()");

    constexpr UIntegral division_value = find_smallest_difference_unsorted<UIntegral> (arr.begin(),arr.end());
    constexpr UIntegral fast_division_value = log_largest_power_of_two_smaller_than(division_value);
    constexpr UIntegral modulo = find_modulo_pow2<UIntegral>(arr.begin(),arr.end(),[fast_division_value](UIntegral l){return l>>fast_division_value;});
    return FastCompressedHash<UIntegral>{fast_division_value,modulo-1,arr.size()};
}

HASHES_NAMESPACE_END



#endif /* FAST_PERFECT_COMPRESSED_HASH_INCLUDED */