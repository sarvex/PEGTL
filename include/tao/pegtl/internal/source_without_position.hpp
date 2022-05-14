// Copyright (c) 2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_PEGTL_INTERNAL_SOURCE_WITHOUT_POSITION_HPP
#define TAO_PEGTL_INTERNAL_SOURCE_WITHOUT_POSITION_HPP

#include <ostream>
#include <utility>

namespace tao::pegtl::internal
{
   template< typename Source >
   struct source_without_position
   {
      Source source;

      template< typename S >
      explicit source_without_position( S&& s )
         : source( std::forward< S >( s ) )
      {}
   };

   template< typename Source >
   [[nodiscard]] bool operator==( const source_without_position< Source >& l, const source_without_position< Source >& r ) noexcept
   {
      return l.source == r.source;
   }

   template< typename Source >
   [[nodiscard]] bool operator!=( const source_without_position< Source >& l, const source_without_position< Source >& r ) noexcept
   {
      return !( l == r );
   }

   template< typename Source >
   std::ostream& operator<<( std::ostream& os, const source_without_position< Source >& p )
   {
      return os << p.source;
   }

}  // namespace tao::pegtl::internal

#endif
