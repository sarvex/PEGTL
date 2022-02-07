// Copyright (c) 2014-2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_PEGTL_INTERNAL_DATA_AND_SIZE_HPP
#define TAO_PEGTL_INTERNAL_DATA_AND_SIZE_HPP

#include <cstdint>

namespace tao::pegtl::internal
{
   template< typename Data, typename Size = std::uint8_t >
   struct data_and_size
   {
      Data data;
      std::uint8_t size;

      using data_t = Data;
      using size_t = Size;

      [[nodiscard]] explicit operator bool() const noexcept
      {
         return size > 0;
      }
   };

}  // namespace tao::pegtl::internal

#endif
