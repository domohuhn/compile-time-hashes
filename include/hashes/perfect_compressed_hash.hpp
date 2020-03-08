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

template<typename Iterator,typename BinaryPred>
constexpr bool is_unique_unsorted (Iterator begin,Iterator end,BinaryPred op) 
{
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

template<typename UIntegral, typename Iterator> 
constexpr CompressedHash<UIntegral> create_perfect_compressed_hash(Iterator begin, Iterator end) 
{
    auto comp = [](UIntegral lhs,UIntegral rhs){return lhs==rhs;};
    if(!is_unique_unsorted(begin,end,comp)) // O(n2)
        throw std::runtime_error("You have to give a list of unique numbers to create_compressed_hash()");

    UIntegral division_value = find_smallest_difference_unsorted<UIntegral> (begin,end); // O(n2)
    UIntegral modulo = find_modulo<UIntegral>(begin,end,[division_value](UIntegral l){return l/division_value;}); // O(n3)
    UIntegral modulo2 = find_modulo<UIntegral>(begin,end,[division_value,modulo](UIntegral l){return (l/division_value)%modulo;}); // O(n3)
    // benchmark gives O(n3)
    // changes: sort vector to get O(nlog(n)),O(n),O(n)
    // create copy in find modulo, assign value, sort, unique -> (O(n),  O(nlog(n)), O(n))*O(n)
    // try to use binary search for modulo
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