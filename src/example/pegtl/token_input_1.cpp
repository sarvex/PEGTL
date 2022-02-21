// Copyright (c) 2020-2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#include <cassert>
#include <iostream>
#include <string>
#include <vector>

#include <tao/pegtl.hpp>

#include <tao/pegtl/contrib/analyze_traits.hpp>

namespace tao::pegtl
{
   namespace internal
   {
      template< typename Type, Type Value >
      struct token_type
      {
         using rule_t = token_type;
         using subs_t = empty_list;

         template< typename ParseInput >
         static bool match( ParseInput& in )
         {
            if( ( !in.empty() ) && ( in.current()->type == Value ) ) {
               in.template consume< token_type >( 1 );
               return true;
            }
            return false;
         }
      };

   }  // namespace internal

   template< auto Value >
   using token_type = internal::token_type< decltype( Value ), Value >;

   template< typename Name, typename Type, Type Value >
   struct analyze_traits< Name, internal::token_type< Type, Value > >
      : analyze_any_traits<>
   {};

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
struct my_action< token_type< my_type::a > >
{
   template< typename ActionInput >
   static void apply( const ActionInput& in, my_state& st )
   {
      std::cout << "A";
      st.as.emplace_back( in.begin()->data );
   }
};

template<>
struct my_action< token_type< my_type::b > >
{
   template< typename ActionInput >
   static void apply( const ActionInput& in, my_state& st )
   {
      std::cout << "B";
      st.as.emplace_back( in.begin()->data );
   }
};

template<>
struct my_action< token_type< my_type::c > >
{
   static void apply0( my_state& st )
   {
      std::cout << "C";
      ++st.cs;
   }
};

struct any_token
   : sor< token_type< my_type::a >, token_type< my_type::b >, token_type< my_type::c > >
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
   internal::container_input< std::vector< my_token > > in( v );
   parse< my_grammar, my_action >( in, st );
   std::cout << std::endl;
   assert( st.cs == 2 );
   return 0;
}
