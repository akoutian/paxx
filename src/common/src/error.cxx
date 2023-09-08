// SPDX-License-Identifier: GPL-3.0-or-later

#include "common/error.hxx"

namespace paxx::cmn
{

Error::Error(std::string message) : m_error(std::move(message))
{
}

std::string Error::get()
{
    return m_error;
}

bool Error::operator==(const Error &other) const
{
    return m_error == other.m_error;
}

bool Error::operator!=(const Error &other) const
{
    return !(*this == other);
}

} // namespace paxx::cmn
