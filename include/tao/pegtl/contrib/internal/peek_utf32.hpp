// Copyright (c) 2014-2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_PEGTL_CONTRIB_INTERNAL_PEEK_UTF32_HPP
#define TAO_PEGTL_CONTRIB_INTERNAL_PEEK_UTF32_HPP

#include <cstddef>
#include <cstdint>

#include "../../internal/data_and_size.hpp"

#include "endian.hpp"
#include "peek_endian_impl.hpp"

namespace tao::pegtl::internal
{
   template< typename Endian >
   struct peek_utf32_impl
   {
      using data_t = char32_t;
      using pair_t = data_and_size< char32_t >;

      static constexpr std::size_t fixed_size = 4;

      static_assert( sizeof( char32_t ) == 4 );

      template< typename ParseInput >
      [[nodiscard]] static pair_t peek( ParseInput& in, const std::size_t offset ) noexcept( noexcept( in.size( 42 ) ) )
      {
         const pair_t r = peek_endian_impl< char32, Endian >::peek( in, offset );

         if( ( r.data <= 0x10ffff ) && !( r.data >= 0xd800 && r.data <= 0xdfff ) ) {
            return r;
         }
         return { 0, 0 };
      }
   };

   using peek_utf32_be = peek_utf32_impl< big_endian >;
   using peek_utf32_le = peek_utf32_impl< little_endian >;

}  // namespace tao::pegtl::internal

#endif
