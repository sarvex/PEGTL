// Copyright (c) 2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_PEGTL_INTERNAL_CONTAINER_INPUT_HPP
#define TAO_PEGTL_INTERNAL_CONTAINER_INPUT_HPP

#include <cstddef>
#include <initializer_list>
#include <utility>

#include "count_position.hpp"
#include "memory_input.hpp"
#include "pointer_position.hpp"
#include "rewind_guard.hpp"

namespace tao::pegtl::internal
{
   template< typename Container >
   class container_input
   {
   public:
      using data_t = typename Container::value_type;
      using pointer_t = const data_t*;
      using memory_input_t = memory_input< data_t >;

      container_input( data_t* in_begin, data_t* in_end )
         : m_container( in_begin, in_end ),
           m_current( m_container.data() )
      {}

      container_input( data_t* in_begin, const std::size_t in_size )
         : container_input( in_begin, in_begin + in_size )
      {}

      container_input( Container&& in_data )
         : m_container( std::move( in_data ) ),
           m_current( m_container.data() )
      {}

      container_input( const Container& in_data )
         : m_container( in_data ),
           m_current( m_container.data() )
      {}

      container_input( std::initializer_list< data_t > in_data )
         : m_container( in_data ),
           m_current( m_container.data() )
      {}

      [[nodiscard]] bool empty() const noexcept
      {
         return size( 1 ) == 0;
      }

      [[nodiscard]] std::size_t size( const std::size_t /*unused*/ = 0 ) const noexcept
      {
         return end() - m_current;
      }

      [[nodiscard]] pointer_t begin() const noexcept
      {
         return m_container.data();
      }

      [[nodiscard]] pointer_t current( const std::size_t offset = 0 ) const noexcept
      {
         return m_current + offset;
      }

      [[nodiscard]] pointer_t end( const std::size_t /*unused*/ = 0 ) const noexcept
      {
         return m_container.data() + m_container.size();
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
         return rewind_guard< M, container_input >( this );
      }

      [[nodiscard]] auto rewind_position() const noexcept
      {
         return rewind_position_t( m_current );
      }

      void rewind_position( const rewind_position_t& saved ) noexcept
      {
         m_current = saved.current;
      }

      void private_set_current( const pointer_t in_current ) noexcept
      {
         m_current = in_current;
      }

      [[nodiscard]] auto current_position() const noexcept
      {
         return previous_position( m_current );
      }

      [[nodiscard]] auto previous_position( const pointer_t previous ) const noexcept
      {
         return count_position< std::size_t >( previous - begin() );
      }

      [[nodiscard]] Container&& container() && noexcept
      {
         return std::move( m_container );
      }

      [[nodiscard]] const Container& container() const& noexcept
      {
         return m_container;
      }

   protected:
      Container m_container;
      pointer_t m_current;
   };

}  // namespace tao::pegtl::internal

#endif
