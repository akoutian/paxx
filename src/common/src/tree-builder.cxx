// SPDX-License-Identifier: GPL-3.0-or-later

#include "common/tree-builder.hxx"

#include "fs-directory-entry.hxx"
#include "fs-directory-iterator-traits.hxx"
#include "tree-writer.hxx"

#include <filesystem>
#include <iostream>

namespace paxx::cmn
{

template <typename Traits> void BuildTree(typename Traits::Iterator it, tree::TreeState &state);

namespace
{

template <typename Traits>
void HandleDirectory(const typename Traits::Entry &e, tree::TreeState &state)
{
    state.name = e.stem();

    tree::Write(std::cout, state);

    if (!state.last)
    {
        state.stack.insert(state.depth);
    }

    ++state.depth;
    BuildTree<Traits>(typename Traits::Iterator(e.path()), state);
    --state.depth;

    state.stack.erase(state.depth);
}

template <typename Entry> void HandleFile(const Entry &e, tree::TreeState &state)
{
    state.name = e.stem();
    tree::Write(std::cout, state);
}

} // namespace

namespace fs = std::filesystem;

template <typename Traits> void BuildTree(typename Traits::Iterator it, tree::TreeState &state)
{
    const auto handle = [&](const auto &i)
    {
        if (i.is_directory())
        {
            HandleDirectory<Traits>(i, state);
            return;
        }

        HandleFile(i, state);
    };

    // post-increment and dereference inside the loop because it is an InputIterator
    for (auto i = Traits::begin(it); i != Traits::end(it);)
    {
        const typename Traits::Entry entry = *(i++);

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

// TODO: Unit Tests
void BuildTree(fs::path p)
{
    tree::TreeState info{.name = p.filename()};
    BuildTree<FsDirectoryIteratorTraits>(fs::directory_iterator(p), info);
}

} // namespace paxx::cmn
