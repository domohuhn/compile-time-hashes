/** @file
 *
 * @date 01.03.2020
 * @author domohuhn
 * @copyright This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef PERFECT_COMPRESSED_HASH_INCLUDED
#define PERFECT_COMPRESSED_HASH_INCLUDED

#include "hashes/config.hpp"
#include "utility/is_unique.hpp"
#include "utility/smallest_difference.hpp"
#include "utility/find_modulo.hpp"
#include "sort/radix_sort.hpp"

HASHES_NAMESPACE_BEGIN

template<typename UIntegral>
class CompressedHash {
public:
    constexpr CompressedHash(UIntegral div, UIntegral mod, UIntegral mod2,UIntegral size) noexcept : m_division{div}, m_modulo{mod}, m_modulo2{mod2}, m_size{size} {};
    CompressedHash()=delete;
    ~CompressedHash()=default;
    CompressedHash(const CompressedHash&)=default;
    CompressedHash(CompressedHash&&)=default;
    CompressedHash& operator=(const CompressedHash&)=default;
    CompressedHash& operator=(CompressedHash&&)=default;

    constexpr UIntegral operator()(UIntegral in) const noexcept
    {
        return (in/m_division)%m_modulo%m_modulo2;
    }

    constexpr UIntegral max() const noexcept
    {
        return m_modulo2-1;
    }

    constexpr UIntegral size() const noexcept
    {
        return m_modulo2;
    }

    
    constexpr UIntegral modulo1() const noexcept
    {
        return m_modulo;
    }

    constexpr UIntegral modulo2() const noexcept
    {
        return m_modulo2;
    }

    constexpr UIntegral division() const noexcept
    {
        return m_division;
    }

    
    constexpr double density() const noexcept
    {
        return static_cast<double>(m_size)/static_cast<double>(m_modulo2);
    }

private:
    UIntegral m_division{1};
    UIntegral m_modulo{1};
    UIntegral m_modulo2{1};
    UIntegral m_size{1};
};



template<typename UIntegral, typename Iterator> 
constexpr CompressedHash<UIntegral> create_perfect_compressed_hash(Iterator begin, Iterator end) 
{
    auto comp = [](UIntegral lhs,UIntegral rhs){return lhs==rhs;};
    radix_sort(begin,end); // O(n)
    if(!is_unique_sorted(begin,end,comp)) // O(n)
        throw std::runtime_error("You have to give a list of unique numbers to create_compressed_hash()");

    UIntegral division_value = find_smallest_difference_sorted<UIntegral> (begin,end); // O(n)
    UIntegral modulo = find_modulo_sorted<UIntegral>(begin,end,division_value); // O(n2*k)
    UIntegral modulo2 = find_modulo_sorted<UIntegral>(begin,end,division_value); // O(n2*k)
    // benchmark gives O(n3)
    // try to use binary search for modulo
    // try adding fast_hash befor the rest to reduce range of numbers
    return CompressedHash<UIntegral>{division_value,modulo,modulo2,static_cast<UIntegral>(std::distance(begin,end))};
}

template<typename UIntegral, typename X> 
constexpr CompressedHash<UIntegral> create_perfect_compressed_hash(X arg) 
{
    constexpr auto arr= arg();
    constexpr auto comp = [](UIntegral lhs,UIntegral rhs){return lhs==rhs;};
    static_assert(is_unique_unsorted(arr.begin(),arr.end(),comp),"You have to give a list of unique numbers to create_compressed_hash()");

    constexpr UIntegral division_value = find_smallest_difference_unsorted<UIntegral> (arr.begin(),arr.end());
    constexpr UIntegral modulo = find_modulo<UIntegral>(arr.begin(),arr.end(),[division_value](UIntegral l){return l/division_value;});
    constexpr UIntegral modulo2 = find_modulo<UIntegral>(arr.begin(),arr.end(),[division_value,modulo](UIntegral l){return (l/division_value)%modulo;});
    return CompressedHash<UIntegral>{division_value,modulo,modulo2,arr.size()};
}

HASHES_NAMESPACE_END



#endif /* PERFECT_COMPRESSED_HASH_INCLUDED */