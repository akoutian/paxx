// SPDX-License-Identifier: GPL-3.0-or-later

#include "show-tree.h"

#include "tree.h"

#include <algorithm>
#include <iostream>
#include <set>

namespace pass
{

// Slow. This is O(n^2). TODO: improve.
bool IsLast(const fs::path &path)
{
    if (!path.has_parent_path())
    {
        return true;
    }

    auto parent = fs::directory_iterator{path.parent_path()};

    while (parent->path() != path)
    {
        ++parent;
    }

    auto next = std::next(parent);

    if (next == end(parent))
    {
        return true;
    }

    const auto nextIsDot = next->path().filename().string().starts_with(".");

    if (nextIsDot)
    {
        next = std::next(parent);
        return next == end(parent);
    }

    return false;
}

void ShowTree(fs::recursive_directory_iterator it)
{
    std::cout << "Password Store\n";

    std::set<size_t> pending;

    const auto handle = [&](const auto &i)
    {
        const auto &path = i.path();

        if (path.filename().string().starts_with("."))
        {
            return;
        }

        bool isLast = IsLast(path);
        bool isDir = i.is_directory();

        size_t depth = static_cast<size_t>(it.depth());

        if (isDir)
        {
            pending.insert(depth);
        }

        if (isDir && isLast)
        {
            pending.erase(depth);
        }

        auto info = tree::TreeInfo{
            .isLast{isLast},
            .depth = depth,
            .name = path.filename().stem(),
            .pending = pending,
        };

        tree::Print(std::cout, info);
    };

    std::for_each(begin(it), end(it), handle);
}

} // namespace pass
