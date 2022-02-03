// Copyright (c) 2017-2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_PEGTL_INTERNAL_APPLY_HPP
#define TAO_PEGTL_INTERNAL_APPLY_HPP

#include "if_apply.hpp"
#include "success.hpp"

namespace tao::pegtl::internal
{
   template< typename... Actions >
   using apply = if_apply< success, Actions... >;

}  // namespace tao::pegtl::internal

#endif
