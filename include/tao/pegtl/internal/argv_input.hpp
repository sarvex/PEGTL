// Copyright (c) 2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_PEGTL_INTERNAL_ARGV_INPUT_HPP
#define TAO_PEGTL_INTERNAL_ARGV_INPUT_HPP

#include <cstring>

#include "input_traits.hpp"
#include "memory_input.hpp"

namespace tao::pegtl::internal
{
   class argv_input
      : public memory_input< char >
   {
   public:
      argv_input( char** argv, const int argn )
         : memory_input< char >( argv[ argn ], std::strlen( argv[ argn ] ) )
      {}
   };

   template<>
   struct input_traits< argv_input >
   {
      using memory_input_t = memory_input< char >;
   };

}  // namespace tao::pegtl::internal

#endif
