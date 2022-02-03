// Copyright (c) 2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_PEGTL_INTERNAL_BYTE_POSITION_HPP
#define TAO_PEGTL_INTERNAL_BYTE_POSITION_HPP

#include <ostream>

#include "byte_rewind_position.hpp"
#include "everything.hpp"

namespace tao::pegtl::internal
{
   template< typename Size >
   struct [[nodiscard]] byte_position
   {
      Size byte = 0;

      using lazy_rule = everything;

      explicit byte_position( const Size b = 0 ) noexcept
         : byte( b )
      {}

      template< typename Data >
      explicit byte_position( const byte_rewind_position< Data, Size >& saved )
         : byte( saved.byte )
      {
         static_assert( sizeof( Data ) == 1 );
      }

      template< typename Rule, typename Data >
      void consumed( const Data* /*unused*/, const std::size_t n ) noexcept
      {
         static_assert( sizeof( Data ) == 1);
         byte += n;
      }

      template< typename Data >
      [[nodiscard]] auto rewind_save( const Data* current ) const noexcept
      {
         static_assert( sizeof( Data ) == 1);
         return byte_rewind_position( current, byte );
      }

      template< typename Data >
      [[nodiscard]] const Data* rewind_restore( const Data* /*unused*/, const byte_rewind_position< Data, Size >& saved ) noexcept
      {
         static_assert( sizeof( Data ) == 1);
         byte = saved.byte;
         return saved.current;
      }
   };

   template< typename Size >
   [[nodiscard]] bool operator==( const byte_position< Size >& l, const byte_position< Size >& r ) noexcept
   {
      return l.byte == r.byte;
   }

   template< typename Size >
   [[nodiscard]] bool operator!=( const byte_position< Size >& l, const byte_position< Size >& r ) noexcept
   {
      return !( l == r );
   }

   template< typename Size >
   std::ostream& operator<<( std::ostream& os, const byte_position< Size >& p )
   {
      return os << p.byte;
   }

}  // namespace tao::pegtl::internal

#endif
