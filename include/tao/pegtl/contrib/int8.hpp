// Copyright (c) 2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_PEGTL_CONTRIB_INT8_HPP
#define TAO_PEGTL_CONTRIB_INT8_HPP

#include "../internal/result_on_found.hpp"
#include "../internal/rules.hpp"

#include "internal/peek_int8.hpp"

namespace tao::pegtl::int8
{
   // clang-format off
   struct any : internal::any< internal::peek_int8 > {};

   template< std::int8_t... Cs > struct not_one : internal::one< internal::result_on_found::failure, internal::peek_int8, Cs... > {};
   template< std::int8_t Lo, std::int8_t Hi > struct not_range : internal::range< internal::result_on_found::failure, internal::peek_int8, Lo, Hi > {};
   template< std::int8_t... Cs > struct one : internal::one< internal::result_on_found::success, internal::peek_int8, Cs... > {};
   template< std::int8_t Lo, std::int8_t Hi > struct range : internal::range< internal::result_on_found::success, internal::peek_int8, Lo, Hi > {};
   template< std::int8_t... Cs > struct ranges : internal::ranges< internal::peek_int8, Cs... > {};
   template< std::int8_t... Cs > struct string : internal::seq< internal::one< internal::result_on_found::success, internal::peek_int8, Cs >... > {};
   // clang-format on

}  // namespace tao::pegtl::int8

#endif
