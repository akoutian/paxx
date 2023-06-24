// SPDX-License-Identifier: GPL-3.0-or-later

#include "show-tree.h"

#include "tree.h"

#include <algorithm>
#include <iostream>
#include <set>

namespace pass
{

void ShowTree(fs::directory_iterator it, tree::TreeInfo &info)
{
    const auto handle = [&](const auto &i)
    {
        if (i.is_directory())
        {
            info.name = i.path().filename().stem();

            tree::Print(std::cout, info);

            if (!info.isLast)
            {
                info.pending.insert(info.depth);
            }

            ++info.depth;

            ShowTree(fs::directory_iterator(i), info);

            --info.depth;

            info.pending.erase(info.depth);

            return;
        }

        info.name = i.path().filename().stem();
        tree::Print(std::cout, info);
    };

    for (auto i = fs::begin(it); i != fs::end(it); /*see below*/)
    {
        // advancing the iterator invalidates its previous copies
        // solution: use post-increment and dereference
        auto entry = *(i++);

        if (entry.path().filename().string().starts_with("."))
        {
            continue;
        }

        if (i == fs::end(it))
        {
            info.isLast = true;
            handle(entry);
        }
        else
        {
            info.isLast = false;
            handle(entry);
        }
    }
}

// TODO: Unit Tests. Consider mocking fs::directory iterator
void ShowTree(fs::path p)
{
    tree::TreeInfo info{.name = p.filename()};
    ShowTree(fs::directory_iterator(p), info);
}

} // namespace pass
