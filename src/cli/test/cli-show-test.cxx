// SPDX-License-Identifier: GPL-3.0-or-later

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "src/build-cli.h"

#include <doctest/doctest.h>
#include <lyra/lyra.hpp>

namespace pass::cli
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
    const auto result = BuildCli(parsed, ready).parse({"argv[0]", "show", "-c1"});

    REQUIRE(result);
    REQUIRE(std::holds_alternative<cmn::ShowArgs>(ready));

    const auto r = std::get<cmn::ShowArgs>(ready);

    CHECK(r.line.has_value());
    CHECK(r.line == 1);
    CHECK(!r.name.has_value());
    CHECK(r.outputType == cmn::OutputType::CLIPBOARD);
}

TEST_CASE("Check Show IIb")
{
    cmn::parsed::Args parsed;
    cmn::ready::Args ready;
    const auto result = BuildCli(parsed, ready).parse({"argv[0]", "show", "-c1", "something"});

    REQUIRE(result);
    REQUIRE(std::holds_alternative<cmn::ShowArgs>(ready));

    const auto r = std::get<cmn::ShowArgs>(ready);

    CHECK(r.line.has_value());
    CHECK(r.line == 1);
    CHECK(r.name.has_value());
    CHECK(r.name.value() == "something");
    CHECK(r.outputType == cmn::OutputType::CLIPBOARD);
}

TEST_CASE("Check Show IIc")
{
    cmn::parsed::Args parsed;
    cmn::ready::Args ready;
    const auto result = BuildCli(parsed, ready).parse({"argv[0]", "show", "-q1"});

    REQUIRE(result);
    REQUIRE(std::holds_alternative<cmn::ShowArgs>(ready));

    const auto r = std::get<cmn::ShowArgs>(ready);

    CHECK(r.line.has_value());
    CHECK(r.line == 1);
    CHECK(!r.name.has_value());
    CHECK(r.outputType == cmn::OutputType::QRCODE);
}

TEST_CASE("Check Show IId")
{
    cmn::parsed::Args parsed;
    cmn::ready::Args ready;
    const auto result = BuildCli(parsed, ready).parse({"argv[0]", "show", "-q1", "something"});

    REQUIRE(result);
    REQUIRE(std::holds_alternative<cmn::ShowArgs>(ready));

    const auto r = std::get<cmn::ShowArgs>(ready);

    CHECK(r.line.has_value());
    CHECK(r.line == 1);
    CHECK(r.name.has_value());
    CHECK(r.name.value() == "something");
    CHECK(r.outputType == cmn::OutputType::QRCODE);
}

TEST_CASE("Check Show IIIa")
{
    cmn::parsed::Args parsed;
    cmn::ready::Args ready;
    const auto result = BuildCli(parsed, ready).parse({"argv[0]", "show", "-c=1"});

    REQUIRE(result);
    REQUIRE(std::holds_alternative<cmn::ShowArgs>(ready));

    const auto r = std::get<cmn::ShowArgs>(ready);

    CHECK(r.line.has_value());
    CHECK(r.line == 1);
    CHECK(!r.name.has_value());
    CHECK(r.outputType == cmn::OutputType::CLIPBOARD);
}

TEST_CASE("Check Show IIIb")
{
    cmn::parsed::Args parsed;
    cmn::ready::Args ready;
    const auto result = BuildCli(parsed, ready).parse({"argv[0]", "show", "-c=1", "something"});

    REQUIRE(result);
    REQUIRE(std::holds_alternative<cmn::ShowArgs>(ready));

    const auto r = std::get<cmn::ShowArgs>(ready);

    CHECK(r.line.has_value());
    CHECK(r.line == 1);
    CHECK(r.name.has_value());
    CHECK(r.name.value() == "something");
    CHECK(r.outputType == cmn::OutputType::CLIPBOARD);
}

TEST_CASE("Check Show IIIc")
{
    cmn::parsed::Args parsed;
    cmn::ready::Args ready;
    const auto result = BuildCli(parsed, ready).parse({"argv[0]", "show", "-q=1"});

    REQUIRE(result);
    REQUIRE(std::holds_alternative<cmn::ShowArgs>(ready));

    const auto r = std::get<cmn::ShowArgs>(ready);

    CHECK(r.line.has_value());
    CHECK(r.line == 1);
    CHECK(!r.name.has_value());
    CHECK(r.outputType == cmn::OutputType::QRCODE);
}

