// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <cstddef>
#include <ostream>
#include <set>

namespace pass::tree
{

struct TreeInfo
{
    bool isLast{false};
    size_t depth{0};
    std::string name;
    std::set<size_t> pending;
};

void Write(std::ostream &, const TreeInfo &);

} // namespace pass::tree
