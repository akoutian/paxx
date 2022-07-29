// SPDX-License-Identifier: GPL-3.0-or-later

#include <optional>
#include <string>

namespace pass::cli
{

struct ShowArgs
{
    std::optional<std::string> passName;
};

struct Args
{
    bool help{};
    bool show{};
    bool version{};
};

} // namespace pass::cli
