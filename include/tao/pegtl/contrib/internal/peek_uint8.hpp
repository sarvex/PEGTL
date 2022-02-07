// Copyright (c) 2018-2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_PEGTL_CONTRIB_INTERNAL_PEEK_UINT8_HPP
#define TAO_PEGTL_CONTRIB_INTERNAL_PEEK_UINT8_HPP

#include <cstdint>

#include "../../internal/peek_copy.hpp"

namespace tao::pegtl::internal
{
   using peek_uint8 = peek_copy< std::uint8_t >;

}  // namespace tao::pegtl::internal

#endif
