// Copyright (c) 2021 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_PEGTL_INTERNAL_POINTER_POSITION_HPP
#define TAO_PEGTL_INTERNAL_POINTER_POSITION_HPP

#include <ostream>

#include "everything.hpp"

namespace tao::pegtl::internal
{
   template< typename Data >
   struct pointer_position
   {
      const Data* current;

      using lazy_rule = everything;

      explicit pointer_position( const Data* c ) noexcept
         : current( c )
      {}
   };

   template< typename Data >
   pointer_position( const Data* ) -> pointer_position< Data >;

   template< typename Data >
   [[nodiscard]] bool operator==( const pointer_position< Data >& l, const pointer_position< Data >& r ) noexcept
   {
      return l.current == r.current;
   }

   template< typename Data >
   [[nodiscard]] bool operator!=( const pointer_position< Data >& l, const pointer_position< Data >& r ) noexcept
   {
      return !( l == r );
   }

   template< typename Data >
   std::ostream& operator<<( std::ostream& os, const pointer_position< Data >& p )
   {
      return os << static_cast< const void* >( p.current );
   }

}  // namespace tao::pegtl::internal

#endif
