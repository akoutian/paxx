// SPDX-License-Identifier: GPL-3.0-or-later

#include "fs-directory-entry.hxx"

namespace paxx::cmn
{

fs_directory_entry::fs_directory_entry(fs::path path) : m_entry(std::move(path))
{
}

std::string fs_directory_entry::path() const
{
    return m_entry.path().string();
}

std::string fs_directory_entry::filename() const
{
    return m_entry.path().filename().string();
}

std::string fs_directory_entry::stem() const
{
    return m_entry.path().filename().stem().string();
}

bool fs_directory_entry::is_directory() const
{
    return m_entry.is_directory();
}

fs::directory_entry fs_directory_entry::entry() const
{
    return m_entry;
}

} // namespace paxx::cmn
