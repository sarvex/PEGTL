// Copyright (c) 2014-2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_PEGTL_INTERNAL_READ_INPUT_HPP
#define TAO_PEGTL_INTERNAL_READ_INPUT_HPP

#include <cstdio>
#include <string>

#include "container_input.hpp"
#include "fake_buffer_input.hpp"
#include "filesystem.hpp"
#include "memory_input.hpp"
#include "read_file.hpp"

namespace tao::pegtl::internal
{
   class read_input
      : public container_input< std::string >
   {
   public:
      explicit read_input( const filesystem::path& path )
         : container_input< std::string >( read_file_impl( path ).read_string() )
      {}

      read_input( std::FILE* file, const filesystem::path& path )
         : container_input< std::string >( read_file_impl( file, path ).read_string() )
      {}
   };

}  // namespace tao::pegtl::internal

#endif
