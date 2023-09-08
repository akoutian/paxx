// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <string>

namespace paxx::cmn
{

class [[nodiscard]] Error
{
  public:
    Error() = delete;

    explicit Error(std::string);

    std::string get();

    bool operator==(const Error&) const;
    bool operator!=(const Error&) const;

  private:
    std::string m_error;
};

} // namespace paxx::cmn
