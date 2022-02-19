// Copyright (c) 2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#include "test.hpp"

#include "verify_meta.hpp"

namespace tao::pegtl
{
   void unit_test()
   {
      verify_meta< separated< any >, internal::success >();
      verify_meta< separated< any, alpha >, internal::seq< alpha >, alpha >();
      verify_meta< separated< any, alpha, digit >, internal::seq< alpha, any, digit >, alpha, any, digit >();
      verify_meta< separated< any, alpha, digit, space >, internal::seq< alpha, any, digit, any, space >, alpha, any, digit, any, space >();
   }

}  // namespace tao::pegtl

#include "main.hpp"
