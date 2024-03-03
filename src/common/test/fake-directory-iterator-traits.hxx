// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include "fake-directory-entry.hxx"
#include "fake-directory-iterator.hxx"

namespace paxx::tree
{

struct fake_directory_iterator_traits
{
    using iterator = fake_directory_iterator;
    using entry = fake_directory_entry;

    static auto begin(fake_directory_iterator it)
    {
        return it.begin();
    }

    static auto end(fake_directory_iterator it)
    {
        return it.end();
    }
};

} // namespace paxx::tree
