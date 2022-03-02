// Copyright (c) 2017-2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#include <cstddef>
#include <iostream>

#include <tao/pegtl.hpp>

#include <tao/pegtl/contrib/json.hpp>

using namespace tao::pegtl;

std::size_t prepared = 0;
std::size_t performed = 0;

struct rewind_stats_input
   : file_input
{
   using file_input::file_input;

   template< tao::pegtl::rewind_mode M >
   [[nodiscard]] auto make_rewind_guard() noexcept
   {
      return tao::pegtl::internal::rewind_guard< M, rewind_stats_input >( this );
   }

   [[nodiscard]] auto rewind_position() const noexcept
   {
      ++prepared;
      return file_input::rewind_position();
   }

   void rewind_position( const rewind_position_t& saved ) noexcept
   {
      ++performed;
      file_input::rewind_position( saved );
   }
};

using grammar = seq< json::text, eof >;

int main( int argc, char** argv )  // NOLINT(bugprone-exception-escape)
{
   for( int i = 1; i < argc; ++i ) {
      rewind_stats_input in( argv[ i ] );
      parse< grammar >( in );
   }
   std::cout << "REWINDS PREPARED  " << prepared << std::endl;
   std::cout << "REWINDS PERFORMED " << performed << std::endl;
   return 0;
}
