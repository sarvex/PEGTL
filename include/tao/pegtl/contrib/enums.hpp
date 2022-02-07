// Copyright (c) 2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_PEGTL_CONTRIB_ENUMS_HPP
#define TAO_PEGTL_CONTRIB_ENUMS_HPP

#include <type_traits>

#include "../internal/result_on_found.hpp"
#include "../internal/rules.hpp"

#include "internal/peek_enums.hpp"

namespace tao::pegtl
{
   namespace enums_be
   {
      // clang-format off
      // struct any : internal::any< internal::peek_int32_be > {};
      template< auto E, decltype( E )... Es > struct not_one : internal::one< internal::result_on_found::failure, internal::peek_enums_be< decltype( E ) >, E, Es... > {};
      template< auto Lo, decltype( Lo ) Hi > struct not_range : internal::range< internal::result_on_found::failure, internal::peek_enums_be< decltype( E ) >, Lo, Hi > {};
      template< auto E, decltype( E )... Es > struct one : internal::one< internal::result_on_found::success, internal::peek_enums_be< decltype( E ) >, E, Es... > {};
      template< auto Lo, decltype( Lo ) Hi > struct range : internal::range< internal::result_on_found::success, internal::peek_enums_be< decltype( E ) >, Lo, Hi > {};
      template< auto E, decltype( E )... Es > struct ranges : internal::ranges< internal::peek_enums_be< decltype( E ) >, E, Es... > {};
      template< auto E, decltype( E )... Es > struct string : internal::seq< internal::one< internal::result_on_found::success, internal::peek_enums_be< decltype( E ) >, E >, internal::one< internal::result_on_found::success, internal::peek_enums_be< decltype( E ) >, Es >... > {};
      // clang-format on

   }  // namespace int32_be

   namespace enums_le
   {
      // clang-format off
      // struct any : internal::any< internal::peek_int32_le > {};
      template< auto E, decltype( E )... Es > struct not_one : internal::one< internal::result_on_found::failure, internal::peek_enums_le< decltype( E ) >, E, Es... > {};
      template< auto Lo, decltype( Lo ) Hi > struct not_range : internal::range< internal::result_on_found::failure, internal::peek_enums_le< decltype( E ) >, Lo, Hi > {};
      template< auto E, decltype( E )... Es > struct one : internal::one< internal::result_on_found::success, internal::peek_enums_le< decltype( E ) >, E, Es... > {};
      template< auto Lo, decltype( Lo ) Hi > struct range : internal::range< internal::result_on_found::success, internal::peek_enums_le< decltype( E ) >, Lo, Hi > {};
      template< auto E, decltype( E )... Es > struct ranges : internal::ranges< internal::peek_enums_le< decltype( E ) >, E, Es... > {};
      template< auto E, decltype( E )... Es > struct string : internal::seq< internal::one< internal::result_on_found::success, internal::peek_enums_le< decltype( E ) >, E >, internal::one< internal::result_on_found::success, internal::peek_enums_le< decltype( E ) >, Es >... > {};
      // clang-format on

   }  // namespace int32_le

   namespace enums = TAO_PEGTL_ENDIAN_SUFFIXED( enums_ );

}  // namespace tao::pegtl

#endif
