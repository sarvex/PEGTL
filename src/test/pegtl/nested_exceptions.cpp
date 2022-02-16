// Copyright (c) 2020-2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#if !defined( __cpp_exceptions )
#include <iostream>
int main()
{
   std::cout << "Exception support disabled, skipping test..." << std::endl;
}
#else

#include <iostream>

#include "test.hpp"

namespace tao::pegtl
{
   using rule = seq< one< 'a' >, try_catch_raise_nested< one< 'b' >, try_catch_raise_nested< one< 'c' >, must< one< 'D' > > > > >;

   using input_t = internal::defaulted_eager_position_input< internal::text_position< std::size_t >, internal::line_based_input< lf, internal::memory_input< char > > >;

   void unit_test()
   {
      unsigned count = 0;

      try {
         input_t in( "abcd" );
         parse< rule >( in );
      }
      catch( const std::exception& e ) {
         unravel( e, [ &count ]( const auto& e, const unsigned l ){
            TAO_PEGTL_TEST_ASSERT( l == count );
            std::cerr << l << " # " << e.what() << std::endl;
            ++count;
         } );
      }
      TAO_PEGTL_TEST_ASSERT( count == 3 );
      count = 0;

      try {
         input_t in( "abcd" );
         parse< rule >( in );
      }
      catch( const std::exception& e ) {
         unravel( std::current_exception(), [ &count ]( const auto&, const unsigned l ){
            TAO_PEGTL_TEST_ASSERT( l + count == 2 );
            ++count;
         } );
      }
      TAO_PEGTL_TEST_ASSERT( count == 3 );
      count = 0;

      try {
         input_t in( "abcd" );
         parse< rule >( in );
      }
      catch( ... ) {
         unravel( [ &count ]( const auto& e, const unsigned l ){
            TAO_PEGTL_TEST_ASSERT( l + count == 2 );
            if constexpr( std::is_same_v< std::decay_t< decltype( e ) >, parse_error_base > ) {
               std::cerr << l << " $ " << e.position_string() << " $ " << e.message() << std::endl;
            }
            else {
               std::cerr << l << " % " << e.what() << std::endl;
            }
            ++count;
         } );
      }
      TAO_PEGTL_TEST_ASSERT( count == 3 );
   }

}  // namespace tao::pegtl

#include "main.hpp"

#endif
