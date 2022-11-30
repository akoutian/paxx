// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <filesystem>

namespace pass
{

struct TreeInfo
{
    size_t depth{};
    size_t children{};
    std::string_view name{};
};

class TreePrinter
{
  public:
    void Print(std::ostream &, const TreeInfo &info);
};

} // namespace pass
