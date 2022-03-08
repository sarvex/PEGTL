// Copyright (c) 2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_PEGTL_INTERNAL_INPUT_WITH_SOURCE_HPP
#define TAO_PEGTL_INTERNAL_INPUT_WITH_SOURCE_HPP

#include <type_traits>
#include <utility>

#include "position_with_source.hpp"

namespace tao::pegtl::internal
{
   template< typename Source, typename Input >
   struct [[nodiscard]] input_with_source
      : Input
   {
      Source source;

      using typename Input::data_t;
      using typename Input::rewind_position_t;

      template< typename S, typename... As >
      explicit input_with_source( S&& s, As&&... as )
         : Input( std::forward< As >( as )... ),
           source( std::forward< S >( s ) )
      {}

      using position_t = position_with_source< Source, std::decay_t< decltype( std::declval< Input >().current_position() ) > >;

      [[nodiscard]] position_t current_position() const
      {
         return position_t( source, Input::current_position() );
      }

      [[nodiscard]] position_t previous_position( const data_t* where ) const
      {
         return position_t( source, Input::previous_position( where ) );
      }

      [[nodiscard]] position_t previous_position( const rewind_position_t& saved ) const
      {
         return position_t( source, Input::previous_position( saved ) );
      }
   };

}  // namespace tao::pegtl::internal

#endif
