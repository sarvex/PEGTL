// Copyright (c) 2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_PEGTL_INPUTS_HPP
#define TAO_PEGTL_INPUTS_HPP

#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "ascii.hpp"
#include "positions.hpp"

#include "internal/inputs.hpp"

#include "internal/cstream_reader.hpp"
#include "internal/cstring_reader.hpp"
#include "internal/istream_reader.hpp"

namespace tao::pegtl
{
   using argv_input = internal::fake_buffer_input< internal::argv_input >;
   using argv_inputs = internal::count_inputs< argv_input >;

   using file_input = internal::fake_buffer_input< internal::file_input >;
   using file_inputs = internal::count_inputs< file_input >;
   using file_lf_inputs = internal::line_based_file_inputs< ascii::lf, file_input >;
   using file_crlf_lf_inputs = internal::line_based_file_inputs< ascii::crlf_lf, file_input >;

   using read_input = internal::fake_buffer_input< internal::read_input >;
   using read_inputs = internal::count_inputs< read_input >;
   using read_lf_inputs = internal::line_based_file_inputs< ascii::lf, read_input >;
   using read_crlf_lf_inputs = internal::line_based_file_inputs< ascii::crlf_lf, read_input >;

#if defined( TAO_PEGTL_MMAP_AVAILABLE )
   using mmap_input = internal::fake_buffer_input< internal::mmap_input< internal::memory_input< char > > >;
   using mmap_inputs = internal::count_inputs< mmap_input >;
   using mmap_lf_inputs = internal::line_based_file_inputs< ascii::lf, mmap_input >;
   using mmap_crlf_lf_inputs = internal::line_based_file_inputs< ascii::crlf_lf, mmap_input >;
#endif

   using small_input = internal::fake_buffer_input< internal::memory_input< char > >;  // Not restartable which prevents a couple of things like initialized_restartable_eager_position from working.
   using small_inputs = internal::count_inputs< small_input >;
   using small_lf_inputs = internal::line_based_inputs< ascii::lf, small_input >;
   using small_crlf_lf_inputs = internal::line_based_inputs< ascii::crlf_lf, small_input >;

   using memory_input = internal::restartable_input< small_input >;
   using memory_inputs = internal::count_inputs< memory_input >;
   using memory_lf_inputs = internal::line_based_inputs< ascii::lf, memory_input >;
   using memory_crlf_lf_inputs = internal::line_based_inputs< ascii::crlf_lf, memory_input >;

   using string_input = internal::fake_buffer_input< internal::container_input< std::string > >;
   using string_inputs = internal::count_inputs< string_input >;
   using string_lf_inputs = internal::line_based_inputs< ascii::lf, string_input >;
   using string_crlf_lf_inputs = internal::line_based_inputs< ascii::crlf_lf, string_input >;

   using vector_input = internal::fake_buffer_input< internal::container_input< std::vector< char > > >;
   using vector_inputs = internal::count_inputs< vector_input >;
   using vector_lf_inputs = internal::line_based_inputs< ascii::lf, vector_input >;
   using vector_crlf_lf_inputs = internal::line_based_inputs< ascii::crlf_lf, vector_input >;

   using shared_input = internal::fake_buffer_input< internal::pointer_input< std::shared_ptr< char[] > > >;
   using shared_inputs = internal::count_inputs< shared_input >;
   using shared_lf_inputs = internal::line_based_inputs< ascii::lf, shared_input >;
   using shared_crlf_lf_inputs = internal::line_based_inputs< ascii::crlf_lf, shared_input >;

   using unique_input = internal::fake_buffer_input< internal::pointer_input< std::unique_ptr< char[] > > >;
   using unique_inputs = internal::count_inputs< unique_input >;
   using unique_lf_inputs = internal::line_based_inputs< ascii::lf, unique_input >;
   using unique_crlf_lf_inputs = internal::line_based_inputs< ascii::crlf_lf, unique_input >;

