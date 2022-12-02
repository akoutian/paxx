// SPDX-License-Identifier: GPL-3.0-or-later

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "src/tree.h"

#include "doctest/doctest.h"

#include <sstream>

namespace pass::tree
{

namespace
{

void Print(const std::vector<TreeInfo> &entries, std::stringstream &out)
{
    std::for_each(entries.begin(), entries.end(), [&](const auto &i) { Print(out, i); });
}

} // namespace

TEST_CASE("Check Single Entry")
{
    std::vector<TreeInfo> entries{{.isLast = true, .name{"one"}, .pending{}}};

    std::stringstream os;

    Print(entries, os);

    CHECK(os.str() == "\342\224\224\342\224\200\342\224\200 one\n");
}

TEST_CASE("Check Two Entries")
{
    std::vector<TreeInfo> entries{
        {.isLast = false, .depth = 0, .name{"one"}, .pending{}},
        {.isLast = true, .depth = 0, .name{"two"}, .pending{}},
    };

    std::stringstream os;

    Print(entries, os);

    CHECK(os.str() == "\342\224\234\342\224\200\342\224\200 one\n"
                      "\342\224\224\342\224\200\342\224\200 two\n");
}

TEST_CASE("Check Three Entries")
{
    std::vector<TreeInfo> entries{
        {.isLast = false, .depth = 0, .name{"one"}, .pending{}},
        {.isLast = false, .depth = 0, .name{"two"}, .pending{}},
        {.isLast = true, .depth = 0, .name{"three"}, .pending{}},
    };

    std::stringstream os;

    Print(entries, os);

    CHECK(os.str() == "\342\224\234\342\224\200\342\224\200 one\n"
                      "\342\224\234\342\224\200\342\224\200 two\n"
                      "\342\224\224\342\224\200\342\224\200 three\n");
}

TEST_CASE("Check Single Nested Entry")
{
    std::vector<TreeInfo> entries{
        {.isLast = false, .depth = 0, .name{"one"}, .pending{}},
        {.isLast = true, .depth = 1, .name{"two"}, .pending{0}},
        {.isLast = true, .depth = 0, .name{"three"}, .pending{}},
    };

    std::stringstream os;

    Print(entries, os);

    CHECK(os.str() == "\342\224\234\342\224\200\342\224\200 one\n"
                      "\342\224\202   \342\224\224\342\224\200\342\224\200 two\n"
                      "\342\224\224\342\224\200\342\224\200 three\n");
}

TEST_CASE("Check Single Nested Entry")
{
    std::vector<TreeInfo> entries{
        {.isLast = false, .depth = 0, .name{"one"}, .pending{}},
        {.isLast = true, .depth = 1, .name{"two"}, .pending{0}},
        {.isLast = true, .depth = 0, .name{"three"}, .pending{}},
    };

    std::stringstream os;

    Print(entries, os);

    CHECK(os.str() == "\342\224\234\342\224\200\342\224\200 one\n"
                      "\342\224\202   \342\224\224\342\224\200\342\224\200 two\n"
                      "\342\224\224\342\224\200\342\224\200 three\n");
}

TEST_CASE("Check Multiple Nested Entries")
{
    std::vector<TreeInfo> entries{
        {.isLast = false, .depth = 0, .name{"one"}, .pending{}},
        {.isLast = false, .depth = 1, .name{"two"}, .pending{0}},
        {.isLast = false, .depth = 2, .name{"three"}, .pending{0, 1}},
        {.isLast = true, .depth = 2, .name{"four"}, .pending{0, 1}},
        {.isLast = true, .depth = 1, .name{"five"}, .pending{0}},
        {.isLast = false, .depth = 2, .name{"six"}, .pending{0}},
        {.isLast = true, .depth = 2, .name{"seven"}, .pending{0}},
        {.isLast = true, .depth = 3, .name{"eight"}, .pending{0}},
        {.isLast = true, .depth = 0, .name{"nine"}, .pending{}},
        {.isLast = true, .depth = 1, .name{"ten"}, .pending{}},
    };

    std::stringstream os;

    Print(entries, os);

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
