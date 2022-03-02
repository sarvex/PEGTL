// Copyright (c) 2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_PEGTL_INTERNAL_INVERT_HPP
#define TAO_PEGTL_INTERNAL_INVERT_HPP

#include <type_traits>

#include "../type_list.hpp"

#include "any.hpp"
#include "enable_control.hpp"
#include "failure.hpp"
#include "one.hpp"
#include "range.hpp"

namespace tao::pegtl::internal
{
   template< typename Rule >
   struct invert
   {
      using rule_t = invert;
      using subs_t = empty_list;

      using data_t = typename Rule::data_t;
      using peek_t = typename Rule::peek_t;

      template< typename ParseInput >
      [[nodiscard]] static bool match( ParseInput& in ) noexcept( noexcept( peek_t::peek( in ) ) )
      {
         if( const auto t = peek_t::peek( in ) ) {
            if( !Rule::test_one( t.data() ) ) {
               in.consume< invert >( t.size() );
               return true;
            }
         }
         return false;
      }
   };

   template< typename Peek >
   struct invert< any< Peek > >
      : failure
   {};

   template< result_on_found R, typename Peek, typename Peek::data_t... Cs >
   struct invert< one< R, Peek, Cs... > >
      : one< invert_on_found( R ), Peek, Cs... >
   {};

   template< result_on_found R, typename Peek, typename Peek::data_t Lo, typename Peek::data_t Hi >
   struct invert< range< R, Peek, Lo, Hi > >
      : range< invert_on_found( R ), Peek, Lo, Hi >
   {};

   template< typename Rule >
   inline constexpr bool enable_control< invert< Rule > > = false;

}  // namespace tao::pegtl::internal

#endif
