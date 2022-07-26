// SPDX-License-Identifier: GPL-3.0-or-later

#include "show/show.h"

#include "tree.h"
#include "types.h"

#include <algorithm>
#include <filesystem>
#include <iostream>
#include <optional>

namespace pass
{

namespace fs = std::filesystem;

namespace
{

static std::string gl_passwordStoreName = "password-store";

std::optional<fs::path> FindPasswordStore()
{
    fs::path result;

    if (const auto h = std::getenv("HOME"))
    {
        const auto p = fs::path(h) /= "." + gl_passwordStoreName;
        if (fs::exists(p))
        {
            result = p;
        }
    }

    if (const auto h = std::getenv("PASSWORD_STORE_DIR"))
    {
        const auto p = fs::path(h);
        if (fs::exists(p))
        {
            result = p;
        }
    }

    return result.empty() ? std::nullopt : std::make_optional(result);
}

std::vector<PathInfo> Vectorize(const fs::recursive_directory_iterator &it)
{
    std::vector<PathInfo> result;

    for (const auto &a : it)
    {
        result.push_back({a.path(), static_cast<size_t>(it.depth()), a.is_directory()});
    };

    return result;
}

} // namespace

void Show(cmn::Info &info)
{
    const auto p = FindPasswordStore();

    if (!p)
    {
        info.status = 1;
        info.message = "Error: password store is empty. Try \"pass init\".";
        return;
    }

    std::error_code ec;
    const auto it = fs::recursive_directory_iterator(*p, ec);

    const auto ev = ec.value();
    if (ev != 0)
    {
        info.status = ev;
        info.message =
            "Error: found password store but encountered filesystem error: " + ec.message();
        return;
    }

    Tree tree;
    const auto push = [&](const auto &a) { tree.Push(a); };
    const auto v = Vectorize(it);
    std::for_each(v.begin(), v.end(), push);

    const auto result = tree.Get();
    std::for_each(result.begin(), result.end(),
                  [&](const auto &a) { std::cout << a << std::endl; });
}

} // namespace pass
