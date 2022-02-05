// Copyright (c) 2014-2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_PEGTL_PARSE_ERROR_HPP
#define TAO_PEGTL_PARSE_ERROR_HPP

#include <cstddef>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>

namespace tao::pegtl
{
   class parse_error_base
      : public std::runtime_error
   {
   public:
      [[nodiscard]] const char* message() const noexcept
      {
         return std::runtime_error::what() + m_prefix;
      }

      [[nodiscard]] const std::string& position_string() const noexcept
      {
         return m_position_string;
      }

   protected:
      parse_error_base( const std::string& msg, const std::string& pos )
         : parse_error_base( msg, pos, pos + ": " + msg )
      {}

   private:
      parse_error_base( const std::string& /*unused*/, const std::string& pos, const std::string& cat )
         : std::runtime_error( cat ),
           m_prefix( pos.size() + 2 ),
           m_position_string( pos )
      {}

      std::size_t m_prefix;
      std::string m_position_string;
   };

   template< typename Position >
   class parse_error
      : public parse_error_base
   {
   public:
      using position_t = Position;

      parse_error( const char* msg, Position pos )
         : parse_error_base( msg, to_string( pos ) ),
           m_position( std::move( pos ) )
      {}

      parse_error( const std::string& msg, Position pos )
         : parse_error_base( msg, to_string( pos ) ),
           m_position( std::move( pos ) )
      {}

      void position() & noexcept = delete;  // TODO?

      [[nodiscard]] Position&& position() && noexcept
      {
         return std::move( m_position );
      }

      [[nodiscard]] const Position& position() const& noexcept
      {
         return m_position;
      }

   protected:
      Position m_position;

      template< typename T >
      [[nodiscard]] static std::string to_string( const T& t )
      {
         std::ostringstream oss;
         oss << t;
         return std::move( oss ).str();
      }
   };

   template< typename Position >
   parse_error( const char*, Position ) -> parse_error< Position >;

   template< typename Position >
   parse_error( const std::string, Position ) -> parse_error< Position >;

}  // namespace tao::pegtl

#endif