   using dynamic_cstream_input = internal::dynamic_buffer_input< char, internal::cstream_reader >;
   using dynamic_cstream_inputs = internal::count_inputs< dynamic_cstream_input >;
   using dynamic_lf_cstream_inputs = internal::line_based_dynamic_inputs< ascii::lf, dynamic_cstream_input >;
   using dynamic_crlf_lf_cstream_inputs = internal::line_based_dynamic_inputs< ascii::crlf_lf, dynamic_cstream_input >;

   using dynamic_cstring_input = internal::dynamic_buffer_input< char, internal::cstring_reader >;
   using dynamic_cstring_inputs = internal::count_inputs< dynamic_cstring_input >;
   using dynamic_lf_cstring_inputs = internal::line_based_dynamic_inputs< ascii::lf, dynamic_cstring_input >;
   using dynamic_crlf_lf_cstring_inputs = internal::line_based_dynamic_inputs< ascii::crlf_lf, dynamic_cstring_input >;

   using dynamic_istream_input = internal::dynamic_buffer_input< char, internal::istream_reader >;
   using dynamic_istream_inputs = internal::count_inputs< dynamic_istream_input >;
   using dynamic_lf_istream_inputs = internal::line_based_dynamic_inputs< ascii::lf, dynamic_istream_input >;
   using dynamic_crlf_lf_istream_inputs = internal::line_based_dynamic_inputs< ascii::crlf_lf, dynamic_istream_input >;

   template< std::size_t Size, std::size_t Chunk >
   using static_cstream_input = internal::static_buffer_input< char, Size, Chunk, internal::cstream_reader >;
   template< std::size_t Size, std::size_t Chunk >
   using static_cstring_input = internal::static_buffer_input< char, Size, Chunk, internal::cstring_reader >;
   template< std::size_t Size, std::size_t Chunk >
   using static_istream_input = internal::static_buffer_input< char, Size, Chunk, internal::istream_reader >;

   using auto_dynamic_cstream_input = internal::auto_discard_buffer_input< dynamic_cstream_input >;
   using auto_dynamic_cstream_inputs = internal::count_inputs< auto_dynamic_cstream_input >;
   using auto_dynamic_lf_cstream_inputs = internal::line_based_dynamic_inputs< ascii::lf, auto_dynamic_cstream_input >;
   using auto_dynamic_crlf_lf_cstream_inputs = internal::line_based_dynamic_inputs< ascii::crlf_lf, auto_dynamic_cstream_input >;

   using auto_dynamic_cstring_input = internal::auto_discard_buffer_input< dynamic_cstring_input >;
   using auto_dynamic_cstring_inputs = internal::count_inputs< auto_dynamic_cstring_input >;
   using auto_dynamic_lf_cstring_inputs = internal::line_based_dynamic_inputs< ascii::lf, auto_dynamic_cstring_input >;
   using auto_dynamic_crlf_lf_cstring_inputs = internal::line_based_dynamic_inputs< ascii::crlf_lf, auto_dynamic_cstring_input >;

   using auto_dynamic_istream_input = internal::auto_discard_buffer_input< dynamic_istream_input >;
   using auto_dynamic_istream_inputs = internal::count_inputs< auto_dynamic_istream_input >;
   using auto_dynamic_lf_istream_inputs = internal::line_based_dynamic_inputs< ascii::lf, auto_dynamic_istream_input >;
   using auto_dynamic_crlf_lf_istream_inputs = internal::line_based_dynamic_inputs< ascii::crlf_lf, auto_dynamic_istream_input >;

   template< std::size_t Size, std::size_t Chunk >
   using auto_static_cstream_input = internal::auto_discard_buffer_input< static_cstream_input< Size, Chunk > >;
   template< std::size_t Size, std::size_t Chunk >
   using auto_static_cstring_input = internal::auto_discard_buffer_input< static_cstring_input< Size, Chunk > >;
   template< std::size_t Size, std::size_t Chunk >
   using auto_static_istream_input = internal::auto_discard_buffer_input< static_istream_input< Size, Chunk > >;

}  // namespace tao::pegtl

#endif
