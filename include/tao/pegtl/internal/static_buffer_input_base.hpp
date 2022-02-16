// Copyright (c) 2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_PEGTL_INTERNAL_STATIC_BUFFER_INPUT_BASE_HPP
#define TAO_PEGTL_INTERNAL_STATIC_BUFFER_INPUT_BASE_HPP

#include <array>
#include <cstddef>
#include <utility>

namespace tao::pegtl::internal
{
   template< typename Data, std::size_t Size, std::size_t Chunk, typename Reader >
   class static_buffer_input_base
   {
   public:
      using data_t = Data;

      template< typename... As >
      explicit static_buffer_input_base( As&&... as )
         : m_reader( std::forward< As >( as )... )
      {
         static_assert( Chunk > 0 );
         static_assert( Chunk < Size );
      }

      static_buffer_input_base( static_buffer_input_base&& ) = delete;
      static_buffer_input_base( const static_buffer_input_base& ) = delete;

      ~static_buffer_input_base() = default;

      void operator=( static_buffer_input_base&& ) = delete;
      void operator=( const static_buffer_input_base& ) = delete;

      [[nodiscard]] Data* mutable_begin() noexcept
      {
         return m_buffer.data();
      }

      [[nodiscard]] const Data* buffer_begin() const noexcept
      {
         return m_buffer.data();
      }

      [[nodiscard]] std::size_t buffer_capacity() const noexcept
      {
         return m_buffer.size();
      }

      [[nodiscard]] std::size_t buffer_chunk_size() const noexcept
      {
         return Chunk;
      }

   protected:
      std::array< Data, Size > m_buffer;
      Reader m_reader;
   };

}  // namespace tao::pegtl::internal

#endif
