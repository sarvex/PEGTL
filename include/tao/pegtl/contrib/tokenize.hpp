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
      using kind_t = Kind;
      using string_t = String;
      using position_t = Position;

      token() noexcept = default;  // For std::vector< token >::resize()

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
                   typename Token,
                   typename... States >
         [[nodiscard]] static bool match( ParseInput& in, std::vector< Token >& st, States&&... /*unused*/ )
         {
            const std::size_t n = st.size();
            if( !tao::pegtl::match< Rule, A, M, Action, Control >( in, st, n ) ) {
               st.resize( n );
               return false;
            }
            return true;
         }

         template< typename ActionInput, typename Token, typename... States >
         static void apply( const ActionInput& in, std::vector< Token >& st, States&&... /*unused*/ )
         {
            st.emplace_back( Kind, in.string(), in.current_position() );
         }

         template< typename ParseInput, typename Token >
         static void unwind( const ParseInput& /*unused*/, std::vector< Token >& st, const std::size_t n )
         {
            st.resize( n );  // TODO: Do we really need this here?
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

   template< typename Rule, typename ParseInput, typename Token >
   [[nodiscard]] bool tokenize( ParseInput&& in, std::vector< Token >& result )
   {
      return parse< Rule, internal::make_token_action< internal::empty_tokenize_traits >::template type >( in, result );
   };

   template< template< typename...> class Traits, typename Rule, typename ParseInput, typename Token >
   [[nodiscard]] bool tokenize( ParseInput&& in, std::vector< Token >& result )
   {
      return parse< Rule, internal::make_token_action< Traits >::template type >( in, result );
   }

   template< typename Kind, typename Rule, typename ParseInput >
   [[nodiscard]] auto tokenize( ParseInput&& in )
   {
      // TODO: Actually we want text_position_base, not careless_text_position et al.
      using token_t = token< Kind, std::string, std::decay_t< decltype( in.current_position() ) > >;
      std::vector< token_t > result;
      (void)tokenize< must< Rule > >( in, result );
      return result;
   };

   template< template< typename... > class Traits, typename Rule, typename ParseInput >
   [[nodiscard]] auto tokenize( ParseInput&& in )
   {
      // TODO: Actually we want text_position_base, not careless_text_position et al.
      using kind_t = typename Traits< void >::token_kind_type;
      using token_t = token< kind_t, std::string, std::decay_t< decltype( in.current_position() ) > >;
      std::vector< token_t > result;
      (void)tokenize< Traits, must< Rule > >( in, result );
      return result;
   };

}  // namespace tao::pegtl

#endif
