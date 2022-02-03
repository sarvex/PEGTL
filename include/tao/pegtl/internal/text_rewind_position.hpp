// Copyright (c) 2021-2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_PEGTL_INTERNAL_TEXT_REWIND_POSITION_HPP
#define TAO_PEGTL_INTERNAL_TEXT_REWIND_POSITION_HPP

namespace tao::pegtl::internal
{
   template< typename Data, typename Size >
   struct [[nodiscard]] text_rewind_position
   {
      Size line;
      Size byte_in_line;

      text_rewind_position( const Data* in_current, const Size in_line, const Size in_byte_in_line ) noexcept
         : line( in_line ),
           byte_in_line( in_byte_in_line ),
           current( in_current )
      {}

      const Data* current;
   };

   template< typename Data, typename Size >
   text_rewind_position( const Data*, const Size, const Size ) -> text_rewind_position< Data, Size >;

}  // namespace tao::pegtl::internal

#endif
