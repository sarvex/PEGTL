// Copyright (c) 2020-2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#include <cassert>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include <tao/pegtl.hpp>

#include <tao/pegtl/internal/has_token_type.hpp>

namespace tao::pegtl::internal
{
   template< typename Type, typename String, typename Position >
   struct token
   {
      template< typename S >
      token( const Type t, S&& s, const Position& p )
         : type( t ),
           data( std::forward< S >( s ) ),
           pos( p )
      {}

      Type type;
      String data;
      Position pos;
   };

   template< typename Type, typename String, typename Position >
   struct token_state
   {
      std::vector< token< Type, String, Position > > tokens;
   };

   template< auto Type >
   struct token_action_impl
   {
      template< typename ActionInput, typename State >
      static void apply( const ActionInput& in, State& st )
      {
         st.tokens.emplace_back( Type, in.string(), in.current_position() );
      }
   };

   template< template< typename... > class Traits >
   struct make_token_action
   {
      template< typename Rule >
      static auto base()
      {
         if constexpr( has_token_type< Traits< Rule > > ) {
            return token_action_impl< Traits< Rule >::token_type >();
         }
         else {
            return nothing< Rule >();
         }
      }

      template< typename Rule >
      struct type
         : decltype( base< Rule >() )
      {};
   };

   // TODO: BACKTRACKING OF THE STATE!!!

}  // namespace tao::pegtl::internal

namespace tao::pegtl
{
   template< template< typename... > class Traits, typename Rule, typename ParseInput >
   [[nodiscard]] auto tokenize( ParseInput&& in )
   {
      // TODO: Actually we want text_position_base, not careless_text_position et al.
      internal::token_state< typename Traits< void >::token_type_type, std::string, std::decay_t< decltype( in.current_position() ) > > st;
      (void)parse< Rule, internal::make_token_action< Traits >::template type >( in, st );  // TODO: Better must< rule >?
      return std::move( st.tokens );
   };

}  // namespace tao::pegtl

using token = tao::pegtl::sor< tao::pegtl::plus< tao::pegtl::alpha >, tao::pegtl::plus< tao::pegtl::digit > >;
using grammar = tao::pegtl::must< tao::pegtl::list< token, tao::pegtl::space >, tao::pegtl::eof >;

template< typename Rule >
struct traits
{
   using token_type_type = int;
};

template<>
struct traits< tao::pegtl::plus< tao::pegtl::alpha > >
{
   static constexpr int token_type = 42;
};

template<>
struct traits< tao::pegtl::plus< tao::pegtl::digit > >
{
   static constexpr int token_type = 30;
};

int main()
{
   tao::pegtl::internal::fake_buffer_input< tao::pegtl::internal::defaulted_eager_position_input< tao::pegtl::internal::careless_text_position< unsigned >, tao::pegtl::internal::memory_input< char > > > in( "aaa 123 bbb 456 ccc" );
   const auto t = tao::pegtl::tokenize< traits, grammar >( in );
   assert( t.size() == 5 );
   std::cerr << t[ 3 ].type << std::endl;
   std::cerr << t[ 3 ].data << std::endl;
   std::cerr << t[ 3 ].pos << std::endl;
   return 0;
}
