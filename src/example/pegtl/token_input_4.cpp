// Copyright (c) 2020-2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#include <cassert>
#include <iostream>
#include <string>
#include <utility>

#include <tao/pegtl.hpp>

#include <tao/pegtl/contrib/tokenize.hpp>

using token = tao::pegtl::sor< tao::pegtl::plus< tao::pegtl::alpha >, tao::pegtl::plus< tao::pegtl::digit > >;
using grammar = tao::pegtl::must< tao::pegtl::list< token, tao::pegtl::space >, tao::pegtl::eof >;

template< typename Rule >
struct traits
{
   using token_kind_kind = int;
};

template<>
struct traits< tao::pegtl::plus< tao::pegtl::alpha > >
{
   static constexpr int token_kind = 42;
};

template<>
struct traits< tao::pegtl::plus< tao::pegtl::digit > >
{
   static constexpr int token_kind = 30;
};

int main()
{
   tao::pegtl::internal::fake_buffer_input< tao::pegtl::internal::defaulted_eager_position_input< tao::pegtl::internal::careless_text_position< unsigned >, tao::pegtl::internal::memory_input< char > > > in( "aaa 123 bbb 456 ccc" );
   const auto t = tao::pegtl::tokenize< traits, grammar >( in );
   assert( t.size() == 5 );
   std::cerr << t[ 3 ].kind << std::endl;
   std::cerr << t[ 3 ].data << std::endl;
   std::cerr << t[ 3 ].pos << std::endl;
   return 0;
}
