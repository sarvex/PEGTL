// Copyright (c) 2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#include "test.hpp"
#include "verify_meta.hpp"
#include "verify_rule.hpp"

namespace tao::pegtl
{
   void unit_test()
   {
      verify_meta< invert< any >, internal::failure >();

      verify_meta< invert< one< 'a' > >, internal::one< internal::result_on_found::failure, internal::peek_char, 'a' > >();
      verify_meta< invert< not_one< 'a', 'f' > >, internal::one< internal::result_on_found::success, internal::peek_char, 'a', 'f' > >();

      verify_meta< invert< range< 'a', 'f' > >, internal::range< internal::result_on_found::failure, internal::peek_char, 'a', 'f' > >();
      verify_meta< invert< not_range< 'a', 'f' > >, internal::range< internal::result_on_found::success, internal::peek_char, 'a', 'f' > >();

      verify_analyze< invert< one< ' ' > > >( __LINE__, __FILE__, true, false );

      verify_rule< invert< one< 'a' > > >( __LINE__, __FILE__, "b", result_type::success, 0 );
      verify_rule< invert< one< 'a' > > >( __LINE__, __FILE__, "a", result_type::local_failure, 1 );
   }

}  // namespace tao::pegtl

#include "main.hpp"
