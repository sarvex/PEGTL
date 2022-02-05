// Copyright (c) 2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_PEGTL_INTERNAL_INITIALIZED_RESTARTABLE_EAGER_POSITION_INPUT_HPP
#define TAO_PEGTL_INTERNAL_INITIALIZED_RESTARTABLE_EAGER_POSITION_INPUT_HPP

#include <cstddef>
#include <utility>

namespace tao::pegtl::internal
{
   template< typename Position, typename Input >
   class initialized_restartable_eager_position_input
      : public Input
   {
   public:
      using typename Input::data_t;
      //      using memory_input_t = typename Input::memory_input_t;
      using typename Input::pointer_t;
      using position_t = Position;

      template< typename... As >
      explicit initialized_restartable_eager_position_input( Position&& p, As&&... as )  // noexcept( auto )
         : Input( std::forward< As >( as )... ),
           m_initial( std::move( p ) ),
           m_position( m_initial )
      {}

      template< typename... As >
      explicit initialized_restartable_eager_position_input( const Position& p, As&&... as )  // noexcept( auto )
         : Input( std::forward< As >( as )... ),
           m_initial( p ),
           m_position( m_initial )
      {}

      void restart()
      {
         Input::restart();
         m_position = m_initial;
      }

      template< typename Rule >
      void consume( const std::size_t count )  // noexcept( auto )
      {
         m_position.template consume< Rule >( this->current(), count );
         Input::template consume< Rule >( count );
      }

      using rewind_position_t = decltype( std::declval< Position >().rewind_save( std::declval< pointer_t >() ) );

      template< rewind_mode M >
      [[nodiscard]] rewind_guard< M, initialized_restartable_eager_position_input > make_rewind_guard() noexcept
      {
         return rewind_guard< M, initialized_restartable_eager_position_input >( this );
      }

      [[nodiscard]] auto rewind_position() const noexcept
      {
         return m_position.rewind_save( this->current() );
      }

      void rewind_position( rewind_position_t&& saved ) noexcept
      {
         this->private_set_current( m_position.rewind_restore( this->current(), std::move( saved ) ) );
      }

      void rewind_position( const rewind_position_t& saved ) noexcept
      {
         this->private_set_current( m_position.rewind_restore( this->current(), saved ) );
      }

      [[nodiscard]] const Position& current_position() const noexcept
      {
         return m_position;
      }

      [[nodiscard]] Position previous_position( const rewind_position_t& saved ) const
      {
         return Position( saved );
      }

      [[nodiscard]] Position&& private_position() noexcept
      {
         return std::move( m_position );
      }

      [[nodiscard]] const Position& private_position() const noexcept
      {
         return m_position;
      }

      [[nodiscard]] const Position& initial_position() const noexcept
      {
         return m_initial;
      }

   protected:
      Position m_initial;
      Position m_position;
   };

}  // namespace tao::pegtl::internal

#endif
