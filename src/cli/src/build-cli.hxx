// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include "common/args.hxx"
#include "common/types.hxx"

#include <functional>
#include <lyra/lyra.hpp>

namespace paxx::cli
{

lyra::cli BuildCli(cmn::parsed::Args &, cmn::ready::Args &);

} // namespace paxx::cli
