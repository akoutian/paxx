// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <optional>
#include <string>
#include <variant>

namespace pass::cli
{

enum struct OutputType
{
    STDOUT,
    CLIPBOARD,
    QRCODE
};

struct HelpArgs
{
};

struct ShowArgs
{
    std::optional<size_t> line{};
    std::optional<std::string> name{};
    OutputType outputType{};
};

struct VersionArgs
{
};

namespace parsed
{

struct Args
{
    HelpArgs help{};
    ShowArgs show{};
    VersionArgs version{};
};

} // namespace parsed

namespace ready
{

using Args = std::variant<std::monostate, HelpArgs, ShowArgs, VersionArgs>;

} // namespace ready

} // namespace pass::cli
