// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include "tree-writer.hxx"

#include <iostream>

namespace paxx::tree
{

// TODO: unit tests
template <typename traits> void walk_tree(typename traits::iterator, tree::state &, std::ostream &);

} // namespace paxx::tree
