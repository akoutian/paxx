// SPDX-License-Identifier: GPL-3.0-or-later

#include "tree-writer.h"

#include "symbols.h"

#include <algorithm>
#include <string>

namespace pass::tree
{

namespace
{

template <typename Container, typename... Args> void AppendAll(Container &c, Args... args)
{
    ((c += args), ...);
}

auto BuildPrefix(const tree::TreeInfo &info)
{
    // four chars per indent plus four for the "corner" or "tee" and a space
    std::string result;
    result.reserve(info.depth * (gl_indent_depth + 1));

    for (size_t ii{0}; ii < info.depth; ++ii)
    {
        if (info.pending.contains(ii))
        {
            AppendAll(result, gl_bar, gl_space, gl_space, gl_space);
            continue;
        }
        AppendAll(result, gl_space, gl_space, gl_space, gl_space);
    }

    if (info.isLast)
    {
        AppendAll(result, gl_corner, gl_dash, gl_dash, gl_space);
        return result;
    }

    AppendAll(result, gl_tee, gl_dash, gl_dash, gl_space);
    return result;
}

} // namespace

void Write(std::ostream &out, const TreeInfo &info)
{
    out << BuildPrefix(info) << info.name << gl_newline;
}

} // namespace pass::tree
