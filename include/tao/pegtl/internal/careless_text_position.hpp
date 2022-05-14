// Copyright (c) 2021-2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_PEGTL_INTERNAL_CARELESS_TEXT_POSITION_HPP
#define TAO_PEGTL_INTERNAL_CARELESS_TEXT_POSITION_HPP

#include <type_traits>

#include "text_position_base.hpp"
#include "type_tags.hpp"

namespace tao::pegtl::internal
{
   template< typename Size >
   struct careless_text_position
      : text_position_base< Size >
   {
      using typename text_position_base< Size >::lazy_rule;

      using text_position_base< Size >::text_position_base;

      template< typename Rule, typename Data >
      void consume( const Data* /*unused*/, const Size n ) noexcept
      {
         if constexpr( std::is_same_v< Rule, eol_consume_tag > ) {
            ++this->line;
            this->count_in_line = 1;
         }
         else {
            this->count_in_line += n;
         }
      }
   };

}  // namespace tao::pegtl::internal

#endif
