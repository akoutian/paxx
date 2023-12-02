// SPDX-License-Identifier: GPL-3.0-or-later

#include "show/show.hxx"

#include "common/args.hxx"
#include "common/expected.hxx"
#include "common/find-password-store.hxx"
#include "common/pgp-decryptor.hxx"
#include "common/tree.hxx"
#include "common/types.hxx"
#include "qr.hxx"

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

cmn::expected<std::stringstream> decrypt(const std::ifstream &ifs)
{
    std::stringstream cipher;
    cipher << ifs.rdbuf();
    cmn::pgp_decryptor decryptor;

    const auto to = [](auto e)
    {
        std::stringstream out;
        out << e.toString();
        return out;
    };

    const auto result = decryptor.decrypt_file(cipher);

    return decryptor.decrypt_file(cipher).transform(to);
}

// return specific line from a stringstream, if line number is given; else, return the whole content
cmn::expected<std::string> extract_line(std::optional<size_t> lineNumber, std::stringstream &plain)
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
            return cmn::unexpected("There is no password on line " + std::to_string(n) + ".");
        }
    }
    else
    {
        result = plain.str();
    }

    if (!plain.fail())
    {
        return result;
    }
    else
    {
        return cmn::unexpected("error while reading plaintext stream");
    }
}

void output(const cmn::show_args &args, const std::string &result)
{
    switch (args.outputType)
    {
    case cmn::output_type::PLAINTEXT:
        std::cout << result;
        break;
    case cmn::output_type::QRCODE: {
        const auto qr_code = qr(result);
        write_qr(qr_code, std::cout);
        break;
    }
    }
    return;
}

cmn::expected<std::stringstream> decrypt_file(const fs::directory_entry &file)
{
    const auto fp = file.path().string();
    std::ifstream ifs{fp};

    if (!ifs.is_open())
    {
        return cmn::unexpected("Failed to open file " + fp);
    }

    return decrypt(ifs);
}

void handle_file(cmn::context &ctx, const fs::directory_entry &file, const cmn::show_args &args)
{
    auto plain = decrypt_file(file);

    if (!plain)
    {
        ctx.status = 1;
        ctx.message = plain.error().get();
        return;
    }

    const auto line = extract_line(args.line, *plain);
    if (!line)
    {
        ctx.status = 1;
        ctx.message = plain.error().get();
        return;
    }

    output(args, *line);
}

} // namespace

// TODO: further simplify. Ideally only use the context inside this one function.
void show(cmn::context &ctx, const cmn::show_args &args)
{
    const auto p = cmn::find_password_store();

    if (!p)
    {
        ctx.status = 1;
        ctx.message = "error: password store is empty. Try \"pass init\".";
        return;
    }

    if (!args.name)
    {
        std::cout << "Password Store\n";
        cmn::tree(*p);
        return;
    }

    const auto name = *args.name;
    const auto path = *p / fs::path(name);

    if (!path.string().starts_with((*p).string()))
    {
        ctx.status = 1;
        ctx.message = "error: " + name + " is not in the password store.";
        return;
    }

    if (const auto entry = fs::directory_entry{path}; entry.is_directory())
    {
        std::cout << entry.path().filename().string() << '\n';
        cmn::tree(entry);
        return;
    }

    if (const auto file = fs::directory_entry{path.string() + ".gpg"}; file.is_regular_file())
    {
        handle_file(ctx, file, args);
        return;
    }
}

} // namespace paxx
