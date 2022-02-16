// Copyright (c) 2019-2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#include <string>

#include "test.hpp"

namespace tao::pegtl
{
   using dynamic_t = internal::defaulted_eager_position_input< internal::text_position< unsigned >, internal::line_based_input< lf, internal::common_buffer_input< internal::dynamic_buffer_input_base< char, internal::cstring_reader > > > >;

   template< unsigned S, unsigned C >
   using static_t = internal::defaulted_eager_position_input< internal::text_position< unsigned >, internal::line_based_input< lf, internal::common_buffer_input< internal::static_buffer_input_base< char, S, C, internal::cstring_reader > > > >;

   using dynamic_a = internal::auto_discard_buffer_input< dynamic_t >;

   template< unsigned S, unsigned C >
   using static_a = internal::auto_discard_buffer_input< static_t< S, C > >;

   template< typename BufferInput >
   void unit_test_01( BufferInput&& in )
   {
      const auto r = parse< two< 'a' > >( in );
      TAO_PEGTL_TEST_ASSERT( r );
      TAO_PEGTL_TEST_ASSERT( in.buffer_size() == 0 );
      const auto& p = in.current_position();
      TAO_PEGTL_TEST_ASSERT( p.line == 1 );
      TAO_PEGTL_TEST_ASSERT( p.count_in_line == 3 );
   }

   template< typename BufferInput >
   void unit_test_02( BufferInput&& in )
   {
      const auto r = parse< two< 'a' > >( in );
      TAO_PEGTL_TEST_ASSERT( r );
      TAO_PEGTL_TEST_ASSERT( in.buffer_size() == 1 );
      const auto& p = in.current_position();
      TAO_PEGTL_TEST_ASSERT( p.line == 1 );
      TAO_PEGTL_TEST_ASSERT( p.count_in_line == 3 );
   }

   template< typename BufferInput >
   void unit_test_03( BufferInput&& in )
   {
      const auto r = parse< seq< string< 'a', 'a', 'b', 'b' >, discard, string< 'c', 'c', 'd', 'd' > > >( in );
      TAO_PEGTL_TEST_ASSERT( r );
      TAO_PEGTL_TEST_ASSERT( in.buffer_size() == 0 );
      const auto& p = in.current_position();
      TAO_PEGTL_TEST_ASSERT( p.line == 1 );
      TAO_PEGTL_TEST_ASSERT( p.count_in_line == 9 );
   }

   template< typename Rule >
   struct action_06
      : nothing< Rule >
   {};

   template<>
   struct action_06< string< 'a', 'b' > >
   {
      static void apply0() noexcept
      {}
   };

   unsigned count = 0;

   template< typename Rule >
   struct action_07
      : nothing< Rule >
   {};

   template<>
   struct action_07< string< 'a', 'b' > >
   {
      template< typename ActionInput >
      static void apply( const ActionInput& in ) noexcept
      {
         ++count;
         TAO_PEGTL_TEST_ASSERT( in.string() == "ab" );
      }
   };

   template< typename Rule >
   struct action_08
      : nothing< Rule >
   {};

   template<>
   struct action_08< seq< string< 'a', 'b' >, string< 'c', 'd' > > >
   {
      template< typename ActionInput >
      static void apply( const ActionInput& /*unused*/ ) noexcept
      {
         ++count;
      }
   };

