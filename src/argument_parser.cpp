#include <brightness/argument_parser.hpp>

using namespace br;

argument_parser::argument_parser(std::vector<std::string> const& argv)
    : brightness{0}
{
    boost::program_options::options_description general_options{"Options"};
    general_options.add_options()
        ("help,h", "show help menu")
        ("version,v", "show program version");

    boost::program_options::options_description modifying_options{"Modification"};
    modifying_options.add_options()
        ("brightness,b", boost::program_options::value<std::string>(), "percentage of brightness change");

    boost::program_options::positional_options_description positional_arguments{};
    positional_arguments.add("brightness", -1);

    boost::program_options::options_description all_options{};
    all_options.add(general_options).add(modifying_options);

    try
    {
        boost::program_options::command_line_parser parser{argv};
        parser = parser.options(all_options).positional(positional_arguments);
        boost::program_options::store(parser.run(), args);
        boost::program_options::notify(args);

        if (args.count("help"))
        {
            std::cerr << "argument-parser <percentage>\n\n" << all_options << std::endl;
            std::exit(0);
        }

        if (args.count("version"))
        {
            std::cout << PROGRAM_VERSION << std::endl;
            std::exit(0);
        }

        if (args.count("brightness"))
        {
            std::string input{args["brightness"].as<std::string>()};
            brightness = std::stoi(input);
        }

        if (brightness > 100)
        {
            throw boost::program_options::invalid_option_value{args["brightness"].as<std::string>()};
        }
    }
    catch (boost::program_options::error const& err)
    {
        std::cerr << err.what() << std::endl;
        std::exit(1);
    }
}
