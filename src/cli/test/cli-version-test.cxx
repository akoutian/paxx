// SPDX-License-Identifier: GPL-3.0-or-later

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "src/build-cli.hxx"

#include <doctest/doctest.h>
#include <lyra/lyra.hpp>

namespace paxx::cli
{

TEST_CASE("Check version")
{
    cmn::parsed::args parsed;
    cmn::ready::args ready;
    const auto result = build_cli(parsed, ready).parse({"argv[0]", "version"});

    REQUIRE(result);
    REQUIRE(std::holds_alternative<cmn::version_args>(ready));
}

} // namespace paxx::cli
