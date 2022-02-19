// Copyright (c) 2018-2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#include <tao/pegtl/internal/line_view_at.hpp>

#include "test.hpp"

namespace tao::pegtl
{
   void unit_test()
   {
      internal::fake_buffer_input< internal::defaulted_eager_position_input< internal::text_position< unsigned >, internal::line_based_input< lf, internal::memory_input< char > > > > in( "abc\ndef\nghi" );
      TAO_PEGTL_TEST_ASSERT( parse< seq< string< 'a', 'b', 'c' >, eol, one< 'd' > > >( in ) );
      TAO_PEGTL_TEST_ASSERT( line_view_at( in, in.rewind_position() ) == "def" );
   }

}  // namespace tao::pegtl

#include "main.hpp"
