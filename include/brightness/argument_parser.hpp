#pragma once

#include <boost/program_options.hpp>
#include <boost/system.hpp>
#include <stdexcept>
#include <iostream>
#include <cstdint>
#include <string>
#include <vector>

namespace br
{
class argument_parser
{
private:
    boost::program_options::variables_map args;

public:
    std::int8_t percentage;
    bool read_only;

public:
    explicit argument_parser(std::vector<std::string> const& argv);
};
} // br
