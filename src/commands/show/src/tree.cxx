// SPDX-License-Identifier: GPL-3.0-or-later

#include "tree.h"

#include <stdexcept>

namespace pass
{

namespace
{

[[maybe_unused]] static constexpr auto gl_tee = "├";
[[maybe_unused]] static constexpr auto gl_dash = "── ";
[[maybe_unused]] static constexpr auto gl_line = "│";
[[maybe_unused]] static constexpr auto gl_corner = "└";
[[maybe_unused]] static constexpr auto gl_space = " ";
[[maybe_unused]] static constexpr auto gl_indent_depth = 4;

std::string BuildPrefix(size_t depth)
{
    std::string result;

    for (size_t ii{}; ii < depth * gl_indent_depth; ++ii)
    {
        result += gl_space;
    }

    return result;
}

} // namespace

std::vector<std::string> Tree::Get() const
{
    return m_tree;
}

void Tree::Push(const PathInfo &info)
{
    if (info.isDirectory)
    {
        m_tree.push_back(BuildPrefix(info.depth) + gl_corner + gl_dash + info.path.string());
    }
    else
    {
        m_tree.push_back(BuildPrefix(info.depth) + gl_tee + gl_dash + info.path.string());
    }
}

} // namespace pass
