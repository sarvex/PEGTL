// Copyright (c) 2021-2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_PEGTL_INTERNAL_TEXT_COUNT_POSITION_HPP
#define TAO_PEGTL_INTERNAL_TEXT_COUNT_POSITION_HPP

#include <ostream>
#include <type_traits>

#include "any.hpp"
#include "eol.hpp"
#include "eof.hpp"
#include "peek_char.hpp"
#include "sor.hpp"
#include "until.hpp"

#include "text_count_rewind_position.hpp"
#include "type_tags.hpp"

namespace tao::pegtl::internal
{
   template< typename Size >
   struct [[nodiscard]] text_count_position
   {
      Size line = 1;
      Size count_in_line = 1;
      Size count = 0;

      using lazy_rule = until< eof, sor< eol, any< peek_char > > >;

      text_count_position() noexcept = default;

      text_count_position( const Size in_line, const Size in_count_in_line, const Size in_count ) noexcept
         : line( in_line ),
           count_in_line( in_count_in_line ),
           count( in_count )
      {
         // assert( in_line > 0 );
         // assert( in_count_in_line > 0 );
      }

      template< typename Data >
      explicit text_count_position( const text_count_rewind_position< Data, Size >& saved ) noexcept
         : line( saved.line ),
           count_in_line( saved.count_in_line ),
           count( saved.count )
      {}

      template< typename Rule, typename Data >
      void consume( const Data* /*unused*/, const Size n ) noexcept
      {
         if constexpr( std::is_same_v< Rule, eol_consume_tag > ) {
            ++line;
            count_in_line = 1;
         }
         else {
            count_in_line += n;
         }
         count += n;
      }

      template< typename Data >
      [[nodiscard]] auto rewind_save( const Data* current ) const noexcept
      {
         return text_count_rewind_position( current, line, count_in_line, count );
      }

      template< typename Data >
      [[nodiscard]] const Data* rewind_restore( const Data* /*unused*/, const internal::text_count_rewind_position< Data, Size >& saved ) noexcept
      {
         line = saved.line;
         count_in_line = saved.count_in_line;
         count = saved.count;
         return saved.current;
      }
   };

   template< typename Size >
   [[nodiscard]] bool operator==( const text_count_position< Size >& l, const text_count_position< Size >& r ) noexcept
   {
      return ( l.count == r.count ) && ( l.line == r.line ) && ( l.count_in_line == r.count_in_line );
   }

   template< typename Size >
   [[nodiscard]] bool operator!=( const text_count_position< Size >& l, const text_count_position< Size >& r ) noexcept
   {
      return !( l == r );
   }

   template< typename Size >
   std::ostream& operator<<( std::ostream& os, const text_count_position< Size >& p )
   {
      return os << p.line << ':' << p.count_in_line << '@' << p.count;
   }

}  // namespace tao::pegtl::internal

#endif
