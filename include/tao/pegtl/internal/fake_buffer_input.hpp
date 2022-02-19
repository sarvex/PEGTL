// Copyright (c) 2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_PEGTL_INTERNAL_FAKE_BUFFER_INPUT_HPP
#define TAO_PEGTL_INTERNAL_FAKE_BUFFER_INPUT_HPP

#include <cstddef>

#include "input_traits.hpp"

namespace tao::pegtl::internal
{
   template< typename Input >
   class fake_buffer_input
      : public Input
   {
   public:
      using typename Input::data_t;
      // using typename Input::rewind_pointer_t;

      using Input::Input;

      [[nodiscard]] std::size_t size( const std::size_t /*unused*/ ) noexcept( noexcept( Input::size() ) )
      {
         return Input::size();
      }

      [[nodiscard]] std::size_t size( const std::size_t /*unused*/, const std::size_t /*unused*/ ) noexcept( noexcept( Input::size() ) )
      {
         return Input::size();
      }

      // [[nodiscard]] const data_t* end( const std::size_t amount );
      // [[nodiscard]] const data_t* end( const std::size_t minimum, const std::size_t maximum );

      void require( const std::size_t /*unused*/ ) noexcept
      {}

      void discard() noexcept
      {}

      // The buffer_foo() member functions were and are only for actual buffer inputs.
   };

   template< typename Input >
   struct input_traits< fake_buffer_input< Input > >
   {
      using memory_input_t = fake_buffer_input< typename input_traits< Input >::memory_input_t >;
   };

}  // namespace tao::pegtl

#endif
