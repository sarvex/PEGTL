// Copyright (c) 2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_PEGTL_INTERNAL_INITIALIZED_POSITION_INPUT_HPP
#define TAO_PEGTL_INTERNAL_INITIALIZED_POSITION_INPUT_HPP

#include <utility>

#include "input_traits.hpp"

namespace tao::pegtl::internal
{
   template< typename Position, typename Input >
   class initialized_position_input
   {
   public:
      using position_t = Position;

      using typename Input::rewind_position_t;

      template< typename... As >
      explicit initialized_position_input( Position&& p, As&&... as )  // noexcept( auto )
         : Input( std::forward< As >( as )... ),
           m_position( std::move( p ) )
      {}

      template< typename... As >
      explicit initialized_position_input( const Position& p, As&&... as )  // noexcept( auto )
         : Input( std::forward< As >( as )... ),
           m_position( p )
      {}

      [[nodiscard]] const Position& current_position() const noexcept
      {
         return m_position;
      }

      [[nodiscard]] Position previous_position( const rewind_position_t& saved ) const
      {
         return Position( saved );
      }

      [[nodiscard]] Position&& private_position() noexcept
      {
         return std::move( m_position );
      }

      [[nodiscard]] const Position& private_position() const noexcept
      {
         return m_position;
      }

   protected:
      Position m_position;
   };

   template< typename Position, typename Input >
   struct input_traits< initialized_position_input< Position, Input > >
   {
      using memory_input_t = typename input_traits< Input >::memory_input_t;
   };

}  // namespace tao::pegtl::internal

#endif
