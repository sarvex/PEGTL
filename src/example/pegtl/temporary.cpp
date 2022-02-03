#include <iostream>

#include <tao/pegtl.hpp>

using namespace tao::pegtl;

using my_grammar = must< string< 'h', 'a', 'l', 'l', 'o' >, eolf >;

template< typename Rule >
struct my_action
   : nothing< Rule >
{};

template<>
struct my_action< eolf >
{
   static void apply0()
   {
      std::cerr << "EOLF" << std::endl;
   }
};

template<>
struct my_action< string< 'h', 'a', 'l', 'l', 'o' > >
{
   template< typename ActionInput >
   static void apply( const ActionInput& in )
   {
      std::cerr << in.position() << std::endl;
      std::cerr << in.string_view() << std::endl;
   }
};

int main()
{
   // memory_input in( "hallo", 5 );
   internal::eager_position_input< text_position, internal::input_with_eol< one< '\n' >, memory_input > > in( "hallo", 5 );
   // internal::defaulted_lazy_position_input< text_position, internal::input_with_begin< internal::input_with_eol< one< '\n' >, memory_input > > > in( "hallo", 5 );

   //   const bool result = parse< my_grammar, my_action, normal >( in );
   const bool result = parse< my_grammar, my_action, normal >( in );

   std::cerr << result << std::endl;
   std::cerr << in.current_position() << std::endl;
   return 0;
}
