// SPDX-License-Identifier: GPL-3.0-or-later

#include "common/pgp-decryptor.hxx"

#include <gpgme++/data.h>
#include <gpgme++/decryptionresult.h>
#include <gpgme++/global.h>

#include <stdexcept>

namespace paxx::cmn
{

pgp_decryptor::pgp_decryptor()
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

expected<GpgME::Data> pgp_decryptor::decrypt_file(const std::stringstream &in)
{
    const auto &str = in.str();
    auto cipher = GpgME::Data{str.data(), str.size(), false};
    auto plain = GpgME::Data{};

    const auto result = m_ctx->decrypt(cipher, plain);

    const auto error = result.error();
    if (error.code() != 0)
    {
        return unexpected(error.asString());
    }

    return plain;
}

} // namespace paxx::cmn
