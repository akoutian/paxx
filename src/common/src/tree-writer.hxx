// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <cstddef>
#include <ostream>
#include <set>

namespace paxx::tree
{

struct state
{
    // is the current entry the last to appear in a directory
    bool last{false};
    size_t depth{0};
    std::string name;
    // depths of directories currently on the stack
    std::set<size_t> stack;
};

void write(std::ostream &, const state &);

} // namespace paxx::tree
