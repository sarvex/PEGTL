// Copyright (c) 2021-2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_PEGTL_INTERNAL_SELECTED_TEXT_POSITION_HPP
#define TAO_PEGTL_INTERNAL_SELECTED_TEXT_POSITION_HPP

#include <type_traits>

#include "../apply_mode.hpp"
#include "../normal.hpp"
#include "../nothing.hpp"
#include "../rewind_mode.hpp"

#include "careless_text_position.hpp"
#include "fake_buffer_input.hpp"
#include "initialized_eager_position_input.hpp"
#include "line_based_input.hpp"
#include "memory_input.hpp"
#include "text_position_base.hpp"
#include "type_tags.hpp"

namespace tao::pegtl::internal
{
   template< typename Eol, typename Size >
   struct [[nodiscard]] selected_text_position
      : text_position_base< Size >
   {
      using eol_rule = Eol;

      using typename text_position_base< Size >::lazy_rule;

      using text_position_base< Size >::text_position_base;

      template< typename Rule, typename Data >
      void consume( const Data* current, const Size n ) noexcept
      {
         if constexpr( std::is_same_v< Rule, eol_consume_tag > ) {
            ++this->line;
            this->count_in_line = 1;
         }
         else if constexpr( std::is_same_v< Rule, eol_unknown_tag > ) {
            if( n > 0 ) {
               initialized_eager_position_input< careless_text_position< Size >, line_based_input< Eol, fake_buffer_input< memory_input< Data > > > > in( careless_text_position< Size >( this->line, this->count_in_line ), current, n );
               (void)normal< lazy_rule >::template match< apply_mode::nothing, rewind_mode::dontcare, nothing, normal >( in );
               this->line = in.private_position().line;
               this->count_in_line = in.private_position().count_in_line;
            }
         }
         else {
            this->count_in_line += n;  // TODO: More?
         }
      }
   };

}  // namespace tao::pegtl::internal

#endif
