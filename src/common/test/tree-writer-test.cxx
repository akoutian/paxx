// SPDX-License-Identifier: GPL-3.0-or-later

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "src/tree-writer.hxx"

#include <doctest/doctest.h>

#include <sstream>

namespace paxx::tree
{

namespace
{

void write(const std::vector<state> &entries, std::stringstream &out)
{
    std::for_each(entries.begin(), entries.end(), [&](const auto &i) { write(out, i); });
}

} // namespace

TEST_CASE("Check Single entry")
{
    std::vector<state> entries{{.last = true, .name{"one"}, .stack{}}};

    std::stringstream os;

    write(entries, os);

    CHECK(os.str() == "└── one\n");
}

TEST_CASE("Check Two Entries")
{
    std::vector<state> entries{
        {.last = false, .depth = 0, .name{"one"}, .stack{}},
        {.last = true, .depth = 0, .name{"two"}, .stack{}},
    };

    std::stringstream os;

    write(entries, os);

    CHECK(os.str() == "├── one\n"
                      "└── two\n");
}

TEST_CASE("Check Three Entries")
{
    std::vector<state> entries{
        {.last = false, .depth = 0, .name{"one"}, .stack{}},
        {.last = false, .depth = 0, .name{"two"}, .stack{}},
        {.last = true, .depth = 0, .name{"three"}, .stack{}},
    };

    std::stringstream os;

    write(entries, os);

    CHECK(os.str() == "├── one\n"
                      "├── two\n"
                      "└── three\n");
}

TEST_CASE("Check Single Nested entry")
{
    std::vector<state> entries{
        {.last = false, .depth = 0, .name{"one"}, .stack{}},
        {.last = true, .depth = 1, .name{"two"}, .stack{0}},
        {.last = true, .depth = 0, .name{"three"}, .stack{}},
    };

    std::stringstream os;

    write(entries, os);

    CHECK(os.str() == "├── one\n"
                      "│   └── two\n"
                      "└── three\n");
}

TEST_CASE("Check Multiple Nested Entries")
{
    std::vector<state> entries{
        {.last = false, .depth = 0, .name{"one"}, .stack{}},
        {.last = false, .depth = 1, .name{"two"}, .stack{0}},
        {.last = false, .depth = 2, .name{"three"}, .stack{0, 1}},
        {.last = true, .depth = 2, .name{"four"}, .stack{0, 1}},
        {.last = true, .depth = 1, .name{"five"}, .stack{0}},
        {.last = false, .depth = 2, .name{"six"}, .stack{0}},
        {.last = true, .depth = 2, .name{"seven"}, .stack{0}},
        {.last = true, .depth = 3, .name{"eight"}, .stack{0}},
        {.last = true, .depth = 0, .name{"nine"}, .stack{}},
        {.last = true, .depth = 1, .name{"ten"}, .stack{}},
    };

    std::stringstream os;

    write(entries, os);

    CHECK(os.str() == "├── one\n"
                      "│   ├── two\n"
                      "│   │   ├── three\n"
                      "│   │   └── four\n"
                      "│   └── five\n"
                      "│       ├── six\n"
                      "│       └── seven\n"
                      "│           └── eight\n"
                      "└── nine\n"
                      "    └── ten\n");
}

} // namespace paxx::tree
