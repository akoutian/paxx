// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <filesystem>
#include <optional>
#include <string>

namespace paxx::cmn
{

namespace fs = std::filesystem;

static std::string gl_password_store_name = "password-store";

inline std::optional<fs::path> find_password_store()
{
    fs::path result;

    if (const auto h = std::getenv("HOME"))
    {
        const auto p = fs::path(h) / std::format(".{}", gl_password_store_name);
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

} // namespace paxx::cmn
