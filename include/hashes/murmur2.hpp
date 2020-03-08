/** @file
 *
 * @date 01.03.2020
 * @author domohuhn
 * @copyright This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef MURMUR2_HASH_INCLUDED
#define MURMUR2_HASH_INCLUDED

#include "hashes/config.hpp"
#include <string_view>
#include <cstring>

HASHES_NAMESPACE_BEGIN

namespace detail {
    
    template <typename UIntegral,typename... Args>
    constexpr UIntegral combine_bytes_to_larger_type(Args... in)
    {
        UIntegral rv=0;
        UIntegral i=0;
        UIntegral x[]={ (rv|=static_cast<UIntegral>(in)<<i,i=i+8)...};
        return rv;
    }
}

template <typename UIntegral>
class Murmur2;

template <>
class Murmur2<uint32_t> {
public:
    /** Murmur hash 2A */
    static constexpr uint32_t hash(std::string_view str) noexcept 
    {
        constexpr uint32_t multiply = 0x5bd1e995U;
        constexpr uint32_t shift = 24U;
        constexpr uint32_t seed = 834533232U;
        uint32_t len = str.size();

        const auto * data = str.begin();

        uint32_t hash = seed;

        // string view excludes the terminating null
        while(len+1 >= 4)
        {
            uint32_t k = detail::combine_bytes_to_larger_type<uint64_t>(
                *data,*(data+1),*(data+2),*(data+3));
            k *= multiply;
            k ^= k >> shift;
            k *= multiply;
            hash *= multiply;
            hash ^= k;

            data += 4;
            len -= 4;
        }

        uint32_t final_chars = 0U;

        switch(len)
        {
            case 3: final_chars ^= data[2] << 16U;
            case 2: final_chars ^= data[1] << 8U;
            case 1: final_chars ^= data[0];
        };

        final_chars *= multiply;
        final_chars ^= final_chars >> shift;
        final_chars *= multiply;
        hash *= multiply;
        hash ^= final_chars;

        // string view excludes the terminating null
        len = str.size()?str.size()+1:0;
        len *= multiply;
        len ^= len >> shift;
        len *= multiply;
        hash *= multiply;
        hash ^= len;

        hash ^= hash >> 13U;
        hash *= multiply;
        hash ^= hash >> 15U;

        return hash;
    }
};


template <>
class Murmur2<uint64_t> {
public:
    /** Murmur2 hash 64A */
    static constexpr uint64_t hash(std::string_view str) noexcept
    {
        constexpr uint64_t multiply = 0xc6a4a7935bd1e995ULL;
        constexpr uint64_t shift = 47ULL;
        constexpr uint64_t seed = 700924169573080812ULL;

        const uint64_t len=str.size();
        const uint64_t calclen = len?len+1:0;
        uint64_t hash = seed ^ (calclen * multiply);

        if(len>0){
            const auto * data = str.begin();
            const auto first_loop_iterations = calclen/8;

            for(size_t i=0;i<first_loop_iterations;++i)
            {
                uint64_t k=detail::combine_bytes_to_larger_type<uint64_t>(
                    *data,*(data+1),*(data+2),*(data+3),
                    *(data+4),*(data+5),*(data+6),*(data+7));

                k *= multiply; 
                k ^= k >> shift; 
                k *= multiply; 
                
                hash ^= k;
                hash *= multiply;
                data+=8;
            }

            const auto * data2 = str.begin()+8*first_loop_iterations;

            switch(calclen & 7)
            {
                case 7: hash ^= static_cast<uint64_t>(data2[6]) << 48ULL;
                case 6: hash ^= static_cast<uint64_t>(data2[5]) << 40ULL;
                case 5: hash ^= static_cast<uint64_t>(data2[4]) << 32ULL;
                case 4: hash ^= static_cast<uint64_t>(data2[3]) << 24ULL;
                case 3: hash ^= static_cast<uint64_t>(data2[2]) << 16ULL;
                case 2: hash ^= static_cast<uint64_t>(data2[1]) << 8ULL;
                case 1: hash ^= static_cast<uint64_t>(data2[0]);
                        hash *= multiply;
            };
        }
        
        hash ^= hash >> shift;
        hash *= multiply;
        hash ^= hash >> shift;

        return hash;
    } 

};



using Murmur2_32 = Murmur2<uint32_t>;
using Murmur2_64 = Murmur2<uint64_t>;

HASHES_NAMESPACE_END

#endif /* MURMUR2_HASH_INCLUDED */
