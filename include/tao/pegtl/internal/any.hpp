// Copyright (c) 2014-2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_PEGTL_INTERNAL_ANY_HPP
#define TAO_PEGTL_INTERNAL_ANY_HPP

#include "allow_bulk.hpp"
#include "dependent_false.hpp"
#include "enable_control.hpp"
#include "success.hpp"

#include "../type_list.hpp"

namespace tao::pegtl::internal
{
   template< typename Peek >
   struct any
   {
      using peek_t = Peek;
      using data_t = typename Peek::data_t;

      using rule_t = any;
      using subs_t = empty_list;

      [[nodiscard]] static constexpr bool test_one( const data_t /*unused*/ ) noexcept
      {
         return true;
      }

      template< typename ParseInput >
      [[nodiscard]] static bool match( ParseInput& in ) noexcept( noexcept( in.size( 1 ) ) )
      {
         if constexpr( !allow_bulk< Peek > ) {
            if( const auto t = Peek::peek( in ) ) {
               in.template consume< any >( t.size );
               return true;
            }
            return false;
         }
         else if constexpr( sizeof( *in.current() ) == 1 ) {
            static_assert( Peek::fixed_size > 0 );
            if( in.size( Peek::fixed_size ) >= Peek::fixed_size ) {
               in.template consume< any >( Peek::fixed_size );
               return true;
            }
            return false;
         }
         else if constexpr( sizeof( *in.current() ) == Peek::fixed_size ) {
            static_assert( Peek::fixed_size > 0 );
            if( in.size( 1 ) >= 1 ) {
               in.template consume< any >( 1 );
               return true;
            }
            return false;
         }
         else {
            static_assert( Peek::fixed_size > 0 );
            static_assert( dependent_false< Peek > );
         }
      }
   };

   template< typename Peek >
   inline constexpr bool enable_control< any< Peek > > = false;

}  // namespace tao::pegtl::internal

#endif
