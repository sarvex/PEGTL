// Copyright (c) 2014-2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#include "test.hpp"

#include "verify_meta.hpp"
#include "verify_seqs.hpp"

namespace tao::pegtl
{
   template< typename... Rules >
   using test_action_rule = action< nothing, Rules... >;

   void unit_test()
   {
      verify_meta< action< nothing >, internal::success >();
      verify_meta< action< nothing, eof >, internal::action< nothing, eof >, eof >();
      verify_meta< action< nothing, eof, any >, internal::action< nothing, internal::seq< eof, any > >, internal::seq< eof, any > >();

      verify_seqs< test_action_rule >();
   }

}  // namespace tao::pegtl

#include "main.hpp"
