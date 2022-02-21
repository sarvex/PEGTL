// Copyright (c) 2020-2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#include <cassert>
#include <iostream>
#include <string>
#include <vector>

#include <tao/pegtl.hpp>

using namespace tao::pegtl;

enum my_kind
{
   a,
   b,
   c
};

struct my_token
{
   my_kind kind;
   std::string data;
};

template< my_kind... Ts >  // Two equivalent versions:
// using my_rule = tao::pegtl::member::one< &my_token::kind, Ts... >;
using my_rule = tao::pegtl::member::rules< &my_token::kind >::one< Ts... >;

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
struct my_action< my_rule< my_kind::a > >
{
   template< typename ActionInput >
   static void apply( const ActionInput& in, my_state& st )
   {
      std::cout << "A";
      st.as.emplace_back( in.begin()->data );
   }
};

template<>
struct my_action< my_rule< my_kind::b > >
{
   template< typename ActionInput >
   static void apply( const ActionInput& in, my_state& st )
   {
      std::cout << "B";
      st.as.emplace_back( in.begin()->data );
   }
};

template<>
struct my_action< my_rule< my_kind::c > >
{
   static void apply0( my_state& st )
   {
      std::cout << "C";
      ++st.cs;
   }
};

struct any_token
   : sor< my_rule< my_kind::a >, my_rule< my_kind::b >, my_rule< my_kind::c > >
{};

struct my_grammar
   : must< plus< any_token >, eof >
{};

int main()
{
   const std::vector< my_token > v{
      { my_kind::a, "A1" },
      { my_kind::b, "B1" },
      { my_kind::c, "C1" },
      { my_kind::c, "C2" },
      { my_kind::a, "A2" },
      { my_kind::b, "B2" }
   };
   my_state st;
   internal::fake_buffer_input< internal::container_input< std::vector< my_token > > > in( v );
   parse< my_grammar, my_action >( in, st );
   std::cout << std::endl;
   assert( st.cs == 2 );
   return 0;
}
