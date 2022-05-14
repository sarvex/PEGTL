#include <tao/pegtl.hpp>

namespace tao::pegtl
{
   // - base input
   // - eol
   // - static buffer parameters
   // - position type
   // - initial position
   // - explicit source
   // - implicit source for files
   // - automatic file input for filesystem::path
   // - automatic fake_buffer_input
   // - optional other stuff
   //   * input_with_depth
   //   * trace stuff
   //   * coverage stuff

   template<>
   struct internal::input_traits< internal::filesystem::path >
   {
      using magic_input_t = file_input;
   };

   namespace magic
   {
      template< typename R >
      struct eol
      {
         using Rule = R;

         explicit eol( const R& /*unused*/ )
         {}
      };

      struct file
      {
         template< typename T >
         explicit file( T&& t )
            : p( std::forward< T >( t ) )
         {}

         internal::filesystem::path p;
      };

      template< typename D >
      struct data
      {
         template< typename T >
         explicit data( T&& t )
            : d( std::forward< T >( t ) )
         {}

         D d;
      };

      template< typename T >
      data( T&& t ) -> data< std::decay_t< T > >;

      template< typename S >
      struct source
      {
         using Source = S;

         template< typename T >
         explicit source( T&& t )
            : s( std::forward< T >( t ) )
         {}

         S s;
      };

      template< typename T >
      source( T&& t ) -> source< std::decay_t< T > >;

      template< typename Input, typename... Ts >
      struct intermediate
      {
         using input_t = Input;

         std::tuple< Ts... > args;
      };

      template< typename L, typename R >
      [[nodiscard]] decltype( auto ) operator+( L&& l, R&& r )
      {
         if constexpr( magic_traits< L, R >::less ) {
            return magic_traits< L, R >::add( std::forward< L >( l ), std::forward< R >( r ) );
         }
         else {
            return magic_traits< R, L >::add( std::forward< R >( R ), std::forward< L >( l ) );
         }
      }

   }  // namespace magic

   template< typename Input >
   struct magic_input
      : Input
   {
      template< typename... Ts >
      explicit magic_input( magic::intermediate< Input, Ts... >&& t )
         : magic_input( std::move( t.args ), std::index_sequence_for< Ts... >() )
      {}

   private:
      template< typename... Ts, std::size_t... Is >
      magic_input( std::tuple< Ts... >&& t, const std::index_sequence< Is... >& /*unused*/ )
         : Input( std::get< Is >( std::move( t ) )... )
      {}
   };

   template< typename Input, typename... Ts >
   magic_input( magic::intermediate< Input, Ts... >&& ) -> magic_input< Input >;

#if 0
   auto in = file_input( “foo.txt” ).with_eol( lf() );
   auto in = tao::pegtl::magic_input< tao::pegtl::memory_input >( tao::pegtl::eol_tag< tao::pegtl::lf >() )( bla.data(), bla.size() );
   auto in = magic_input( file_input( "my_file.txt" ), custom_eol<...>{} );
   auto in = file_input( "my_file.txt" )  + eol<...>;
   auto in = input( "my_file.txt" )  + eol<...>;

   auto in = default_text_position();
   auto in = filename( "foo" ) + text_position() + depth_counter();
#endif

}  // namespace tao::pegtl

template< typename T >
void foo( const T& /*unused*/ )
{}

int main( int /*unused*/, char** /*unused*/ )
{
   foo( tao::pegtl::magic::eol( tao::pegtl::ascii::lf() ) );
   return 0;
}
