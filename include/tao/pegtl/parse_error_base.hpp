// Copyright (c) 2014-2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_PEGTL_PARSE_ERROR_BASE_HPP
#define TAO_PEGTL_PARSE_ERROR_BASE_HPP

#include <cstddef>
#include <stdexcept>
#include <string>

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

}  // namespace tao::pegtl

#endif
