// Copyright (c) 2017-2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_PEGTL_INTERNAL_CONSUME_HPP
#define TAO_PEGTL_INTERNAL_CONSUME_HPP

#include "enable_control.hpp"

#include "../type_list.hpp"

namespace tao::pegtl::internal
{
   template< unsigned Count >
   struct consume
   {
      using rule_t = consume;
      using subs_t = empty_list;

      template< typename ParseInput >
      [[nodiscard]] static bool match( ParseInput& in ) noexcept
      {
         if( !in.empty() ) {
            in.template consume< consume >( Count );
            return true;
         }
         return false;
      }
   };

   template< unsigned Count >
   inline constexpr bool enable_control< consume< Count > > = false;

}  // namespace tao::pegtl::internal

#endif
