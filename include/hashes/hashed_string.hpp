/** @file
 *
 * @date 01.03.2020
 * @author domohuhn
 * @copyright This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef HASHED_STRING_INCLUDED
#define HASHED_STRING_INCLUDED

#include "hashes/config.hpp"
#include <string_view>

HASHES_NAMESPACE_BEGIN

template<typename rep, class traits>
class HashedStringView {
public:
    using value_t = rep;
    using operations_t = traits;

    constexpr HashedStringView(std::string_view s) noexcept : m_hash{operations_t::hash(s)}, m_str{std::move(s)} {}
    
    HashedStringView(const HashedStringView&) = default;
    HashedStringView(HashedStringView&&) = default;
    HashedStringView& operator=(const HashedStringView&) = default;
    HashedStringView& operator=(HashedStringView&&) = default;
    ~HashedStringView() = default;

    constexpr value_t hash() const noexcept {
        return m_hash;
    }

    constexpr const std::string_view string_view() const noexcept {
        return std::string_view{m_str};
    }

    constexpr bool operator== (const HashedStringView<rep,traits>& other) const noexcept{
        return m_hash==other.m_hash;
    }

    constexpr bool operator!= (const HashedStringView<rep,traits>& other) const noexcept{
        return m_hash!=other.m_hash;
    }
private:
    std::string_view m_str{};
    value_t m_hash{0};
};

HASHES_NAMESPACE_END

#endif /* HASHED_STRING_INCLUDED */