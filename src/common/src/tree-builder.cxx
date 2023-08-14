// SPDX-License-Identifier: GPL-3.0-or-later

#include "tree-builder.hxx"

#include "fs-directory-entry.hxx"
#include "fs-directory-iterator-traits.hxx"
#include "tree-writer.hxx"

#include <filesystem>
#include <iostream>

namespace paxx::tree
{

template void BuildTree<cmn::FsDirectoryIteratorTraits>(cmn::FsDirectoryIteratorTraits::Iterator,
                                                        tree::TreeState &, std::ostream &);

namespace
{

template <typename Traits>
void HandleDirectory(const typename Traits::Entry &e, tree::TreeState &state, std::ostream &out)
{
    state.name = e.stem();

    tree::Write(out, state);

    if (!state.last)
    {
        state.stack.insert(state.depth);
    }

    ++state.depth;
    BuildTree<Traits>(typename Traits::Iterator(e.entry()), state, out);
    --state.depth;

    state.stack.erase(state.depth);
}

template <typename Entry> void HandleFile(const Entry &e, tree::TreeState &state, std::ostream &out)
{
    state.name = e.stem();
    tree::Write(out, state);
}

} // namespace

// TODO: Unit Tests
template <typename Traits>
void BuildTree(typename Traits::Iterator it, tree::TreeState &state, std::ostream &out)
{
    const auto handle = [&](const auto &i)
    {
        if (i.is_directory())
        {
            HandleDirectory<Traits>(i, state, out);
            return;
        }

        HandleFile(i, state, out);
    };

    // post-increment and dereference inside the loop because it is an InputIterator
    for (auto i = Traits::begin(it); i != Traits::end(it);)
    {
        const auto e = *(i++);
        const typename Traits::Entry entry(e.path());

        if (entry.filename().starts_with("."))
        {
            continue;
        }

        if (i == Traits::end(it))
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
