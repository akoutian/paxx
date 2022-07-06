// SPDX-License-Identifier: GPL-3.0-or-later

#include "tree.h"

#include <stdexcept>

namespace pass
{

namespace
{

static constexpr auto gl_tee = "├";
static constexpr auto gl_dash = "── ";
[[maybe_unused]] static constexpr auto gl_line = "│";
static constexpr auto gl_corner = "└";
static constexpr auto gl_space = " ";
static constexpr auto gl_indent_depth = 4;

std::string BuildPrefix(size_t depth, [[maybe_unused]] size_t tees)
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

void Tree::Tee(const std::string &s)
{
    m_tree.push_back(BuildPrefix(m_depth, m_tees) + gl_tee + gl_dash + s);
    ++m_tees;
}

void Tree::Corner(const std::string &s)
{
    m_tree.push_back(BuildPrefix(m_depth, m_tees) + gl_corner + gl_dash + s);
}

void Tree::Indent()
{
    ++m_depth;
}

void Tree::Dedent()
{
    if (m_depth == 0)
    {
        throw std::runtime_error("You tried to dedent with zero depth!");
    }
    --m_depth;
}

} // namespace pass
