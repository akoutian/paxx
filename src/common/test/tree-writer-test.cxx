// SPDX-License-Identifier: GPL-3.0-or-later

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "src/tree-writer.hxx"

#include <doctest/doctest.h>

#include <sstream>

namespace paxx::tree
{

namespace
{

void Write(const std::vector<TreeState> &entries, std::stringstream &out)
{
    std::for_each(entries.begin(), entries.end(), [&](const auto &i) { Write(out, i); });
}

} // namespace

TEST_CASE("Check Single Entry")
{
    std::vector<TreeState> entries{{.last = true, .name{"one"}, .stack{}}};

    std::stringstream os;

    Write(entries, os);

    CHECK(os.str() == "\342\224\224\342\224\200\342\224\200 one\n");
}

TEST_CASE("Check Two Entries")
{
    std::vector<TreeState> entries{
        {.last = false, .depth = 0, .name{"one"}, .stack{}},
        {.last = true, .depth = 0, .name{"two"}, .stack{}},
    };

    std::stringstream os;

    Write(entries, os);

    CHECK(os.str() == "\342\224\234\342\224\200\342\224\200 one\n"
                      "\342\224\224\342\224\200\342\224\200 two\n");
}

TEST_CASE("Check Three Entries")
{
    std::vector<TreeState> entries{
        {.last = false, .depth = 0, .name{"one"}, .stack{}},
        {.last = false, .depth = 0, .name{"two"}, .stack{}},
        {.last = true, .depth = 0, .name{"three"}, .stack{}},
    };

    std::stringstream os;

    Write(entries, os);

    CHECK(os.str() == "\342\224\234\342\224\200\342\224\200 one\n"
                      "\342\224\234\342\224\200\342\224\200 two\n"
                      "\342\224\224\342\224\200\342\224\200 three\n");
}

TEST_CASE("Check Single Nested Entry")
{
    std::vector<TreeState> entries{
        {.last = false, .depth = 0, .name{"one"}, .stack{}},
        {.last = true, .depth = 1, .name{"two"}, .stack{0}},
        {.last = true, .depth = 0, .name{"three"}, .stack{}},
    };

    std::stringstream os;

    Write(entries, os);

    CHECK(os.str() == "\342\224\234\342\224\200\342\224\200 one\n"
                      "\342\224\202   \342\224\224\342\224\200\342\224\200 two\n"
                      "\342\224\224\342\224\200\342\224\200 three\n");
}

TEST_CASE("Check Single Nested Entry")
{
    std::vector<TreeState> entries{
        {.last = false, .depth = 0, .name{"one"}, .stack{}},
        {.last = true, .depth = 1, .name{"two"}, .stack{0}},
        {.last = true, .depth = 0, .name{"three"}, .stack{}},
    };

    std::stringstream os;

    Write(entries, os);

    CHECK(os.str() == "\342\224\234\342\224\200\342\224\200 one\n"
                      "\342\224\202   \342\224\224\342\224\200\342\224\200 two\n"
                      "\342\224\224\342\224\200\342\224\200 three\n");
}

TEST_CASE("Check Multiple Nested Entries")
{
    std::vector<TreeState> entries{
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

    Write(entries, os);

    CHECK(os.str() == "\342\224\234\342\224\200\342\224\200 one\n"
                      "\342\224\202   \342\224\234\342\224\200\342\224\200 two\n"
                      "\342\224\202   \342\224\202   \342\224\234\342\224\200\342\224\200 three\n"
                      "\342\224\202   \342\224\202   \342\224\224\342\224\200\342\224\200 four\n"
                      "\342\224\202   \342\224\224\342\224\200\342\224\200 five\n"
                      "\342\224\202       \342\224\234\342\224\200\342\224\200 six\n"
                      "\342\224\202       \342\224\224\342\224\200\342\224\200 seven\n"
                      "\342\224\202           \342\224\224\342\224\200\342\224\200 eight\n"
                      "\342\224\224\342\224\200\342\224\200 nine\n"
                      "    \342\224\224\342\224\200\342\224\200 ten\n");
}

} // namespace paxx::tree
