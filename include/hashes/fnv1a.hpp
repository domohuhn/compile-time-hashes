/** @file
 *
 * @date 01.03.2020
 * @author domohuhn
 * @copyright This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef FNV1A_HASH_INCLUDED
#define FNV1A_HASH_INCLUDED

#include "hashes/config.hpp"
#include <string_view>

HASHES_NAMESPACE_BEGIN

namespace detail {

template <typename UIntegral>
constexpr UIntegral basic_hash_impl(std::string_view str, UIntegral prime , UIntegral offset) noexcept
{
    UIntegral hash=offset;
    for(auto c:str){
        hash=(hash^c)*prime;
    }
    return hash;
}

}


template <typename UIntegral>
class FNV1A;


template <>
class FNV1A<uint64_t> {
public:
    static constexpr uint64_t hash(std::string_view str) noexcept {
        constexpr uint64_t offset = 14695981039346656037ULL;
        constexpr uint64_t prime = 1099511628211ULL;
        return detail::basic_hash_impl<uint64_t>(str,prime,offset);
    }
};


template <>
class FNV1A<uint32_t> {
public:
    static constexpr uint32_t hash(std::string_view str) noexcept {
        constexpr uint32_t offset = 2166136261U;
        constexpr uint32_t prime = 16777619U;
        return detail::basic_hash_impl<uint32_t>(str,prime,offset);
    }
};

using FNV1A_32 = FNV1A<uint32_t>;
using FNV1A_64 = FNV1A<uint64_t>;

HASHES_NAMESPACE_END

#endif /* FNV1A_HASH_INCLUDED */
