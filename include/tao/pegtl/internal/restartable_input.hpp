// Copyright (c) 2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_PEGTL_INTERNAL_RESTARTABLE_INPUT_HPP
#define TAO_PEGTL_INTERNAL_RESTARTABLE_INPUT_HPP

#include "count_position.hpp"
#include "input_traits.hpp"

namespace tao::pegtl::internal
{
   template< typename Input >
   class restartable_input
      : public Input
   {
   public:
      using typename Input::data_t;
      using typename Input::rewind_position_t;

      template< typename... As >
      explicit restartable_input( As&&... as ) noexcept( noexcept( Input( std::forward< As >( as )... ) ) )
         : Input( std::forward< As >( as )... ),
           m_begin( this->current() )
      {
         // static_assert( Input is NOT any kind of buffer input )
         // static_assert( Input does NOT already have begin() or restart() )
         // static_assert( Input only returns a pointer_position wherefore current_position() here is an improvement )
      }

      [[nodiscard]] const data_t* begin() const noexcept
      {
         return m_begin;
      }

      void restart() noexcept
      {
         this->private_set_current( m_begin );
      }

      [[nodiscard]] auto current_position() const noexcept
      {
         return previous_position( this->current() );
      }

      [[nodiscard]] auto previous_position( const data_t* previous ) const noexcept
      {
         return count_position( previous - m_begin );
      }

      [[nodiscard]] auto previous_position( const rewind_position_t previous ) const noexcept
      {
         return previous_position( previous.current );
      }

   protected:
      const data_t* m_begin;
   };

   template< typename Input >
   struct input_traits< restartable_input< Input > >
   {
      using memory_input_t = typename input_traits< Input >::memory_input_t;
   };

}  // namespace tao::pegtl::internal

#endif
