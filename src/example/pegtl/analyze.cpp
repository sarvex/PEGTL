// Copyright (c) 2017-2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#include <iostream>

#include <tao/pegtl.hpp>

using namespace tao::pegtl;

struct bar;

struct foo
   : sor< digit, bar >
{};

struct bar
   : plus< foo >  // seq< foo, opt< bar > >
{};

int main()  // NOLINT(bugprone-exception-escape)
{
   if( analyze< foo >( std::cout ) > 0 ) {
      std::cout << "There are problems!" << std::endl;
      return 1;
   }
   return 0;
}
