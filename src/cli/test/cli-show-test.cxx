// SPDX-License-Identifier: GPL-3.0-or-later

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "src/build-cli.hxx"

#include <doctest/doctest.h>
#include <lyra/lyra.hpp>

namespace paxx::cli
{

TEST_CASE("Check show Ia")
{
    cmn::parsed::args parsed;
    cmn::ready::args ready;
    const auto result = build_cli(parsed, ready).parse({"argv[0]", "show"});

    REQUIRE(result);
    REQUIRE(std::holds_alternative<cmn::show_args>(ready));

    const auto r = std::get<cmn::show_args>(ready);

    CHECK(!r.line.has_value());
    CHECK(!r.name.has_value());
    CHECK(r.outputType == cmn::output_type::PLAINTEXT);
}

TEST_CASE("Check show Ib")
{
    cmn::parsed::args parsed;
    cmn::ready::args ready;
    const auto result = build_cli(parsed, ready).parse({"argv[0]", "show", "something"});

    REQUIRE(result);
    REQUIRE(std::holds_alternative<cmn::show_args>(ready));

    const auto r = std::get<cmn::show_args>(ready);

    CHECK(!r.line.has_value());
    CHECK(r.name == "something");
    CHECK(r.outputType == cmn::output_type::PLAINTEXT);
}

} // namespace paxx::cli
