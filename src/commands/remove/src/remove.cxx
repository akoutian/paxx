// SPDX-License-Identifier: GPL-3.0-or-later

#include "remove/remove.hxx"

#include "common/args.hxx"
#include "common/find-password-store.hxx"
#include "common/types.hxx"

#include <filesystem>
#include <iostream>
#include <stdexcept>

namespace paxx
{

namespace fs = std::filesystem;

namespace
{

bool YesNo(const std::string &prompt)
{
    while (true)
    {
        std::cout << prompt << " [y/N] ";
        std::string line;

        if (!getline(std::cin, line))
        {
            throw std::runtime_error("unexpected input error");
        }

        else if (line.size() == 1 and line.find_first_of("YyNn") != line.npos)
        {
            return line == "Y" || line == "y";
        }

        else if (line.size() == 0)
        {
            return false;
        }
    }
}

void handle_directory(const fs::directory_entry &entry, const cmn::remove_args &args,
                      cmn::context &ctx)
{
    if (args.recursive)
    {
        fs::remove_all(entry.path());
        return;
    }

    ctx.status = 1;
    ctx.message = "cannot remove '" + entry.path().string() + "': is a directory";
    return;
}

void handle_file(const fs::directory_entry &entry)
{
    fs::remove(entry.path());

    if (const auto parent = entry.path().parent_path(); fs::is_empty(parent))
    {
        fs::remove(parent);
    }

    return;
}

} // namespace

void remove(cmn::context &ctx, const cmn::remove_args &args)
{
    const auto p = cmn::find_password_store();

    if (!p)
    {
        ctx.status = 1;
        ctx.message = "error: password store is empty. Try \"pass init\".";
        return;
    }

    const auto name = args.name;
    const auto path = *p / fs::path(name);

    const auto prompt = "Are you sure you would like to remove " + name + "?";
    if (!(args.force || YesNo(prompt)))
    {
        return;
    }

    if (const auto entry = fs::directory_entry{path}; entry.is_directory())
    {
        handle_directory(entry, args, ctx);
        return;
    }

    if (const auto entry = fs::directory_entry{path.string() + ".gpg"}; entry.is_regular_file())
    {
        handle_file(entry);
        return;
    }

    ctx.status = 1;
    ctx.message = "error: " + name + " is not in the password store.";
    return;
}

} // namespace paxx
