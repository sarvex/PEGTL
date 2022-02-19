// Copyright (c) 2021-2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_PEGTL_INTERNAL_LINE_BASED_INPUT_HPP
#define TAO_PEGTL_INTERNAL_LINE_BASED_INPUT_HPP

#include "../apply_mode.hpp"
#include "../rewind_mode.hpp"

#include "input_traits.hpp"
#include "type_tags.hpp"

namespace tao::pegtl::internal
{
   template< typename Eol, typename Input >
   class line_based_input
      : public Input
   {
   public:
      using eol_rule = Eol;

      using typename Input::data_t;

      using Input::Input;

      template< apply_mode A,
                rewind_mode M,
                template< typename... >
                class Action,
                template< typename... >
                class Control,
                typename ParseInput,
                typename... States >
      [[nodiscard]] static bool match_eol( ParseInput& in, States&&... st )
      {
         if( Control< Eol >::template match< A, M, Action, Control >( in, st... ) ) {
            in.template consume< eol_consume_tag >( 0 );
            return true;
         }
         return false;
      }
   };

   template< typename Eol, typename Input >
   struct input_traits< line_based_input< Eol, Input > >
   {
      using memory_input_t = line_based_input< Eol, typename input_traits< Input >::memory_input_t >;
   };

}  // namespace tao::pegtl::internal

#endif
