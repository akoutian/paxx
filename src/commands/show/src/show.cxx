// SPDX-License-Identifier: GPL-3.0-or-later

#include "show/show.h"

#include "show-tree.h"

#include <algorithm>
#include <cstddef>
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

    ShowTree(it);
}

} // namespace pass
