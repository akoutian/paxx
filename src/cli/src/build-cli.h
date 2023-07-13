// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include "common/args.h"
#include "common/types.h"

#include <functional>
#include <lyra/lyra.hpp>

namespace pass::cli
{

lyra::cli BuildCli(cmn::parsed::Args &, cmn::ready::Args &);

} // namespace pass::cli
