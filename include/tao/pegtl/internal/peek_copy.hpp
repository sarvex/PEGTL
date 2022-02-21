// Copyright (c) 2014-2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_PEGTL_INTERNAL_PEEK_COPY_HPP
#define TAO_PEGTL_INTERNAL_PEEK_COPY_HPP

#include <cstddef>

#include "allow_bulk.hpp"
#include "data_and_size.hpp"

namespace tao::pegtl::internal
{
   template< typename T >
   struct peek_copy
   {
      using data_t = T;
      using pair_t = data_and_size< T >;

      static constexpr std::size_t fixed_size = sizeof( T );

      template< typename ParseInput >
      [[nodiscard]] static pair_t peek( ParseInput& in, const std::size_t offset = 0 ) noexcept( noexcept( in.size( 42 ) ) )
      {
         using peek_t = typename ParseInput::data_t;

         static_assert( sizeof( peek_t ) == sizeof( data_t ) );

         if( in.size( offset + 1 ) > offset ) {
            return pair_t( T( *in.current( offset ) ) );
         }
         return pair_t();
      }
   };

   using peek_char = peek_copy< char >;
   using peek_int8 = peek_copy< std::int8_t >;
   using peek_uint8 = peek_copy< std::uint8_t >;
   using peek_byte = peek_copy< std::byte >;

   template< typename T >
   inline constexpr bool allow_bulk< peek_copy< T > > = true;

}  // namespace tao::pegtl::internal

#endif
