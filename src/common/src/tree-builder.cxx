// SPDX-License-Identifier: GPL-3.0-or-later

#include "tree-builder.hxx"

#include "fs-directory-iterator-traits.hxx"
#include "tree-writer.hxx"

#include <iostream>

namespace paxx::tree
{

template void build_tree<cmn::fs_directory_iterator_traits>(
    cmn::fs_directory_iterator_traits::iterator, tree::state &, std::ostream &);

namespace
{

template <typename traits>
void handle_directory(const typename traits::entry &e, tree::state &state, std::ostream &out)
{
    state.name = e.stem();

    tree::write(out, state);

    if (!state.last)
    {
        state.stack.insert(state.depth);
    }

    ++state.depth;
    build_tree<traits>(typename traits::iterator(e.entry()), state, out);
    --state.depth;

    state.stack.erase(state.depth);
}

template <typename entry> void handle_file(const entry &e, tree::state &state, std::ostream &out)
{
    state.name = e.stem();
    tree::write(out, state);
}

} // namespace

// TODO: Unit Tests
template <typename traits>
void build_tree(typename traits::iterator it, tree::state &state, std::ostream &out)
{
    const auto handle = [&](const auto &i)
    {
        if (i.is_directory())
        {
            handle_directory<traits>(i, state, out);
            return;
        }

        handle_file(i, state, out);
    };

    // post-increment and dereference inside the loop because it is an InputIterator
    for (auto i = traits::begin(it); i != traits::end(it);)
    {
        const auto e = *(i++);
        const typename traits::entry entry(e.path());

        if (entry.filename().starts_with("."))
        {
            continue;
        }

        if (i == traits::end(it))
        {
            state.last = true;
            handle(entry);
        }
        else
        {
            state.last = false;
            handle(entry);
        }
    }
}

} // namespace paxx::tree
