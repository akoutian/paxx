// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <qrcodegen/qrcodegen.hpp>

namespace pass
{

using qrcodegen::QrCode;

QrCode Qr(const std::string &text);

void WriteQr(const QrCode &, std::ostream &);

} // namespace pass
