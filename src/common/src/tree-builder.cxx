// SPDX-License-Identifier: GPL-3.0-or-later

#include "common/tree-builder.hxx"

#include "tree-writer.hxx"

#include <algorithm>
#include <iostream>
#include <set>

namespace paxx::cmn
{

void BuildTree(fs::directory_iterator it, tree::TreeState &state);

namespace
{

void HandleDirectory(const fs::directory_entry &e, tree::TreeState &state)
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

void HandleFile(const fs::directory_entry &e, tree::TreeState &state)
{
    state.name = e.path().filename().stem();
    tree::Write(std::cout, state);
}

} // namespace

namespace fs = std::filesystem;

void BuildTree(fs::directory_iterator it, tree::TreeState &state)
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

    for (auto i = fs::begin(it); i != fs::end(it);
         /* deliberately not incrementing here, see below*/)
    {
        // advancing the iterator invalidates its previous copies
        // solution: use post-increment and dereference to get the next entry
        const auto entry = *(i++);

        if (entry.path().filename().string().starts_with("."))
        {
            continue;
        }

        if (i == fs::end(it))
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
