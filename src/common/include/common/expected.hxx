// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include "error.hxx"

#include <expected>

namespace paxx::cmn
{

template <class T> using expected = std::expected<T, errors>;

inline auto unexpected(std::string &&e)
{
    return std::unexpected(errors{std::move(e)});
}

} // namespace paxx::cmn
