// Copyright (c) 2014-2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#include <iostream>

#include <tao/pegtl.hpp>

#include "json_errors.hpp"

namespace pegtl = tao::pegtl;

namespace example
{
   template< typename Rule >
   struct action
      : pegtl::nothing< Rule >
   {};

   template<>
   struct action< pegtl::json::end_array >
   {
      template< typename ActionInput >
      static void apply( const ActionInput& in )
      {
         std::cout << "enda: " << in.current_position() << std::endl;
      }
   };

   using grammar = pegtl::must< pegtl::json::text, pegtl::eof >;

}  // namespace example

int main( int argc, char** argv )  // NOLINT(bugprone-exception-escape)
{
   if( argc != 2 ) {
      std::cerr << "Usage: " << argv[ 0 ] << " FILE...\n"
                << "Parse one or more JSON files.\n\n"
                << "Example: " << argv[ 0 ] << " file.json" << std::endl;
      return 1;
   }
   for( int i = 1; i < argc; ++i ) {
      {
         pegtl::internal::fake_buffer_input< pegtl::internal::file_input > in( argv[ i ] );
         pegtl::parse< example::grammar, example::action, example::control >( in );
         std::cout << "done: " << in.current_position() << std::endl;
      } {
         pegtl::internal::defaulted_lazy_position_input< pegtl::internal::count_position< unsigned >, pegtl::internal::fake_buffer_input< pegtl::internal::file_input > > in( argv[ i ] );
         pegtl::parse< example::grammar, example::action, example::control >( in );
         std::cout << "done: " << in.current_position() << std::endl;
      } {
         pegtl::internal::defaulted_lazy_position_input< pegtl::internal::careless_text_position< unsigned >, pegtl::internal::line_based_input< pegtl::ascii::lf, pegtl::internal::fake_buffer_input< pegtl::internal::file_input > > > in( argv[ i ] );
         pegtl::parse< example::grammar, example::action, example::control >( in );
         std::cout << "done: " << in.current_position() << std::endl;
      } {
         pegtl::internal::defaulted_lazy_position_input< pegtl::internal::paranoid_text_position< pegtl::ascii::lf, unsigned >, pegtl::internal::line_based_input< pegtl::ascii::lf, pegtl::internal::fake_buffer_input< pegtl::internal::file_input > > > in( argv[ i ] );
         pegtl::parse< example::grammar, example::action, example::control >( in );
         std::cout << "done: " << in.current_position() << std::endl;
      } {
         pegtl::internal::defaulted_lazy_position_input< pegtl::internal::selected_text_position< pegtl::ascii::lf, unsigned >, pegtl::internal::line_based_input< pegtl::ascii::lf, pegtl::internal::fake_buffer_input< pegtl::internal::file_input > > > in( argv[ i ] );
         pegtl::parse< example::grammar, example::action, example::control >( in );
         std::cout << "done: " << in.current_position() << std::endl;
      } {
         pegtl::internal::initialized_lazy_position_input< pegtl::internal::position_with_source< std::string, pegtl::internal::selected_text_position< pegtl::ascii::lf, unsigned > >, pegtl::internal::line_based_input< pegtl::ascii::lf, pegtl::internal::fake_buffer_input< pegtl::internal::file_input > > > in( pegtl::internal::position_with_source< std::string, pegtl::internal::selected_text_position< pegtl::ascii::lf, unsigned > >( argv[ i ] ), argv[ i ] );
         pegtl::parse< example::grammar, example::action, example::control >( in );
         std::cout << "done: " << in.current_position() << std::endl;
      }
   }
   return 0;
}
