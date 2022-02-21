// Copyright (c) 2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_PEGTL_MEMBER_HPP
#define TAO_PEGTL_MEMBER_HPP

#include <type_traits>

#include "internal/peek_member.hpp"
#include "internal/result_on_found.hpp"
#include "internal/rules.hpp"

namespace tao::pegtl::member
{
   // clang-format off
   template< auto M, auto... Ts > struct not_one : internal::one< internal::result_on_found::failure, internal::peek_member< M >, Ts... > {};
   template< auto M, auto Lo, auto Hi > struct not_range : internal::range< internal::result_on_found::failure, internal::peek_member< M >, Lo, Hi > {};
   template< auto M, auto... Ts > struct one : internal::one< internal::result_on_found::success, internal::peek_member< M >, Ts... > {};
   template< auto M, auto Lo, auto Hi > struct range : internal::range< internal::result_on_found::success, internal::peek_member< M >, Lo, Hi > {};
   template< auto M, auto... Ts > struct ranges : internal::ranges< internal::peek_member< M >, Ts... > {};
   template< auto M, auto... Ts > struct string : internal::seq< internal::one< internal::result_on_found::success, internal::peek_member< M >, Ts >... > {};
   // clang-format on

   template< auto M >
   struct rules  // TODO: Keep structs, use using, or remove?
   {
      // clang-format off
      template< auto... Ts > struct not_one : internal::one< internal::result_on_found::failure, internal::peek_member< M >, Ts... > {};
      template< auto Lo, auto Hi > struct not_range : internal::range< internal::result_on_found::failure, internal::peek_member< M >, Lo, Hi > {};
      template< auto... Ts > struct one : internal::one< internal::result_on_found::success, internal::peek_member< M >, Ts... > {};
      template< auto Lo, auto Hi > struct range : internal::range< internal::result_on_found::success, internal::peek_member< M >, Lo, Hi > {};
      template< auto... Ts > struct ranges : internal::ranges< internal::peek_member< M >, Ts... > {};
      template< auto... Ts > struct string : internal::seq< internal::one< internal::result_on_found::success, internal::peek_member< M >, Ts >... > {};
      // clang-format on
   };

}  // namespace tao::pegtl::member

#endif
