// Copyright (c) 2018-2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_PEGTL_CONTRIB_INTERNAL_PEEK_ENUMS_HPP
#define TAO_PEGTL_CONTRIB_INTERNAL_PEEK_ENUMS_HPP

#include <type_traits>

#include "endian.hpp"
#include "peek_endian_impl.hpp"

namespace tao::pegtl::internal
{
   template< typename E >
   struct peek_enums_be
      : peek_endian_impl< E, from_be >
   {
      static_assert( std::is_enum_v< E > );
   };

   template< typename E >
   struct peek_enums_le
      : peek_endian_impl< E, from_le >
   {
      static_assert( std::is_enum_v< E > );
   };

}  // namespace tao::pegtl::internal

#endif
