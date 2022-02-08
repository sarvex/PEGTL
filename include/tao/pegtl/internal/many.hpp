// Copyright (c) 2014-2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_PEGTL_INTERNAL_MANY_HPP
#define TAO_PEGTL_INTERNAL_MANY_HPP

#include "dependent_false.hpp"
#include "enable_control.hpp"
#include "success.hpp"

#include "../type_list.hpp"

namespace tao::pegtl::internal
{
   template< unsigned Count, typename Peek, unsigned Fixed = Peek::fixed_size >
   struct many
   {
      using rule_t = many;
      using subs_t = empty_list;

      template< typename ParseInput >
      [[nodiscard]] static bool match( ParseInput& in ) noexcept( noexcept( in.size( Count ) ) )
      {
         if constexpr( sizeof( *in.current() ) == 1 ) {
            if( in.size( Count * Fixed ) >= Count * Fixed ) {
               in.template consume< many >( Count * Fixed );
               return true;
            }
            return false;
         }
         else if constexpr( sizeof( *in.current() ) == Fixed ) {
            if( in.size( Count ) >= Count ) {
               in.template consume< many >( Count );
               return true;
            }
            return false;
         }
         else {
            static_assert( dependent_false< Peek > );
         }
      }
   };

   template< unsigned Count, typename Peek >
   struct many< Count, Peek, 0 >
   {
      using rule_t = many;
      using subs_t = empty_list;

      template< typename ParseInput >
      [[nodiscard]] static bool match( ParseInput& in ) noexcept( noexcept( in.size( Count ) ) )
      {
         std::size_t done = 0;

         for( unsigned i = 0; i < Count; ++i ) {
            if( const auto t = Peek::peek( in, done ) ) {
               done += t.size;
               continue;
            }
            return false;
         }
         in.template consume< many >( done );
         return true;
      }
   };

   template< typename Peek, unsigned Fixed >
   struct many< 0, Peek, Fixed >
      : success
   {};

   template< typename Peek >
   struct many< 0, Peek, 0 >
      : success
   {};

   template< unsigned Count, typename Peek, unsigned Fixed >
   inline constexpr bool enable_control< many< Count, Peek, Fixed > > = false;

}  // namespace tao::pegtl::internal

#endif
