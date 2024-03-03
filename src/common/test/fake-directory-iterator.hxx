// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include "fake-directory-entry.hxx"
#include "fake-directory-node.hxx"

#include <memory>

namespace paxx::tree
{

// mimicks a few operations of std::filesystem::directory_iterator for testing purposes
class fake_directory_iterator
{
  public:
    fake_directory_iterator(fake_directory_entry entry) : m_index{}, m_node{std::move(entry.m_node)}
    {
    }

    fake_directory_iterator begin() const
    {
        return fake_directory_iterator(0, m_node);
    }

    fake_directory_iterator end() const
    {
        return fake_directory_iterator(m_node->children.size(), m_node);
    }

    fake_directory_entry operator*() const
    {
        return fake_directory_entry{m_node->children[m_index]};
    }

    fake_directory_iterator operator++(int)
    {
        fake_directory_iterator copy{*this};
        ++m_index;
        return copy;
    }

    friend bool operator==(const fake_directory_iterator &lhs, const fake_directory_iterator &rhs)
    {
        return lhs.m_index == rhs.m_index && lhs.m_node == rhs.m_node;
    }

  private:
    fake_directory_iterator(size_t index, std::shared_ptr<fake_directory_node> node)
        : m_index{index}, m_node{std::move(node)}
    {
    }

    size_t m_index;
    std::shared_ptr<fake_directory_node> m_node;
};

} // namespace paxx::tree
