#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "src/build-cli.h"

#include <doctest/doctest.h>
#include <lyra/lyra.hpp>

namespace pass::cli
{

TEST_CASE("Check Version")
{
    parsed::Args parsed;
    ready::Args ready;
    const auto result = BuildCli(parsed, ready).parse({"argv[0]", "version"});

    REQUIRE(result);
    REQUIRE(std::holds_alternative<VersionArgs>(ready));
}

} // namespace pass::cli
