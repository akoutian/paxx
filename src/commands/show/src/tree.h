// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include "types.h"

#include <string>
#include <vector>

namespace pass
{

class Tree
{
  public:
    void Push(const PathInfo &);

    std::vector<std::string> Get() const;

  private:
    std::vector<std::string> m_tree;
};

} // namespace pass
