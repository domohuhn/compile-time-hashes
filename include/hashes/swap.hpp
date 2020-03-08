/** @file
 *
 * @date 08.03.2020
 * @author domohuhn
 * @copyright This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef HASHES_SWAP_INCLUDED
#define HASHES_SWAP_INCLUDED


#include "hashes/config.hpp"
#include <type_traits>

HASHES_NAMESPACE_BEGIN

template<typename T>
constexpr void swap(T& a, T& b) noexcept(std::is_nothrow_move_assignable<T>::value && std::is_nothrow_move_constructible<T>::value)
{
    auto tmp = std::move(a);
    a=std::move(b);
    b = std::move(tmp);
}

HASHES_NAMESPACE_END

#endif /* HASHES_SWAP_INCLUDED */