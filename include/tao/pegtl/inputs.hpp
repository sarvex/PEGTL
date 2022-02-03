// Copyright (c) 2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_PEGTL_INPUTS_HPP
#define TAO_PEGTL_INPUTS_HPP

#include <memory>
#include <string>
#include <vector>

#include "ascii.hpp"
#include "rules.hpp"

#include "internal/container_input.hpp"
#include "internal/file_input.hpp"
#include "internal/memory_input.hpp"
#include "internal/pointer_input.hpp"
#include "internal/read_input.hpp"

#include "internal/input_with_begin.hpp"
#include "internal/input_with_eol.hpp"

#include "internal/byte_position.hpp"
#include "internal/text_position.hpp"

#include "internal/defaulted_lazy_position_input.hpp"
#include "internal/eager_position_input.hpp"
#include "internal/initialized_lazy_position_input.hpp"

namespace tao::pegtl
{
   using file_input = internal::file_input;
   // using mmap_input = internal::mmap_input< internal::input_with_begin< internal::memory_input< char > > >;

   using memory_input = internal::memory_input< char >;
   // using ???_input = internal::input_with_begin< internal::memory_input< char > >;

   using string_input = internal::container_input< std::string >;
   using vector_input = internal::container_input< std::vector< char > >;

   using shared_input = internal::pointer_input< std::shared_ptr< char[] > >;
   using unique_input = internal::pointer_input< std::unique_ptr< char[] > >;

   using mmap_input = internal::input_with_eol< lf, internal::mmap_input< internal::input_with_begin< internal::memory_input< char > > > >;

   // TODO: What exactly?

}  // namespace tao::pegtl

#endif
