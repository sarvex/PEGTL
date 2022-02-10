// Copyright (c) 2018-2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_PEGTL_CONTRIB_INTERNAL_PEEK_MASK_UINT_HPP
#define TAO_PEGTL_CONTRIB_INTERNAL_PEEK_MASK_UINT_HPP

#include <cstddef>
#include <cstdint>

#include "../../internal/data_and_size.hpp"

#include "endian.hpp"
#include "peek_endian_impl.hpp"

namespace tao::pegtl::internal
{
   template< typename Data, Data Mask, typename Endian >
   struct peek_mask_uint_impl
   {
      using data_t = Data;
      using pair_t = data_and_size< data_t >;

      static constexpr std::size_t fixed_size = sizeof( Data );

      template< typename ParseInput >
      [[nodiscard]] static pair_t peek( ParseInput& in ) noexcept( noexcept( in.size( sizeof( data_t ) ) ) )
      {
         pair_t r = peek_endian_impl< Data, Endian >::peek( in );
         r.data &= Mask;
         return r;
      }
   };

   template< std::uint16_t Mask >
   using peek_mask_uint16_be = peek_mask_uint_impl< std::uint16_t, Mask, big_endian >;
   template< std::uint32_t Mask >
   using peek_mask_uint32_be = peek_mask_uint_impl< std::uint32_t, Mask, big_endian >;
   template< std::uint64_t Mask >
   using peek_mask_uint64_be = peek_mask_uint_impl< std::uint64_t, Mask, big_endian >;

   template< std::uint16_t Mask >
   using peek_mask_uint16_le = peek_mask_uint_impl< std::uint16_t, Mask, little_endian >;
   template< std::uint32_t Mask >
   using peek_mask_uint32_le = peek_mask_uint_impl< std::uint32_t, Mask, little_endian >;
   template< std::uint64_t Mask >
   using peek_mask_uint64_le = peek_mask_uint_impl< std::uint64_t, Mask, little_endian >;

}  // namespace tao::pegtl::internal

#endif
