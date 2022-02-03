// Copyright (c) 2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_PEGTL_INTERNAL_MMAP_FILE_HPP
#define TAO_PEGTL_INTERNAL_MMAP_FILE_HPP

#if defined( __unix__ ) || ( defined( __APPLE__ ) && defined( __MACH__ ) )
#include <unistd.h>  // Required for _POSIX_MAPPED_FILES
#endif

#if defined( _POSIX_MAPPED_FILES )
#include "mmap_file_posix.hpp"
#define TAO_PEGTL_MMAP_AVAILABLE 1
#elif defined( _WIN32 )
#include "mmap_file_win32.hpp"
#define TAO_PEGTL_MMAP_AVAILABLE 1
#else
#undef TAO_PEGTL_MMAP_AVAILABLE
#endif

#if defined( TAO_PEGTL_MMAP_AVAILABLE )

#include "filesystem.hpp"

namespace tao::pegtl::internal
{
   struct mmap_file_base
   {
      const mmap_file_impl data;

      explicit mmap_file_base( const internal::filesystem::path& path )
         : data( path )
      {}

      mmap_file_base( const mmap_file_base& ) = delete;
      mmap_file_base( mmap_file_base&& ) = delete;

      ~mmap_file_base() = default;

      mmap_file_base& operator=( const mmap_file_base& ) = delete;
      mmap_file_base& operator=( mmap_file_base&& ) = delete;
   };

}  // namespace tao::pegtl::internal

#endif
#endif
