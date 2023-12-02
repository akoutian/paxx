#pragma once

#include "tree-writer.hxx"

#include <iostream>

namespace paxx::tree
{

template <typename traits>
void build_tree(typename traits::iterator, tree::state &, std::ostream &);

}
