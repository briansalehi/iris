#include <brightness/argument_parser.hpp>

#include <filesystem>
#include <iostream>
#include <exception>
#include <fstream>
#include <ranges>
#include <vector>
#include <string>
#include <cmath>
#include <print>

int main(int argc, char** argv)
{
    try
    {
        auto arg_range = std::ranges::subrange(argv + 1, argv + argc);
        std::vector<std::string> args = std::ranges::to<std::vector<std::string>>(arg_range | std::views::transform([](char const* arg) { return std::string{arg}; }));

        br::argument_parser options(args);

        std::vector<std::filesystem::directory_entry> displays;
        for (std::filesystem::directory_entry const& entry: std::filesystem::directory_iterator{"/sys/class/backlight"})
        {
            displays.push_back(entry);
        }

        for (std::filesystem::directory_entry const& entry: displays)
        {
            std::uint64_t current_brightness{}, max_brightness{}, current_percentage{}, target_brightness{}, target_percentage{};
            std::string buffer{};
            std::filesystem::path brightness_filepath{entry.path() / "brightness"};

            if (!std::filesystem::exists(brightness_filepath))
                throw std::runtime_error{"display brightness file does not exist"};

            std::ifstream brightness_file{brightness_filepath};
            std::ifstream max_brightness_file{entry.path() / "max_brightness"};

            brightness_file >> buffer;
            current_brightness = std::stoull(std::move(buffer));

            max_brightness_file >> buffer;
            max_brightness = std::stoull(std::move(buffer));

            current_percentage = current_brightness * 100 / max_brightness;
            target_percentage = options.percentage;
            target_brightness = target_percentage * max_brightness / 100;

            if (options.read_only)
                std::println("{}: {}%", entry.path().filename().string(), current_percentage);
            else
                std::ofstream{brightness_filepath} << target_brightness;
        }
    }
    catch (std::exception const& exp)
    {
        std::println(std::cerr, "{}", exp.what());
    }
}
