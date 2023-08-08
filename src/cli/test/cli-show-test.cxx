// SPDX-License-Identifier: GPL-3.0-or-later

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "src/build-cli.h"

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
    CHECK(r.outputType == cmn::OutputType::STDOUT);
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
    CHECK(r.outputType == cmn::OutputType::STDOUT);
}

TEST_CASE("Check Show IIa")
{
    cmn::parsed::Args parsed;
    cmn::ready::Args ready;
    const auto result = BuildCli(parsed, ready).parse({"argv[0]", "show", "-c"});

    REQUIRE(result);
    REQUIRE(std::holds_alternative<cmn::ShowArgs>(ready));

    const auto r = std::get<cmn::ShowArgs>(ready);

    CHECK(!r.line.has_value());
    CHECK(!r.name.has_value());
    CHECK(r.outputType == cmn::OutputType::CLIPBOARD);
}

TEST_CASE("Check Show IIb")
{
    cmn::parsed::Args parsed;
    cmn::ready::Args ready;
    const auto result = BuildCli(parsed, ready).parse({"argv[0]", "show", "-c", "-l1"});

    REQUIRE(result);
    REQUIRE(std::holds_alternative<cmn::ShowArgs>(ready));

    const auto r = std::get<cmn::ShowArgs>(ready);

    REQUIRE(r.line.has_value());
    CHECK(r.line.value() == 1);
    CHECK(!r.name.has_value());
    CHECK(r.outputType == cmn::OutputType::CLIPBOARD);
}

TEST_CASE("Check Show IIc")
{
    cmn::parsed::Args parsed;
    cmn::ready::Args ready;
    const auto result = BuildCli(parsed, ready).parse({"argv[0]", "show", "-c", "-l=1"});

    REQUIRE(result);
    REQUIRE(std::holds_alternative<cmn::ShowArgs>(ready));

    const auto r = std::get<cmn::ShowArgs>(ready);

    REQUIRE(r.line.has_value());
    CHECK(r.line.value() == 1);
    CHECK(!r.name.has_value());
    CHECK(r.outputType == cmn::OutputType::CLIPBOARD);
}

TEST_CASE("Check Show IId")
{
    cmn::parsed::Args parsed;
    cmn::ready::Args ready;
    const auto result = BuildCli(parsed, ready).parse({"argv[0]", "show", "-c", "-l 1"});

    REQUIRE(result);
    REQUIRE(std::holds_alternative<cmn::ShowArgs>(ready));

    const auto r = std::get<cmn::ShowArgs>(ready);

    REQUIRE(r.line.has_value());
    CHECK(r.line.value() == 1);
    CHECK(!r.name.has_value());
    CHECK(r.outputType == cmn::OutputType::CLIPBOARD);
}

TEST_CASE("Check Show IIe")
{
    cmn::parsed::Args parsed;
    cmn::ready::Args ready;
    const auto result = BuildCli(parsed, ready).parse({"argv[0]", "show", "-c", "--line 1"});

    REQUIRE(result);
    REQUIRE(std::holds_alternative<cmn::ShowArgs>(ready));

    const auto r = std::get<cmn::ShowArgs>(ready);

    REQUIRE(r.line.has_value());
    CHECK(r.line.value() == 1);
    CHECK(!r.name.has_value());
    CHECK(r.outputType == cmn::OutputType::CLIPBOARD);
}

TEST_CASE("Check Show IIf")
{
    cmn::parsed::Args parsed;
    cmn::ready::Args ready;
    const auto result = BuildCli(parsed, ready).parse({"argv[0]", "show", "-c", "--line=1"});

    REQUIRE(result);
    REQUIRE(std::holds_alternative<cmn::ShowArgs>(ready));

    const auto r = std::get<cmn::ShowArgs>(ready);

    REQUIRE(r.line.has_value());
    CHECK(r.line.value() == 1);
    CHECK(!r.name.has_value());
    CHECK(r.outputType == cmn::OutputType::CLIPBOARD);
}

