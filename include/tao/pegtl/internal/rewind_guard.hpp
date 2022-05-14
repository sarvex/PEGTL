// Copyright (c) 2014-2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_PEGTL_INTERNAL_REWIND_GUARD_HPP
#define TAO_PEGTL_INTERNAL_REWIND_GUARD_HPP

#include <utility>

#include "../rewind_mode.hpp"

namespace tao::pegtl::internal
{
   template< rewind_mode M, typename ParseInput >
   class [[nodiscard]] rewind_guard
   {
   public:
      static constexpr rewind_mode next_rewind_mode = M;

      explicit rewind_guard( ParseInput* /*unused*/ ) noexcept
      {}

      rewind_guard( const rewind_guard& ) = delete;
      rewind_guard( rewind_guard&& ) = delete;

      ~rewind_guard() = default;

      rewind_guard& operator=( const rewind_guard& ) = delete;
      rewind_guard& operator=( rewind_guard&& ) = delete;

      [[nodiscard]] bool operator()( const bool result ) const noexcept
      {
         return result;
      }
   };

   template< typename ParseInput >
   class [[nodiscard]] rewind_guard< rewind_mode::required, ParseInput >
   {
   public:
      using data_t = typename ParseInput::data_t;

      static constexpr rewind_mode next_rewind_mode = rewind_mode::optional;

      explicit rewind_guard( ParseInput* in ) noexcept
         : m_input( in ),
           m_saved( in->rewind_position() )
      {}

      rewind_guard( const rewind_guard& ) = delete;
      rewind_guard( rewind_guard&& ) = delete;

      ~rewind_guard()
      {
         if( m_input != nullptr ) {
            m_input->rewind_position( std::move( m_saved ) );
         }
      }

      rewind_guard& operator=( const rewind_guard& ) = delete;
      rewind_guard& operator=( rewind_guard&& ) = delete;

      void cancel_rewind() noexcept
      {
         m_input = nullptr;
      }

      void repeatable_rewind() const
      {
         m_input->rewind_position( m_saved );
      }

      [[nodiscard]] const data_t* current() const noexcept
      {
         return m_saved.current;
      }

      using rewind_position_t = typename ParseInput::rewind_position_t;

      [[nodiscard]] const rewind_position_t& saved() const noexcept
      {
         return m_saved;
      }

      [[nodiscard]] bool operator()( const bool result ) noexcept
      {
         if( result ) {
            cancel_rewind();
            return true;
         }
         return false;
      }

   private:
      ParseInput* m_input;
      rewind_position_t m_saved;
   };

}  // namespace tao::pegtl::internal

#endif
