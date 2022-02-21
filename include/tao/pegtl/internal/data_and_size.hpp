// Copyright (c) 2014-2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_PEGTL_INTERNAL_DATA_AND_SIZE_HPP
#define TAO_PEGTL_INTERNAL_DATA_AND_SIZE_HPP

#include <cstdint>
#include <type_traits>

namespace tao::pegtl::internal
{
   template< typename Data, typename Size = std::uint8_t >
   class data_and_size
   {
   public:
      using data_t = Data;
      using size_t = Size;

      static_assert( !std::is_pointer_v< Data > );
      static_assert( !std::is_reference_v< Data > );
      static_assert( !std::is_member_pointer_v< Data > );

      data_and_size() noexcept = default;

      explicit data_and_size( const Data d, const Size s = 1 ) noexcept
         : m_data( d ),
           m_size( s )
      {}

      [[nodiscard]] Size size() const noexcept
      {
         return m_size;
      }

      [[nodiscard]] Data data() const noexcept
      {
         return m_data;
      }

      [[nodiscard]] explicit operator bool() const noexcept
      {
         return m_size > 0;
      }

   private:
      Data m_data;
      Size m_size = 0;
   };

   template< typename Data, typename Size >
   class data_and_size< const Data*, Size >
   {
   public:
      using data_t = Data;

      data_and_size() noexcept = default;

      explicit data_and_size( const Data* d ) noexcept
         : m_data( d )
      {}

      [[nodiscard]] static Size size() noexcept
      {
         return 1;
      }

      [[nodiscard]] const Data& data() const noexcept
      {
         return *m_data;
      }

      [[nodiscard]] explicit operator bool() const noexcept
      {
         return m_data != nullptr;
      }

   private:
      const Data* m_data = nullptr;
   };

   template< typename Data, typename Size >
   class data_and_size< Data*, Size >
      : public data_and_size< const Data*, Size >
   {};

}  // namespace tao::pegtl::internal

#endif
