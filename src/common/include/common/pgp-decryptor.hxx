// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include "common/expected.hxx"

#include <gpgme++/context.h>

#include <memory>
#include <sstream>

namespace paxx::cmn
{

class PGPDecryptor
{
  public:
    PGPDecryptor();

    Expected<GpgME::Data> decrypt_file(const std::stringstream &);

  private:
    std::unique_ptr<GpgME::Context> m_ctx;
};

} // namespace paxx::cmn
