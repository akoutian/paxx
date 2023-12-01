// SPDX-License-Identifier: GPL-3.0-or-later

#include "common/tree.hxx"

#include "fs-directory-iterator-traits.hxx"
#include "tree-builder.hxx"

#include <filesystem>
#include <iostream>

namespace paxx::cmn
{

namespace fs = std::filesystem;

void Tree(fs::path p)
{
    tree::TreeState info{.name = p.filename(), .stack{}};
    BuildTree<FsDirectoryIteratorTraits>(fs::directory_iterator(p), info, std::cout);
}

} // namespace paxx::cmn
