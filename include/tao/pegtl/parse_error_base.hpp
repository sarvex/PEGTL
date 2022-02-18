// Copyright (c) 2014-2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_PEGTL_PARSE_ERROR_BASE_HPP
#define TAO_PEGTL_PARSE_ERROR_BASE_HPP

#include <cstddef>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>

namespace tao::pegtl
{
   namespace internal
   {
      template< typename T >
      [[nodiscard]] std::string to_string( const T& t )
      {
         std::ostringstream oss;
         oss << t;
         return std::move( oss ).str();
      }

      class parse_error_impl_base
      {
      public:
         parse_error_impl_base( parse_error_impl_base&& ) = delete;
         parse_error_impl_base( const parse_error_impl_base& ) = delete;

         ~parse_error_impl_base() = default;

         void operator=( parse_error_impl_base&& ) = delete;
         void operator=( const parse_error_impl_base& ) = delete;

         const std::size_t prefix;
         const std::string position_string;

      protected:
         explicit parse_error_impl_base( const std::string& str )
            : prefix( str.size() + 2 ),
              position_string( str )
         {}
      };

      template< typename Position >
      class parse_error_impl
         : public parse_error_impl_base
      {
      public:
         parse_error_impl( const std::string& str, Position&& pos )
            : parse_error_impl_base( str ),
              position( std::move( pos ) )
         {}

         const Position position;
      };

   }  // namespace internal

   class parse_error_base
      : public std::runtime_error
   {
   public:
      [[nodiscard]] const char* message() const noexcept
      {
         return std::runtime_error::what() + m_impl->prefix;
      }

      [[nodiscard]] const std::string& position_string() const noexcept
      {
         return m_impl->position_string;
      }

   protected:
      template< typename Position >
      parse_error_base( const std::string& msg, Position&& pos )
         : parse_error_base( internal::to_string( pos ), msg, std::move( pos ) )
      {}

      std::shared_ptr< internal::parse_error_impl_base > m_impl;

   private:
      template< typename Position >
      parse_error_base( const std::string& str, const std::string& msg, Position&& pos )
         : std::runtime_error( str + ": " + msg ),
           m_impl( std::make_shared< internal::parse_error_impl< Position > >( str, std::move( pos ) ) )
      {}
   };

}  // namespace tao::pegtl

#endif
