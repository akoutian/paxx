// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include "args.h"
#include "common/types.h"

namespace pass::cli
{

void HandleArgs(const ready::Args &, cmn::Context &);

} // namespace pass::cli
