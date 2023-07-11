// SPDX-License-Identifier: GPL-3.0-or-later

#include "show/show.h"

#include "common/args.h"
#include "common/find-password-store.h"
#include "common/pgp-decryptor.h"
#include "common/tree-builder.h"
#include "common/types.h"

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

void HandleFile(cmn::Context &ctx, const fs::directory_entry &file, const cli::ShowArgs &args)
{
    if (args.line)
    {
        throw std::runtime_error("TODO: implement");
    }

    const auto fp = file.path().string();
    std::ifstream ifs{fp};

    if (!ifs.is_open())
    {
        ctx.status = 1;
        ctx.message = "Error: failed to open file " + fp;
        return;
    }

    std::stringstream ss;
    ss << ifs.rdbuf();
    cmn::PGPDecryptor decryptor;

    switch (args.outputType)
    {
    case cli::OutputType::STDOUT:
        decryptor.decrypt_file(ss, std::cout);
        return;
    case cli::OutputType::QRCODE:
        throw std::runtime_error("TODO: implement");
    case cli::OutputType::CLIPBOARD:
        throw std::runtime_error("TODO: implement");
    }

    return;
}

} // namespace

void Show(cmn::Context &ctx, const cli::ShowArgs &args)
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
        BuildTree(*p);
        return;
    }

    const auto name = *args.name;
    const auto path = *p / fs::path(name);

    if (const auto entry = fs::directory_entry{path}; entry.is_directory())
    {
        std::cout << entry.path().filename().string() << '\n';
        BuildTree(entry);
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
