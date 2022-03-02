// Copyright (c) 2014-2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_PEGTL_INTERNAL_RESULT_ON_FOUND_HPP
#define TAO_PEGTL_INTERNAL_RESULT_ON_FOUND_HPP

namespace tao::pegtl::internal
{
   enum class result_on_found : bool
   {
      success = true,
      failure = false
   };

   [[nodiscard]] constexpr result_on_found invert_on_found( const result_on_found rof ) noexcept
   {
      return result_on_found( !bool( rof ) );
   }

}  // namespace tao::pegtl::internal

#endif
