// SPDX-License-Identifier: GPL-3.0-or-later

#include "tree.h"

#include <filesystem>

namespace pass
{

namespace
{

[[maybe_unused]] static constexpr auto gl_corner = "\342\224\224";
[[maybe_unused]] static constexpr auto gl_dash = "\342\224\200\342\224\200 ";
[[maybe_unused]] static constexpr auto gl_bar = "\342\224\202";
[[maybe_unused]] static constexpr auto gl_newline = '\n';
[[maybe_unused]] static constexpr auto gl_space = ' ';
[[maybe_unused]] static constexpr auto gl_tee = "\342\224\234";
[[maybe_unused]] static constexpr size_t gl_indent_depth = 4;

auto BuildPrefix(size_t depth)
{
    return std::string(gl_indent_depth * depth, gl_space);
}

} // namespace

void TreePrinter::Print(std::ostream &out, const TreeInfo &info)
{
    out << BuildPrefix(info.depth);

    if (info.children > 0)
    {
        out << info.name << " directory" << gl_newline;
        return;
    }

    out << info.name << gl_newline;
}

} // namespace pass
