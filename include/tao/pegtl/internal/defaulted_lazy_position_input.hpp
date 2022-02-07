// Copyright (c) 2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_PEGTL_INTERNAL_DEFAULTED_LAZY_POSITION_INPUT_HPP
#define TAO_PEGTL_INTERNAL_DEFAULTED_LAZY_POSITION_INPUT_HPP

#include <utility>

#include "../apply_mode.hpp"
#include "../normal.hpp"
#include "../nothing.hpp"
#include "../rewind_mode.hpp"

#include "defaulted_eager_position_input.hpp"

namespace tao::pegtl::internal
{
   template< typename Position, typename Input >
   class defaulted_lazy_position_input
      : public Input
   {
   public:
      using data_t = typename Input::data_t;
      using pointer_t = typename Input::pointer_t;
      using position_t = Position;
      using rewind_position_t = typename Input::rewind_position_t;
      //      using memory_input_t = typename Input::memory_input_t;

      using Input::Input;

      [[nodiscard]] Position current_position() const  // noexcept( auto )
      {
         return previous_position( this->current() );
      }

      [[nodiscard]] Position previous_position( const pointer_t where ) const  // noexcept( auto )
      {
         defaulted_eager_position_input< Position, typename Input::memory_input_t >in( this->begin(), where );
         (void)normal< typename Position::lazy_rule >::template match< apply_mode::nothing, rewind_mode::dontcare, nothing, normal >( in );
         return std::move( in.private_position() );
      }

      [[nodiscard]] Position previous_position( const rewind_position_t& saved ) const
      {
         return previous_position( saved.current );
      }
   };

} // namespace tao::pegtl::internal

#endif