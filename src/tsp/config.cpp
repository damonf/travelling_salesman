#include "config.h"

#include <sstream>
#include <optional>

#include <boost/program_options.hpp>
#include <boost/optional.hpp>
#include <boost/optional/optional_io.hpp>

namespace tsp {

Config::Config(int argc, char *argv[])
    :
        options_{}
      , desc_{}
{

    po::options_description desc(
            "Usage: tsp (--nodes <count> | --graph_file <filename>) [OPTION]...\n\n"
            "Options"
            );

    auto help = false;
    boost::optional<int> nodes;
    boost::optional<std::string> graph_file;
    boost::optional<std::string> output_dir;
    std::string algorithm_str;
    auto verbose = false;
 
    desc.add_options()
        ("help,h"      , po::bool_switch(&help)   , "show help")
        ("nodes,n"     , po::value(&nodes)        , "generate a random asymmetric graph with the specified number of nodes")
        ("graph-file,f", po::value(&graph_file)   , "read a graph from file")
        ("output-dir,o", po::value(&output_dir)   , "write solution(s) to output dir")
        ("algorithm,a" , po::value(&algorithm_str)->default_value("all"), "algorithm to use (brute | genetic | all)\n[default: all]") 
        ("verbose,v"   , po::bool_switch(&verbose), "be verbose\n[default: off]")
        ;

    std::ostringstream oss;
    oss << desc;
    desc_ = oss.str();

    parse_command_line(argc, argv, desc);

    if (!help && (!nodes && !graph_file) || (nodes && graph_file)) {
        throw std::logic_error(
                error_msg("exactly one of the options '--nodes' or '--graph_file' must be set")
                );
    }

    Algorithm algorithm = parse_algorithm(algorithm_str);

    options_ = Options {
        help,
        nodes      ? std::make_optional<int>(*nodes)              : std::nullopt,
        graph_file ? std::make_optional<std::string>(*graph_file) : std::nullopt,
        output_dir ? std::make_optional<std::string>(*output_dir) : std::nullopt,
        algorithm,
        verbose
    };
}

void Config::parse_command_line(
          int argc
        , char *argv[]
        , const po::options_description& desc
        ) {

    try {
        po::variables_map vm;
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);
    }
    catch (const std::exception& e) {
        throw std::logic_error(error_msg(e.what()));
    }
}

Algorithm Config::parse_algorithm(const std::string& algorithm_str) {

    if (const auto it = algorithms.find(algorithm_str); it != algorithms.end()) {
        return it->second;
    }
    else {
        throw std::logic_error(
                error_msg("invalid argument for option '--algorithm'")
                );
    }
}

std::string Config::error_msg(const char* const message) {
    std::ostringstream oss;
    oss << message << "\n"
        << "Try 'tsp --help' for more information.\n";
    return oss.str();
}

std::ostream& operator << (std::ostream& os, const Algorithm& algorithm)
{
    switch(algorithm) {
        case Algorithm::all: {
            os << "all";
            break;
        }
        case Algorithm::brute: {
            os << "brute";
            break;
        }
        case Algorithm::genetic: {
            os << "genetic";
            break;
        }
    }

    return os;
}

}
