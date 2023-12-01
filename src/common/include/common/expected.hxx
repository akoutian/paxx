// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include "error.hxx"

#include <nonstd/expected.hpp>

namespace paxx::cmn
{

template <class T> using Expected = nonstd::expected<T, Error>;

inline auto Unexpected(std::string&& e)
{
    return nonstd::make_unexpected(Error{e});
}

}
