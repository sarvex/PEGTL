// Copyright (c) 2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_PEGTL_INTERNAL_EXTRACT_POSITION_HPP
#define TAO_PEGTL_INTERNAL_EXTRACT_POSITION_HPP

#include "has_current_position.hpp"

namespace tao::pegtl::internal
{
   template< typename T >
   [[nodiscard]] decltype( auto ) extract_position( const T& t )
   {
      if constexpr( !has_current_position< T > ) {
         return t;
      }
      else if constexpr( !has_current_position< decltype( *t.current() ) > ) {
         return t.current_position();
      }
      else {
         return t.current()->current_position();
      }
   }

}  // namespace tao::pegtl::internal

#endif
