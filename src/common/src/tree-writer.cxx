// SPDX-License-Identifier: GPL-3.0-or-later

#include "tree-writer.hxx"

#include "symbols.hxx"

#include <sstream>

namespace paxx::tree
{

namespace
{

using cmn::gl_bar;
using cmn::gl_corner;
using cmn::gl_dash;
using cmn::gl_newline;
using cmn::gl_space;
using cmn::gl_tee;

auto BuildPrefix(const tree::TreeState &state)
{
    std::stringstream result;

    for (size_t ii{}; ii < state.depth; ++ii)
    {
        if (state.stack.contains(ii))
        {
            result << gl_bar << gl_space << gl_space << gl_space;
            continue;
        }
        result << gl_space << gl_space << gl_space << gl_space;
    }

    if (state.last)
    {
        result << gl_corner << gl_dash << gl_dash << gl_space;
        return result;
    }

    result << gl_tee << gl_dash << gl_dash << gl_space;
    return result;
}

} // namespace

void Write(std::ostream &out, const TreeState &state)
{
    out << BuildPrefix(state).str() << state.name << gl_newline;
}

} // namespace paxx::tree
