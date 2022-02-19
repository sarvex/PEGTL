// Copyright (c) 2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_PEGTL_INTERNAL_SEPARATED_HPP
#define TAO_PEGTL_INTERNAL_SEPARATED_HPP

#include "enable_control.hpp"
#include "seq.hpp"
#include "success.hpp"

namespace tao::pegtl::internal
{
   template< typename... >
   struct separated;

   template< typename Sep >
   struct separated< Sep >
      : success
   {};

   template< typename... Ls, typename... Rs >
   [[nodiscard]] seq< Ls..., Rs... > operator+( const seq< Ls... >&, const seq< Rs... >& ) noexcept;

   template< typename Sep, typename Rule, typename... Rules >
   struct separated< Sep, Rule, Rules... >
      : decltype( ( seq< Rule >() + ... + seq< Sep, Rules >() ) )
   {};

   template< typename Sep, typename... Rules >
   inline constexpr bool enable_control< separated< Sep, Rules... > > = false;

}  // namespace tao::pegtl::internal

#endif
