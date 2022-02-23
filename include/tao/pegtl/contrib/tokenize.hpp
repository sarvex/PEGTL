// Copyright (c) 2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_PEGTL_CONTRIB_TOKENIZE_HPP
#define TAO_PEGTL_CONTRIB_TOKENIZE_HPP

#include <string>
#include <type_traits>
#include <utility>
#include <vector>

#include "../parse.hpp"

namespace tao::pegtl
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

      [[nodiscard]] const Position& current_position() const noexcept
      {
         return pos;
      }
   };

   namespace internal
   {
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
            st.tokens.resize( n );  // TODO: Do we really need this here?
         }
      };

      template< typename, typename = void >
      inline constexpr bool has_token_kind = false;

      template< typename C >
      inline constexpr bool has_token_kind< C, decltype( C::token_kind, void() ) > = true;

      template< template< typename... > class Traits >
      struct make_token_action
      {
         template< typename Rule >
         static auto base()
         {
            if constexpr( has_token_kind< Traits< Rule > > ) {
               return token_action_impl< Traits< Rule >::token_kind >();
            }
            else if constexpr( has_token_kind< Rule > ) {
               return token_action_impl< Rule::token_kind >();
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

      template< typename... >
      struct empty_tokenize_traits
      {};

   }  // namespace internal

   template< typename Kind, typename Rule, typename ParseInput >
   [[nodiscard]] auto tokenize( ParseInput&& in )
   {
      // TODO: Actually we want text_position_base, not careless_text_position et al.
      internal::token_state< Kind, std::string, std::decay_t< decltype( in.current_position() ) > > st;
      (void)parse< Rule, internal::make_token_action< internal::empty_tokenize_traits >::template type >( in, st );  // TODO: Better must< rule >?
      return std::move( st.tokens );
   };

   template< template< typename... > class Traits, typename Rule, typename ParseInput >
   [[nodiscard]] auto tokenize( ParseInput&& in )
   {
      // TODO: Actually we want text_position_base, not careless_text_position et al.
      internal::token_state< typename Traits< void >::token_kind_kind, std::string, std::decay_t< decltype( in.current_position() ) > > st;
      (void)parse< Rule, internal::make_token_action< Traits >::template type >( in, st );  // TODO: Better must< rule >?
      return std::move( st.tokens );
   };

}  // namespace tao::pegtl

#endif
