// Copyright (c) 2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_PEGTL_INTERNAL_DYNAMIC_BUFFER_INPUT_HPP
#define TAO_PEGTL_INTERNAL_DYNAMIC_BUFFER_INPUT_HPP

#include <memory>

#if defined( __cpp_exceptions )
#include <stdexcept>
#else
#include <cstdio>
#endif

#include "../internal/pointer_position.hpp"
#include "../internal/rewind_guard.hpp"

namespace tao::pegtl::internal
{
   template< typename Data, typename Reader >
   class dynamic_buffer_input
   {
   public:
      template< typename... As >
      dynamic_buffer_input( const std::size_t size, const std::size_t chunk, As&&... as )
         : m_size( size ),
           m_chunk( chunk ),
           m_buffer( new Data[ size ] ),
           m_current( m_buffer.get() ),
           m_end( m_buffer.get() ),
           m_reader( std::forward< As >( as )... )
      {
         // assert( chunk > 0 );
         // assert( buffer > chunk );
      }

      dynamic_buffer_input( dynamic_buffer_input&& ) = delete;
      dynamic_buffer_input( const dynamic_buffer_input& ) = delete;

      ~dynamic_buffer_input() = default;

      void operator=( dynamic_buffer_input&& ) = delete;
      void operator=( const dynamic_buffer_input& ) = delete;

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

         if( ( s > 0 ) && ( m_current > m_buffer.get() + Chunk ) ) {
            std::memmove( m_buffer.get(), m_current, s );
         }
         m_current = m_buffer.get();
         m_end = m_buffer.get() + s;
      }

      void require( const std::size_t amount )
      {
         if( m_current + amount <= m_end ) {
            return;
         }
         if( m_current + amount > m_buffer.get() + m_size ) {
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
         return m_size();
      }

      [[nodiscard]] std::size_t buffer_free_before_current() const noexcept
      {
         // assert( m_current >= m_buffer.get() );
         return std::size_t( m_current - m_buffer.get() );
      }

      [[nodiscard]] std::size_t buffer_free_after_end() const noexcept
      {
         // assert( m_buffer.get() + m_size >= m_end );
         return std::size_t( m_buffer.get() + m_size - m_end );
      }

      using rewind_position_t = pointer_position< Data >;

      template< rewind_mode M >
      [[nodiscard]] auto make_rewind_guard() noexcept
      {
         return internal::rewind_guard< M, dynamic_buffer_input >( this );
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

   private:
      const std::size_t m_size;
      const std::size_t m_chunk;
      const std::unique_ptr< Data[] > m_buffer;
      const Data* m_current;
      const Data* m_end;
      Reader m_reader;
   };

}  // namespace tao::pegtl::internal

#endif