TEST_CASE("Check Show IIId")
{
    cmn::parsed::Args parsed;
    cmn::ready::Args ready;
    const auto result = BuildCli(parsed, ready).parse({"argv[0]", "show", "-q=1", "something"});

    REQUIRE(result);
    REQUIRE(std::holds_alternative<cmn::ShowArgs>(ready));

    const auto r = std::get<cmn::ShowArgs>(ready);

    CHECK(r.line.has_value());
    CHECK(r.line == 1);
    CHECK(r.name.has_value());
    CHECK(r.name.value() == "something");
    CHECK(r.outputType == cmn::OutputType::QRCODE);
}

TEST_CASE("Check Show IVa")
{
    cmn::parsed::Args parsed;
    cmn::ready::Args ready;
    const auto result = BuildCli(parsed, ready).parse({"argv[0]", "show", "-c 1"});

    REQUIRE(result);
    REQUIRE(std::holds_alternative<cmn::ShowArgs>(ready));

    const auto r = std::get<cmn::ShowArgs>(ready);

    CHECK(r.line.has_value());
    CHECK(r.line == 1);
    CHECK(!r.name.has_value());
    CHECK(r.outputType == cmn::OutputType::CLIPBOARD);
}

TEST_CASE("Check Show IVb")
{
    cmn::parsed::Args parsed;
    cmn::ready::Args ready;
    const auto result = BuildCli(parsed, ready).parse({"argv[0]", "show", "-c 1", "something"});

    REQUIRE(result);
    REQUIRE(std::holds_alternative<cmn::ShowArgs>(ready));

    const auto r = std::get<cmn::ShowArgs>(ready);

    CHECK(r.line.has_value());
    CHECK(r.line == 1);
    CHECK(r.name.has_value());
    CHECK(r.name.value() == "something");
    CHECK(r.outputType == cmn::OutputType::CLIPBOARD);
}

TEST_CASE("Check Show IVc")
{
    cmn::parsed::Args parsed;
    cmn::ready::Args ready;
    const auto result = BuildCli(parsed, ready).parse({"argv[0]", "show", "-q 1"});

    REQUIRE(result);
    REQUIRE(std::holds_alternative<cmn::ShowArgs>(ready));

    const auto r = std::get<cmn::ShowArgs>(ready);

    CHECK(r.line.has_value());
    CHECK(r.line == 1);
    CHECK(!r.name.has_value());
    CHECK(r.outputType == cmn::OutputType::QRCODE);
}

TEST_CASE("Check Show IVd")
{
    cmn::parsed::Args parsed;
    cmn::ready::Args ready;
    const auto result = BuildCli(parsed, ready).parse({"argv[0]", "show", "-q 1", "something"});

    REQUIRE(result);
    REQUIRE(std::holds_alternative<cmn::ShowArgs>(ready));

    const auto r = std::get<cmn::ShowArgs>(ready);

    CHECK(r.line.has_value());
    CHECK(r.line == 1);
    CHECK(r.name.has_value());
    CHECK(r.name.value() == "something");
    CHECK(r.outputType == cmn::OutputType::QRCODE);
}

TEST_CASE("Check Show Va")
{
    cmn::parsed::Args parsed;
    cmn::ready::Args ready;
    const auto result = BuildCli(parsed, ready).parse({"argv[0]", "show", "--clip 1"});

    REQUIRE(result);
    REQUIRE(std::holds_alternative<cmn::ShowArgs>(ready));

    const auto r = std::get<cmn::ShowArgs>(ready);

    CHECK(r.line.has_value());
    CHECK(r.line == 1);
    CHECK(!r.name.has_value());
    CHECK(r.outputType == cmn::OutputType::CLIPBOARD);
}

TEST_CASE("Check Show Vb")
{
    cmn::parsed::Args parsed;
    cmn::ready::Args ready;
    const auto result = BuildCli(parsed, ready).parse({"argv[0]", "show", "--clip 1", "something"});

    REQUIRE(result);
    REQUIRE(std::holds_alternative<cmn::ShowArgs>(ready));

    const auto r = std::get<cmn::ShowArgs>(ready);

    CHECK(r.line.has_value());
    CHECK(r.line == 1);
    CHECK(r.name.has_value());
    CHECK(r.name.value() == "something");
    CHECK(r.outputType == cmn::OutputType::CLIPBOARD);
}

TEST_CASE("Check Show Vc")
{
    cmn::parsed::Args parsed;
    cmn::ready::Args ready;
    const auto result = BuildCli(parsed, ready).parse({"argv[0]", "show", "--qrcode 1"});

    REQUIRE(result);
    REQUIRE(std::holds_alternative<cmn::ShowArgs>(ready));

    const auto r = std::get<cmn::ShowArgs>(ready);

    CHECK(r.line.has_value());
    CHECK(r.line == 1);
    CHECK(!r.name.has_value());
    CHECK(r.outputType == cmn::OutputType::QRCODE);
}

