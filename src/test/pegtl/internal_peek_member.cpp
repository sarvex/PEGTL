// Copyright (c) 2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#include <type_traits>

#include <tao/pegtl/internal/peek_member.hpp>

#include "test.hpp"

namespace tao::pegtl
{
   struct token_01
   {
      int i = 42;
   };

   void unit_test_01()
   {
      token_01 t;
      internal::fake_buffer_input< internal::memory_input< token_01 > > in( &t, 1 );
      const auto a = internal::peek_member< &token_01::i >::peek( in );
      static_assert( std::is_same_v< decltype( a ), const internal::data_and_size< int, std::uint8_t > > );
      TAO_PEGTL_TEST_ASSERT( a.data() == 42 );
   }

   int int_02 = 43;

   struct token_02
   {
      int* i = &int_02;
   };

   void unit_test_02()
   {
      token_02 t;
      internal::fake_buffer_input< internal::memory_input< token_02 > > in( &t, 1 );
      const auto a = internal::peek_member< &token_02::i >::peek( in );
      static_assert( std::is_same_v< decltype( a ), const internal::data_and_size< const int*, std::uint8_t > > );
      TAO_PEGTL_TEST_ASSERT( a.data() == 43 );
   }

   int int_03 = 44;

   struct token_03
   {
      const int* i = &int_03;
   };

   void unit_test_03()
   {
      token_03 t;
      internal::fake_buffer_input< internal::memory_input< token_03 > > in( &t, 1 );
      const auto a = internal::peek_member< &token_03::i >::peek( in );
      static_assert( std::is_same_v< decltype( a ), const internal::data_and_size< const int*, std::uint8_t > > );
      TAO_PEGTL_TEST_ASSERT( a.data() == 44 );
   }

   void unit_test()
   {
      unit_test_01();
      unit_test_02();
      unit_test_03();
   }

}  // namespace tao::pegtl

#include "main.hpp"
