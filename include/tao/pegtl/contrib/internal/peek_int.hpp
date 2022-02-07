// Copyright (c) 2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_PEGTL_CONTRIB_INTERNAL_PEEK_INT_HPP
#define TAO_PEGTL_CONTRIB_INTERNAL_PEEK_INT_HPP

#include <cstddef>
#include <cstdint>

#include "endian.hpp"
#include "peek_endian_impl.hpp"

namespace tao::pegtl::internal
{
   using peek_int16_be = peek_endian_impl< std::int16_t, from_be >;
   using peek_int32_be = peek_endian_impl< std::int32_t, from_be >;
   using peek_int64_be = peek_endian_impl< std::int64_t, from_be >;

   using peek_int16_le = peek_endian_impl< std::int16_t, from_le >;
   using peek_int32_le = peek_endian_impl< std::int32_t, from_le >;
   using peek_int64_le = peek_endian_impl< std::int64_t, from_le >;

}  // namespace tao::pegtl::internal

#endif
