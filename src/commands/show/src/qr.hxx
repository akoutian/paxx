// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <qrcodegencpp/qrcodegen.hpp>

namespace paxx
{

using qrcodegen::QrCode;

QrCode qr(const std::string &text);

void write_qr(const QrCode &, std::ostream &);

} // namespace paxx
