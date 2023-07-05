// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <gpgme++/context.h>

#include <memory>
#include <sstream>

namespace pass::cmn
{

class PGPDecryptor
{
  public:
    PGPDecryptor();

    void decrypt_file(const std::stringstream &, std::ostream &);

  private:
    std::unique_ptr<GpgME::Context> m_ctx;
};

} // namespace pass::cmn
