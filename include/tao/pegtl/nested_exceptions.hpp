// Copyright (c) 2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_PEGTL_NESTED_EXCEPTIONS_HPP
#define TAO_PEGTL_NESTED_EXCEPTIONS_HPP

#include <stdexcept>

#include "internal/nested_exceptions.hpp"

#include "parse_error.hpp"

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

   template< typename Exception, typename Visitor >
   void unravel( const Exception& e, Visitor&& v )
   {
      internal::nested_exceptions< std::exception, parse_error_base >::unravel( e, v );
   }

}  // namespace tao::pegtl

#endif
