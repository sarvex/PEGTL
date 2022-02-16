// Copyright (c) 2014-2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_PEGTL_INTERNAL_MMAP_INPUT_HPP
#define TAO_PEGTL_INTERNAL_MMAP_INPUT_HPP

#include "filesystem.hpp"
#include "input_traits.hpp"
#include "mmap_file.hpp"

namespace tao::pegtl::internal
{
   template< typename MemoryInput >
   class mmap_input
      : private mmap_file_base,
        public MemoryInput
   {
   public:
      using memory_input_t = MemoryInput;

      explicit mmap_input( const filesystem::path& path )
         : mmap_file_base( path ),
           MemoryInput( data.begin(), data.end() )
      {}
   };

   template< typename MemoryInput >
   struct input_traits< mmap_input< MemoryInput > >
   {
      using memory_input_t = MemoryInput;
   };

}  // namespace tao::pegtl::internal

#endif
