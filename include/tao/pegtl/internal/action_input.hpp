// Copyright (c) 2016-2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_PEGTL_INTERNAL_ACTION_INPUT_HPP
#define TAO_PEGTL_INTERNAL_ACTION_INPUT_HPP

#include <cstddef>
#include <cstdint>
#include <string>
#include <string_view>

namespace tao::pegtl::internal
{
   template< typename ParseInput >
   class action_input
   {
   public:
      using data_t = typename ParseInput::data_t;
      using pointer_t = const data_t*;
      using input_t = ParseInput;
      using rewind_position_t = typename ParseInput::rewind_position_t;

      action_input( const rewind_position_t& in_saved, const ParseInput& in_input ) noexcept
         : m_saved( in_saved ),
           m_input( in_input )
      {}

      action_input( const action_input& ) = delete;
      action_input( action_input&& ) = delete;

      ~action_input() = default;

      action_input& operator=( const action_input& ) = delete;
      action_input& operator=( action_input&& ) = delete;

      [[nodiscard]] pointer_t begin() const noexcept
      {
         return m_saved.current;
      }

      [[nodiscard]] pointer_t end() const noexcept
      {
         return input().current();
      }

      [[nodiscard]] bool empty() const noexcept
      {
         return begin() == end();
      }

      [[nodiscard]] std::size_t size() const noexcept
      {
         return std::size_t( end() - begin() );
      }

      [[nodiscard]] std::string string() const
      {
         return std::string( begin(), size() );
      }

      [[nodiscard]] std::string_view string_view() const noexcept
      {
         return std::string_view( begin(), size() );
      }

      [[nodiscard]] data_t peek( const std::size_t offset = 0 ) const noexcept
      {
         return begin()[ offset ];
      }

      [[nodiscard]] char peek_char( const std::size_t offset = 0 ) const noexcept
      {
         static_assert( sizeof( data_t ) == 1 );
         return reinterpret_cast< const char* >( begin() )[ offset ];
      }

      [[nodiscard]] std::uint8_t peek_uint8( const std::size_t offset = 0 ) const noexcept
      {
         static_assert( sizeof( data_t ) == 1 );
         return reinterpret_cast< const std::uint8_t* >( begin() )[ offset ];
      }

      [[nodiscard]] const ParseInput& input() const noexcept
      {
         return m_input;
      }

      [[nodiscard]] decltype( auto ) current_position() const
      {
         return m_input.previous_position( m_saved );  // NOTE: For lazy inputs this is O(n) where n is m_saved.current() - m_input.begin().
      }

   protected:
      const rewind_position_t m_saved;
      const ParseInput& m_input;
   };

}  // namespace tao::pegtl::internal

#endif
