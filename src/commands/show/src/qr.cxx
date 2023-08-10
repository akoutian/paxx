// SPDX-License-Identifier: GPL-3.0-or-later

#include "qr.hxx"

#include <ostream>

namespace paxx
{

QrCode Qr(const std::string &text)
{
    QrCode::Ecc ecc = QrCode::Ecc::LOW;
    QrCode result = QrCode::encodeText(text.c_str(), ecc);
    return result;
}

void WriteQr(const QrCode &qr, std::ostream &out)
{
    int border = 1;

    for (int yy = -border; yy < qr.getSize() + border; yy++)
    {
        for (int xx = -border; xx < qr.getSize() + border; xx++)
        {
            const auto k = qr.getModule(xx, yy) ? "  " : "██";
            out << k;
        }

        out << std::endl;
    }

    out << std::endl;
}

} // namespace paxx
