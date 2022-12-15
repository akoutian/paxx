// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <filesystem>

namespace pass
{

namespace fs = std::filesystem;

struct PathInfo
{
    fs::path path{};
    size_t depth;
    bool isDirectory;
};

} // namespace pass
