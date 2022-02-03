// Copyright (c) 2014-2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_PEGTL_HPP
#define TAO_PEGTL_HPP

#include "pegtl/ascii.hpp"
#include "pegtl/demangle.hpp"
#include "pegtl/inputs.hpp"
#include "pegtl/parse.hpp"
#include "pegtl/positions.hpp"
#include "pegtl/rules.hpp"
#include "pegtl/utf8.hpp"
#include "pegtl/version.hpp"
#include "pegtl/visit.hpp"

#include "pegtl/change_action.hpp"
#include "pegtl/change_action_and_state.hpp"
#include "pegtl/change_action_and_states.hpp"
#include "pegtl/change_control.hpp"
#include "pegtl/change_state.hpp"
#include "pegtl/change_states.hpp"
#include "pegtl/disable_action.hpp"
#include "pegtl/enable_action.hpp"

#if defined( __cpp_exceptions )
#include "pegtl/must_if.hpp"
#endif

#endif
