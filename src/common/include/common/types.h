// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <optional>
#include <string>

namespace pass::cmn
{

struct Info
{
    int status{};
    std::optional<std::string> message{};
};

} // namespace pass::cmn
