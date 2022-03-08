// Copyright (c) 2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_PEGTL_INTERNAL_INPUTS_HPP
#define TAO_PEGTL_INTERNAL_INPUTS_HPP

#include "argv_input.hpp"
#include "container_input.hpp"
#include "file_input.hpp"
#include "memory_input.hpp"
#include "pointer_input.hpp"
#include "read_input.hpp"

#include "line_based_input.hpp"
#include "restartable_input.hpp"

#include "initialized_position_input.hpp"

#include "defaulted_eager_position_input.hpp"
#include "defaulted_lazy_position_input.hpp"
#include "initialized_eager_position_input.hpp"
#include "initialized_lazy_position_input.hpp"
#include "initialized_restartable_eager_position_input.hpp"

#include "auto_discard_buffer_input.hpp"
#include "dynamic_buffer_input_base.hpp"
#include "static_buffer_input_base.hpp"
#include "common_buffer_input.hpp"

#include "fake_buffer_input.hpp"
#include "input_with_source.hpp"

namespace tao::pegtl::internal
{
   template< typename Data, typename Reader >
   using dynamic_buffer_input = common_buffer_input< dynamic_buffer_input_base< Data, Reader > >;

   template< typename Data, std::size_t Size, std::size_t Chunk, typename Reader >
   using static_buffer_input = common_buffer_input< static_buffer_input_base< Data, Size, Chunk, Reader > >;

}  // namespace tao::pegtl::internal

#endif
