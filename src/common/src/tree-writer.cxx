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
            result << cmn::gl_bar << cmn::gl_space << cmn::gl_space << cmn::gl_space;
            continue;
        }
        result << cmn::gl_space << cmn::gl_space << cmn::gl_space << cmn::gl_space;
    }

    if (info.last)
    {
        result << cmn::gl_corner << cmn::gl_dash << cmn::gl_dash << cmn::gl_space;
        return result;
    }

    result << cmn::gl_tee << cmn::gl_dash << cmn::gl_dash << cmn::gl_space;
    return result;
}

} // namespace

void Write(std::ostream &out, const TreeState &info)
{
    out << BuildPrefix(info).str() << info.name << cmn::gl_newline;
}

} // namespace pass::tree
