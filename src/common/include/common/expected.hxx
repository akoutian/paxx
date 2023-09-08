// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include "error.hxx"

#include <tl/expected.hpp>

namespace paxx::cmn
{

template <class T> using Expected = tl::expected<T, Error>;

inline auto Unexpected(std::string&& e)
{
    return tl::make_unexpected(Error{e});
}

}
