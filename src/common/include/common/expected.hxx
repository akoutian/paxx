// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include "error.hxx"

#include <expected>

namespace paxx::cmn
{

template <class T> using expected = std::expected<T, error>;

inline auto unexpected(std::string&& e)
{
    return std::unexpected(error{e});
}

}
