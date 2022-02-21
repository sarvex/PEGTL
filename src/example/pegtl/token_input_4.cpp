// Copyright (c) 2020-2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#include <cassert>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include <tao/pegtl.hpp>

#include <tao/pegtl/internal/has_token_kind.hpp>

namespace tao::pegtl::internal
{
   template< typename Kind, typename String, typename Position >
   struct token
   {
      token() noexcept = default;  // For resize()

      template< typename S >
      token( const Kind t, S&& s, const Position& p )
         : kind( t ),
           data( std::forward< S >( s ) ),
           pos( p )
      {}

      Kind kind;
      String data;
      Position pos;
   };

   template< typename Kind, typename String, typename Position >
   struct token_state
   {
      std::vector< token< Kind, String, Position > > tokens;
   };

   // template< auto Kind >
   // struct token_action_impl
   // {
   //    template< typename ActionInput, typename State, typename... States >
   //    static void apply( const ActionInput& in, State& st, States&&... /*unused*/ )
   //    {
   //       st.tokens.emplace_back( Kind, in.string(), in.current_position() );
   //    }
   // };

   template< auto Kind >
   struct token_action_impl
   {
      template< typename Rule,
                apply_mode A,
                rewind_mode M,
                template< typename... >
                class Action,
                template< typename... >
                class Control,
                typename ParseInput,
                typename State,
                typename... States >
      [[nodiscard]] static bool match( ParseInput& in, State&& st, States&&... /*unused*/ )
      {
         const std::size_t n = st.tokens.size();
         if( !tao::pegtl::match< Rule, A, M, Action, Control >( in, st, n ) ) {
            st.tokens.resize( n );
            return false;
         }
         return true;
      }

      template< typename ActionInput, typename State, typename... States >
      static void apply( const ActionInput& in, State& st, States&&... /*unused*/ )
      {
         st.tokens.emplace_back( Kind, in.string(), in.current_position() );
      }

      template< typename ParseInput, typename State >
      static void unwind( const ParseInput& /*unused*/, State& st, const std::size_t n )
      {
         st.tokens.resize( n );
      }
   };

   template< template< typename... > class Traits >
   struct make_token_action
   {
      template< typename Rule >
      static auto base()
      {
         if constexpr( has_token_kind< Traits< Rule > > ) {
            return token_action_impl< Traits< Rule >::token_kind >();
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

}  // namespace tao::pegtl::internal

namespace tao::pegtl
{
   template< template< typename... > class Traits, typename Rule, typename ParseInput >
   [[nodiscard]] auto tokenize( ParseInput&& in )
   {
      // TODO: Actually we want text_position_base, not careless_text_position et al.
      internal::token_state< typename Traits< void >::token_kind_kind, std::string, std::decay_t< decltype( in.current_position() ) > > st;
      (void)parse< Rule, internal::make_token_action< Traits >::template type >( in, st );  // TODO: Better must< rule >?
      return std::move( st.tokens );
   };

}  // namespace tao::pegtl

using token = tao::pegtl::sor< tao::pegtl::plus< tao::pegtl::alpha >, tao::pegtl::plus< tao::pegtl::digit > >;
using grammar = tao::pegtl::must< tao::pegtl::list< token, tao::pegtl::space >, tao::pegtl::eof >;

template< typename Rule >
struct traits
{
   using token_kind_kind = int;
};

template<>
struct traits< tao::pegtl::plus< tao::pegtl::alpha > >
{
   static constexpr int token_kind = 42;
};

template<>
struct traits< tao::pegtl::plus< tao::pegtl::digit > >
{
   static constexpr int token_kind = 30;
};

int main()
{
   tao::pegtl::internal::fake_buffer_input< tao::pegtl::internal::defaulted_eager_position_input< tao::pegtl::internal::careless_text_position< unsigned >, tao::pegtl::internal::memory_input< char > > > in( "aaa 123 bbb 456 ccc" );
   const auto t = tao::pegtl::tokenize< traits, grammar >( in );
   assert( t.size() == 5 );
   std::cerr << t[ 3 ].kind << std::endl;
   std::cerr << t[ 3 ].data << std::endl;
   std::cerr << t[ 3 ].pos << std::endl;
   return 0;
}
