// Copyright (c) 2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_PEGTL_INTERNAL_TEMPORARY_HPP
#define TAO_PEGTL_INTERNAL_TEMPORARY_HPP

#include "inputs.hpp"
#include "positions.hpp"

namespace tao::pegtl::internal
{
   // Eager inputs must use input_with_source, lazy inputs can also directly use position_with_source.

   template< typename Input >
   struct count_inputs
   {
      using input = Input;

      // Eager doesn't make sense for count_position given that in.current_position() is O(1) for lazy, too.
      // using eager_count_input = defaulted_eager_position_input< count_position< std::size_t >, input >;
      // using initialized_eager_count_input = initialized_eager_position_input< count_position< std::size_t >, input >;
      // using restartable_eager_count_input = initialized_restartable_eager_position_input< count_position< std::size_t >, input >;

      using lazy_count_input = defaulted_lazy_position_input< count_position< std::size_t >, input >;

      using initialized_lazy_count_input = initialized_lazy_position_input< count_position< std::size_t >, input >;  // Restartable
   };

   template< typename Eol, typename Input >
   struct line_based_inputs
   {
      using input = line_based_input< Eol, Input >;

      // Eager doesn't make sense for count_position given that in.current_position() is O(1) for lazy, too.
      // using eager_count_input = defaulted_eager_position_input< count_position< std::size_t >, input >;
      // using initialized_eager_count_input = initialized_eager_position_input< count_position< std::size_t >, input >;
      // using restartable_eager_count_input = initialized_restartable_eager_position_input< count_position< std::size_t >, input >;

      // Omit defaulted_ as prefix because we consider it the default case (no pun intended).
      using careless_text_input = defaulted_eager_position_input< careless_text_position< std::size_t >, input >;
      using selected_text_input = defaulted_eager_position_input< selected_text_position< Eol, std::size_t >, input >;
      using paranoid_text_input = defaulted_eager_position_input< paranoid_text_position< Eol, std::size_t >, input >;

      using initialized_careless_text_input = initialized_eager_position_input< careless_text_position< std::size_t >, input >;
      using initialized_selected_text_input = initialized_eager_position_input< selected_text_position< Eol, std::size_t >, input >;
      using initialized_paranoid_text_input = initialized_eager_position_input< paranoid_text_position< Eol, std::size_t >, input >;

      using restartable_careless_text_input = initialized_restartable_eager_position_input< careless_text_position< std::size_t >, input >;
      using restartable_selected_text_input = initialized_restartable_eager_position_input< selected_text_position< Eol, std::size_t >, input >;
      using restartable_paranoid_text_input = initialized_restartable_eager_position_input< paranoid_text_position< Eol, std::size_t >, input >;

      using careless_text_count_input = defaulted_eager_position_input< careless_text_count_position< std::size_t >, input >;
      using selected_text_count_input = defaulted_eager_position_input< selected_text_count_position< Eol, std::size_t >, input >;
      using paranoid_text_count_input = defaulted_eager_position_input< paranoid_text_count_position< Eol, std::size_t >, input >;

      using initialized_careless_text_count_input = initialized_eager_position_input< careless_text_count_position< std::size_t >, input >;
      using initialized_selected_text_count_input = initialized_eager_position_input< selected_text_count_position< Eol, std::size_t >, input >;
      using initialized_paranoid_text_count_input = initialized_eager_position_input< paranoid_text_count_position< Eol, std::size_t >, input >;

      using restartable_careless_text_count_input = initialized_restartable_eager_position_input< careless_text_count_position< std::size_t >, input >;
      using restartable_selected_text_count_input = initialized_restartable_eager_position_input< selected_text_count_position< Eol, std::size_t >, input >;
      using restartable_paranoid_text_count_input = initialized_restartable_eager_position_input< paranoid_text_count_position< Eol, std::size_t >, input >;

      // With lazy text positions there is no difference between careless, paranoid and selected since they all re-scan using the eol rule.
      using lazy_count_input = defaulted_lazy_position_input< count_position< std::size_t >, input >;
      using initialized_lazy_count_input = initialized_lazy_position_input< count_position< std::size_t >, input >;  // Restartable
      using lazy_text_input = defaulted_lazy_position_input< careless_text_position< std::size_t >, input >;
      using initialized_lazy_text_input = initialized_lazy_position_input< careless_text_position< std::size_t >, input >;  // Restartable
      using lazy_text_count_input = defaulted_lazy_position_input< careless_text_count_position< std::size_t >, input >;
      using initialized_lazy_text_count_input = initialized_lazy_position_input< careless_text_count_position< std::size_t >, input >;  // Restartable
   };

   // For file based inputs it doesn't really make sense to initialize the position.

   template< typename Eol, typename Input >
   struct line_based_file_inputs
   {
      using input = internal::line_based_input< Eol, Input >;

      using careless_text_input = defaulted_eager_position_input< careless_text_position< std::size_t >, input >;
      using selected_text_input = defaulted_eager_position_input< selected_text_position< Eol, std::size_t >, input >;
      using paranoid_text_input = defaulted_eager_position_input< paranoid_text_position< Eol, std::size_t >, input >;

      using careless_text_count_input = defaulted_eager_position_input< careless_text_count_position< std::size_t >, input >;
      using selected_text_count_input = defaulted_eager_position_input< selected_text_count_position< Eol, std::size_t >, input >;
      using paranoid_text_count_input = defaulted_eager_position_input< paranoid_text_count_position< Eol, std::size_t >, input >;

      using lazy_count_input = internal::input_with_filename< internal::defaulted_lazy_position_input< internal::count_position< std::size_t >, input > >;
      using lazy_text_input = internal::input_with_filename< internal::defaulted_lazy_position_input< internal::careless_text_position< std::size_t >, input > >;
      using lazy_text_count_input = internal::input_with_filename< internal::defaulted_lazy_position_input< internal::careless_text_count_position< std::size_t >, input > >;
   };

   template< typename Eol, typename Input >
   struct line_based_dynamic_inputs
   {
      using input = internal::line_based_input< Eol, Input >;

      // Buffer inputs only work with simple eager positions, not lazy or restartable eager positions.

      using careless_text_input = defaulted_eager_position_input< careless_text_position< std::size_t >, input >;
      using selected_text_input = defaulted_eager_position_input< selected_text_position< Eol, std::size_t >, input >;
      using paranoid_text_input = defaulted_eager_position_input< paranoid_text_position< Eol, std::size_t >, input >;

      using initialized_careless_text_input = initialized_eager_position_input< careless_text_position< std::size_t >, input >;
      using initialized_selected_text_input = initialized_eager_position_input< selected_text_position< Eol, std::size_t >, input >;
      using initialized_paranoid_text_input = initialized_eager_position_input< paranoid_text_position< Eol, std::size_t >, input >;

      using careless_text_count_input = defaulted_eager_position_input< careless_text_count_position< std::size_t >, input >;
      using selected_text_count_input = defaulted_eager_position_input< selected_text_count_position< Eol, std::size_t >, input >;
      using paranoid_text_count_input = defaulted_eager_position_input< paranoid_text_count_position< Eol, std::size_t >, input >;

      using initialized_careless_text_count_input = initialized_eager_position_input< careless_text_count_position< std::size_t >, input >;
      using initialized_selected_text_count_input = initialized_eager_position_input< selected_text_count_position< Eol, std::size_t >, input >;
      using initialized_paranoid_text_count_input = initialized_eager_position_input< paranoid_text_count_position< Eol, std::size_t >, input >;
   };

}  // namespace tao::pegtl::internal

#endif
