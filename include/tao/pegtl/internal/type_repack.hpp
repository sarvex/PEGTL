// Copyright (c) 2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_PEGTL_INTERNAL_TYPE_REPACK_HPP
#define TAO_PEGTL_INTERNAL_TYPE_REPACK_HPP

namespace tao::pegtl::internal
{
   template< template< typename... > class R, typename X >
   struct type_repack;

   template< template< typename... > class R, template< typename... > class P, typename... Ts >
   struct type_repack< R, P< Ts... > >
   {
      using type = R< Ts... >;
   };

   template< template< typename... > class R, typename X >
   using type_repack_t = typename type_repack< R, X >::type;

}  // namespace tao::pegtl::internal

#endif
