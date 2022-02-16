// Copyright (c) 2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_PEGTL_INPUTS_HPP
#define TAO_PEGTL_INPUTS_HPP

#include <memory>
#include <string>
#include <vector>

#include "ascii.hpp"

#include "internal/inputs.hpp"

#include "internal/count_position.hpp"
#include "internal/text_position.hpp"

#include "internal/cstream_reader.hpp"
#include "internal/cstring_reader.hpp"
#include "internal/istream_reader.hpp"

namespace tao::pegtl
{
   using file_input = internal::file_input;
   // using mmap_input = internal::mmap_input< internal::restartable_input< internal::memory_input< char > > >;

   using memory_input = internal::memory_input< char >;
   // using ???_input = internal::restartable_input< internal::memory_input< char > >;

   using string_input = internal::container_input< std::string >;
   using vector_input = internal::container_input< std::vector< char > >;

   using shared_input = internal::pointer_input< std::shared_ptr< char[] > >;
   using unique_input = internal::pointer_input< std::unique_ptr< char[] > >;

   using mmap_input = internal::line_based_input< lf, internal::mmap_input< internal::restartable_input< internal::memory_input< char > > > >;

   // TODO: What exactly?

   // Buffer inputs only work with eager positions, not restartable eager position.

}  // namespace tao::pegtl

#endif
