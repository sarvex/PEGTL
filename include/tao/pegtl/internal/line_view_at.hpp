// Copyright (c) 2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_PEGTL_INTERNAL_LINE_VIEW_AT_HPP
#define TAO_PEGTL_INTERNAL_LINE_VIEW_AT_HPP

#include <string_view>
#include <type_traits>

#include "../apply_mode.hpp"
#include "../normal.hpp"
#include "../nothing.hpp"
#include "../rewind_mode.hpp"

#include "at.hpp"
#include "eolf.hpp"
#include "input_traits.hpp"
#include "until.hpp"

namespace tao::pegtl::internal
{
   template< typename Input, typename RewindPosition >
   [[nodiscard]] const char* begin_of_line( const Input& /*unused*/, const RewindPosition& p ) noexcept
   {
      return p.current - p.count_in_line + 1;
   }

   template< typename Input, typename RewindPosition >
   [[nodiscard]] const char* end_of_line_or_file( const Input& in, const RewindPosition& p ) noexcept
   {
      using input_t = typename input_traits< Input >::memory_input_t;
      input_t i2( p.current, in.end() );
      using grammar = internal::until< internal::at< internal::eolf > >;
      (void)normal< grammar >::match< apply_mode::nothing, rewind_mode::dontcare, nothing, normal >( i2 );
      return i2.current();
   }

   template< typename Input, typename RewindPosition >
   [[nodiscard]] std::string_view line_view_at( const Input& in, const RewindPosition& p ) noexcept
   {
      const char* begin = begin_of_line( in, p );
      const char* end = end_of_line_or_file( in, p );
      return std::string_view( begin, end - begin );
   }

}  // namespace tao::pegtl::internal

#endif
