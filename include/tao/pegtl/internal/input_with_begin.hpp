// Copyright (c) 2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_PEGTL_INTERNAL_INPUT_WITH_BEGIN_HPP
#define TAO_PEGTL_INTERNAL_INPUT_WITH_BEGIN_HPP

#include "byte_position.hpp"

namespace tao::pegtl::internal
{
   template< typename Input >
   class input_with_begin
      : public Input
   {
   public:
      using data_t = typename Input::data_t;
      using pointer_t = typename Input::pointer_t;
      using memory_input_t = typename Input::memory_input_t;

      template< typename... As >
      explicit input_with_begin( As&&... as ) noexcept( noexcept( Input( std::forward< As >( as )... ) ) )
         : Input( std::forward< As >( as )... ),
           m_begin( this->current() )
      {
         // static_assert( Input is NOT any kind of buffer input )
         // static_assert( Input does NOT already have begin() or restart() )
         // static_assert( Input only returns a pointer_position wherefore current_position() here is an improvement )
      }

      [[nodiscard]] pointer_t begin() const noexcept
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

      [[nodiscard]] auto previous_position( const pointer_t previous ) const noexcept
      {
         return byte_position( previous - m_begin );
      }

   protected:
      pointer_t m_begin;
   };

}  // namespace tao::pegtl::internal

#endif
