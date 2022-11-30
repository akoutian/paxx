// SPDX-License-Identifier: GPL-3.0-or-later

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "src/tree.h"

#include "doctest/doctest.h"

#include <sstream>

namespace pass
{

TEST_CASE("Check Single Entry")
{
    pass::TreePrinter p;

    pass::TreeInfo i{0, 0, "."};

    std::stringstream os{};

    p.Print(os, i);

    CHECK(os.str() == ".\n");
}

} // namespace pass
