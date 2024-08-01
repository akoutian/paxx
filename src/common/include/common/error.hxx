// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <string>
#include <unordered_set>

namespace paxx::cmn
{

class [[nodiscard]] errors
{
    std::unordered_set<std::string> m_errors;

  public:
    errors() = delete;

    explicit errors(std::string);

    void add_error(std::string &&);

    [[nodiscard]] bool empty() const;

    [[nodiscard]] const std::unordered_set<std::string> &get() const &;

    [[nodiscard]] std::string string() const;

    bool operator==(const errors &) const;
    bool operator!=(const errors &) const;
};

} // namespace paxx::cmn
