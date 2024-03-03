// SPDX-License-Identifier: GPL-3.0-or-later

#include "fake-directory-entry.hxx"
#include "fake-directory-node.hxx"

namespace paxx::tree
{

fake_directory_entry::fake_directory_entry(std::shared_ptr<fake_directory_node> node)
    : m_node{std::move(node)}
{
}

std::string fake_directory_entry::path() const
{
    return m_node->path;
}

std::string fake_directory_entry::filename() const
{
    return m_node->path;
}

std::string fake_directory_entry::stem() const
{
    return m_node->path;
}

bool fake_directory_entry::is_directory() const
{
    return m_node->children.size() > 0;
}

fake_directory_entry fake_directory_entry::entry() const
{
    return *this;
}

}; // namespace paxx::tree
