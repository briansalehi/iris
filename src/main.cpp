#include <brightness/argument_parser.hpp>

#include <ranges>
#include <vector>
#include <string>
#include <print>

int main(int argc, char** argv)
{
    auto arg_range = std::ranges::subrange(argv + 1, argv + argc);
    std::vector<std::string> args = std::ranges::to<std::vector<std::string>>(arg_range | std::views::transform([](char const* arg) { return std::string{arg}; }));

    br::argument_parser options(args);

    std::println("brightness: {:+}", options.brightness);
}
