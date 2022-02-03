// Copyright (c) 2016-2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_PEGTL_CONTRIB_DISCARD_HPP
#define TAO_PEGTL_CONTRIB_DISCARD_HPP

#include "../internal/enable_control.hpp"

#include "../type_list.hpp"

#include "analyze_traits.hpp"

namespace tao::pegtl
{
   namespace internal
   {
      struct discard
      {
         using rule_t = discard;
         using subs_t = empty_list;

         template< typename ParseInput >
         [[nodiscard]] static bool match( ParseInput& in ) noexcept
         {
            static_assert( noexcept( in.discard() ) );
            in.discard();
            return true;
         }
      };

      template<>
      inline constexpr bool enable_control< disable > = false;

   }  // namespace internal

   struct discard
      : internal::discard
   {};

   template< typename Name >
   struct analyze_traits< Name, internal::discard >
      : analyze_opt_traits<>
   {};

}  // namespace tao::pegtl

#endif
