// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <optional>
#include <string>
#include <variant>

namespace paxx::cmn
{

enum struct OutputType
{
    PLAINTEXT,
    QRCODE
};

struct HelpArgs
{
};

struct ShowArgs
{
    std::optional<size_t> line;
    std::optional<std::string> name;
    OutputType outputType{};
};

struct VersionArgs
{
};

struct DeleteArgs
{
    std::string name;
    bool force{};
    bool recursive{};
};

namespace parsed
{

struct Args
{
    HelpArgs help;
    ShowArgs show;
    VersionArgs version;
    DeleteArgs del;
};

} // namespace parsed

namespace ready
{

using Args = std::variant<std::monostate, HelpArgs, ShowArgs, VersionArgs, DeleteArgs>;

} // namespace ready

} // namespace paxx::cmn
