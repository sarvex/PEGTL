// Copyright (c) 2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_PEGTL_POSITIONS_HPP
#define TAO_PEGTL_POSITIONS_HPP

#include <cstddef>

#include "internal/count_position.hpp"
#include "internal/pointer_position.hpp"

#include "internal/careless_text_position.hpp"
#include "internal/paranoid_text_position.hpp"
#include "internal/selected_text_position.hpp"

#include "internal/careless_text_count_position.hpp"
#include "internal/paranoid_text_count_position.hpp"
#include "internal/selected_text_count_position.hpp"

#include "internal/position_with_source.hpp"
#include "internal/source_without_position.hpp"

namespace tao::pegtl
{
   using count_position = internal::count_position< std::size_t >;
   using pointer_position = internal::pointer_position< const char >;

   using careless_text_position = internal::careless_text_position< std::size_t >;
   template< typename Eol >
   using paranoid_text_position = internal::paranoid_text_position< Eol, std::size_t >;
   template< typename Eol >
   using selected_text_position = internal::selected_text_position< Eol, std::size_t >;

   using careless_text_count_position = internal::careless_text_count_position< std::size_t >;
   template< typename Eol >
   using paranoid_text_count_position = internal::paranoid_text_count_position< Eol, std::size_t >;
   template< typename Eol >
   using selected_text_count_position = internal::selected_text_count_position< Eol, std::size_t >;

}  // namespace tao::pegtl

#endif
