// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <qrcodegencpp/qrcodegen.hpp>

namespace paxx
{

using qrcodegen::QrCode;

QrCode Qr(const std::string &text);

void WriteQr(const QrCode &, std::ostream &);

} // namespace paxx
