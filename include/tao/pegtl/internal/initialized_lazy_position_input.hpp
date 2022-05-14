// Copyright (c) 2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_PEGTL_INTERNAL_INITIALIZED_LAZY_POSITION_INPUT_HPP
#define TAO_PEGTL_INTERNAL_INITIALIZED_LAZY_POSITION_INPUT_HPP

#include <utility>

#include "../apply_mode.hpp"
#include "../normal.hpp"
#include "../nothing.hpp"
#include "../rewind_mode.hpp"

#include "forward.hpp"

namespace tao::pegtl::internal
{
   template< typename Position, typename Input >
   class initialized_lazy_position_input
      : public Input
   {
   public:
      using position_t = Position;

      using typename Input::data_t;
      using typename Input::rewind_position_t;

      template< typename... As >
      explicit initialized_lazy_position_input( Position&& p, As&&... as )  // noexcept( auto )
         : Input( std::forward< As >( as )... ),
           m_position( std::move( p ) )
      {}

      template< typename... As >
      explicit initialized_lazy_position_input( const Position& p, As&&... as )  // noexcept( auto )
         : Input( std::forward< As >( as )... ),
           m_position( p )
      {}

      using Input::restart;

      void restart( Position&& p )
      {
         Input::restart();
         m_position = std::move( p );
      }

      void restart( const Position& p )
      {
         Input::restart();
         m_position = p;
      }

      [[nodiscard]] Position current_position() const  // noexcept( auto )
      {
         return previous_position( this->current() );
      }

      [[nodiscard]] Position previous_position( const data_t* previous ) const  // noexcept( auto )
      {
         using input_t = typename input_traits< initialized_lazy_position_input >::lazy_input_scan_t;
         input_t in( m_position, this->begin(), previous );
         (void)normal< typename Position::lazy_rule >::template match< apply_mode::nothing, rewind_mode::optional, nothing, normal >( in );
         return std::move( in.private_position() );
      }

      [[nodiscard]] Position previous_position( const rewind_position_t& previous ) const
      {
         return previous_position( previous.current );
      }

   protected:
      Position m_position;
   };

} // namespace tao::pegtl::internal

#endif
