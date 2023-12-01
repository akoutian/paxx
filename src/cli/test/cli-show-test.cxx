// SPDX-License-Identifier: GPL-3.0-or-later

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "src/build-cli.hxx"

#include <doctest/doctest.h>
#include <lyra/lyra.hpp>

namespace paxx::cli
{

TEST_CASE("Check Show Ia")
{
    cmn::parsed::Args parsed;
    cmn::ready::Args ready;
    const auto result = BuildCli(parsed, ready).parse({"argv[0]", "show"});

    REQUIRE(result);
    REQUIRE(std::holds_alternative<cmn::ShowArgs>(ready));

    const auto r = std::get<cmn::ShowArgs>(ready);

    CHECK(!r.line.has_value());
    CHECK(!r.name.has_value());
    CHECK(r.outputType == cmn::OutputType::PLAINTEXT);
}

TEST_CASE("Check Show Ib")
{
    cmn::parsed::Args parsed;
    cmn::ready::Args ready;
    const auto result = BuildCli(parsed, ready).parse({"argv[0]", "show", "something"});

    REQUIRE(result);
    REQUIRE(std::holds_alternative<cmn::ShowArgs>(ready));

    const auto r = std::get<cmn::ShowArgs>(ready);

    CHECK(!r.line.has_value());
    CHECK(r.name == "something");
    CHECK(r.outputType == cmn::OutputType::PLAINTEXT);
}

} // namespace paxx::cli
