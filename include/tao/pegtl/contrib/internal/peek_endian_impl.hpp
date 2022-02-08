// Copyright (c) 2018-2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_PEGTL_CONTRIB_INTERNAL_PEEK_ENDIAN_IMPL_HPP
#define TAO_PEGTL_CONTRIB_INTERNAL_PEEK_ENDIAN_IMPL_HPP

#include "../../internal/data_and_size.hpp"
#include "../../internal/dependent_false.hpp"

namespace tao::pegtl::internal
{
   template< typename Data, typename Endian >
   struct peek_endian_impl
   {
      using data_t = Data;
      using pair_t = data_and_size< data_t >;

      static constexpr std::size_t fixed_size = sizeof( Data );

      template< typename ParseInput >
      [[nodiscard]] static pair_t peek( ParseInput& in, const std::size_t offset = 0 ) noexcept( noexcept( in.size( 42 ) ) )
      {
         using peek_t = typename ParseInput::data_t;

         if constexpr( sizeof( peek_t ) == 1 ) {
            if( in.size( sizeof( data_t ) + offset ) < sizeof( data_t ) + offset ) {
               return { 0, 0 };
            }
            return { Endian::template from< Data >( in.current() + offset ), sizeof( data_t ) };
         }
         else if constexpr( sizeof( peek_t ) == sizeof( data_t ) ) {
            if( in.size( 1 + offset ) < 1 + offset ) {
               return { 0, 0 };
            }
            return { Endian::template from< Data >( *( in.current() + offset ) ), 1 };
         }
         else {
            static_assert( dependent_false< ParseInput > );
         }
      }
   };

}  // namespace tao::pegtl::internal

#endif
