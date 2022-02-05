// Copyright (c) 2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_PEGTL_INTERNAL_NESTED_EXCEPTIONS_HPP
#define TAO_PEGTL_INTERNAL_NESTED_EXCEPTIONS_HPP

#include <exception>

namespace tao::pegtl::internal
{
   template< typename... >
   struct rethrow_and_catch_if_nested;

   template<>
   struct rethrow_and_catch_if_nested<>
   {
      template< typename Recurse, typename Outer, typename Visitor >
      static void rethrow( const Outer& outer, Visitor&& /*unused*/, const unsigned /*unused*/ )
      {
         std::rethrow_if_nested( outer );
      }

      template< typename Recurse, typename Visitor >
      static void rethrow( const std::exception_ptr& outer, Visitor&& /*unused*/, const unsigned /*unused*/ )
      {
         std::rethrow_exception( outer );
      }
   };

   template< typename Inner, typename... Inners >
   struct rethrow_and_catch_if_nested< Inner, Inners... >
   {
      template< typename Recurse, typename Outer, typename Visitor >
      static void rethrow( const Outer& outer, Visitor&& visitor, const unsigned level )
      {
         try {
            rethrow_and_catch_if_nested< Inners... >::template rethrow< Recurse >( outer, visitor, level );
         }
         catch( const Inner& inner ) {
            Recurse::caught( inner, visitor, level );
         }
      }
   };

   template< typename Catch >
   struct visit_before_recurse
   {
      template< typename Visitor, typename Exception >
      static void caught( const Exception& error, Visitor&& visitor, const unsigned level )
      {
         visitor( error, level );
         Catch::template rethrow< visit_before_recurse >( error, visitor, level + 1 );
      }
   };

   template< typename Catch >
   struct recurse_before_visit
   {
      template< typename Visitor, typename Exception >
      static void caught( const Exception& error, Visitor&& visitor, const unsigned level )
      {
         Catch::template rethrow< recurse_before_visit >( error, visitor, level + 1 );
         visitor( error, level );
      }
   };

   template< typename... Exceptions >
   struct nested_exceptions
   {
      static_assert( sizeof...( Exceptions ) > 0 );

      template< typename Exception, typename Visitor >
      static void unravel( const Exception& outer, Visitor&& visitor )
      {
         using Catch = internal::rethrow_and_catch_if_nested< Exceptions... >;
         using Recurse = internal::visit_before_recurse< Catch >;
         Recurse::caught( outer, visitor, 0 );
      }

      template< typename Visitor >
      static void unravel( const std::exception_ptr& outer, Visitor&& visitor )
      {
         using Catch = internal::rethrow_and_catch_if_nested< Exceptions... >;
         using Recurse = internal::recurse_before_visit< Catch >;
         Catch::template rethrow< Recurse >( outer, visitor, 0 );
      }

      template< typename Visitor >
      static void unravel( Visitor&& visitor )
      {
         unravel( std::current_exception(), visitor );
      }
   };

}  // namespace tao::pegtl::internal

#endif
