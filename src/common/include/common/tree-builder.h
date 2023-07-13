// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <filesystem>

namespace pass::cmn
{

namespace fs = std::filesystem;

void BuildTree(fs::path);

} // namespace pass::cmn
