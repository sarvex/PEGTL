// Copyright (c) 2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_PEGTL_INTERNAL_AUTO_DISCARD_BUFFER_INPUT_HPP
#define TAO_PEGTL_INTERNAL_AUTO_DISCARD_BUFFER_INPUT_HPP

#include <cstddef>
#include <utility>

#include "rewind_cancel_guard.hpp"

namespace tao::pegtl::internal
{
   template< typename BufferInput >
   class auto_discard_buffer_input
      : public BufferInput
   {
   public:
      using BufferInput::BufferInput;

      template< typename Rule >
      void consume( const std::size_t count ) noexcept
      {
         BufferInput::template consume< Rule >( count );
         automatic_discard();
      }

      using rewind_position_t = typename BufferInput::rewind_position_t;

      template< rewind_mode M >
      [[nodiscard]] auto make_rewind_guard() noexcept
      {
         return rewind_cancel_guard< M, auto_discard_buffer_input >( this );
      }

      [[nodiscard]] auto rewind_position() noexcept
      {
         ++m_saved_rewinds;
         return BufferInput::rewind_position();
      }

      void rewind_position( rewind_position_t&& saved ) noexcept
      {
         --m_saved_rewinds;
         BufferInput::rewind_position( std::move( saved ) );
      }

      void cancel_position( const rewind_position_t&& /*unused*/ ) noexcept
      {
         --m_saved_rewinds;
         automatic_discard();
      }

      void automatic_discard()
      {
         if( m_saved_rewinds == 0 ) {
            this->discard();
         }
      }

   protected:
      std::size_t m_saved_rewinds = 0;  // TODO? mutable w/rewind_position() const noexcept
   };

}  // namespace tao::pegtl::internal

#endif
