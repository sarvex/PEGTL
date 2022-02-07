// Copyright (c) 2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_PEGTL_POSITIONS_HPP
#define TAO_PEGTL_POSITIONS_HPP

#include <cstddef>

#include "internal/count_position.hpp"
#include "internal/pointer_position.hpp"
#include "internal/text_count_position.hpp"
#include "internal/text_position.hpp"

namespace tao::pegtl
{
   using count_position = internal::count_position< std::size_t >;
   using pointer_position = internal::pointer_position< const char >;
   using text_count_position = internal::text_count_position< std::size_t >;
   using text_position = internal::text_position< std::size_t >;

}  // namespace tao::pegtl

#endif
