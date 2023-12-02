// SPDX-License-Identifier: GPL-3.0-or-later

#include "common/error.hxx"

namespace paxx::cmn
{

error::error(std::string message) : m_error(std::move(message))
{
}

std::string error::get()
{
    return m_error;
}

bool error::operator==(const error &other) const
{
    return m_error == other.m_error;
}

bool error::operator!=(const error &other) const
{
    return !(*this == other);
}

} // namespace paxx::cmn
