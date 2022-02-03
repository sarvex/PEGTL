// Copyright (c) 2021-2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_PEGTL_INTERNAL_TEXT_POSITION_HPP
#define TAO_PEGTL_INTERNAL_TEXT_POSITION_HPP

#include <ostream>
#include <type_traits>

#include "any.hpp"
#include "eol.hpp"
#include "eof.hpp"
#include "peek_char.hpp"
#include "sor.hpp"
#include "until.hpp"

#include "text_rewind_position.hpp"
#include "type_tags.hpp"

namespace tao::pegtl::internal
{
   template< typename Size >
   struct [[nodiscard]] text_position
   {
      Size line = 1;
      Size byte_in_line = 1;

      using lazy_rule = until< eof, sor< eol, any< peek_char > > >;

      text_position() noexcept = default;

      text_position( const Size in_line, const Size in_byte_in_line ) noexcept
         : line( in_line ),
           byte_in_line( in_byte_in_line )
      {
         // assert( in_line > 0 );
         // assert( in_byte_in_line > 0 );
      }

      template< typename Data >
      explicit text_position( const text_rewind_position< Data, Size >& saved ) noexcept
         : line( saved.line ),
           byte_in_line( saved.byte_in_line )
      {
         static_assert( sizeof( Data ) == 1 );
      }

      template< typename Rule, typename Data >
      void consume( const Data* /*unused*/, const Size n ) noexcept
      {
         static_assert( sizeof( Data ) == 1 );

         if constexpr( std::is_same_v< Rule, eol_consume_tag > ) {
            ++line;
            byte_in_line = 1;
         }
         else {
            byte_in_line += n;
         }
      }

      template< typename Data >
      [[nodiscard]] auto rewind_save( const Data* current ) const noexcept
      {
         static_assert( sizeof( Data ) == 1 );
         return text_rewind_position( current, line, byte_in_line );
      }

      template< typename Data >
      [[nodiscard]] const Data* rewind_restore( const Data* /*unused*/, const internal::text_rewind_position< Data, Size >& saved ) noexcept
      {
         static_assert( sizeof( Data ) == 1 );
         line = saved.line;
         byte_in_line = saved.byte_in_line;
         return saved.current;
      }
   };

   template< typename Size >
   [[nodiscard]] bool operator==( const text_position< Size >& l, const text_position< Size >& r ) noexcept
   {
      return ( l.line == r.line ) && ( l.byte_in_line == r.byte_in_line );
   }

   template< typename Size >
   [[nodiscard]] bool operator!=( const text_position< Size >& l, const text_position< Size >& r ) noexcept
   {
      return !( l == r );
   }

   template< typename Size >
   std::ostream& operator<<( std::ostream& os, const text_position< Size >& p )
   {
      return os << p.line << ':' << p.byte_in_line;
   }

}  // namespace tao::pegtl::internal

#endif
