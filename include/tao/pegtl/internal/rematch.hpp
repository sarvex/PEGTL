// Copyright (c) 2019-2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_PEGTL_INTERNAL_REMATCH_HPP
#define TAO_PEGTL_INTERNAL_REMATCH_HPP

#include "enable_control.hpp"

#include "../apply_mode.hpp"
#include "../rewind_mode.hpp"
#include "../type_list.hpp"

namespace tao::pegtl::internal
{
   template< typename Head, typename... Rules >
   struct rematch;

   template< typename Head >
   struct rematch< Head >
   {
      using rule_t = rematch;
      using subs_t = type_list< Head >;

      template< apply_mode A,
                rewind_mode M,
                template< typename... >
                class Action,
                template< typename... >
                class Control,
                typename ParseInput,
                typename... States >
      [[nodiscard]] static bool match( ParseInput& in, States&&... st )
      {
         return Control< Head >::template match< A, M, Action, Control >( in, st... );
      }
   };

   template< typename Head, typename Rule, typename... Rules >
   struct rematch< Head, Rule, Rules... >
   {
      using rule_t = rematch;
      using subs_t = type_list< Head, Rule, Rules... >;

      template< apply_mode A,
                rewind_mode,
                template< typename... >
                class Action,
                template< typename... >
                class Control,
                typename ParseInput,
                typename... States >
      [[nodiscard]] static bool match( ParseInput& in, States&&... st )
      {
         auto m = in.template make_rewind_guard< rewind_mode::required >();

         if( Control< Head >::template match< A, rewind_mode::optional, Action, Control >( in, st... ) ) {
            memory_input< ParseInput::tracking_mode_v, typename ParseInput::eol_t, typename ParseInput::source_t > i2( m.frobnicator(), in.current(), in.source() );
            using input_t = input_traits< ParseInput >::rematch_input_t;
            input_t i2( cherry_pick_tag(), m, in );
            return m( ( Control< Rule >::template match< A, rewind_mode::optional, Action, Control >( i2, st... ) && ... && ( i2.restart( m ), Control< Rules >::template match< A, rewind_mode::optional, Action, Control >( i2, st... ) ) ) );
         }
         return false;
      }

      // template< apply_mode A,
      //           rewind_mode,
      //           template< typename... >
      //           class Action,
      //           template< typename... >
      //           class Control,
      //           typename ParseInput,
      //           typename... States >
      // [[nodiscard]] static bool match( ParseInput& in, States&&... st )
      // {
      //    auto m = in.template make_rewind_guard< rewind_mode::required >();
      //    if( Control< Head >::template match< A, rewind_mode::optional, Action, Control >( in, st... ) ) {
      //       const auto n = in.template make_rewind_guard< rewind_mode::required >();
      //       const auto e = in.private_get_end();
      //       try {
      //          in.private_set_end( n.current() );
      //          const bool r = ( ( m.repeatable_rewind(), Control< Rule >::template match< A, rewind_mode::optional, Action, Control >( in, st... ) ) && ... && ( m.repeatable_rewind(), Control< Rules >::template match< A, rewind_mode::optional, Action, Control >( in, st... ) ) );
      //          in.private_set_end( e );
      //          if( r ) {
      //             m.cancel_rewind();
      //             // if( in.current() == n.current() ) {
      //             //    n.cancel_rewind();  // Optional: Suppress redundant rewind to n.
      //             // }
      //             return true;  // Implicit "rewind" to n.
      //          }
      //          // n.cancel_rewind();  // Optional: Suppress redundant rewind to n.
      //       }
      //       catch( ... ) {
      //          // n.cancel_rewind();  // Optional: Suppress redundant rewind to n.
      //          in.private_set_end( e );
      //          throw;
      //       }
      //    }
      //    return m( false );
      // }
   };

   template< typename Head, typename... Rules >
   inline constexpr bool enable_control< rematch< Head, Rules... > > = false;

}  // namespace tao::pegtl::internal

#endif
