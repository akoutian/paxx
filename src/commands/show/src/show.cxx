// SPDX-License-Identifier: GPL-3.0-or-later

#include "show/show.h"

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

void Show(cmn::Info &info)
{
    const auto p = FindPasswordStore();

    if (p)
    {
        for (const auto &d : fs::recursive_directory_iterator(*p))
        {
            std::cout << d << std::endl;
        }
    }
    else
    {
        info.status = 1;
        info.message = "Error: password store is empty. Try \"pass init\".";
    }
}

} // namespace pass