TEST_CASE("Check Show Vd")
{
    cmn::parsed::Args parsed;
    cmn::ready::Args ready;
    const auto result =
        BuildCli(parsed, ready).parse({"argv[0]", "show", "--qrcode 1", "something"});

    REQUIRE(result);
    REQUIRE(std::holds_alternative<cmn::ShowArgs>(ready));

    const auto r = std::get<cmn::ShowArgs>(ready);

    CHECK(r.line.has_value());
    CHECK(r.line == 1);
    CHECK(r.name.has_value());
    CHECK(r.name.value() == "something");
    CHECK(r.outputType == cmn::OutputType::QRCODE);
}

TEST_CASE("Check Show VIa")
{
    cmn::parsed::Args parsed;
    cmn::ready::Args ready;
    const auto result = BuildCli(parsed, ready).parse({"argv[0]", "show", "--clip=1"});

    REQUIRE(result);
    REQUIRE(std::holds_alternative<cmn::ShowArgs>(ready));

    const auto r = std::get<cmn::ShowArgs>(ready);

    CHECK(r.line.has_value());
    CHECK(r.line == 1);
    CHECK(!r.name.has_value());
    CHECK(r.outputType == cmn::OutputType::CLIPBOARD);
}

TEST_CASE("Check Show VIb")
{
    cmn::parsed::Args parsed;
    cmn::ready::Args ready;
    const auto result = BuildCli(parsed, ready).parse({"argv[0]", "show", "--clip=1", "something"});

    REQUIRE(result);
    REQUIRE(std::holds_alternative<cmn::ShowArgs>(ready));

    const auto r = std::get<cmn::ShowArgs>(ready);

    CHECK(r.line.has_value());
    CHECK(r.line == 1);
    CHECK(r.name.has_value());
    CHECK(r.name.value() == "something");
    CHECK(r.outputType == cmn::OutputType::CLIPBOARD);
}

TEST_CASE("Check Show VIc")
{
    cmn::parsed::Args parsed;
    cmn::ready::Args ready;
    const auto result = BuildCli(parsed, ready).parse({"argv[0]", "show", "--qrcode=1"});

    REQUIRE(result);
    REQUIRE(std::holds_alternative<cmn::ShowArgs>(ready));

    const auto r = std::get<cmn::ShowArgs>(ready);

    CHECK(r.line.has_value());
    CHECK(r.line == 1);
    CHECK(!r.name.has_value());
    CHECK(r.outputType == cmn::OutputType::QRCODE);
}

TEST_CASE("Check Show VId")
{
    cmn::parsed::Args parsed;
    cmn::ready::Args ready;
    const auto result =
        BuildCli(parsed, ready).parse({"argv[0]", "show", "--qrcode=1", "something"});

    REQUIRE(result);
    REQUIRE(std::holds_alternative<cmn::ShowArgs>(ready));

    const auto r = std::get<cmn::ShowArgs>(ready);

    CHECK(r.line.has_value());
    CHECK(r.line == 1);
    CHECK(r.name.has_value());
    CHECK(r.name.value() == "something");
    CHECK(r.outputType == cmn::OutputType::QRCODE);
}

TEST_CASE("Check ls")
{
    cmn::parsed::Args parsed;
    cmn::ready::Args ready;
    const auto result = BuildCli(parsed, ready).parse({"argv[0]", "ls"});

    REQUIRE(result);
    REQUIRE(std::holds_alternative<cmn::ShowArgs>(ready));

    const auto r = std::get<cmn::ShowArgs>(ready);

    CHECK(!r.line.has_value());
    CHECK(!r.name.has_value());
    CHECK(r.outputType == cmn::OutputType::STDOUT);
}

TEST_CASE("Check list")
{
    cmn::parsed::Args parsed;
    cmn::ready::Args ready;
    const auto result = BuildCli(parsed, ready).parse({"argv[0]", "ls"});

    REQUIRE(result);
    REQUIRE(std::holds_alternative<cmn::ShowArgs>(ready));

    const auto r = std::get<cmn::ShowArgs>(ready);

    CHECK(!r.line.has_value());
    CHECK(!r.name.has_value());
    CHECK(r.outputType == cmn::OutputType::STDOUT);
}

} // namespace pass::cli
