// Copyright (c) 2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_PEGTL_CONTRIB_INT16_HPP
#define TAO_PEGTL_CONTRIB_INT16_HPP

#include "../internal/result_on_found.hpp"
#include "../internal/rules.hpp"

#include "internal/peek_int.hpp"

namespace tao::pegtl
{
   namespace int16_be
   {
      // clang-format off
      struct any : internal::any< internal::peek_int16_be > {};

      template< std::int16_t... Cs > struct not_one : internal::one< internal::result_on_found::failure, internal::peek_int16_be, Cs... > {};
      template< std::int16_t Lo, std::int16_t Hi > struct not_range : internal::range< internal::result_on_found::failure, internal::peek_int16_be, Lo, Hi > {};
      template< std::int16_t... Cs > struct one : internal::one< internal::result_on_found::success, internal::peek_int16_be, Cs... > {};
      template< std::int16_t Lo, std::int16_t Hi > struct range : internal::range< internal::result_on_found::success, internal::peek_int16_be, Lo, Hi > {};
      template< std::int16_t... Cs > struct ranges : internal::ranges< internal::peek_int16_be, Cs... > {};
      template< std::int16_t... Cs > struct string : internal::seq< internal::one< internal::result_on_found::success, internal::peek_int16_be, Cs >... > {};
      // clang-format on

   }  // namespace int16_be

   namespace int16_le
   {
      // clang-format off
      struct any : internal::any< internal::peek_int16_le > {};

      template< std::int16_t... Cs > struct not_one : internal::one< internal::result_on_found::failure, internal::peek_int16_le, Cs... > {};
      template< std::int16_t Lo, std::int16_t Hi > struct not_range : internal::range< internal::result_on_found::failure, internal::peek_int16_le, Lo, Hi > {};
      template< std::int16_t... Cs > struct one : internal::one< internal::result_on_found::success, internal::peek_int16_le, Cs... > {};
      template< std::int16_t Lo, std::int16_t Hi > struct range : internal::range< internal::result_on_found::success, internal::peek_int16_le, Lo, Hi > {};
      template< std::int16_t... Cs > struct ranges : internal::ranges< internal::peek_int16_le, Cs... > {};
      template< std::int16_t... Cs > struct string : internal::seq< internal::one< internal::result_on_found::success, internal::peek_int16_le, Cs >... > {};
      // clang-format on

   }  // namespace int16_le

}  // namespace tao::pegtl

#endif
