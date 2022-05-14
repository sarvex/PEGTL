// Copyright (c) 2021-2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_PEGTL_INTERNAL_MEMORY_INPUT_HPP
#define TAO_PEGTL_INTERNAL_MEMORY_INPUT_HPP

#include <array>
#include <cstddef>
#include <string>
#include <string_view>
#include <type_traits>

#include "pointer_position.hpp"
#include "rewind_guard.hpp"

namespace tao::pegtl::internal
{
   template< typename Data >
   class memory_input
   {
   public:
      using data_t = Data;

      memory_input( const Data* in_begin, const Data* in_end ) noexcept
         : m_current( in_begin ),
           m_end( in_end )
      {}

      memory_input( const Data* in_begin, const std::size_t in_size ) noexcept
         : memory_input( in_begin, in_begin + in_size )
      {}

      memory_input( const std::string&& ) = delete;

      explicit memory_input( const std::string& in_view ) noexcept
         : memory_input( in_view.data(), in_view.size() )
      {}

      explicit memory_input( const std::string_view in_view ) noexcept
         : memory_input( in_view.data(), in_view.size() )
      {}

      template< std::size_t N >
      explicit memory_input( const char( &in_literal )[ N ] ) noexcept
         : memory_input( in_literal, N - 1 )
      {
         static_assert( std::is_same_v< Data, char > );
      }

      template< std::size_t Size >
      explicit memory_input( const std::array< Data, Size >& in_array ) noexcept
         : memory_input( in_array.data(), in_array.size() )
      {}

      [[nodiscard]] bool empty() const noexcept
      {
         return size() == 0;
      }

      [[nodiscard]] std::size_t size() const noexcept
      {
         return m_end - m_current;
      }

      [[nodiscard]] const Data* current( const std::size_t offset = 0 ) const noexcept
      {
         return m_current + offset;
      }

      [[nodiscard]] const Data* end() const noexcept
      {
         return m_end;
      }

      template< typename Rule >
      void consume( const std::size_t count ) noexcept
      {
         m_current += count;
      }

      using rewind_position_t = pointer_position< Data >;

      template< rewind_mode M >
      [[nodiscard]] auto make_rewind_guard() noexcept
      {
         return rewind_guard< M, memory_input >( this );
      }

      [[nodiscard]] auto rewind_position() const noexcept
      {
         return rewind_position_t( m_current );
      }

      void rewind_position( const rewind_position_t& saved ) noexcept
      {
         m_current = saved.current;
      }

      void private_set_current( const Data* in_current ) noexcept
      {
         m_current = in_current;
      }

      void private_set_end( const Data* in_end ) noexcept
      {
         m_end = in_end;
      }

      [[nodiscard]] const Data* private_get_end() const noexcept
      {
         return m_end;
      }

      [[nodiscard]] auto current_position() const noexcept
      {
         return previous_position( m_current );
      }

      [[nodiscard]] auto previous_position( const Data* previous ) const noexcept
      {
         return pointer_position( previous );
      }

      [[nodiscard]] auto previous_position( const rewind_position_t& previous ) const noexcept
      {
         return pointer_position( previous.current );
      }

   protected:
      const Data* m_current;
      const Data* m_end;
   };

}  // namespace tao::pegtl::internal

#endif
