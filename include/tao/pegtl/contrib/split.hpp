// Copyright (c) 2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_PEGTL_CONTRIB_SPLIT_HPP
#define TAO_PEGTL_CONTRIB_SPLIT_HPP

#include <string>
#include <type_traits>
#include <utility>
#include <vector>

#include "../ascii.hpp"
#include "../inputs.hpp"
#include "../match.hpp"
#include "../nothing.hpp"
#include "../parse.hpp"
#include "../rules.hpp"

namespace tao::pegtl
{
   namespace internal
   {
      template< typename R >
      using split_grammar = seq< list< R, one< result_on_found::success, peek_char, ' ', '\t' > >, eof >;

      template< typename R, typename Rule >
      struct split_action_impl
         : nothing< Rule >
      {
         static_assert( !std::is_same_v< R, Rule > );
      };

      template< typename R >
      struct split_action_impl< R, R >
      {
         template< typename ActionInput, typename String >
         static void apply( const ActionInput& in, std::vector< String >& result )
         {
            result.emplace_back( in.string_view() );
         }
      };

      template< typename R >
      struct make_split_action
      {
         template< typename Rule >
         struct type
            : split_action_impl< R, Rule >
         {};
      };

      using default_split_rule = pegtl::plus< ascii::graph >;

   }  // namespace internal

   [[nodiscard]] bool split( const std::string& str, std::vector< std::string >& result )
   {
      memory_input in( str );
      return parse< internal::split_grammar< internal::default_split_rule >, internal::make_split_action< internal::default_split_rule >::template type >( in, result );
   }

   [[nodiscard]] std::vector< std::string > split( const std::string& str )
   {
      std::vector< std::string > result;
      memory_input in( str );
      (void)parse< must< internal::split_grammar< internal::default_split_rule > >, internal::make_split_action< internal::default_split_rule >::template type >( in, result );
      return result;
   }

}  // namespace tao::pegtl

#endif
