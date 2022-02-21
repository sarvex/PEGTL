// Copyright (c) 2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_PEGTL_NESTED_EXCEPTIONS_HPP
#define TAO_PEGTL_NESTED_EXCEPTIONS_HPP

#include <stdexcept>
#include <utility>

#include "parse_error_base.hpp"
#include "type_list.hpp"

#include "internal/nested_exceptions.hpp"

namespace tao::pegtl
{
   template< typename Visitor >
   void unravel( Visitor&& v )
   {
      internal::nested_exceptions< std::exception, parse_error_base >::unravel( v );
   }

   template< typename Visitor >
   void unravel( const std::exception_ptr& e, Visitor&& v )
   {
      internal::nested_exceptions< std::exception, parse_error_base >::unravel( e, v );
   }

   template< typename Caught, typename Visitor >
   void unravel( const Caught& e, Visitor&& v )
   {
      internal::nested_exceptions< std::exception, parse_error_base >::unravel( e, v );
   }

   template< typename E, typename Visitor >
   void unravel_type( Visitor&& v )
   {
      internal::nested_exceptions< std::exception, parse_error_base, E >::unravel( v );
   }

   template< typename E, typename Visitor >
   void unravel_type( const std::exception_ptr& e, Visitor&& v )
   {
      internal::nested_exceptions< std::exception, parse_error_base, E >::unravel( e, v );
   }

   template< typename E, typename Caught, typename Visitor >
   void unravel_type( const Caught& e, Visitor&& v )
   {
      internal::nested_exceptions< std::exception, parse_error_base, E >::unravel( e, v );
   }

   template< typename... Es, typename Visitor >
   void unravel_types( type_list< Es... > /*unused*/, Visitor&& v )
   {
      internal::nested_exceptions< std::exception, parse_error_base, Es... >::unravel( v );
   }

   template< typename... Es, typename Visitor >
   void unravel_types( type_list< Es... > /*unused*/, const std::exception_ptr& e, Visitor&& v )
   {
      internal::nested_exceptions< std::exception, parse_error_base, Es... >::unravel( e, v );
   }

   template< typename... Es, typename Caught, typename Visitor >
   void unravel_types( type_list< Es... > /*unused*/, const Caught& e, Visitor&& v )
   {
      internal::nested_exceptions< std::exception, parse_error_base, Es... >::unravel( e, v );
   }

   template< typename List, typename Visitor >
   void unravel_types( Visitor&& v )
   {
      static_assert( is_type_list< List > );
      unravel_types( List(), std::forward< Visitor >( v ) );
   }

   template< typename List, typename Visitor >
   void unravel_types( const std::exception_ptr& e, Visitor&& v )
   {
      static_assert( is_type_list< List > );
      unravel_types( List(), e, std::forward< Visitor >( v ) );
   }

   template< typename List, typename Caught, typename Visitor >
   void unravel_types( const Caught& e, Visitor&& v )
   {
      static_assert( is_type_list< List > );
      unravel_types( List(), e, std::forward< Visitor >( v ) );
   }

}  // namespace tao::pegtl

#endif
