// Copyright (c) 2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_PEGTL_INTERNAL_DYNAMIC_BUFFER_INPUT_BASE_HPP
#define TAO_PEGTL_INTERNAL_DYNAMIC_BUFFER_INPUT_BASE_HPP

#include <cstddef>
#include <memory>
#include <utility>

namespace tao::pegtl::internal
{
   template< typename Data, typename Reader >
   class dynamic_buffer_input_base
   {
   public:
      using data_t = Data;
      using pointer_t = const Data*;

      template< typename... As >
      dynamic_buffer_input_base( const std::size_t size, const std::size_t chunk, As&&... as )
         : m_size( size ),
           m_chunk( chunk ),
           m_buffer( new Data[ size ] ),
           m_reader( std::forward< As >( as )... )
      {
         // assert( chunk > 0 );
         // assert( buffer > chunk );
      }

      dynamic_buffer_input_base( dynamic_buffer_input_base&& ) = delete;
      dynamic_buffer_input_base( const dynamic_buffer_input_base& ) = delete;

      ~dynamic_buffer_input_base() = default;

      void operator=( dynamic_buffer_input_base&& ) = delete;
      void operator=( const dynamic_buffer_input_base& ) = delete;

      [[nodiscard]] Data* mutable_begin() noexcept
      {
         return m_buffer.get();
      }

      [[nodiscard]] const Data* buffer_begin() const noexcept
      {
         return m_buffer.get();
      }

      [[nodiscard]] std::size_t buffer_capacity() const noexcept
      {
         return m_size;
      }

      [[nodiscard]] std::size_t buffer_chunk_size() const noexcept
      {
         return m_chunk;
      }

   protected:
      const std::size_t m_size;
      const std::size_t m_chunk;
      const std::unique_ptr< Data[] > m_buffer;
      Reader m_reader;
   };

}  // namespace tao::pegtl::internal

#endif
