// Copyright (c) 2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_PEGTL_INPUTS_HPP
#define TAO_PEGTL_INPUTS_HPP

#include <memory>
#include <string>
#include <vector>

#include "ascii.hpp"
#include "positions.hpp"

#include "internal/inputs.hpp"

#include "internal/cstream_reader.hpp"
#include "internal/cstring_reader.hpp"
#include "internal/istream_reader.hpp"

namespace tao::pegtl
{
   using memory_input = internal::fake_buffer_input< internal::memory_input< char > >;

   using argv_input = internal::fake_buffer_input< internal::argv_input >;
   using file_input = internal::fake_buffer_input< internal::file_input >;
   using mmap_input = internal::fake_buffer_input< internal::mmap_input< internal::memory_input< char > > >;
   using read_input = internal::fake_buffer_input< internal::read_input >;

   using string_input = internal::fake_buffer_input< internal::container_input< std::string > >;
   using vector_input = internal::fake_buffer_input< internal::container_input< std::vector< char > > >;

   using shared_input = internal::fake_buffer_input< internal::pointer_input< std::shared_ptr< char[] > > >;
   using unique_input = internal::fake_buffer_input< internal::pointer_input< std::unique_ptr< char[] > > >;

   // using mmap_input = internal::line_based_input< lf, internal::mmap_input< internal::restartable_input< internal::memory_input< char > > > >;

   using lf_memory_input = internal::line_based_input< lf, memory_input >;
   // ...

   using crlf_memory_input = internal::line_based_input< crlf, memory_input >;
   // ...

   // Omit defaulted_ prefix because that's the, well, default case...?

   using eager_text_lf_memory_input = internal::defaulted_eager_position_input< internal::careless_text_position< std::size_t >, lf_memory_input >;
   // ...

   using eager_text_crlf_memory_input = internal::defaulted_eager_position_input< internal::careless_text_position< std::size_t >, crlf_memory_input >;
   // ...

   using lazy_text_lf_memory_input = internal::defaulted_lazy_position_input< internal::careless_text_position< std::size_t >, lf_memory_input >;
   // ...

   using lazy_text_crlf_memory_input = internal::defaulted_lazy_position_input< internal::careless_text_position< std::size_t >, crlf_memory_input >;
   // ...

   using initialized_eager_text_lf_memory_input = internal::initialized_eager_position_input< internal::careless_text_position< std::size_t >, lf_memory_input >;
   // ...

   using initialized_eager_text_crlf_memory_input = internal::initialized_eager_position_input< internal::careless_text_position< std::size_t >, crlf_memory_input >;
   // ...

   using initialized_lazy_text_lf_memory_input = internal::initialized_lazy_position_input< internal::careless_text_position< std::size_t >, lf_memory_input >;
   // ...

   using initialized_lazy_text_crlf_memory_input = internal::initialized_lazy_position_input< internal::careless_text_position< std::size_t >, crlf_memory_input >;
   // ...

   // TODO: initialized_restartable_eager_position_input requires restartable_input around memory_inputs.

   // Buffer inputs only work with simple eager positions, not restartable eager position.

   using dynamic_cstream_input = internal::dynamic_buffer_input< char, internal::cstream_reader >;
   using dynamic_cstring_input = internal::dynamic_buffer_input< char, internal::cstring_reader >;
   using dynamic_istream_input = internal::dynamic_buffer_input< char, internal::istream_reader >;

   template< std::size_t Size, std::size_t Chunk >
   using static_cstream_input = internal::static_buffer_input< char, Size, Chunk, internal::cstream_reader >;

   template< std::size_t Size, std::size_t Chunk >
   using static_cstring_input = internal::static_buffer_input< char, Size, Chunk, internal::cstring_reader >;

   template< std::size_t Size, std::size_t Chunk >
   using static_istream_input = internal::static_buffer_input< char, Size, Chunk, internal::istream_reader >;

   // TODO: ... ???

}  // namespace tao::pegtl

#endif
