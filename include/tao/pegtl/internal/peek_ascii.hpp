// Copyright (c) 2014-2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_PEGTL_INTERNAL_PEEK_ASCII_HPP
#define TAO_PEGTL_INTERNAL_PEEK_ASCII_HPP

#include "peek_copy.hpp"

namespace tao::pegtl::internal
{
   struct peek_ascii
   {
      using data_t = char;
      using pair_t = data_and_size< char >;

      static constexpr std::size_t fixed_size = 1;

      template< typename ParseInput >
      [[nodiscard]] static pair_t peek( ParseInput& in, const std::size_t offset = 0 ) noexcept( noexcept( in.size( 42 ) ) )
      {
         const pair_t r = peek_copy< char >::peek( in, offset );

         if( ( r.data & 0x80 ) == 0 ) {
            return r;
         }
         return pair_t();
      }
   };

}  // namespace tao::pegtl::internal

#endif
