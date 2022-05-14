// Copyright (c) 2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_PEGTL_INTERNAL_INPUT_WITH_FILENAME_HPP
#define TAO_PEGTL_INTERNAL_INPUT_WITH_FILENAME_HPP

#include <type_traits>
#include <utility>

#include "filesystem.hpp"
#include "position_with_source.hpp"

namespace tao::pegtl::internal
{
   template< typename Input >
   struct input_with_filename
      : Input
   {
      filesystem::path source;

      using typename Input::data_t;
      using typename Input::rewind_position_t;

      explicit input_with_filename( filesystem::path&& path )
         : Input( static_cast< const filesystem::path& >( path ) ),
           source( std::move( path ) )
      {}

      explicit input_with_filename( const filesystem::path& path )
         : Input( path ),
           source( path )
      {}

      using position_t = position_with_source< filesystem::path, std::decay_t< decltype( std::declval< Input >().current_position() ) > >;

      [[nodiscard]] position_t current_position() const
      {
         return position_t( source, Input::current_position() );
      }

      [[nodiscard]] position_t previous_position( const data_t* previous ) const
      {
         return position_t( source, Input::previous_position( previous ) );
      }

      [[nodiscard]] position_t previous_position( const rewind_position_t& previous ) const
      {
         return position_t( source, Input::previous_position( previous ) );
      }
   };

}  // namespace tao::pegtl::internal

#endif
