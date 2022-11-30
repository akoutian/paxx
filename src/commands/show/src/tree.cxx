// SPDX-License-Identifier: GPL-3.0-or-later

#include "tree.h"
#include "symbols.h"

#include <filesystem>

namespace pass
{

namespace
{

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
