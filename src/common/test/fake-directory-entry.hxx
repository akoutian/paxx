// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include "fake-directory-node.hxx"

#include <memory>
#include <string>

namespace paxx::tree
{

class fake_directory_entry
{
    friend class fake_directory_iterator;

  public:
    fake_directory_entry(std::shared_ptr<fake_directory_node>);

    std::string path() const;

    std::string filename() const;

    std::string stem() const;

    bool is_directory() const;

    fake_directory_entry entry() const;

  private:
    std::shared_ptr<fake_directory_node> m_node;
};

} // namespace paxx::tree