TEST_CASE("Check Show IIIa")
{
    cmn::parsed::Args parsed;
    cmn::ready::Args ready;
    const auto result = BuildCli(parsed, ready).parse({"argv[0]", "show", "--clip"});

    REQUIRE(result);
    REQUIRE(std::holds_alternative<cmn::ShowArgs>(ready));

    const auto r = std::get<cmn::ShowArgs>(ready);

    CHECK(!r.line.has_value());
    CHECK(!r.name.has_value());
    CHECK(r.outputType == cmn::OutputType::CLIPBOARD);
}

TEST_CASE("Check Show IIIb")
{
    cmn::parsed::Args parsed;
    cmn::ready::Args ready;
    const auto result = BuildCli(parsed, ready).parse({"argv[0]", "show", "--clip", "-l1"});

    REQUIRE(result);
    REQUIRE(std::holds_alternative<cmn::ShowArgs>(ready));

    const auto r = std::get<cmn::ShowArgs>(ready);

    REQUIRE(r.line.has_value());
    CHECK(r.line.value() == 1);
    CHECK(!r.name.has_value());
    CHECK(r.outputType == cmn::OutputType::CLIPBOARD);
}

TEST_CASE("Check Show IIIc")
{
    cmn::parsed::Args parsed;
    cmn::ready::Args ready;
    const auto result = BuildCli(parsed, ready).parse({"argv[0]", "show", "--clip", "-l=1"});

    REQUIRE(result);
    REQUIRE(std::holds_alternative<cmn::ShowArgs>(ready));

    const auto r = std::get<cmn::ShowArgs>(ready);

    REQUIRE(r.line.has_value());
    CHECK(r.line.value() == 1);
    CHECK(!r.name.has_value());
    CHECK(r.outputType == cmn::OutputType::CLIPBOARD);
}

TEST_CASE("Check Show IIId")
{
    cmn::parsed::Args parsed;
    cmn::ready::Args ready;
    const auto result = BuildCli(parsed, ready).parse({"argv[0]", "show", "--clip", "-l 1"});

    REQUIRE(result);
    REQUIRE(std::holds_alternative<cmn::ShowArgs>(ready));

    const auto r = std::get<cmn::ShowArgs>(ready);

    REQUIRE(r.line.has_value());
    CHECK(r.line.value() == 1);
    CHECK(!r.name.has_value());
    CHECK(r.outputType == cmn::OutputType::CLIPBOARD);
}

TEST_CASE("Check Show IIIe")
{
    cmn::parsed::Args parsed;
    cmn::ready::Args ready;
    const auto result = BuildCli(parsed, ready).parse({"argv[0]", "show", "--clip", "--line 1"});

    REQUIRE(result);
    REQUIRE(std::holds_alternative<cmn::ShowArgs>(ready));

    const auto r = std::get<cmn::ShowArgs>(ready);

    REQUIRE(r.line.has_value());
    CHECK(r.line.value() == 1);
    CHECK(!r.name.has_value());
    CHECK(r.outputType == cmn::OutputType::CLIPBOARD);
}

TEST_CASE("Check Show IIIf")
{
    cmn::parsed::Args parsed;
    cmn::ready::Args ready;
    const auto result = BuildCli(parsed, ready).parse({"argv[0]", "show", "--clip", "--line=1"});

    REQUIRE(result);
    REQUIRE(std::holds_alternative<cmn::ShowArgs>(ready));

    const auto r = std::get<cmn::ShowArgs>(ready);

    REQUIRE(r.line.has_value());
    CHECK(r.line.value() == 1);
    CHECK(!r.name.has_value());
    CHECK(r.outputType == cmn::OutputType::CLIPBOARD);
}

