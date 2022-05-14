// Copyright (c) 2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_PEGTL_INTERNAL_POINTER_INPUT_HPP
#define TAO_PEGTL_INTERNAL_POINTER_INPUT_HPP

#include <cstddef>
#include <type_traits>
#include <utility>

#include "count_position.hpp"
#include "memory_input.hpp"
#include "pointer_position.hpp"
#include "rewind_guard.hpp"

namespace tao::pegtl::internal
{
   template< typename Pointer >
   class pointer_input
   {
   public:
      using data_t = std::decay_t< typename Pointer::element_type >;

      pointer_input( Pointer&& in_pointer, const std::size_t in_size )
         : m_pointer( std::move( in_pointer ) ),
           m_current( m_pointer.get() ),
           m_end( m_current + in_size )
      {}

      pointer_input( const Pointer& in_pointer, const std::size_t in_size )
         : m_pointer( in_pointer ),
           m_current( m_pointer.get() ),
           m_end( m_current + in_size )
      {}

      [[nodiscard]] bool empty() const noexcept
      {
         return size() == 0;
      }

      [[nodiscard]] std::size_t size() const noexcept
      {
         return end() - m_current;
      }

      [[nodiscard]] const data_t* begin() const noexcept
      {
         return m_pointer.get();
      }

      [[nodiscard]] const data_t* current( const std::size_t offset = 0 ) const noexcept
      {
         return m_current + offset;
      }

      [[nodiscard]] const data_t* end() const noexcept
      {
         return m_end;
      }

      void restart() noexcept
      {
         private_set_current( begin() );
      }

      template< typename Rule >
      void consume( const std::size_t count ) noexcept
      {
         m_current += count;
      }

      using rewind_position_t = pointer_position< data_t >;

      template< rewind_mode M >
      [[nodiscard]] auto make_rewind_guard() noexcept
      {
         return rewind_guard< M, pointer_input >( this );
      }

      [[nodiscard]] auto rewind_position() const noexcept
      {
         return rewind_position_t( m_current );
      }

      void rewind_position( const rewind_position_t& saved ) noexcept
      {
         m_current = saved.pointer();
      }

      void private_set_current( const data_t* in_current ) noexcept
      {
         m_current = in_current;  // Used by rematch.
      }

      [[nodiscard]] auto current_position() const noexcept
      {
         return previous_position( m_current );
      }

      [[nodiscard]] auto previous_position( const data_t* previous ) const noexcept
      {
         return count_position< std::size_t >( previous - begin() );
      }

      [[nodiscard]] auto previous_position( const rewind_position_t& previous ) const noexcept
      {
         return previous_position( previous.current );
      }

      [[nodiscard]] Pointer&& pointer() && noexcept
      {
         return std::move( m_pointer );
      }

      [[nodiscard]] const Pointer& pointer() const& noexcept
      {
         return m_pointer;
      }

   protected:
      Pointer m_pointer;

      const data_t* m_current;
      const data_t* m_end;
   };

}  // namespace tao::pegtl::internal

#endif
