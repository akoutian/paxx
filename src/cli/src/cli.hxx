#pragma once

#include "common/args.hxx"

#include <lyra/lyra.hpp>

namespace paxx::cli
{

class cli
{
    lyra::cli m_cli;
    cmn::ready::args m_result;
    cmn::parsed::args m_args;

  public:
    cli();

    lyra::parse_result parse(int argc, char **argv);

    cmn::ready::args get() const;
};

} // namespace paxx::cli