TEST_CASE("Check Show IVa")
{
    cmn::parsed::Args parsed;
    cmn::ready::Args ready;
    const auto result = BuildCli(parsed, ready).parse({"argv[0]", "show", "-c", "something"});

    REQUIRE(result);
    REQUIRE(std::holds_alternative<cmn::ShowArgs>(ready));

    const auto r = std::get<cmn::ShowArgs>(ready);

    CHECK(!r.line.has_value());
    REQUIRE(r.name.has_value());
    REQUIRE(r.name.value() == "something");
    CHECK(r.outputType == cmn::OutputType::CLIPBOARD);
}

TEST_CASE("Check Show IVb")
{
    cmn::parsed::Args parsed;
    cmn::ready::Args ready;
    const auto result =
        BuildCli(parsed, ready).parse({"argv[0]", "show", "-c", "-l1", "something"});

    REQUIRE(result);
    REQUIRE(std::holds_alternative<cmn::ShowArgs>(ready));

    const auto r = std::get<cmn::ShowArgs>(ready);

    REQUIRE(r.line.has_value());
    CHECK(r.line.value() == 1);
    REQUIRE(r.name.has_value());
    REQUIRE(r.name.value() == "something");
    CHECK(r.outputType == cmn::OutputType::CLIPBOARD);
}

TEST_CASE("Check Show IVc")
{
    cmn::parsed::Args parsed;
    cmn::ready::Args ready;
    const auto result =
        BuildCli(parsed, ready).parse({"argv[0]", "show", "-c", "-l=1", "something"});

    REQUIRE(result);
    REQUIRE(std::holds_alternative<cmn::ShowArgs>(ready));

    const auto r = std::get<cmn::ShowArgs>(ready);

    REQUIRE(r.line.has_value());
    CHECK(r.line.value() == 1);
    REQUIRE(r.name.has_value());
    REQUIRE(r.name.value() == "something");
    CHECK(r.outputType == cmn::OutputType::CLIPBOARD);
}

TEST_CASE("Check Show IVd")
{
    cmn::parsed::Args parsed;
    cmn::ready::Args ready;
    const auto result =
        BuildCli(parsed, ready).parse({"argv[0]", "show", "-c", "-l 1", "something"});

    REQUIRE(result);
    REQUIRE(std::holds_alternative<cmn::ShowArgs>(ready));

    const auto r = std::get<cmn::ShowArgs>(ready);

    REQUIRE(r.line.has_value());
    CHECK(r.line.value() == 1);
    REQUIRE(r.name.has_value());
    REQUIRE(r.name.value() == "something");
    CHECK(r.outputType == cmn::OutputType::CLIPBOARD);
}

TEST_CASE("Check Show IVe")
{
    cmn::parsed::Args parsed;
    cmn::ready::Args ready;
    const auto result =
        BuildCli(parsed, ready).parse({"argv[0]", "show", "-c", "--line 1", "something"});

    REQUIRE(result);
    REQUIRE(std::holds_alternative<cmn::ShowArgs>(ready));

    const auto r = std::get<cmn::ShowArgs>(ready);

    REQUIRE(r.line.has_value());
    CHECK(r.line.value() == 1);
    REQUIRE(r.name.has_value());
    REQUIRE(r.name.value() == "something");
    CHECK(r.outputType == cmn::OutputType::CLIPBOARD);
}

TEST_CASE("Check Show IVf")
{
    cmn::parsed::Args parsed;
    cmn::ready::Args ready;
    const auto result =
        BuildCli(parsed, ready).parse({"argv[0]", "show", "-c", "--line=1", "something"});

    REQUIRE(result);
    REQUIRE(std::holds_alternative<cmn::ShowArgs>(ready));

    const auto r = std::get<cmn::ShowArgs>(ready);

    REQUIRE(r.line.has_value());
    CHECK(r.line.value() == 1);
    REQUIRE(r.name.has_value());
    REQUIRE(r.name.value() == "something");
    CHECK(r.outputType == cmn::OutputType::CLIPBOARD);
}

} // namespace paxx::cli
