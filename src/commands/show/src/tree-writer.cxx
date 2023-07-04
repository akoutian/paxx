// SPDX-License-Identifier: GPL-3.0-or-later

#include "tree-writer.h"

#include "symbols.h"

#include <algorithm>
#include <sstream>

namespace pass::tree
{

namespace
{

auto BuildPrefix(const tree::TreeState &info)
{
    std::stringstream result;

    for (size_t ii{}; ii < info.depth; ++ii)
    {
        if (info.open.contains(ii))
        {
            result << gl_bar << gl_space << gl_space << gl_space;
            continue;
        }
        result << gl_space << gl_space << gl_space << gl_space;
    }

    if (info.last)
    {
        result << gl_corner << gl_dash << gl_dash << gl_space;
        return result;
    }

    result << gl_tee << gl_dash << gl_dash << gl_space;
    return result;
}

} // namespace

void Write(std::ostream &out, const TreeState &info)
{
    out << BuildPrefix(info).str() << info.name << gl_newline;
}

} // namespace pass::tree
