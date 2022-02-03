// Copyright (c) 2014-2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_PEGTL_INTERNAL_FILE_INPUT_HPP
#define TAO_PEGTL_INTERNAL_FILE_INPUT_HPP

#include "mmap_file.hpp"

#if defined( TAO_PEGTL_MMAP_AVAILABLE )

#include "input_with_begin.hpp"
#include "memory_input.hpp"
#include "mmap_input.hpp"

namespace tao::pegtl::internal
{
   using file_input = mmap_input< input_with_begin< memory_input< char > > >;

}  // namespace tao::pegtl::internal

#else

#include "read_input.hpp"

namespace tao::pegtl::internal
{
   using file_input = read_input;

}  // namespace tao::pegtl::internal

#endif
#endif
