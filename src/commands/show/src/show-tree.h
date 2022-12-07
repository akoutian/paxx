// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <filesystem>

namespace pass
{

namespace fs = std::filesystem;

void ShowTree(fs::recursive_directory_iterator);

} // namespace pass
