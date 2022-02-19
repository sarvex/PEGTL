// Copyright (c) 2020-2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#include "test.hpp"

namespace tao::pegtl
{
   using grammar = seq< string< 'a', 'b', 'c' >, eof >;

   using inner_input_t = internal::fake_buffer_input< internal::line_based_input< lf, internal::restartable_input< internal::memory_input< char > > > >;

   void test_memory()
   {
      const std::string data = "abc";
      inner_input_t in( data.data(), data.size() );
      {
         const bool success = parse< grammar >( in );
         TAO_PEGTL_TEST_ASSERT( success );
      }
      in.restart();
      {
         const bool success = parse< grammar >( in );
         TAO_PEGTL_TEST_ASSERT( success );
      }
   }

   template< typename Input >
   void test_defaulted()
   {
      const std::string data = "abc";
      Input in( data.data(), data.size() );
      {
         const bool success = parse< grammar >( in );
         const auto position = in.current_position();
         TAO_PEGTL_TEST_ASSERT( success );
         TAO_PEGTL_TEST_ASSERT( position.line == 1 );
         TAO_PEGTL_TEST_ASSERT( position.count_in_line == 4 );
      }
      in.restart();
      {
         const bool success = parse< grammar >( in );
         const auto position = in.current_position();
         TAO_PEGTL_TEST_ASSERT( success );
         TAO_PEGTL_TEST_ASSERT( position.line == 1 );
         TAO_PEGTL_TEST_ASSERT( position.count_in_line == 4 );
      }
   }

   template< typename Input >
   void test_initialized()
   {
      const std::string data = "abc";
      const internal::careless_text_position< unsigned > pos( 50, 60 );
      Input in( pos, data.data(), data.size() );
      {
         const bool success = parse< grammar >( in );
         const auto position = in.current_position();
         TAO_PEGTL_TEST_ASSERT( success );
         TAO_PEGTL_TEST_ASSERT( position.line == 50 );
         TAO_PEGTL_TEST_ASSERT( position.count_in_line == 63 );
      }
      in.restart();
      {
         const bool success = parse< grammar >( in );
         const auto position = in.current_position();
         TAO_PEGTL_TEST_ASSERT( success );
         TAO_PEGTL_TEST_ASSERT( position.line == 50 );
         TAO_PEGTL_TEST_ASSERT( position.count_in_line == 63 );
      }
   }

   void unit_test()
   {
      test_memory();
      test_defaulted< internal::defaulted_lazy_position_input< internal::careless_text_position< unsigned >, inner_input_t > >();
      test_defaulted< internal::defaulted_eager_position_input< internal::careless_text_position< unsigned >, inner_input_t > >();
      test_initialized< internal::initialized_lazy_position_input< internal::careless_text_position< unsigned >, inner_input_t > >();
      test_initialized< internal::initialized_restartable_eager_position_input< internal::careless_text_position< unsigned >, inner_input_t > >();
   }

}  // namespace tao::pegtl

#include "main.hpp"
