// SPDX-License-Identifier: GPL-3.0-or-later

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "src/build-cli.h"

#include <doctest/doctest.h>
#include <lyra/lyra.hpp>

namespace pass::cli
{

TEST_CASE("Check Help")
{
    parsed::Args parsed;
    ready::Args ready;
    const auto result = BuildCli(parsed, ready).parse({"argv[0]", "help"});

    REQUIRE(result);
    REQUIRE(std::holds_alternative<HelpArgs>(ready));
}

} // namespace pass::cli
