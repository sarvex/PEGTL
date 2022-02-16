// Copyright (c) 2018-2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#include <tao/pegtl/internal/endian.hpp>

#include "test.hpp"

namespace tao::pegtl
{
   void unit_test()
   {
      TAO_PEGTL_TEST_ASSERT( internal::big_endian::from( std::int8_t( 0x7a ) ) == std::int8_t( 0x7a ) );
      TAO_PEGTL_TEST_ASSERT( internal::big_endian::from( std::uint8_t( 0x7a ) ) == std::uint8_t( 0x7a ) );
      TAO_PEGTL_TEST_ASSERT( internal::little_endian::from( std::int8_t( 0x7a ) ) == std::int8_t( 0x7a ) );
      TAO_PEGTL_TEST_ASSERT( internal::little_endian::from( std::uint8_t( 0x7a ) ) == std::uint8_t( 0x7a ) );

      TAO_PEGTL_TEST_ASSERT( internal::native_endian::from( std::int16_t( 0x7a39 ) ) == std::int16_t( 0x7a39 ) );
      TAO_PEGTL_TEST_ASSERT( internal::native_endian::from( std::uint16_t( 0x7a39 ) ) == std::uint16_t( 0x7a39 ) );
      TAO_PEGTL_TEST_ASSERT( internal::other_endian::from( std::int16_t( 0x7a39 ) ) == std::int16_t( 0x397a ) );
      TAO_PEGTL_TEST_ASSERT( internal::other_endian::from( std::uint16_t( 0x7a39 ) ) == std::uint16_t( 0x397a ) );

      TAO_PEGTL_TEST_ASSERT( internal::native_endian::from( std::int32_t( 0x7a391f2b ) ) == std::int32_t( 0x7a391f2b ) );
      TAO_PEGTL_TEST_ASSERT( internal::native_endian::from( std::uint32_t( 0x7a391f2b ) ) == std::uint32_t( 0x7a391f2b ) );
      TAO_PEGTL_TEST_ASSERT( internal::other_endian::from( std::int32_t( 0x7a391f2b ) ) == std::int32_t( 0x2b1f397a ) );
      TAO_PEGTL_TEST_ASSERT( internal::other_endian::from( std::uint32_t( 0x7a391f2b ) ) == std::uint32_t( 0x2b1f397a ) );

      TAO_PEGTL_TEST_ASSERT( internal::native_endian::from( std::int64_t( 0x7a391f2b33445567 ) ) == std::int64_t( 0x7a391f2b33445567 ) );
      TAO_PEGTL_TEST_ASSERT( internal::native_endian::from( std::uint64_t( 0x7a391f2b33445567 ) ) == std::uint64_t( 0x7a391f2b33445567 ) );
      TAO_PEGTL_TEST_ASSERT( internal::other_endian::from( std::int64_t( 0x7a391f2b33445567 ) ) == std::int64_t( 0x675544332b1f397a ) );
      TAO_PEGTL_TEST_ASSERT( internal::other_endian::from( std::uint64_t( 0x7a391f2b33445567 ) ) == std::uint64_t( 0x675544332b1f397a ) );
   }

}  // namespace tao::pegtl

#include "main.hpp"
