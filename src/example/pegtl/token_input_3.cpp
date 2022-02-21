// Copyright (c) 2020-2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#include <cassert>
#include <iostream>
#include <string>
#include <vector>

#include <tao/pegtl.hpp>

using namespace tao::pegtl;

struct my_token
{
   my_token( const std::string& d, const tao::pegtl::internal::text_position_base< unsigned >& p )
      : data( d ),
        pos( p )
   {}

   [[nodiscard]] const auto& current_position() const noexcept
   {
      return pos;  // This function changes the position in exceptions thrown when parsing the std::vector< my_token > from the input's position to the token's position.
   }

   std::string data;
   tao::pegtl::internal::text_position_base< unsigned > pos;
};

template< typename Rule >
struct my_action
   : nothing< Rule >
{};

template<>
struct my_action< plus< alpha > >
{
   template< typename ActionInput >
   static void apply( const ActionInput& in, std::vector< my_token >& tokens )
   {
      tokens.emplace_back( in.string(), in.current_position() );
   }
};

int main()
{
   try {
      std::vector< my_token > tokens;
      internal::fake_buffer_input< internal::defaulted_eager_position_input< internal::careless_text_position< unsigned >, internal::memory_input< char > > > in( "aaa bbb ccc" );
      (void)parse< must< list< plus< alpha >, space >, eof >, my_action >( in, tokens );
      internal::fake_buffer_input< internal::container_input< std::vector< my_token > > > ts( tokens );
      (void)parse< must< consume< 1 >, failure > >( ts );
   }
   catch( const std::exception& e ) {
      unravel( e, []( const auto& e, const unsigned l ){
         std::cerr << l << " # " << e.what() << std::endl;
      } );
   }
   return 0;
}
