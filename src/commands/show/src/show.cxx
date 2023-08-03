// SPDX-License-Identifier: GPL-3.0-or-later

#include "show/show.h"

#include "common/args.h"
#include "common/find-password-store.h"
#include "common/pgp-decryptor.h"
#include "common/tree-builder.h"
#include "common/types.h"
#include "qr.h"

#include <algorithm>
#include <cstddef>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <optional>

namespace pass
{

namespace fs = std::filesystem;

namespace
{

std::stringstream Decrypt(const std::ifstream &ifs)
{
    std::stringstream cipher;
    cipher << ifs.rdbuf();
    cmn::PGPDecryptor decryptor;

    std::stringstream plain;
    decryptor.decrypt_file(cipher, plain);

    return plain;
}

void HandleLineNumber(std::string &result, std::optional<size_t> lineNumber,
                      std::stringstream &plain, cmn::Context &ctx)
{
    if (lineNumber)
    {
        const auto n = *lineNumber;

        std::string line;
        for (size_t ii{1}; std::getline(plain, line); ++ii)
        {
            // mimic legacy "pass": both zero and one give the first line
            if (ii == n || n == 0)
            {
                result = line;
                break;
            }
        }

        if (plain.eof())
        {
            ctx.status = 1;
            ctx.message = "There is no password on line " + std::to_string(n) + ".";
            return;
        }

        // std::getline strips the delimiter (newline in this case) so we put it back in
        if (!plain.fail())
        {
            result.push_back('\n');
        }
    }
    else
    {
        result = plain.str();
    }
}

void Output(const cmn::ShowArgs &args, const std::string &result)
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
    case cmn::OutputType::CLIPBOARD:
        throw std::runtime_error("TODO: implement");
    }
}

void HandleFile(cmn::Context &ctx, const fs::directory_entry &file, const cmn::ShowArgs &args)
{

    const auto fp = file.path().string();
    std::ifstream ifs{fp};

    if (!ifs.is_open())
    {
        ctx.status = 1;
        ctx.message = "Error: failed to open file " + fp;
        return;
    }

    auto plain = Decrypt(ifs);

    std::string result;

    HandleLineNumber(result, args.line, plain, ctx);
    if (ctx.status != 0)
    {
        return;
    }

    Output(args, result);
}

} // namespace

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
        cmn::BuildTree(*p);
        return;
    }

    const auto name = *args.name;
    const auto path = *p / fs::path(name);

    if (const auto entry = fs::directory_entry{path}; entry.is_directory())
    {
        std::cout << entry.path().filename().string() << '\n';
        cmn::BuildTree(entry);
        return;
    }

    if (const auto file = fs::directory_entry{path.string() + ".gpg"}; file.is_regular_file())
    {
        HandleFile(ctx, file, args);
        return;
    }

    ctx.status = 1;
    ctx.message = "Error: " + name + " is not in the password store.";
    return;
}

} // namespace pass
