// SPDX-License-Identifier: GPL-3.0-or-later

#include "fs-directory-entry.hxx"

namespace paxx::cmn
{

FsDirectoryEntry::FsDirectoryEntry(fs::path path) : m_entry(std::move(path))
{
}

std::string FsDirectoryEntry::path() const
{
    return m_entry.path().string();
}

std::string FsDirectoryEntry::filename() const
{
    return m_entry.path().filename().string();
}

std::string FsDirectoryEntry::stem() const
{
    return m_entry.path().filename().stem().string();
}

bool FsDirectoryEntry::is_directory() const
{
    return m_entry.is_directory();
}

fs::directory_entry FsDirectoryEntry::entry() const
{
    return m_entry;
}

} // namespace paxx::cmn
