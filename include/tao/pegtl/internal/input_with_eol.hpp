// Copyright (c) 2021-2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_PEGTL_INTERNAL_INPUT_WITH_EOL_HPP
#define TAO_PEGTL_INTERNAL_INPUT_WITH_EOL_HPP

#include "type_tags.hpp"

#include "../apply_mode.hpp"
#include "../rewind_mode.hpp"

namespace tao::pegtl::internal
{
   template< typename Rule, typename Input >
   class input_with_eol
      : public Input
   {
   public:
      using eol_t = Rule;
      using typename Input::data_t;
      using typename Input::pointer_t;
      using memory_input_t = input_with_eol< Rule, typename Input::memory_input_t >;

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
         if( Control< Rule >::template match< A, M, Action, Control >( in, st... ) ) {
            in.template consume< eol_consume_tag >( 0 );
            return true;
         }
         return false;
      }
   };

}  // namespace tao::pegtl::internal

#endif
