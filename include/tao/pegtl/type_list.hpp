// Copyright (c) 2020-2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_PEGTL_TYPE_LIST_HPP
#define TAO_PEGTL_TYPE_LIST_HPP

#include <cstddef>

namespace tao::pegtl
{
   template< typename... Ts >
   struct type_list
   {
      static constexpr std::size_t size = sizeof...( Ts );
   };

   using empty_list = type_list<>;

   template< typename... Ls, typename... Rs >
   [[nodiscard]] type_list< Ls..., Rs... > operator+( const type_list< Ls... >&, const type_list< Rs... >& ) noexcept;

   template< typename... Ts >
   using type_list_concat = decltype( ( empty_list() + ... + Ts() ) );

}  // namespace tao::pegtl

#endif
