// Copyright (c) 2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_PEGTL_INTERNAL_INPUT_TRAITS_HPP
#define TAO_PEGTL_INTERNAL_INPUT_TRAITS_HPP

#include "forward.hpp"
#include "inputs.hpp"

namespace tao::pegtl::internal
{
   template<>
   struct input_traits< argv_input >
   {
      using lazy_input_scan_t = memory_input< char >;
      using rematch_input_t = memory_input< char >;
   };

   template< typename Container >
   struct input_traits< container_input< Container > >
   {
      using lazy_input_scan_t = memory_input< typename container_input< Container >::data_t >;
      using rematch_input_t = memory_input< typename container_input< Container >::data_t >;
   };

   template< typename Position, typename Input >
   struct input_traits< defaulted_eager_position_input< Position, Input > >
   {
      using lazy_input_scan_t = typename input_traits< Input >::lazy_input_scan_t;
      using rematch_input_t = initialized_eager_position_input< Position, Input >;
   };

   template< typename Position, typename Input >
   struct input_traits< defaulted_lazy_position_input< Position, Input > >
   {
      using lazy_input_scan_t = defaulted_eager_position_input< Position, typename input_traits< Input >::lazy_input_scan_t >;
      using rematch_input_t = initialized_lazy_position_input< Position, Input >;
   };

   template< typename Input >
   struct input_traits< fake_buffer_input< Input > >
   {
      using lazy_input_scan_t = fake_buffer_input< typename input_traits< Input >::lazy_input_scan_t >;
      using rematch_input_t = fake_buffer_input< typename input_traits< Input >::rematch_input_t >;
   };

   template< typename Position, typename Input >
   struct input_traits< initialized_eager_position_input< Position, Input > >
   {
      using lazy_input_scan_t = typename input_traits< Input >::lazy_input_scan_t;
      using rematch_input_t = initialized_eager_position_input< Position, Input >;
   };

   template< typename Position, typename Input >
   struct input_traits< initialized_lazy_position_input< Position, Input > >
   {
      using lazy_input_scan_t = initialized_eager_position_input< Position, typename input_traits< Input >::lazy_input_scan_t >;
      using rematch_input_t = initialized_lazy_position_input< Position, Input >;
   };

   template< typename Position, typename Input >
   struct input_traits< initialized_restartable_eager_position_input< Position, Input > >
   {
      using lazy_input_scan_t = typename input_traits< Input >::lazy_input_scan_t;
      using rematch_input_t = initialized_eager_position_input< Position, Input >;
   };

   template< typename Input >
   struct input_traits< input_with_filename< Input > >
   {
      using lazy_input_scan_t = typename input_traits< Input >::lazy_input_scan_t;
   };

   template< typename Source, typename Input >
   struct input_traits< input_with_source< Source, Input > >
   {
      using lazy_input_scan_t = typename input_traits< Input >::lazy_input_scan_t;
   };

   template< typename Eol, typename Input >
   struct input_traits< line_based_input< Eol, Input > >
   {
      using lazy_input_scan_t = line_based_input< Eol, typename input_traits< Input >::lazy_input_scan_t >;
   };

   template< typename Data >
   struct input_traits< memory_input< Data > >
   {
      using lazy_input_scan_t = memory_input< Data >;
   };

   template< typename MemoryInput >
   struct input_traits< mmap_input< MemoryInput > >
   {
      using lazy_input_scan_t = MemoryInput;
   };

   template< typename Pointer >
   struct input_traits< pointer_input< Pointer > >
   {
      using lazy_input_scan_t = memory_input< typename pointer_input< Pointer >::data_t >;
   };

   template<>
   struct input_traits< read_input >
   {
      using lazy_input_scan_t = memory_input< char >;
   };

   template< typename Input >
   struct input_traits< restartable_input< Input > >
   {
      using lazy_input_scan_t = typename input_traits< Input >::lazy_input_scan_t;
   };

}  // namespace tao::pegtl::internal

#endif
