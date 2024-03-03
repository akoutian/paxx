// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <memory>
#include <string>
#include <vector>

namespace paxx::tree
{

struct fake_directory_node
{
    std::string path;
    std::vector<std::shared_ptr<fake_directory_node>> children;
};

} // namespace paxx::tree
