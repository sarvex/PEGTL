// Copyright (c) 2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_PEGTL_INTERNAL_POSITION_WITH_SOURCE_HPP
#define TAO_PEGTL_INTERNAL_POSITION_WITH_SOURCE_HPP

#include <ostream>
#include <utility>

namespace tao::pegtl::internal
{
   template< typename Source, typename Position >
   struct [[nodiscard]] position_with_source
      : Position
   {
      Source source;

      template< typename S, typename... As >
      explicit position_with_source( S&& s, As&&... as )
         : Position( std::forward< As >( as )... ),
           source( std::forward< S >( s ) )
      {}

      [[nodiscard]] const Position& base() const noexcept
      {
         return *this;
      }
   };

   template< typename Source, typename Position >
   [[nodiscard]] bool operator==( const position_with_source< Source, Position >& l, const position_with_source< Source, Position >& r ) noexcept
   {
      return ( l.source == r.source ) && ( l.base() == r.base() );
   }

   template< typename Source, typename Position >
   [[nodiscard]] bool operator!=( const position_with_source< Source, Position >& l, const position_with_source< Source, Position >& r ) noexcept
   {
      return !( l == r );
   }

   template< typename Source, typename Position >
   std::ostream& operator<<( std::ostream& os, const position_with_source< Source, Position >& p )
   {
      return os << p.source << '@' << p.base();
   }

}  // namespace tao::pegtl::internal

#endif
