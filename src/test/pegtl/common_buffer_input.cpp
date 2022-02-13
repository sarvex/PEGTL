// Copyright (c) 2019-2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#include <string>

#include "test.hpp"

namespace tao::pegtl
{
   using dynamic_t = internal::defaulted_eager_position_input< internal::text_position< unsigned >, internal::input_with_eol< lf, internal::common_buffer_input< internal::dynamic_buffer_input_base< char, internal::cstring_reader > > > >;

   template< unsigned S, unsigned C >
   using static_t = internal::defaulted_eager_position_input< internal::text_position< unsigned >, internal::input_with_eol< lf, internal::common_buffer_input< internal::static_buffer_input_base< char, S, C, internal::cstring_reader > > > >;

   template< typename BufferInput >
   void unit_test_01( BufferInput&& in )
   {
      const auto r = parse< two< 'a' > >( in );
      TAO_PEGTL_TEST_ASSERT( r );
      TAO_PEGTL_TEST_ASSERT( in.buffer_size() == 0 );
   }

   template< typename BufferInput >
   void unit_test_02( BufferInput&& in )
   {
      const auto r = parse< two< 'a' > >( in );
      TAO_PEGTL_TEST_ASSERT( r );
      TAO_PEGTL_TEST_ASSERT( in.buffer_size() == 1 );
   }

   void unit_test()
   {
      unit_test_01( static_t< 8, 1 >( "aax" ) );
      unit_test_01( dynamic_t( 8, 1, "aax" ) );

      unit_test_02( static_t< 8, 4 >( "aax" ) );
      unit_test_02( dynamic_t( 8, 4, "aax" ) );
   }

}  // namespace tao::pegtl

#include "main.hpp"
