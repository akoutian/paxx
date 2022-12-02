// SPDX-License-Identifier: GPL-3.0-or-later

#include "show/show.h"

#include "tree.h"

#include <algorithm>
#include <filesystem>
#include <iostream>
#include <optional>
#include <vector>

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

[[maybe_unused]] void ShowTree(fs::recursive_directory_iterator it)
{
    std::cout << "Password Store" << std::endl;

    const auto handle = [&](const auto &i)
    {
        const auto path = i.path();
        tree::TreeInfo info{
            .depth{static_cast<size_t>(it.depth())},
            .name{path.filename().string()},
            .pending{},
        };
        tree::Print(std::cout, info);
    };

    std::for_each(begin(it), end(it), handle);
}

} // namespace

void Show(cmn::Context &ctx)
{
    const auto p = FindPasswordStore();

    if (!p)
    {
        ctx.status = 1;
        ctx.message = "Error: password store is empty. Try \"pass init\".";
        return;
    }

    std::error_code ec;
    const auto it = fs::recursive_directory_iterator{*p, ec};

    const auto ev = ec.value();
    if (ev != 0)
    {
        ctx.status = ev;
        ctx.message =
            "Error: found password store but encountered filesystem error: " + ec.message();
        return;
    }
}

} // namespace pass
