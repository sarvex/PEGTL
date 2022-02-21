// Copyright (c) 2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_PEGTL_INTERNAL_PEEK_MEMBER_HPP
#define TAO_PEGTL_INTERNAL_PEEK_MEMBER_HPP

#include <type_traits>

#include "allow_bulk.hpp"
#include "data_and_size.hpp"

namespace tao::pegtl::internal
{
   template< typename T, T, typename = void >
   struct peek_member_impl;

   template< typename C, typename T, T C::*P >
   struct peek_member_impl< T C::*, P, std::enable_if_t< std::is_member_object_pointer_v< T C::* > > >
   {
      using data_t = std::decay_t< std::conditional_t< std::is_pointer_v< std::decay_t< T > >, std::remove_pointer_t< T >, T > >;
      using pair_t = data_and_size< std::conditional_t< std::is_pointer_v< T >, const data_t*, data_t > >;

      static constexpr std::size_t fixed_size = 1;

      template< typename ParseInput >
      [[nodiscard]] static pair_t peek( ParseInput& in, const std::size_t offset = 0 ) noexcept( noexcept( in.size( 42 ) ) )
      {
         if( in.size( offset + 1 ) > offset ) {
            return pair_t( ( *in.current( offset ) ).*P );
         }
         return pair_t();
      }
   };

   // TODO: Do we need to finish access via functions?

   // template< bool N, typename C, typename T, T ( *P )( const C& ) noexcept( N ) >
   // struct peek_member_impl< T ( * )( const C& ) noexcept( N ), P >
   // {
   //    using data_t = std::decay_t< T >;
   //    using pair_t = data_and_size< T >;

   //    template< typename ParseInput >
   //    [[nodiscard]] static pair_t peek( ParseInput& in, const std::size_t offset = 0 ) noexcept( N && noexcept( in.size( 42 ) ) )
   //    {
   //       if( in.size( offset + 1 ) > offset ) {
   //          return pair_t( P( *in.current( offset ) ) );
   //       }
   //       return pair_t();
   //    }
   // };

   // template< bool N, typename C, typename T, T ( C::*P )() const noexcept( N ) >
   // struct peek_member_impl< T ( C::* )() const noexcept( N ), P >
   // {
   //    using data_t = std::decay_t< T >;
   //    using pair_t = data_and_size< T >;

   //    template< typename ParseInput >
   //    [[nodiscard]] static pair_t peek( ParseInput& in, const std::size_t offset = 0 ) noexcept( N && noexcept( in.size( 42 ) ) )
   //    {
   //       if( in.size( offset + 1 ) > offset ) {
   //          return pair_t( ( ( *in.current( offset ) ).*P )() );
   //       }
   //       return pair_t();
   //    }
   // };

   template< typename T, T F, typename Z >
   inline constexpr bool allow_bulk< peek_member_impl< T, F, Z > > = true;

   template< auto T >
   using peek_member = peek_member_impl< decltype( T ), T >;

}  // namespace tao::pegtl::internal

#endif
