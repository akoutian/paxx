// SPDX-License-Identifier: GPL-3.0-or-later

#include "common/tree.hxx"

#include "fs-directory-iterator-traits.hxx"
#include "tree-walker.hxx"

#include <filesystem>
#include <iostream>

namespace paxx::cmn
{

namespace fs = std::filesystem;

void tree(fs::path p)
{
    tree::state info{.name = p.filename(), .stack{}};
    walk_tree<fs_directory_iterator_traits>(fs::directory_iterator(p), info, std::cout);
}

} // namespace paxx::cmn
