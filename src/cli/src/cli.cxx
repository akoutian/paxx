#include "cli.hxx"

#include "build-cli.hxx"

namespace paxx::cli
{

cli::cli() : m_cli{build_cli(m_args, m_result)}
{
}

lyra::parse_result cli::parse(int argc, char **argv)
{
    return m_cli.parse({argc, argv});
}

cmn::ready::args cli::get() const
{
    return m_result;
}

} // namespace paxx::cli
