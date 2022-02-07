// Copyright (c) 2018-2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_PEGTL_CONTRIB_INTERNAL_PEEK_MASK_UINT8_HPP
#define TAO_PEGTL_CONTRIB_INTERNAL_PEEK_MASK_UINT8_HPP

#include <cstddef>
#include <cstdint>

#include "../../internal/data_and_size.hpp"

namespace tao::pegtl::internal
{
   template< std::uint8_t Mask >
   struct peek_mask_uint8
   {
      using data_t = std::uint8_t;
      using pair_t = data_and_size< std::uint8_t >;

      template< typename ParseInput >
      [[nodiscard]] static pair_t peek( ParseInput& in ) noexcept( noexcept( in.empty() ) )
      {
         using peek_t = typename ParseInput::data_t;

         static_assert( sizeof( peek_t ) == 1 );

         if( in.empty() ) {
            return { 0, 0 };
         }
         return { std::uint8_t( *in.current() ) & Mask, 1 };
      }
   };

}  // namespace tao::pegtl::internal

#endif
