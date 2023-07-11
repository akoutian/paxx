// SPDX-License-Identifier: GPL-3.0-or-later

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "src/build-cli.h"

#include <doctest/doctest.h>
#include <lyra/lyra.hpp>

namespace pass::cli
{

TEST_CASE("Check Show Ia")
{
    parsed::Args parsed;
    ready::Args ready;
    const auto result = BuildCli(parsed, ready).parse({"argv[0]", "show"});

    REQUIRE(result);
    REQUIRE(std::holds_alternative<ShowArgs>(ready));

    const auto r = std::get<ShowArgs>(ready);

    CHECK(!r.line.has_value());
    CHECK(!r.name.has_value());
    CHECK(r.outputType == OutputType::STDOUT);
}

TEST_CASE("Check Show Ib")
{
    parsed::Args parsed;
    ready::Args ready;
    const auto result = BuildCli(parsed, ready).parse({"argv[0]", "show", "something"});

    REQUIRE(result);
    REQUIRE(std::holds_alternative<ShowArgs>(ready));

    const auto r = std::get<ShowArgs>(ready);

    CHECK(!r.line.has_value());
    CHECK(r.name == "something");
    CHECK(r.outputType == OutputType::STDOUT);
}

TEST_CASE("Check Show IIa")
{
    parsed::Args parsed;
    ready::Args ready;
    const auto result = BuildCli(parsed, ready).parse({"argv[0]", "show", "-c1"});

    REQUIRE(result);
    REQUIRE(std::holds_alternative<ShowArgs>(ready));

    const auto r = std::get<ShowArgs>(ready);

    CHECK(r.line.has_value());
    CHECK(r.line == 1);
    CHECK(!r.name.has_value());
    CHECK(r.outputType == OutputType::CLIPBOARD);
}

TEST_CASE("Check Show IIb")
{
    parsed::Args parsed;
    ready::Args ready;
    const auto result = BuildCli(parsed, ready).parse({"argv[0]", "show", "-c1", "something"});

    REQUIRE(result);
    REQUIRE(std::holds_alternative<ShowArgs>(ready));

    const auto r = std::get<ShowArgs>(ready);

    CHECK(r.line.has_value());
    CHECK(r.line == 1);
    CHECK(r.name.has_value());
    CHECK(r.name.value() == "something");
    CHECK(r.outputType == OutputType::CLIPBOARD);
}

TEST_CASE("Check Show IIc")
{
    parsed::Args parsed;
    ready::Args ready;
    const auto result = BuildCli(parsed, ready).parse({"argv[0]", "show", "-q1"});

    REQUIRE(result);
    REQUIRE(std::holds_alternative<ShowArgs>(ready));

    const auto r = std::get<ShowArgs>(ready);

    CHECK(r.line.has_value());
    CHECK(r.line == 1);
    CHECK(!r.name.has_value());
    CHECK(r.outputType == OutputType::QRCODE);
}

TEST_CASE("Check Show IId")
{
    parsed::Args parsed;
    ready::Args ready;
    const auto result = BuildCli(parsed, ready).parse({"argv[0]", "show", "-q1", "something"});

    REQUIRE(result);
    REQUIRE(std::holds_alternative<ShowArgs>(ready));

    const auto r = std::get<ShowArgs>(ready);

    CHECK(r.line.has_value());
    CHECK(r.line == 1);
    CHECK(r.name.has_value());
    CHECK(r.name.value() == "something");
    CHECK(r.outputType == OutputType::QRCODE);
}

TEST_CASE("Check Show IIIa")
{
    parsed::Args parsed;
    ready::Args ready;
    const auto result = BuildCli(parsed, ready).parse({"argv[0]", "show", "-c=1"});

    REQUIRE(result);
    REQUIRE(std::holds_alternative<ShowArgs>(ready));

    const auto r = std::get<ShowArgs>(ready);

    CHECK(r.line.has_value());
    CHECK(r.line == 1);
    CHECK(!r.name.has_value());
    CHECK(r.outputType == OutputType::CLIPBOARD);
}

TEST_CASE("Check Show IIIb")
{
    parsed::Args parsed;
    ready::Args ready;
    const auto result = BuildCli(parsed, ready).parse({"argv[0]", "show", "-c=1", "something"});

    REQUIRE(result);
    REQUIRE(std::holds_alternative<ShowArgs>(ready));

    const auto r = std::get<ShowArgs>(ready);

    CHECK(r.line.has_value());
    CHECK(r.line == 1);
    CHECK(r.name.has_value());
    CHECK(r.name.value() == "something");
    CHECK(r.outputType == OutputType::CLIPBOARD);
}

TEST_CASE("Check Show IIIc")
{
    parsed::Args parsed;
    ready::Args ready;
    const auto result = BuildCli(parsed, ready).parse({"argv[0]", "show", "-q=1"});

    REQUIRE(result);
    REQUIRE(std::holds_alternative<ShowArgs>(ready));

    const auto r = std::get<ShowArgs>(ready);

    CHECK(r.line.has_value());
    CHECK(r.line == 1);
    CHECK(!r.name.has_value());
    CHECK(r.outputType == OutputType::QRCODE);
}

TEST_CASE("Check Show IIId")
{
    parsed::Args parsed;
    ready::Args ready;
    const auto result = BuildCli(parsed, ready).parse({"argv[0]", "show", "-q=1", "something"});

    REQUIRE(result);
    REQUIRE(std::holds_alternative<ShowArgs>(ready));

    const auto r = std::get<ShowArgs>(ready);

    CHECK(r.line.has_value());
    CHECK(r.line == 1);
    CHECK(r.name.has_value());
    CHECK(r.name.value() == "something");
    CHECK(r.outputType == OutputType::QRCODE);
}

TEST_CASE("Check Show IVa")
{
    parsed::Args parsed;
    ready::Args ready;
    const auto result = BuildCli(parsed, ready).parse({"argv[0]", "show", "-c 1"});

    REQUIRE(result);
    REQUIRE(std::holds_alternative<ShowArgs>(ready));

    const auto r = std::get<ShowArgs>(ready);

    CHECK(r.line.has_value());
    CHECK(r.line == 1);
    CHECK(!r.name.has_value());
    CHECK(r.outputType == OutputType::CLIPBOARD);
}

TEST_CASE("Check Show IVb")
{
    parsed::Args parsed;
    ready::Args ready;
    const auto result = BuildCli(parsed, ready).parse({"argv[0]", "show", "-c 1", "something"});

    REQUIRE(result);
    REQUIRE(std::holds_alternative<ShowArgs>(ready));

    const auto r = std::get<ShowArgs>(ready);

    CHECK(r.line.has_value());
    CHECK(r.line == 1);
    CHECK(r.name.has_value());
    CHECK(r.name.value() == "something");
    CHECK(r.outputType == OutputType::CLIPBOARD);
}

TEST_CASE("Check Show IVc")
{
    parsed::Args parsed;
    ready::Args ready;
    const auto result = BuildCli(parsed, ready).parse({"argv[0]", "show", "-q 1"});

    REQUIRE(result);
    REQUIRE(std::holds_alternative<ShowArgs>(ready));

    const auto r = std::get<ShowArgs>(ready);

    CHECK(r.line.has_value());
    CHECK(r.line == 1);
    CHECK(!r.name.has_value());
    CHECK(r.outputType == OutputType::QRCODE);
}

TEST_CASE("Check Show IVd")
{
    parsed::Args parsed;
    ready::Args ready;
    const auto result = BuildCli(parsed, ready).parse({"argv[0]", "show", "-q 1", "something"});

    REQUIRE(result);
    REQUIRE(std::holds_alternative<ShowArgs>(ready));

    const auto r = std::get<ShowArgs>(ready);

    CHECK(r.line.has_value());
    CHECK(r.line == 1);
    CHECK(r.name.has_value());
    CHECK(r.name.value() == "something");
    CHECK(r.outputType == OutputType::QRCODE);
}

TEST_CASE("Check Show Va")
{
    parsed::Args parsed;
    ready::Args ready;
    const auto result = BuildCli(parsed, ready).parse({"argv[0]", "show", "--clip 1"});

    REQUIRE(result);
    REQUIRE(std::holds_alternative<ShowArgs>(ready));

    const auto r = std::get<ShowArgs>(ready);

    CHECK(r.line.has_value());
    CHECK(r.line == 1);
    CHECK(!r.name.has_value());
    CHECK(r.outputType == OutputType::CLIPBOARD);
}

TEST_CASE("Check Show Vb")
{
    parsed::Args parsed;
    ready::Args ready;
    const auto result = BuildCli(parsed, ready).parse({"argv[0]", "show", "--clip 1", "something"});

    REQUIRE(result);
    REQUIRE(std::holds_alternative<ShowArgs>(ready));

    const auto r = std::get<ShowArgs>(ready);

    CHECK(r.line.has_value());
    CHECK(r.line == 1);
    CHECK(r.name.has_value());
    CHECK(r.name.value() == "something");
    CHECK(r.outputType == OutputType::CLIPBOARD);
}

TEST_CASE("Check Show Vc")
{
    parsed::Args parsed;
    ready::Args ready;
    const auto result = BuildCli(parsed, ready).parse({"argv[0]", "show", "--qrcode 1"});

    REQUIRE(result);
    REQUIRE(std::holds_alternative<ShowArgs>(ready));

    const auto r = std::get<ShowArgs>(ready);

    CHECK(r.line.has_value());
    CHECK(r.line == 1);
    CHECK(!r.name.has_value());
    CHECK(r.outputType == OutputType::QRCODE);
}

TEST_CASE("Check Show Vd")
{
    parsed::Args parsed;
    ready::Args ready;
    const auto result =
        BuildCli(parsed, ready).parse({"argv[0]", "show", "--qrcode 1", "something"});

    REQUIRE(result);
    REQUIRE(std::holds_alternative<ShowArgs>(ready));

    const auto r = std::get<ShowArgs>(ready);

    CHECK(r.line.has_value());
    CHECK(r.line == 1);
    CHECK(r.name.has_value());
    CHECK(r.name.value() == "something");
    CHECK(r.outputType == OutputType::QRCODE);
}

TEST_CASE("Check Show VIa")
{
    parsed::Args parsed;
    ready::Args ready;
    const auto result = BuildCli(parsed, ready).parse({"argv[0]", "show", "--clip=1"});

    REQUIRE(result);
    REQUIRE(std::holds_alternative<ShowArgs>(ready));

    const auto r = std::get<ShowArgs>(ready);

    CHECK(r.line.has_value());
    CHECK(r.line == 1);
    CHECK(!r.name.has_value());
    CHECK(r.outputType == OutputType::CLIPBOARD);
}

TEST_CASE("Check Show VIb")
{
    parsed::Args parsed;
    ready::Args ready;
    const auto result = BuildCli(parsed, ready).parse({"argv[0]", "show", "--clip=1", "something"});

    REQUIRE(result);
    REQUIRE(std::holds_alternative<ShowArgs>(ready));

    const auto r = std::get<ShowArgs>(ready);

    CHECK(r.line.has_value());
    CHECK(r.line == 1);
    CHECK(r.name.has_value());
    CHECK(r.name.value() == "something");
    CHECK(r.outputType == OutputType::CLIPBOARD);
}

TEST_CASE("Check Show VIc")
{
    parsed::Args parsed;
    ready::Args ready;
    const auto result = BuildCli(parsed, ready).parse({"argv[0]", "show", "--qrcode=1"});

    REQUIRE(result);
    REQUIRE(std::holds_alternative<ShowArgs>(ready));

    const auto r = std::get<ShowArgs>(ready);

    CHECK(r.line.has_value());
    CHECK(r.line == 1);
    CHECK(!r.name.has_value());
    CHECK(r.outputType == OutputType::QRCODE);
}

TEST_CASE("Check Show VId")
{
    parsed::Args parsed;
    ready::Args ready;
    const auto result =
        BuildCli(parsed, ready).parse({"argv[0]", "show", "--qrcode=1", "something"});

    REQUIRE(result);
    REQUIRE(std::holds_alternative<ShowArgs>(ready));

    const auto r = std::get<ShowArgs>(ready);

    CHECK(r.line.has_value());
    CHECK(r.line == 1);
    CHECK(r.name.has_value());
    CHECK(r.name.value() == "something");
    CHECK(r.outputType == OutputType::QRCODE);
}

TEST_CASE("Check ls")
{
    parsed::Args parsed;
    ready::Args ready;
    const auto result = BuildCli(parsed, ready).parse({"argv[0]", "ls"});

    REQUIRE(result);
    REQUIRE(std::holds_alternative<ShowArgs>(ready));

    const auto r = std::get<ShowArgs>(ready);

    CHECK(!r.line.has_value());
    CHECK(!r.name.has_value());
    CHECK(r.outputType == OutputType::STDOUT);
}

TEST_CASE("Check list")
{
    parsed::Args parsed;
    ready::Args ready;
    const auto result = BuildCli(parsed, ready).parse({"argv[0]", "ls"});

    REQUIRE(result);
    REQUIRE(std::holds_alternative<ShowArgs>(ready));

    const auto r = std::get<ShowArgs>(ready);

    CHECK(!r.line.has_value());
    CHECK(!r.name.has_value());
    CHECK(r.outputType == OutputType::STDOUT);
}

} // namespace pass::cli
