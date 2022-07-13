#ifndef __CONFIG_H
#define __CONFIG_H

#include <string>
#include <unordered_map>
#include <optional>

#include <boost/program_options.hpp>

namespace tsp {

    namespace po = boost::program_options;

    enum class Algorithm { all, brute, genetic };

    struct Options {
        bool help;
        std::optional<int> nodes;
        std::optional<std::string> graph_file;
        std::optional<std::string> output_dir;
        Algorithm algorithm;
        bool verbose;
    };

    class Config {
        public:
            Config(int argc, char *argv[]);

            [[nodiscard]] Options get_options() const {
                return options_;
            }

            [[nodiscard]] const std::string& desc() const {
                return desc_;
            }

        private:
            void parse_command_line(int argc, char *argv[], const po::options_description& desc);
            Algorithm parse_algorithm(const std::string& algorithm_str);
            static std::string error_msg(const char* message);

            Options options_;

            std::string desc_;

            inline static constexpr Algorithm default_algorithm{Algorithm::all};

            inline static const std::unordered_map<std::string, Algorithm> algorithms = {
                {"all", Algorithm::all},
                {"genetic", Algorithm::genetic},
                {"brute", Algorithm::brute}
            };
    };

    std::ostream& operator << (std::ostream& os, const Algorithm& algorithm);
}

#endif // __CONFIG_H

