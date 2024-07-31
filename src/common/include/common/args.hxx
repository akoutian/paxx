// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <optional>
#include <string>
#include <variant>

namespace paxx::cmn
{

enum struct output_format
{
    PLAINTEXT,
    QRCODE
};

struct help_args
{
};

struct show_args
{
    std::optional<size_t> line;
    std::optional<std::string> name;
    output_format format{};
};

struct version_args
{
};

struct remove_args
{
    std::string name;
    bool force{};
    bool recursive{};
};

namespace parsed
{

struct args
{
    help_args help;
    show_args show;
    version_args version;
    remove_args remove;
};

} // namespace parsed

namespace ready
{

using args = std::variant<std::monostate, help_args, show_args, version_args, remove_args>;

} // namespace ready

} // namespace paxx::cmn
