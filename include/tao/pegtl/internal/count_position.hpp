// Copyright (c) 2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_PEGTL_INTERNAL_COUNT_POSITION_HPP
#define TAO_PEGTL_INTERNAL_COUNT_POSITION_HPP

#include <ostream>

#include "count_rewind_position.hpp"
#include "everything.hpp"

namespace tao::pegtl::internal
{
   template< typename Size >
   struct [[nodiscard]] count_position
   {
      Size count = 0;

      using lazy_rule = everything;

      explicit count_position( const Size in_count = 0 ) noexcept
         : count( in_count )
      {}

      template< typename Data >
      explicit count_position( const count_rewind_position< Data, Size >& saved )
         : count( saved.count )
      {}

      template< typename Rule, typename Data >
      void consumed( const Data* /*unused*/, const std::size_t n ) noexcept
      {
         count += n;
      }

      template< typename Data >
      [[nodiscard]] auto rewind_save( const Data* current ) const noexcept
      {
         return count_rewind_position( current, count );
      }

      template< typename Data >
      [[nodiscard]] const Data* rewind_restore( const Data* /*unused*/, const count_rewind_position< Data, Size >& saved ) noexcept
      {
         count = saved.count;
         return saved.current;
      }
   };

   template< typename Size >
   [[nodiscard]] bool operator==( const count_position< Size >& l, const count_position< Size >& r ) noexcept
   {
      return l.count == r.count;
   }

   template< typename Size >
   [[nodiscard]] bool operator!=( const count_position< Size >& l, const count_position< Size >& r ) noexcept
   {
      return !( l == r );
   }

   template< typename Size >
   std::ostream& operator<<( std::ostream& os, const count_position< Size >& p )
   {
      return os << p.count;
   }

}  // namespace tao::pegtl::internal

#endif
