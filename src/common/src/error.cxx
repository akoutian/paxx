// SPDX-License-Identifier: GPL-3.0-or-later

#include "common/error.hxx"

#include <ranges>

namespace paxx::cmn
{

errors::errors(std::string message)
{
    add_error(std::move(message));
}

void errors::add_error(std::string &&message)
{
    m_errors.insert(std::move(message));
}

[[nodiscard]] const std::unordered_set<std::string> &errors::get() const &
{
    return m_errors;
}

[[nodiscard]] std::string errors::string() const
{
    return std::ranges::join_with_view(m_errors, ", ") | std::ranges::to<std::string>();
}

bool errors::operator==(const errors &other) const
{
    return m_errors == other.m_errors;
}

bool errors::operator!=(const errors &other) const
{
    return !(*this == other);
}

} // namespace paxx::cmn
