// Copyright (c) 2021-2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_PEGTL_INTERNAL_TEXT_POSITION_BASE_HPP
#define TAO_PEGTL_INTERNAL_TEXT_POSITION_BASE_HPP

#include <ostream>
#include <type_traits>

#include "consume.hpp"
#include "eol.hpp"
#include "eof.hpp"
#include "sor.hpp"
#include "until.hpp"

#include "text_rewind_position.hpp"

namespace tao::pegtl::internal
{
   template< typename Size >
   struct [[nodiscard]] text_position_base
   {
      Size line = 1;
      Size count_in_line = 1;

      using lazy_rule = until< eof, sor< eol, consume< 1 > > >;

      text_position_base() noexcept = default;

      text_position_base( const Size in_line, const Size in_count_in_line ) noexcept
         : line( in_line ),
           count_in_line( in_count_in_line )
      {
         // assert( in_line > 0 );
         // assert( in_count_in_line > 0 );
      }

      template< typename Data >
      explicit text_position_base( const text_rewind_position< Data, Size >& saved ) noexcept
         : line( saved.line ),
           count_in_line( saved.count_in_line )
      {}

      template< typename Data >
      [[nodiscard]] auto rewind_save( const Data* current ) const noexcept
      {
         return text_rewind_position( current, line, count_in_line );
      }

      template< typename Data >
      [[nodiscard]] const Data* rewind_restore( const Data* /*unused*/, const internal::text_rewind_position< Data, Size >& saved ) noexcept
      {
         line = saved.line;
         count_in_line = saved.count_in_line;
         return saved.current;
      }
   };

   template< typename Size >
   [[nodiscard]] bool operator==( const text_position_base< Size >& l, const text_position_base< Size >& r ) noexcept
   {
      return ( l.line == r.line ) && ( l.count_in_line == r.count_in_line );
   }

   template< typename Size >
   [[nodiscard]] bool operator!=( const text_position_base< Size >& l, const text_position_base< Size >& r ) noexcept
   {
      return !( l == r );
   }

   template< typename Size >
   std::ostream& operator<<( std::ostream& os, const text_position_base< Size >& p )
   {
      return os << p.line << ':' << p.count_in_line;
   }

}  // namespace tao::pegtl::internal

#endif
