// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include "error.hxx"

#include <expected>

namespace paxx::cmn
{

template <class T> using Expected = std::expected<T, Error>;

inline auto Unexpected(std::string&& e)
{
    return std::unexpected(Error{e});
}

}
