// Copyright (c) 2017-2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_PEGTL_CONTRIB_REP_ONE_MIN_MAX_HPP
#define TAO_PEGTL_CONTRIB_REP_ONE_MIN_MAX_HPP

#include <algorithm>
#include <type_traits>

#include "../analyze_traits.hpp"
#include "../type_list.hpp"

#include "../internal/enable_control.hpp"
#include "../internal/opt.hpp"

namespace tao::pegtl
{
   namespace internal
   {
      template< unsigned Min, unsigned Max, char C >
      struct rep_one_min_max
      {
         using rule_t = rep_one_min_max;
         using subs_t = empty_list;

         static_assert( Min <= Max );

         // [[nodiscard]] static constexpr bool test_one( const char c ) noexcept
         // {
         //    static_assert( ( Min == 1 ) && ( Max == 1 ) );
         //    return C == c;
         // }

         template< typename ParseInput >
         [[nodiscard]] static bool match( ParseInput& in )
         {
            static_assert( sizeof( *in.current() ) == 1 );
            const auto size = in.size( Max + 1 );
            if( size < Min ) {
               return false;
            }
            unsigned i = 0;
            while( ( i < size ) && ( static_cast< char >( i[ in.current() ] ) == C ) ) {
               ++i;
            }
            if( ( Min <= i ) && ( i <= Max ) ) {
               in.template consume< rep_one_min_max >( i );
               return true;
            }
            return false;
         }
      };

      template< unsigned Max, char C >
      struct rep_one_min_max< 0, Max, C >
      {
         using rule_t = rep_one_min_max;
         using subs_t = empty_list;

         template< typename ParseInput >
         [[nodiscard]] static bool match( ParseInput& in )
         {
            static_assert( sizeof( *in.current() ) == 1 );
            const auto size = in.size( Max + 1 );
            unsigned i = 0;
            while( ( i < size ) && ( static_cast< char >( i[ in.current() ] ) == C ) ) {
               ++i;
            }
            if( i <= Max ) {
               in.template consume< rep_one_min_max >( i );
               return true;
            }
            return false;
         }
      };

      template< unsigned Min, unsigned Max, char C >
      inline constexpr bool enable_control< rep_one_min_max< Min, Max, C > > = false;

   }  // namespace internal

   inline namespace ascii
   {
      template< unsigned Min, unsigned Max, char C >
      struct rep_one_min_max
         : internal::rep_one_min_max< Min, Max, C >
      {};

   }  // namespace ascii

   template< typename Name, unsigned Min, unsigned Max, char C >
   struct analyze_traits< Name, internal::rep_one_min_max< Min, Max, C > >
      : std::conditional_t< ( Min != 0 ), analyze_any_traits<>, analyze_opt_traits<> >
   {};

}  // namespace tao::pegtl

#endif
