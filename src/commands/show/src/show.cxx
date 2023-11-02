// SPDX-License-Identifier: GPL-3.0-or-later

#include "show/show.hxx"

#include "common/args.hxx"
#include "common/expected.hxx"
#include "common/find-password-store.hxx"
#include "common/pgp-decryptor.hxx"
#include "common/tree.hxx"
#include "common/types.hxx"
#include "qr.hxx"

#include <clip.h>
#include <gpgme++/data.h>

#include <cstddef>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <optional>

namespace paxx
{

namespace fs = std::filesystem;

namespace
{

cmn::Expected<std::stringstream> Decrypt(const std::ifstream &ifs)
{
    std::stringstream cipher;
    cipher << ifs.rdbuf();
    cmn::PGPDecryptor decryptor;

    const auto to = [](auto e)
    {
        std::stringstream out;
        out << e.toString();
        return out;
    };

    return decryptor.decrypt_file(cipher).map(to);
}

// return specific line from a stringstream, if line number is given; else, return the whole content
cmn::Expected<std::string> ExtractLine(std::optional<size_t> lineNumber, std::stringstream &plain)
{
    std::string result;

    if (lineNumber)
    {
        const auto n = *lineNumber;

        for (size_t ii{1}; std::getline(plain, result); ++ii)
        {
            // mimic legacy "pass": both zero and one give the first line
            if (ii == n || n == 0)
            {
                break;
            }
        }

        if (plain.eof())
        {
            return cmn::Unexpected("There is no password on line " + std::to_string(n) + ".");
        }
    }
    else
    {
        result = plain.str();
    }

    // std::getline strips the delimiter (newline in this case) so we put it back in
    if (!plain.fail())
    {
        result.push_back('\n');
    }
    else
    {
        return cmn::Unexpected("Error while reading plaintext stream");
    }

    return result;
}

void Output(const cmn::ShowArgs &args, const std::string &result, cmn::Context &ctx)
{
    switch (args.outputType)
    {
    case cmn::OutputType::STDOUT:
        std::cout << result;
        return;
    case cmn::OutputType::QRCODE: {
        const auto qr = Qr(result);
        WriteQr(qr, std::cout);
        return;
    }
    case cmn::OutputType::CLIPBOARD: {
        const auto success = clip::set_text(result);
        if (!success)
        {
            ctx.status = 1;
            ctx.message = "Failed to copy password to clipboard.";
            return;
        }
    }
    }
}

cmn::Expected<std::stringstream> DecryptFile(const fs::directory_entry &file)
{
    const auto fp = file.path().string();
    std::ifstream ifs{fp};

    if (!ifs.is_open())
    {
        return cmn::Unexpected("Failed to open file " + fp);
    }

    return Decrypt(ifs);
}

void HandleFile(cmn::Context &ctx, const fs::directory_entry &file, const cmn::ShowArgs &args)
{
    auto plain = DecryptFile(file);

    if (!plain)
    {
        ctx.status = 1;
        ctx.message = plain.error().get();
        return;
    }

    const auto line = ExtractLine(args.line, *plain);
    if (!line)
    {
        ctx.status = 1;
        ctx.message = plain.error().get();
        return;
    }

    Output(args, *line, ctx);
}

} // namespace

// TODO: further simplify. Ideally only use the context inside this one function.
void Show(cmn::Context &ctx, const cmn::ShowArgs &args)
{
    const auto p = cmn::FindPasswordStore();

    if (!p)
    {
        ctx.status = 1;
        ctx.message = "Error: password store is empty. Try \"pass init\".";
        return;
    }

    if (!args.name)
    {
        std::cout << "Password Store\n";
        cmn::Tree(*p);
        return;
    }

    const auto name = *args.name;
    const auto path = *p / fs::path(name);

    if (!path.string().starts_with((*p).string()))
    {
        ctx.status = 1;
        ctx.message = "Error: " + name + " is not in the password store.";
        return;
    }

    if (const auto entry = fs::directory_entry{path}; entry.is_directory())
    {
        std::cout << entry.path().filename().string() << '\n';
        cmn::Tree(entry);
        return;
    }

    if (const auto file = fs::directory_entry{path.string() + ".gpg"}; file.is_regular_file())
    {
        HandleFile(ctx, file, args);
        return;
    }
}

} // namespace paxx
