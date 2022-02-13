// Copyright (c) 2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_PEGTL_INTERNAL_COMMON_BUFFER_INPUT_HPP
#define TAO_PEGTL_INTERNAL_COMMON_BUFFER_INPUT_HPP

#include <algorithm>
#include <cstring>
#include <utility>

#if defined( __cpp_exceptions )
#include <exception>
#include <stdexcept>
#else
#include <cstdio>
#endif

#include "dummy_position.hpp"
#include "memory_input.hpp"
#include "pointer_position.hpp"
#include "rewind_guard.hpp"

namespace tao::pegtl::internal
{
   template< typename Base >
   class common_buffer_input
      : public Base
   {
   public:
      using data_t = typename Base::data_t;
      using pointer_t = typename Base::pointer_t;

      using memory_input_t = memory_input< data_t >;

      template< typename... As >
      common_buffer_input( As&&... as )
         : Base( std::forward< As >( as )... ),
           m_current( this->mutable_begin() ),
           m_end( this->mutable_begin() )
      {
         // assert( buffer_chunk_size() > 0 );
         // assert( buffer_chunk_size() < buffer_capacity() );
      }

      common_buffer_input( common_buffer_input&& ) = delete;
      common_buffer_input( const common_buffer_input& ) = delete;

      ~common_buffer_input() = default;

      void operator=( common_buffer_input&& ) = delete;
      void operator=( const common_buffer_input& ) = delete;

      [[nodiscard]] bool empty() const
      {
         return size( 1 ) == 0;
      }

      [[nodiscard]] std::size_t size( const std::size_t amount )
      {
         require( amount );
         return this->buffer_size();
      }

      [[nodiscard]] std::size_t size( const std::size_t minimum, const std::size_t maximum )
      {
         require( maximum );
         buffer_check_size( minimum );
         return this->buffer_size();
      }

      [[nodiscard]] pointer_t current( const std::size_t offset = 0 ) const noexcept
      {
         return m_current + offset;
      }

      // [[nodiscard]] pointer_t end( const std::size_t amount );
      // [[nodiscard]] pointer_t end( const std::size_t minimum, const std::size_t maximum );

      template< typename Rule >
      void consume( const std::size_t count ) noexcept
      {
         m_current += count;
      }

      void discard() noexcept
      {
         const std::size_t s = m_end - m_current;

         if( ( s > 0 ) && ( m_current > this->buffer_begin() + this->buffer_chunk_size() ) ) {
            std::memmove( this->mutable_begin(), m_current, s );
         }
         m_current = this->mutable_begin();
         m_end = m_current + s;
      }

      void require( const std::size_t amount )
      {
         if( m_current + amount <= m_end ) {
            return;
         }
         if( m_current + amount > this->buffer_begin() + this->buffer_capacity() ) {
#if defined( __cpp_exceptions )
            throw std::overflow_error( "require() beyond end of buffer" );
#else
            std::fputs( "overflow error: require() beyond end of buffer\n", stderr );
            std::terminate();
#endif
         }
         m_end += this->m_reader( m_end, ( std::min )( buffer_free_after_end(), ( std::max )( amount - buffer_size(), this->buffer_chunk_size() ) ) );
      }

      void buffer_check_size( const std::size_t amount )
      {
         if( this->buffer_size() < amount ) {
#if defined( __cpp_exceptions )
            throw std::overflow_error( "require() beyond end of reader" );
#else
            std::fputs( "overflow error: require() beyond end of reader\n", stderr );
            std::terminate();
#endif
         }
      }

      [[nodiscard]] std::size_t buffer_size() const noexcept
      {
         // assert( m_end >= m_current );
         return m_end - m_current;
      }

      [[nodiscard]] std::size_t buffer_free_before_current() const noexcept
      {
         // assert( m_current >= this->buffer_begin() );
         return std::size_t( m_current - this->buffer_begin() );
      }

      [[nodiscard]] std::size_t buffer_free_after_end() const noexcept
      {
         // assert( this->buffer_begin() + m_size >= m_end );
         return std::size_t( this->buffer_begin() + this->buffer_capacity() - m_end );
      }

      using rewind_position_t = pointer_position< data_t >;

      template< rewind_mode M >
      [[nodiscard]] auto make_rewind_guard() noexcept
      {
         return internal::rewind_guard< M, common_buffer_input >( this );
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

      void private_set_current( const pointer_t in_current ) noexcept
      {
         m_current = const_cast< data_t* >( in_current );
      }

      [[nodiscard]] pointer_t private_get_end() const noexcept
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
      data_t* m_current;
      data_t* m_end;

   };

}  // namespace tao::pegtl::internal

#endif
