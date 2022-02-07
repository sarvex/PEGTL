// Copyright (c) 2014-2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_PEGTL_INTERNAL_PEEK_COPY_HPP
#define TAO_PEGTL_INTERNAL_PEEK_COPY_HPP

#include "data_and_size.hpp"

namespace tao::pegtl::internal
{
   template< typename T >
   struct peek_copy
   {
      using data_t = T;
      using pair_t = data_and_size< T >;

      template< typename ParseInput >
      [[nodiscard]] static pair_t peek( ParseInput& in ) noexcept( noexcept( in.empty() ) )
      {
         using peek_t = typename ParseInput::data_t;

         static_assert( sizeof( peek_t ) == sizeof( data_t ) );

         if( in.empty() ) {
            return { 0, 0 };
         }
         return { T( *in.current() ), 1 };
      }
   };

}  // namespace tao::pegtl::internal

#endif
