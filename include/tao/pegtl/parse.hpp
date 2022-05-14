// Copyright (c) 2014-2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_PEGTL_PARSE_HPP
#define TAO_PEGTL_PARSE_HPP

#include "apply_mode.hpp"
#include "normal.hpp"
#include "nothing.hpp"
#include "parse_error.hpp"
#include "rewind_mode.hpp"

namespace tao::pegtl
{
   template< typename Rule,
             template< typename... > class Action = nothing,
             template< typename... > class Control = normal,
             apply_mode A = apply_mode::action,
             rewind_mode M = rewind_mode::optional,
             typename ParseInput,
             typename... States >
   auto parse( ParseInput&& in, States&&... st )
   {
      return Control< Rule >::template match< A, M, Action, Control >( in, st... );
   }

   template< typename Rule,
             template< typename... > class Action = nothing,
             template< typename... > class Control = normal,
             apply_mode A = apply_mode::action,
             rewind_mode M = rewind_mode::optional,
             typename Ambience,
             typename ParseInput,
             typename... States >
   auto parse_nested( const Ambience& am, ParseInput&& in, States&&... st )
   {
#if defined( __cpp_exceptions )
      try {
         return parse< Rule, Action, Control, A, M >( in, st... );
      }
      catch( const parse_error_base& /*unused*/ ) {
         Control< Ambience >::raise_nested( am, st... );
      }
#else
      (void)am;
      return parse< Rule, Action, Control, A, M >( in, st... );
#endif
   }

}  // namespace tao::pegtl

#endif
