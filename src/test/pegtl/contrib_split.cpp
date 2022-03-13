// Copyright (c) 2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#include "test.hpp"

#include "verify_meta.hpp"
#include "verify_rule.hpp"

#include <tao/pegtl/contrib/split.hpp>

namespace tao::pegtl
{
   void unit_test()
   {
      const std::string i1 = "";
      TAO_PEGTL_TEST_THROWS( (void)split( i1 ) );

      const std::string i2 = "a";
      const std::vector< std::string > v2 = split( i2 );
      TAO_PEGTL_TEST_ASSERT( v2.size() == 1 );
      TAO_PEGTL_TEST_ASSERT( v2[ 0 ] == "a" );

      const std::string i3 = "abc";
      const std::vector< std::string > v3 = split( i3 );
      TAO_PEGTL_TEST_ASSERT( v3.size() == 1 );
      TAO_PEGTL_TEST_ASSERT( v3[ 0 ] == "abc" );

      const std::string i4 = "a b\tc";
      const std::vector< std::string > v4 = split( i4 );
      TAO_PEGTL_TEST_ASSERT( v4.size() == 3 );
      TAO_PEGTL_TEST_ASSERT( v4[ 0 ] == "a" );
      TAO_PEGTL_TEST_ASSERT( v4[ 1 ] == "b" );
      TAO_PEGTL_TEST_ASSERT( v4[ 2 ] == "c" );
   }

}  // namespace tao::pegtl

#include "main.hpp"
