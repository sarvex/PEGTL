// Copyright (c) 2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#include <tao/pegtl/internal/has_current_position.hpp>

#include "test.hpp"

namespace tao::pegtl
{
   void unit_test()
   {
      static_assert( internal::has_current_position< internal::memory_input< char > > );
      static_assert( !internal::has_current_position< internal::count_position< std::size_t > > );
   }

}  // namespace tao::pegtl

#include "main.hpp"
