// SPDX-License-Identifier: GPL-3.0-or-later

#include "common/tree-builder.hxx"

#include "tree-writer.hxx"

#include <algorithm>
#include <iostream>
#include <set>

namespace paxx::cmn
{

template <typename Iterator> void BuildTree(Iterator it, tree::TreeState &state);

namespace
{

template <typename Entry> void HandleDirectory(const Entry &e, tree::TreeState &state)
{
    state.name = e.path().filename().stem();

    tree::Write(std::cout, state);

    if (!state.last)
    {
        state.stack.insert(state.depth);
    }

    ++state.depth;

    BuildTree(fs::directory_iterator(e), state);

    --state.depth;

    state.stack.erase(state.depth);
}

template <typename Entry> void HandleFile(const Entry &e, tree::TreeState &state)
{
    state.name = e.path().filename().stem();
    tree::Write(std::cout, state);
}

} // namespace

namespace fs = std::filesystem;

template <typename Iterator> void BuildTree(Iterator it, tree::TreeState &state)
{
    const auto handle = [&](const auto &i)
    {
        if (i.is_directory())
        {
            HandleDirectory(i, state);
            return;
        }

        HandleFile(i, state);
    };

    for (auto i = begin(it); i != end(it);
         /* deliberately not incrementing here, see below*/)
    {
        // advancing the iterator invalidates its previous copies
        // solution: use post-increment and dereference to get the next entry
        const auto entry = *(i++);

        if (entry.path().filename().string().starts_with("."))
        {
            continue;
        }

        if (i == end(it))
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

// TODO: Unit Tests. Consider mocking fs::directory iterator
void BuildTree(fs::path p)
{
    tree::TreeState info{.name = p.filename()};
    BuildTree(fs::directory_iterator(p), info);
}

} // namespace paxx::cmn
