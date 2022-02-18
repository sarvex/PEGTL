// Copyright (c) 2020-2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#include <iostream>

#include "test.hpp"

#include <tao/pegtl/contrib/parse_tree.hpp>
#include <tao/pegtl/contrib/parse_tree_to_dot.hpp>

namespace tao::pegtl
{
   // clang-format off
   struct A : one< 'a' > {};
   struct B : one< 'b' > {};
   struct C : one< 'c' > {};

#if defined( __cpp_exceptions )
   struct S : if_must< one< '[' >, until< one< ']' > > > {};
#else
   struct S : seq< one< '[' >, until< one< ']' > > > {};
#endif

   struct D : sor< seq< A, B >, seq< A, C, S > > {};
   // clang-format on

   template< typename Rule >
   struct selector
      : parse_tree::selector< Rule, parse_tree::store_content::on< A, B, C, D, S > >
   {};

   void unit_test()
   {
      using memory_input_t = internal::fake_buffer_input< internal::defaulted_eager_position_input< internal::text_position< std::size_t >, internal::line_based_input< lf, internal::memory_input< char > > > >;
      memory_input_t in( "ac[\"\\\x01\x7f\b\n\r\f\t\a\v]" );
      const auto root = parse_tree::parse< D, selector >( in );
      parse_tree::print_dot( std::cout, *root );
   }

}  // namespace tao::pegtl

#include "main.hpp"
