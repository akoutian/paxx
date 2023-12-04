// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <filesystem>
#include <string>

namespace paxx::cmn
{

namespace fs = std::filesystem;

// facade to fs::directory_entry that exposes only the few operations that we need
class fs_directory_entry
{
  public:
    fs_directory_entry(fs::path);

    std::string path() const;

    std::string filename() const;

    std::string stem() const;

    bool is_directory() const;

    fs::directory_entry entry() const;

  private:
    fs::directory_entry m_entry;
};

} // namespace paxx::cmn
