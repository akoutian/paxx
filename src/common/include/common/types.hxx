// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <optional>
#include <string>

namespace paxx::cmn
{

struct command_status
{
    std::optional<std::string> message{};
};

} // namespace paxx::cmn
