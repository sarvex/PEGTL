// Copyright (c) 2020-2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_PEGTL_CONTRIB_TOKEN_KIND_HPP
#define TAO_PEGTL_CONTRIB_TOKEN_KIND_HPP

#include "../internal/enable_control.hpp"

#include "../analyze_traits.hpp"
#include "../type_list.hpp"

namespace tao::pegtl
{
   namespace internal
   {
      template< typename Kind, Kind Value >
      struct token_kind
      {
         using rule_t = token_kind;
         using subs_t = empty_list;

         template< typename ParseInput >
         static bool match( ParseInput& in )
         {
            if( ( !in.empty() ) && ( in.current()->kind == Value ) ) {
               in.template consume< token_kind >( 1 );
               return true;
            }
            return false;
         }
      };

      template< typename Kind, Kind Value >
      inline constexpr bool enable_control< token_kind< Kind, Value > > = false;

   }  // namespace internal

   template< auto Value >
   using token_kind = internal::token_kind< decltype( Value ), Value >;

   template< typename Name, typename Kind, Kind Value >
   struct analyze_traits< Name, internal::token_kind< Kind, Value > >
      : analyze_any_traits<>
   {};

}  // namespace tao::pegtl

#endif
