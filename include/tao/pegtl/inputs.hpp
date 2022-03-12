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

   using file_input = internal::fake_buffer_input< internal::file_input >;
   using mmap_input = internal::fake_buffer_input< internal::mmap_input< internal::memory_input< char > > >;
   using read_input = internal::fake_buffer_input< internal::read_input >;

   using memory_input = internal::fake_buffer_input< internal::memory_input< char > >;
   using string_input = internal::fake_buffer_input< internal::container_input< std::string > >;
   using vector_input = internal::fake_buffer_input< internal::container_input< std::vector< char > > >;

   using shared_input = internal::fake_buffer_input< internal::pointer_input< std::shared_ptr< char[] > > >;
   using unique_input = internal::fake_buffer_input< internal::pointer_input< std::unique_ptr< char[] > > >;

   using restartable_input = internal::restartable_input< memory_input >;

   using dynamic_cstream_input = internal::dynamic_buffer_input< char, internal::cstream_reader >;
   using dynamic_cstring_input = internal::dynamic_buffer_input< char, internal::cstring_reader >;
   using dynamic_istream_input = internal::dynamic_buffer_input< char, internal::istream_reader >;

   template< std::size_t Size, std::size_t Chunk >
   using static_cstream_input = internal::static_buffer_input< char, Size, Chunk, internal::cstream_reader >;
   template< std::size_t Size, std::size_t Chunk >
   using static_cstring_input = internal::static_buffer_input< char, Size, Chunk, internal::cstring_reader >;
   template< std::size_t Size, std::size_t Chunk >
   using static_istream_input = internal::static_buffer_input< char, Size, Chunk, internal::istream_reader >;

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
   // Buffer inputs only work with simple eager positions, not lazy or restartable eager positions.
   // initialized_restartable_eager_position_input requires restartable_input around memory_inputs.
   // Eager inputs must use input_with_source, lazy inputs can directly use position_with_source.
   // It might not make sense to keep lazy and eager for count_position, lazy is enough since current_position() is O(1).
   // It probably doesn't make sense to use Eols with argv_input.


   // TODO: Other line endings
   // TODO: With source -- only file?
   // TODO: Not just memory_input


   // Class templates (ab)used as namespace templates:

   template< typename Input >
   struct count_inputs
   {
      using input = Input;

      // using eager_count_input = internal::defaulted_eager_position_input< internal::count_position< std::size_t >, input >;

      // using initialized_eager_count_input = internal::initialized_eager_position_input< internal::count_position< std::size_t >, input >;
      // using restartable_eager_count_input = internal::initialized_restartable_eager_position_input< internal::count_position< std::size_t >, input >;

      using lazy_count_input = internal::defaulted_lazy_position_input< internal::count_position< std::size_t >, input >;

      using initialized_lazy_count_input = internal::initialized_lazy_position_input< internal::count_position< std::size_t >, input >;  // Restartable
   };

   using argv_inputs = count_inputs< argv_input >;

   template< typename Eol, typename Input >
   struct line_based_eager_inputs
   {
      using input = internal::line_based_input< Eol, Input >;

      // using eager_count_input = internal::defaulted_eager_position_input< internal::count_position< std::size_t >, input >;

      // using initialized_eager_count_input = internal::initialized_eager_position_input< internal::count_position< std::size_t >, input >;
      // using restartable_eager_count_input = internal::initialized_restartable_eager_position_input< internal::count_position< std::size_t >, input >;

      using careless_text_input = internal::defaulted_eager_position_input< internal::careless_text_position< std::size_t >, input >;
      using selected_text_input = internal::defaulted_eager_position_input< internal::selected_text_position< Eol, std::size_t >, input >;
      using paranoid_text_input = internal::defaulted_eager_position_input< internal::paranoid_text_position< Eol, std::size_t >, input >;

      using initialized_careless_text_input = internal::initialized_eager_position_input< internal::careless_text_position< std::size_t >, input >;
      using initialized_selected_text_input = internal::initialized_eager_position_input< internal::selected_text_position< Eol, std::size_t >, input >;
      using initialized_paranoid_text_input = internal::initialized_eager_position_input< internal::paranoid_text_position< Eol, std::size_t >, input >;

      using restartable_careless_text_input = internal::initialized_restartable_eager_position_input< internal::careless_text_position< std::size_t >, input >;
      using restartable_selected_text_input = internal::initialized_restartable_eager_position_input< internal::selected_text_position< Eol, std::size_t >, input >;
      using restartable_paranoid_text_input = internal::initialized_restartable_eager_position_input< internal::paranoid_text_position< Eol, std::size_t >, input >;

      using careless_text_count_input = internal::defaulted_eager_position_input< internal::careless_text_count_position< std::size_t >, input >;
      using selected_text_count_input = internal::defaulted_eager_position_input< internal::selected_text_count_position< Eol, std::size_t >, input >;
      using paranoid_text_count_input = internal::defaulted_eager_position_input< internal::paranoid_text_count_position< Eol, std::size_t >, input >;

      using initialized_careless_text_count_input = internal::initialized_eager_position_input< internal::careless_text_count_position< std::size_t >, input >;
      using initialized_selected_text_count_input = internal::initialized_eager_position_input< internal::selected_text_count_position< Eol, std::size_t >, input >;
      using initialized_paranoid_text_count_input = internal::initialized_eager_position_input< internal::paranoid_text_count_position< Eol, std::size_t >, input >;

      using restartable_careless_text_count_input = internal::initialized_restartable_eager_position_input< internal::careless_text_count_position< std::size_t >, input >;
      using restartable_selected_text_count_input = internal::initialized_restartable_eager_position_input< internal::selected_text_count_position< Eol, std::size_t >, input >;
      using restartable_paranoid_text_count_input = internal::initialized_restartable_eager_position_input< internal::paranoid_text_count_position< Eol, std::size_t >, input >;
   };

   template< typename Eol, typename Input >
   struct line_based_lazy_inputs
   {
      using input = internal::line_based_input< Eol, Input >;

      using lazy_count_input = internal::defaulted_lazy_position_input< internal::count_position< std::size_t >, input >;
      using initialized_lazy_count_input = internal::initialized_lazy_position_input< internal::count_position< std::size_t >, input >;  // Restartable
      using lazy_text_input = internal::defaulted_lazy_position_input< internal::careless_text_position< std::size_t >, input >;
      using initialized_lazy_text_input = internal::initialized_lazy_position_input< internal::careless_text_position< std::size_t >, input >;  // Restartable
      using lazy_text_count_input = internal::defaulted_lazy_position_input< internal::careless_text_count_position< std::size_t >, input >;
      using initialized_lazy_text_count_input = internal::initialized_lazy_position_input< internal::careless_text_count_position< std::size_t >, input >;  // Restartable
   };

   template< typename Eol, typename Input >
   struct line_based_inputs
      : line_based_eager_inputs< Eol, Input >,
        line_based_lazy_inputs< Eol, Input >
   {
      using input = internal::line_based_input< Eol, Input >;
   };

   using memory_lf_inputs = line_based_inputs< ascii::lf, memory_input >;
   using memory_crlf_lf_inputs = line_based_inputs< ascii::crlf_lf, memory_input >;

   using string_lf_inputs = line_based_inputs< ascii::lf, string_input >;
   using string_crlf_lf_inputs = line_based_inputs< ascii::crlf_lf, string_input >;

   using vector_lf_inputs = line_based_inputs< ascii::lf, vector_input >;
   using vector_crlf_lf_inputs = line_based_inputs< ascii::crlf_lf, vector_input >;

   using shared_lf_inputs = line_based_inputs< ascii::lf, shared_input >;
   using shared_crlf_lf_inputs = line_based_inputs< ascii::crlf_lf, shared_input >;

   using unique_lf_inputs = line_based_inputs< ascii::lf, unique_input >;
   using unique_crlf_lf_inputs = line_based_inputs< ascii::crlf_lf, unique_input >;

   using restartable_lf_inputs = line_based_inputs< ascii::lf, restartable_input >;
   using restartable_crlf_lf_inputs = line_based_inputs< ascii::crlf_lf, restartable_input >;

   template< typename Eol, typename Input, typename Source >
   struct file_based_inputs;

   namespace internal
   {
      template< typename Input >
      struct file_input_string
         : Input
      {
         explicit file_input_string( std::string&& f )
            : Input( "", f )
         {
            this->source = std::move( f );
         }

         explicit file_input_string( const std::string& f )
            : Input( f, f )
         {}

         explicit file_input_string( const filesystem::path& p )
            : Input( p, p )
         {}
      };

   }  // namespace internal

   template< typename Eol, typename Input >
   struct file_based_inputs< Eol, Input, std::string >
   {
      using input = internal::line_based_input< Eol, Input >;

      using lazy_count_input = internal::file_input_string< internal::input_with_source< std::string, internal::defaulted_lazy_position_input< internal::count_position< std::size_t >, input > > >;



      // using lazy_count_input = internal::input_with_source< std::string, internal::defaulted_lazy_position_input< internal::count_position< std::size_t >, input > >;
      //      using initialized_lazy_count_input = internal::input_with_source< std::string, internal::initialized_lazy_position_input< internal::count_position< std::size_t >, input > >;
      using lazy_text_input = internal::input_with_source< std::string, internal::defaulted_lazy_position_input< internal::careless_text_position< std::size_t >, input > >;
      //      using initialized_lazy_text_input = internal::input_with_source< std::string, internal::initialized_lazy_position_input< internal::careless_text_position< std::size_t >, input > >;
      using lazy_text_count_input = internal::input_with_source< std::string, internal::defaulted_lazy_position_input< internal::careless_text_count_position< std::size_t >, input > >;
      //      using initialized_lazy_text_count_input = internal::input_with_source< std::string, internal::initialized_lazy_position_input< internal::careless_text_count_position< std::size_t >, input > >;
   };

   template< typename Eol, typename Input >
   struct file_based_inputs< Eol, Input, std::string_view >
   {
      using input = internal::line_based_input< Eol, Input >;

      struct lazy_count_input
         : internal::input_with_source< std::string_view, internal::defaulted_lazy_position_input< internal::count_position< std::size_t >, input > >
      {
         explicit lazy_count_input( const std::string_view f )
            : internal::input_with_source< std::string_view, internal::defaulted_lazy_position_input< internal::count_position< std::size_t >, input > >( f, f )
         {}
      };
   };

   template< typename Eol, typename Input >
   struct file_based_inputs< Eol, Input, internal::filesystem::path >
   {
      using input = internal::line_based_input< Eol, Input >;

      struct lazy_count_input
         : internal::input_with_source< internal::filesystem::path, internal::defaulted_lazy_position_input< internal::count_position< std::size_t >, input > >
      {
         explicit lazy_count_input( internal::filesystem::path&& f )
            : internal::input_with_source< std::string_view, internal::defaulted_lazy_position_input< internal::count_position< std::size_t >, input > >( "", f )
         {
            this->source = std::move( f );
         }

         explicit lazy_count_input( const internal::filesystem::path& f )
            : internal::input_with_source< std::string_view, internal::defaulted_lazy_position_input< internal::count_position< std::size_t >, input > >( f, f )
         {}
      };
   };

   using file_lf_inputs = file_based_inputs< lf, file_input, std::string >;
   using file_crlf_lf_inputs = file_based_inputs< crlf_lf, file_input, std::string >;

   using mmap_lf_inputs = file_based_inputs< lf, mmap_input, std::string >;
   using mmap_crlf_lf_inputs = file_based_inputs< crlf_lf, mmap_input, std::string >;

   using read_lf_inputs = file_based_inputs< lf, read_input, std::string >;
   using read_crlf_lf_inputs = file_based_inputs< crlf_lf, read_input, std::string >;

   /*
   using file_lf_inputs = file_based_inputs< lf, file_input, std::string_view >;
   using file_crlf_lf_inputs = file_based_inputs< crlf_lf, file_input, std::string_view >;

   using mmap_lf_inputs = file_based_inputs< lf, mmap_input, std::string_view >;
   using mmap_crlf_lf_inputs = file_based_inputs< crlf_lf, mmap_input, std::string_view >;

   using read_lf_inputs = file_based_inputs< lf, read_input, std::string_view >;
   using read_crlf_lf_inputs = file_based_inputs< crlf_lf, read_input, std::string_view >;

   using file_lf_inputs = file_based_inputs< lf, file_input, internal::filesystem::path >;
   using file_crlf_lf_inputs = file_based_inputs< crlf_lf, file_input, internal::filesystem::path >;

   using mmap_lf_inputs = file_based_inputs< lf, mmap_input, internal::filesystem::path >;
   using mmap_crlf_lf_inputs = file_based_inputs< crlf_lf, mmap_input, internal::filesystem::path >;

   using read_lf_inputs = file_based_inputs< lf, read_input, internal::filesystem::path >;
   using read_crlf_lf_inputs = file_based_inputs< crlf_lf, read_input, internal::filesystem::path >;
   */

}  // namespace tao::pegtl

#endif
