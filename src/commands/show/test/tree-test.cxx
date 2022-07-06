#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "../src/tree.h"

#include "doctest/doctest.h"

#include <stdexcept>

TEST_CASE("Check Tee")
{
    pass::Tree tree;

    tree.Tee("tee");
    tree.Tee("tee");

    const auto result = tree.Get();

    CHECK(result.size() == 2);
    CHECK(result.at(0) == "├── tee");
    CHECK(result.at(1) == "├── tee");
}

TEST_CASE("Check Corner")
{
    pass::Tree tree;

    tree.Corner("corner");
    tree.Corner("corner");

    const auto result = tree.Get();

    CHECK(result.size() == 2);
    CHECK(result.at(0) == "└── corner");
    CHECK(result.at(1) == "└── corner");
}

TEST_CASE("Check Tee With Indent")
{
    pass::Tree tree;

    tree.Tee("tee");
    tree.Indent();
    tree.Tee("tee");

    const auto result = tree.Get();

    CHECK(result.size() == 2);
    CHECK(result.at(0) == "├── tee");
    CHECK(result.at(1) == "│   ├── tee");
}

TEST_CASE("Check Corner With Indent")
{
    pass::Tree tree;

    tree.Corner("corner");
    tree.Indent();
    tree.Corner("corner");

    const auto result = tree.Get();

    CHECK(result.size() == 2);
    CHECK(result.at(0) == "└── corner");
    CHECK(result.at(1) == "    └── corner");
}

TEST_CASE("Check Tee With Dedent")
{
    pass::Tree tree;

    tree.Tee("tee");
    tree.Indent();
    tree.Tee("tee");
    tree.Dedent();
    tree.Tee("tee");

    const auto result = tree.Get();

    CHECK(result.size() == 3);
    CHECK(result.at(0) == "├── tee");
    CHECK(result.at(1) == "│   ├── tee");
    CHECK(result.at(2) == "├── tee");
}

TEST_CASE("Check Corner With Dedent")
{
    pass::Tree tree;

    tree.Corner("corner");
    tree.Indent();
    tree.Corner("corner");
    tree.Dedent();
    tree.Corner("corner");

    const auto result = tree.Get();

    CHECK(result.size() == 3);
    CHECK(result.at(0) == "└── corner");
    CHECK(result.at(1) == "    └── corner");
    CHECK(result.at(2) == "└── corner");
}

TEST_CASE("Check Dedent Zero Depth")
{
    pass::Tree tree;

    CHECK_THROWS_WITH_AS(tree.Dedent(), "You tried to dedent with zero depth!", std::runtime_error);
}
