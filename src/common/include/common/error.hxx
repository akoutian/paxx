// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <string>

namespace paxx::cmn
{

class [[nodiscard]] error
{
  public:
    error() = delete;

    explicit error(std::string);

    std::string get() const;

    bool operator==(const error&) const;
    bool operator!=(const error&) const;

  private:
    std::string m_error;
};

} // namespace paxx::cmn