   void unit_test()
   {
      unit_test_01( static_t< 8, 1 >( "aax" ) );
      unit_test_01( dynamic_t( 8, 1, "aax" ) );
      unit_test_01( static_a< 8, 1 >( "aax" ) );
      unit_test_01( dynamic_a( 8, 1, "aax" ) );

      unit_test_02( static_t< 8, 4 >( "aax" ) );
      unit_test_02( dynamic_t( 8, 4, "aax" ) );
      unit_test_02( static_a< 8, 4 >( "aax" ) );
      unit_test_02( dynamic_a( 8, 4, "aax" ) );

      unit_test_03( static_t< 8, 4 >( "aabbccdd" ) );
      unit_test_03( dynamic_t( 8, 4, "aabbccdd" ) );
      unit_test_03( static_a< 8, 4 >( "aabbccdd" ) );
      unit_test_03( dynamic_a( 8, 4, "aabbccdd" ) );

      TAO_PEGTL_TEST_THROWS( parse< string< 'a', 'b', 'c', 'd' > >( static_t< 3, 1 >( "abcd" ) ) );
      TAO_PEGTL_TEST_THROWS( parse< string< 'a', 'b', 'c', 'd' > >( dynamic_t( 3, 1, "abcd" ) ) );
      TAO_PEGTL_TEST_THROWS( parse< string< 'a', 'b', 'c', 'd' > >( static_a< 3, 1 >( "abcd" ) ) );
      TAO_PEGTL_TEST_THROWS( parse< string< 'a', 'b', 'c', 'd' > >( dynamic_a( 3, 1, "abcd" ) ) );

      TAO_PEGTL_TEST_THROWS( parse< seq< string< 'a', 'b' >, string< 'c', 'd' > > >( static_t< 3, 1 >( "abcd" ) ) );
      TAO_PEGTL_TEST_THROWS( parse< seq< string< 'a', 'b' >, string< 'c', 'd' > > >( dynamic_t( 3, 1, "abcd" ) ) );
      TAO_PEGTL_TEST_ASSERT( parse< seq< string< 'a', 'b' >, string< 'c', 'd' > > >( static_a< 3, 1 >( "abcd" ) ) );
      TAO_PEGTL_TEST_ASSERT( parse< seq< string< 'a', 'b' >, string< 'c', 'd' > > >( dynamic_a( 3, 1, "abcd" ) ) );

      TAO_PEGTL_TEST_THROWS( parse< seq< string< 'a', 'b' >, string< 'c', 'd' > >, action_06 >( static_t< 3, 1 >( "abcd" ) ) );
      TAO_PEGTL_TEST_THROWS( parse< seq< string< 'a', 'b' >, string< 'c', 'd' > >, action_06 >( dynamic_t( 3, 1, "abcd" ) ) );
      TAO_PEGTL_TEST_ASSERT( parse< seq< string< 'a', 'b' >, string< 'c', 'd' > >, action_06 >( static_a< 3, 1 >( "abcd" ) ) );
      TAO_PEGTL_TEST_ASSERT( parse< seq< string< 'a', 'b' >, string< 'c', 'd' > >, action_06 >( dynamic_a( 3, 1, "abcd" ) ) );

      count = 0;
      TAO_PEGTL_TEST_THROWS( parse< seq< string< 'a', 'b' >, string< 'c', 'd' > >, action_07 >( static_t< 3, 1 >( "abcd" ) ) );
      TAO_PEGTL_TEST_ASSERT( count == 1 );
      TAO_PEGTL_TEST_THROWS( parse< seq< string< 'a', 'b' >, string< 'c', 'd' > >, action_07 >( dynamic_t( 3, 1, "abcd" ) ) );
      TAO_PEGTL_TEST_ASSERT( count == 2 );
      TAO_PEGTL_TEST_ASSERT( parse< seq< string< 'a', 'b' >, string< 'c', 'd' > >, action_07 >( static_a< 3, 1 >( "abcd" ) ) );
      TAO_PEGTL_TEST_ASSERT( count == 3 );
      TAO_PEGTL_TEST_ASSERT( parse< seq< string< 'a', 'b' >, string< 'c', 'd' > >, action_07 >( dynamic_a( 3, 1, "abcd" ) ) );
      TAO_PEGTL_TEST_ASSERT( count == 4 );

      count = 0;
      TAO_PEGTL_TEST_THROWS( parse< seq< string< 'a', 'b' >, string< 'c', 'd' > >, action_08 >( static_t< 3, 1 >( "abcd" ) ) );
      TAO_PEGTL_TEST_ASSERT( count == 0 );
      TAO_PEGTL_TEST_THROWS( parse< seq< string< 'a', 'b' >, string< 'c', 'd' > >, action_08 >( dynamic_t( 3, 1, "abcd" ) ) );
      TAO_PEGTL_TEST_ASSERT( count == 0 );
      TAO_PEGTL_TEST_THROWS( parse< seq< string< 'a', 'b' >, string< 'c', 'd' > >, action_08 >( static_a< 3, 1 >( "abcd" ) ) );
      TAO_PEGTL_TEST_ASSERT( count == 0 );
      TAO_PEGTL_TEST_THROWS( parse< seq< string< 'a', 'b' >, string< 'c', 'd' > >, action_08 >( dynamic_a( 3, 1, "abcd" ) ) );
      TAO_PEGTL_TEST_ASSERT( count == 0 );
   }

}  // namespace tao::pegtl

#include "main.hpp"
