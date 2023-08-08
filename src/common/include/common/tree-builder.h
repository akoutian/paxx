// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <filesystem>

namespace paxx::cmn
{

namespace fs = std::filesystem;

void BuildTree(fs::path);

} // namespace paxx::cmn
