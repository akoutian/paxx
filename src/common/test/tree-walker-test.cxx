// SPDX-License-Identifier: GPL-3.0-or-later

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "fake-directory-entry.hxx"
#include "fake-directory-iterator-traits.hxx"
#include "fake-directory-iterator.hxx"
#include "fake-directory-node.hxx"
#include "src/tree-walker.hxx"

#include <doctest/doctest.h>

#include <memory>

namespace paxx::tree
{

std::shared_ptr<fake_directory_node> build_simple_test_node()
{
    const auto b = std::make_shared<fake_directory_node>(fake_directory_node{"b", {}});
    const auto a = std::make_shared<fake_directory_node>(fake_directory_node{"a", {b}});
    const auto c = std::make_shared<fake_directory_node>(fake_directory_node{"c", {}});

    return std::make_shared<fake_directory_node>(fake_directory_node{"root", {a, c}});
}

std::shared_ptr<fake_directory_node> build_not_so_simple_test_node()
{

    const auto c = std::make_shared<fake_directory_node>(fake_directory_node{"c", {}});
    const auto d = std::make_shared<fake_directory_node>(fake_directory_node{"d", {}});
    const auto e = std::make_shared<fake_directory_node>(fake_directory_node{"e", {}});
    const auto b = std::make_shared<fake_directory_node>(fake_directory_node{"b", {c, d, e}});
    const auto g = std::make_shared<fake_directory_node>(fake_directory_node{"g", {}});
    const auto h = std::make_shared<fake_directory_node>(fake_directory_node{"h", {}});
    const auto f = std::make_shared<fake_directory_node>(fake_directory_node{"f", {g, h}});
    const auto i = std::make_shared<fake_directory_node>(fake_directory_node{"i", {}});
    const auto j = std::make_shared<fake_directory_node>(fake_directory_node{"j", {}});
    const auto k = std::make_shared<fake_directory_node>(fake_directory_node{"k", {}});
    const auto l = std::make_shared<fake_directory_node>(fake_directory_node{"l", {}});
    const auto a =
        std::make_shared<fake_directory_node>(fake_directory_node{"a", {b, f, i, j, k, l}});
    const auto o = std::make_shared<fake_directory_node>(fake_directory_node{"o", {}});
    const auto p = std::make_shared<fake_directory_node>(fake_directory_node{"p", {}});
    const auto n = std::make_shared<fake_directory_node>(fake_directory_node{"n", {o, p}});
    const auto m = std::make_shared<fake_directory_node>(fake_directory_node{"m", {n}});

    return std::make_shared<fake_directory_node>(fake_directory_node{"root", {a, m}});
}

void walk(std::shared_ptr<fake_directory_node> node, std::stringstream &ss)
{
    tree::state state{.name = node->path, .stack{}};
    walk_tree<fake_directory_iterator_traits>(fake_directory_iterator{fake_directory_entry{node}},
                                              state, ss);
}

TEST_CASE("Test empty tree")
{
    const auto test_node = std::make_shared<fake_directory_node>(fake_directory_node{"root", {}});

    std::stringstream ss;

    walk(test_node, ss);

    CHECK(ss.str() == "");
}

TEST_CASE("Test simple tree")
{
    const auto test_node = build_simple_test_node();

    std::stringstream ss;

    walk(test_node, ss);

    const std::string expected = "├── a\n"
                                 "│   └── b\n"
                                 "└── c\n";

    CHECK(ss.str() == expected);
}

TEST_CASE("Test not so simple tree")
{
    const auto test_node = build_not_so_simple_test_node();

    std::stringstream ss;

    walk(test_node, ss);

    const std::string expected = "├── a\n"
                                 "│   ├── b\n"
                                 "│   │   ├── c\n"
                                 "│   │   ├── d\n"
                                 "│   │   └── e\n"
                                 "│   ├── f\n"
                                 "│   │   ├── g\n"
                                 "│   │   └── h\n"
                                 "│   ├── i\n"
                                 "│   ├── j\n"
                                 "│   ├── k\n"
                                 "│   └── l\n"
                                 "└── m\n"
                                 "    └── n\n"
                                 "        ├── o\n"
                                 "        └── p\n";

    CHECK(ss.str() == expected);
}

} // NAMESPace paxx::tree
