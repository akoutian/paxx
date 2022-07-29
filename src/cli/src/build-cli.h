// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include "args.h"
#include "common/types.h"

#include <functional>
#include <lyra/lyra.hpp>

namespace pass::cli
{

lyra::cli BuildCli(parsed::Args &, ready::Args &);

} // namespace pass::cli
