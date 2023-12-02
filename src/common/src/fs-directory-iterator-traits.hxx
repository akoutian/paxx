// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include "fs-directory-entry.hxx"

#include <filesystem>

namespace paxx::cmn
{

namespace fs = std::filesystem;

struct fs_directory_iterator_traits
{
    using iterator = fs::directory_iterator;
    using entry = fs_directory_entry;

    static fs::directory_iterator begin(fs::directory_iterator it)
    {
        return fs::begin(it);
    }

    static fs::directory_iterator end(fs::directory_iterator it)
    {
        return fs::end(it);
    }
};

} // namespace paxx::cmn
