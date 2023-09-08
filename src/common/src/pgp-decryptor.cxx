// SPDX-License-Identifier: GPL-3.0-or-later

#include "common/pgp-decryptor.hxx"

#include <gpgme++/data.h>
#include <gpgme++/decryptionresult.h>
#include <gpgme++/global.h>

#include <cassert>
#include <stdexcept>
#include <tl/expected.hpp>

namespace paxx::cmn
{

PGPDecryptor::PGPDecryptor()
{
    GpgME::initializeLibrary();

    auto ctx = std::unique_ptr<GpgME::Context>(
        GpgME::Context::createForProtocol(GpgME::Protocol::OpenPGP));

    if (!ctx)
    {
        throw std::runtime_error("Failed to acquire GpgME::Context.");
    }

    m_ctx = std::unique_ptr<GpgME::Context>(std::move(ctx));
}

Expected<GpgME::Data> PGPDecryptor::decrypt_file(const std::stringstream &in)
{
    const auto &str = in.str();
    auto cipher = GpgME::Data{str.data(), str.size(), false};
    auto plain = GpgME::Data{};

    const auto result = m_ctx->decrypt(cipher, plain);

    const auto error = result.error();
    if (error.code() != 0)
    {
        return Unexpected(error.asString());
    }

    return plain;
}

} // namespace paxx::cmn
