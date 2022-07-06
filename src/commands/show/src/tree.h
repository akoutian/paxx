// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <string>
#include <vector>

namespace pass
{

class Tree
{
  public:
    void Corner(const std::string &);

    void Tee(const std::string &);

    void Dedent();

    void Indent();

    std::vector<std::string> Get() const;

  private:
    std::vector<std::string> m_tree;
    size_t m_depth;
    size_t m_tees;
};

} // namespace pass
