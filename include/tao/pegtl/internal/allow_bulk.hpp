// Copyright (c) 2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_PEGTL_INTERNAL_ALLOW_BULK_HPP
#define TAO_PEGTL_INTERNAL_ALLOW_BULK_HPP

namespace tao::pegtl::internal
{
   template< typename Peek >
   inline constexpr bool allow_bulk = false;

}  // namespace tao::pegtl::internal

#endif
