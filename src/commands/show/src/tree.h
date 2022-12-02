// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <cstddef>
#include <ostream>
#include <set>
#include <string_view>

namespace pass::tree
{

struct TreeInfo
{
    bool isLast{false};
    size_t depth{0};
    std::string_view name;
    std::set<size_t> pending;
};

void Print(std::ostream &, const TreeInfo &info);

} // namespace pass::tree
