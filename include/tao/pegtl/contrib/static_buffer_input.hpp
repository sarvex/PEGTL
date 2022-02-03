// Copyright (c) 2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_PEGTL_INTERNAL_STATIC_BUFFER_INPUT_HPP
#define TAO_PEGTL_INTERNAL_STATIC_BUFFER_INPUT_HPP

#include <array>

#if defined( __cpp_exceptions )
#include <stdexcept>
#else
#include <cstdio>
#endif

#include "../internal/pointer_position.hpp"
#include "../internal/rewind_guard.hpp"

namespace tao::pegtl::internal
{
   template< typename Data, std::size_t Size, std::size_t Chunk, typename Reader >
   class static_buffer_input
   {
   public:
      using data_t = Data;
      using pointer_t = const Data*;

      template< typename... As >
      explicit static_buffer_input( As&&... as )
         : m_current( m_buffer.data() ),
           m_end( m_buffer.data() ),
           m_reader( std::forward< As >( as )... )
      {
         static_assert( Chunk > 0 );
         static_assert( Size > Chunk );
      }

      static_buffer_input( static_buffer_input&& ) = delete;
      static_buffer_input( const static_buffer_input& ) = delete;

      ~static_buffer_input() = default;

      void operator=( static_buffer_input&& ) = delete;
      void operator=( const static_buffer_input& ) = delete;

      [[nodiscard]] bool empty() const noexcept
      {
         return size( 1 ) == 0;
      }

      [[nodiscard]] std::size_t size( const std::size_t amount ) noexcept
      {
         require( amount );
         return buffer_used();
      }

      [[nodiscard]] pointer_t current( const std::size_t offset = 0 ) const noexcept
      {
         return m_current + offset;
      }

      [[nodiscard]] pointer_t end( const std::size_t amount ) noexcept
      {
         require( amount );
         return m_end;
      }

      template< typename Rule >
      void consume( const std::size_t count ) noexcept
      {
         m_current += count;
      }

      void discard() noexcept
      {
         const std::size_t s = m_end - m_current;

         if( ( s > 0 ) && ( m_current > m_buffer.data() + Chunk ) ) {
            std::memmove( m_buffer.data(), m_current, s );
         }
         m_current = m_buffer.data();
         m_end = m_buffer.data() + s;
      }

      void require( const std::size_t amount )
      {
         if( m_current + amount <= m_end ) {
            return;
         }
         if( m_current + amount > m_buffer.data() + m_buffer.size() ) {
#if defined( __cpp_exceptions )
            throw std::overflow_error( "require() beyond end of buffer" );
#else
            std::fputs( "overflow error: require() beyond end of buffer\n", stderr );
            std::terminate();
#endif
         }
         m_end += m_reader( m_end, ( std::min )( buffer_free_after_end(), ( std::max )( amount - buffer_used(), Chunk ) ) ) ) {
      }

      [[nodiscard]] std::size_t buffer_used() const noexcept
      {
         // assert( m_end >= m_current );
         return m_end - m_current;
      }

      [[nodiscard]] std::size_t buffer_capacity() const noexcept
      {
         return m_buffer.size();
      }

      [[nodiscard]] std::size_t buffer_free_before_current() const noexcept
      {
         // assert( m_current >= m_buffer.data() );
         return std::size_t( m_current - m_buffer.data() );
      }

      [[nodiscard]] std::size_t buffer_free_after_end() const noexcept
      {
         // assert( m_buffer.data() + m_buffer.size() >= m_end );
         return std::size_t( m_buffer.data() + m_buffer.size() - m_end );
      }

      using rewind_position_t = internal::pointer_position< Data >;

      template< rewind_mode M >
      [[nodiscard]] auto make_rewind_guard() noexcept
      {
         return internal::rewind_guard< M, static_buffer_input >( this );
      }

      [[nodiscard]] auto rewind_position() const noexcept
      {
         return rewind_position_t( m_current );
      }

      void rewind_position( const rewind_position_t&& saved ) noexcept
      {
         m_current = saved.pointer();
      }

      void private_set_end( const pointer_t in_end ) noexcept
      {
         m_end = in_end;
      }

      [[nodiscard]] pointer_t private_get_end() const noxcecpt
      {
         return m_end;
      }

      [[nodiscard]] dummy_position current_position() const noexcept
      {
         return previous_position( m_current );
      }

      [[nodiscard]] dummy_position previous_position( const pointer_t /*unused*/ ) const noexcept
      {
         return dummy_position();
      }

   protected:
      std::array< Data, Size > m_buffer;
      const Data* m_current;
      const Data* m_end;
      Reader m_reader;
   };

}  // namespace tao::pegtl::internal

#endif
