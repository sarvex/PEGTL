// Copyright (c) 2018-2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_PEGTL_INTERNAL_PEEK_ENDIAN_HPP
#define TAO_PEGTL_INTERNAL_PEEK_ENDIAN_HPP

#include "allow_bulk.hpp"
#include "data_and_size.hpp"
#include "dependent_false.hpp"

namespace tao::pegtl::internal
{
   template< typename Data, typename Endian >
   struct peek_endian
   {
      using data_t = Data;
      using pair_t = data_and_size< Data >;

      static_assert( sizeof( Data ) > 1 );

      static constexpr std::size_t fixed_size = sizeof( Data );

      template< typename ParseInput >
      [[nodiscard]] static pair_t peek( ParseInput& in, const std::size_t offset = 0 ) noexcept( noexcept( in.size( 42 ) ) )
      {
         using peek_t = typename ParseInput::data_t;

         if constexpr( sizeof( peek_t ) == 1 ) {
            if( in.size( sizeof( Data ) + offset ) < sizeof( Data ) + offset ) {
               return pair_t();
            }
            return pair_t( Endian::template from< Data >( in.current( offset ) ), sizeof( Data ) );
         }
         else if constexpr( sizeof( peek_t ) == sizeof( Data ) ) {
            if( in.size( 1 + offset ) < 1 + offset ) {
               return pair_t();
            }
            return pair_t( Endian::template from< Data >( *in.current( offset ) ), 1 );
         }
         else {
            static_assert( dependent_false< peek_endian > );
         }
      }
   };

   template< typename Data, typename Endian >
   inline constexpr bool allow_bulk< peek_endian< Data, Endian > > = true;

}  // namespace tao::pegtl::internal

#endif
