#pragma once

#include "tree-writer.hxx"

#include <iostream>

namespace paxx::tree
{

template <typename Traits>
void BuildTree(typename Traits::Iterator, tree::TreeState &, std::ostream &);

}
