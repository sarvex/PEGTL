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
   // Basic Inputs (15)

   using memory_input = internal::fake_buffer_input< internal::memory_input< char > >;

   using argv_input = internal::fake_buffer_input< internal::argv_input >;
   using file_input = internal::fake_buffer_input< internal::file_input >;
   using mmap_input = internal::fake_buffer_input< internal::mmap_input< internal::memory_input< char > > >;
   using read_input = internal::fake_buffer_input< internal::read_input >;

   using string_input = internal::fake_buffer_input< internal::container_input< std::string > >;
   using vector_input = internal::fake_buffer_input< internal::container_input< std::vector< char > > >;

   using shared_input = internal::fake_buffer_input< internal::pointer_input< std::shared_ptr< char[] > > >;
   using unique_input = internal::fake_buffer_input< internal::pointer_input< std::unique_ptr< char[] > > >;

   using dynamic_cstream_input = internal::dynamic_buffer_input< char, internal::cstream_reader >;
   using dynamic_cstring_input = internal::dynamic_buffer_input< char, internal::cstring_reader >;
   using dynamic_istream_input = internal::dynamic_buffer_input< char, internal::istream_reader >;

   template< std::size_t Size, std::size_t Chunk >
   using static_cstream_input = internal::static_buffer_input< char, Size, Chunk, internal::cstream_reader >;
   template< std::size_t Size, std::size_t Chunk >
   using static_cstring_input = internal::static_buffer_input< char, Size, Chunk, internal::cstring_reader >;
   template< std::size_t Size, std::size_t Chunk >
   using static_istream_input = internal::static_buffer_input< char, Size, Chunk, internal::istream_reader >;

   // Slightly Enhanced Inputs (7)

   using restartable_input = internal::restartable_input< memory_input >;

   using auto_dynamic_cstream_input = internal::auto_discard_buffer_input< dynamic_cstream_input >;
   using auto_dynamic_cstring_input = internal::auto_discard_buffer_input< dynamic_cstring_input >;
   using auto_dynamic_istream_input = internal::auto_discard_buffer_input< dynamic_istream_input >;

   template< std::size_t Size, std::size_t Chunk >
   using auto_static_cstream_input = internal::auto_discard_buffer_input< static_cstream_input< Size, Chunk > >;
   template< std::size_t Size, std::size_t Chunk >
   using auto_static_cstring_input = internal::auto_discard_buffer_input< static_cstring_input< Size, Chunk > >;
   template< std::size_t Size, std::size_t Chunk >
   using auto_static_istream_input = internal::auto_discard_buffer_input< static_istream_input< Size, Chunk > >;

   // Omit defaulted_ prefix because that's the, well, default case...?
   // With lazy positions there is no difference between careless, paranoid and selected.
   // Buffer inputs only work with simple eager positions, not restartable eager position.
   // initialized_restartable_eager_position_input requires restartable_input around memory_inputs.

   using lf_memory_input = internal::line_based_input< lf, memory_input >;

   using lazy_count_lf_memory_input = internal::defaulted_lazy_position_input< internal::count_position< std::size_t >, lf_memory_input >;

   using careless_count_lf_memory_input = internal::defaulted_eager_position_input< internal::count_position< std::size_t >, lf_memory_input >;

   using initialized_lazy_count_lf_memory_input = internal::initialized_lazy_position_input< internal::count_position< std::size_t >, lf_memory_input >;  // Restartable

   using initialized_careless_count_lf_memory_input = internal::initialized_eager_position_input< internal::count_position< std::size_t >, lf_memory_input >;

   using restartable_careless_count_lf_memory_input = internal::initialized_restartable_eager_position_input< internal::count_position< std::size_t >, lf_memory_input >;

   using lazy_text_lf_memory_input = internal::defaulted_lazy_position_input< internal::careless_text_position< std::size_t >, lf_memory_input >;

   using careless_text_lf_memory_input = internal::defaulted_eager_position_input< internal::careless_text_position< std::size_t >, lf_memory_input >;
   using selected_text_lf_memory_input = internal::defaulted_eager_position_input< internal::selected_text_position< lf, std::size_t >, lf_memory_input >;
   using paranoid_text_lf_memory_input = internal::defaulted_eager_position_input< internal::paranoid_text_position< lf, std::size_t >, lf_memory_input >;

   using initialized_lazy_text_lf_memory_input = internal::initialized_lazy_position_input< internal::careless_text_position< std::size_t >, lf_memory_input >;  // Restartable

   using initialized_careless_text_lf_memory_input = internal::initialized_eager_position_input< internal::careless_text_position< std::size_t >, lf_memory_input >;
   using initialized_selected_text_lf_memory_input = internal::initialized_eager_position_input< internal::selected_text_position< lf, std::size_t >, lf_memory_input >;
   using initialized_paranoid_text_lf_memory_input = internal::initialized_eager_position_input< internal::paranoid_text_position< lf, std::size_t >, lf_memory_input >;

   using restartable_careless_text_lf_memory_input = internal::initialized_restartable_eager_position_input< internal::careless_text_position< std::size_t >, lf_memory_input >;
   using restartable_selected_text_lf_memory_input = internal::initialized_restartable_eager_position_input< internal::selected_text_position< lf, std::size_t >, lf_memory_input >;
   using restartable_paranoid_text_lf_memory_input = internal::initialized_restartable_eager_position_input< internal::paranoid_text_position< lf, std::size_t >, lf_memory_input >;

   using lazy_text_count_lf_memory_input = internal::defaulted_lazy_position_input< internal::careless_text_count_position< std::size_t >, lf_memory_input >;

   using careless_text_count_lf_memory_input = internal::defaulted_eager_position_input< internal::careless_text_count_position< std::size_t >, lf_memory_input >;
   using selected_text_count_lf_memory_input = internal::defaulted_eager_position_input< internal::selected_text_count_position< lf, std::size_t >, lf_memory_input >;
   using paranoid_text_count_lf_memory_input = internal::defaulted_eager_position_input< internal::paranoid_text_count_position< lf, std::size_t >, lf_memory_input >;

   using initialized_lazy_text_count_lf_memory_input = internal::initialized_lazy_position_input< internal::careless_text_count_position< std::size_t >, lf_memory_input >;  // Restartable

   using initialized_careless_text_count_lf_memory_input = internal::initialized_eager_position_input< internal::careless_text_count_position< std::size_t >, lf_memory_input >;
   using initialized_selected_text_count_lf_memory_input = internal::initialized_eager_position_input< internal::selected_text_count_position< lf, std::size_t >, lf_memory_input >;
   using initialized_paranoid_text_count_lf_memory_input = internal::initialized_eager_position_input< internal::paranoid_text_count_position< lf, std::size_t >, lf_memory_input >;

   using restartable_careless_text_count_lf_memory_input = internal::initialized_restartable_eager_position_input< internal::careless_text_count_position< std::size_t >, lf_memory_input >;
   using restartable_selected_text_count_lf_memory_input = internal::initialized_restartable_eager_position_input< internal::selected_text_count_position< lf, std::size_t >, lf_memory_input >;
   using restartable_paranoid_text_count_lf_memory_input = internal::initialized_restartable_eager_position_input< internal::paranoid_text_count_position< lf, std::size_t >, lf_memory_input >;



   // TODO: Other line endings
   // TODO: With source
   // TODO: Not just memory_input



}  // namespace tao::pegtl

#endif
