// SPDX-License-Identifier: GPL-3.0-or-later

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "src/tree-writer.h"

#include "doctest/doctest.h"

#include <sstream>

namespace pass::tree
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
    std::vector<TreeState> entries{{.last = true, .name{"one"}, .open{}}};

    std::stringstream os;

    Write(entries, os);

    CHECK(os.str() == "\342\224\224\342\224\200\342\224\200 one\n");
}

TEST_CASE("Check Two Entries")
{
    std::vector<TreeState> entries{
        {.last = false, .depth = 0, .name{"one"}, .open{}},
        {.last = true, .depth = 0, .name{"two"}, .open{}},
    };

    std::stringstream os;

    Write(entries, os);

    CHECK(os.str() == "\342\224\234\342\224\200\342\224\200 one\n"
                      "\342\224\224\342\224\200\342\224\200 two\n");
}

TEST_CASE("Check Three Entries")
{
    std::vector<TreeState> entries{
        {.last = false, .depth = 0, .name{"one"}, .open{}},
        {.last = false, .depth = 0, .name{"two"}, .open{}},
        {.last = true, .depth = 0, .name{"three"}, .open{}},
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
        {.last = false, .depth = 0, .name{"one"}, .open{}},
        {.last = true, .depth = 1, .name{"two"}, .open{0}},
        {.last = true, .depth = 0, .name{"three"}, .open{}},
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
        {.last = false, .depth = 0, .name{"one"}, .open{}},
        {.last = true, .depth = 1, .name{"two"}, .open{0}},
        {.last = true, .depth = 0, .name{"three"}, .open{}},
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
        {.last = false, .depth = 0, .name{"one"}, .open{}},
        {.last = false, .depth = 1, .name{"two"}, .open{0}},
        {.last = false, .depth = 2, .name{"three"}, .open{0, 1}},
        {.last = true, .depth = 2, .name{"four"}, .open{0, 1}},
        {.last = true, .depth = 1, .name{"five"}, .open{0}},
        {.last = false, .depth = 2, .name{"six"}, .open{0}},
        {.last = true, .depth = 2, .name{"seven"}, .open{0}},
        {.last = true, .depth = 3, .name{"eight"}, .open{0}},
        {.last = true, .depth = 0, .name{"nine"}, .open{}},
        {.last = true, .depth = 1, .name{"ten"}, .open{}},
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

} // namespace pass::tree
