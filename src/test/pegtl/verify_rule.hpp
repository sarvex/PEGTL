// Copyright (c) 2014-2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_PEGTL_SRC_TEST_PEGTL_VERIFY_RULE_HPP
#define TAO_PEGTL_SRC_TEST_PEGTL_VERIFY_RULE_HPP

#include <cstdlib>
#include <string>

#include <tao/pegtl.hpp>

#include "result_type.hpp"
#include "verify_impl.hpp"

namespace tao::pegtl
{
   template< typename Rule >
   struct verify_action_impl
   {
      template< typename ActionInput, typename... States >
      static void apply( const ActionInput& /*unused*/, States&&... /*unused*/ )
      {}
   };

   template< typename Rule >
   struct verify_action_impl0
   {
      template< typename... States >
      static void apply0( States&&... /*unused*/ )
      {}
   };

   template< typename Rule, typename Eol = sor< lf, crlf > >
   void verify_rule( const std::size_t line, const char* file, const std::string& data, const result_type expected, int remain = -1 )
   {
      if( remain < 0 ) {
         remain = ( expected == result_type::success ) ? 0 : int( data.size() );
      }
      using input_t = internal::defaulted_eager_position_input< internal::careless_text_position< unsigned >, internal::fake_buffer_input< internal::restartable_input< internal::line_based_input< Eol, internal::memory_input< char > > > > >;
      {
         input_t in( data.data(), data.data() + data.size() );
         verify_impl_one< Rule, nothing >( line, file, data, in, expected, remain );
      }
      {
         input_t in( data.data(), data.data() + data.size() );
         verify_impl_one< Rule, verify_action_impl >( line, file, data, in, expected, remain );
      }
      {
         input_t in( data.data(), data.data() + data.size() );
         verify_impl_one< Rule, verify_action_impl0 >( line, file, data, in, expected, remain );
      }
   }

   template< typename Rule, typename Eol = sor< lf, crlf > >
   void verify_only( const std::size_t line, const char* file, const std::string& data, const result_type expected, const std::size_t remain )
   {
      using input_t = internal::defaulted_eager_position_input< internal::careless_text_position< unsigned >, internal::fake_buffer_input< internal::restartable_input< internal::line_based_input< Eol, internal::memory_input< char > > > > >;
      {
         input_t in( data.data(), data.data() + data.size() );
         verify_impl_one< Rule, nothing >( line, file, data, in, expected, remain );
      }
      {
         input_t in( data.data(), data.data() + data.size() );
         verify_impl_one< Rule, verify_action_impl >( line, file, data, in, expected, remain );
      }
      {
         input_t in( data.data(), data.data() + data.size() );
         verify_impl_one< Rule, verify_action_impl0 >( line, file, data, in, expected, remain );
      }
   }

}  // namespace tao::pegtl

#endif
