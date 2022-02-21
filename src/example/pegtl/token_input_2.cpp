// Copyright (c) 2020-2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#include <cassert>
#include <iostream>
#include <string>
#include <vector>

#include <tao/pegtl.hpp>

#include <tao/pegtl/internal/peek_member.hpp>

namespace tao::pegtl
{
   namespace member
   {
      template< auto M, auto... Ts > struct one : internal::one< internal::result_on_found::success, internal::peek_member< M >, Ts... > {};

   }  // namespace member

}  // namespace tao::pegtl

using namespace tao::pegtl;

enum my_type
{
   a,
   b,
   c
};

struct my_token
{
   my_type type;
   std::string data;
};

template< my_type... Ts >
using my_rule = tao::pegtl::member::one< &my_token::type, Ts... >;

struct my_state
{
   std::vector< std::string > as;
   std::vector< std::string > bs;
   unsigned cs = 0;
};

template< typename Rule >
struct my_action
   : nothing< Rule >
{};

template<>
struct my_action< my_rule< my_type::a > >
{
   template< typename ActionInput >
   static void apply( const ActionInput& in, my_state& st )
   {
      std::cout << "A";
      st.as.emplace_back( in.begin()->data );
   }
};

template<>
struct my_action< my_rule< my_type::b > >
{
   template< typename ActionInput >
   static void apply( const ActionInput& in, my_state& st )
   {
      std::cout << "B";
      st.as.emplace_back( in.begin()->data );
   }
};

template<>
struct my_action< my_rule< my_type::c > >
{
   static void apply0( my_state& st )
   {
      std::cout << "C";
      ++st.cs;
   }
};

struct any_token
   : sor< my_rule< my_type::a >, my_rule< my_type::b >, my_rule< my_type::c > >
{};

struct my_grammar
   : must< plus< any_token >, eof >
{};

int main()
{
   const std::vector< my_token > v{
      { my_type::a, "A1" },
      { my_type::b, "B1" },
      { my_type::c, "C1" },
      { my_type::c, "C2" },
      { my_type::a, "A2" },
      { my_type::b, "B2" }
   };
   my_state st;
   internal::fake_buffer_input< internal::container_input< std::vector< my_token > > > in( v );
   parse< my_grammar, my_action >( in, st );
   std::cout << std::endl;
   assert( st.cs == 2 );
   return 0;
}
