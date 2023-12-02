// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include "common/args.hxx"

#include <lyra/lyra.hpp>

namespace paxx::cli
{

lyra::cli build_cli(cmn::parsed::args &, cmn::ready::args &);

} // namespace paxx::cli
