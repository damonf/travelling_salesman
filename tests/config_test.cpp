#include "config.h"

#include <catch2/catch.hpp>

#include <string>

TEST_CASE("config tests", "[config]")
{

    SECTION("throws error when neither nodes or graph_file is set")
    {
        const char *argv[] = { "app_name" };
        auto argc = std::size(argv);

        REQUIRE_THROWS_WITH(
                tsp::Config(static_cast<int>(argc), const_cast<char **>(argv)),
                Catch::Contains( "--nodes" ) &&
                Catch::Contains( "--graph_file" )
                );
    }
    
    SECTION("throws error when algorithm is invalid")
    {
        const char *argv[] = { "app_name",  "-n", "10", "-a", "invalid" };
        auto argc = std::size(argv);

        REQUIRE_THROWS_WITH(
                tsp::Config(static_cast<int>(argc), const_cast<char **>(argv)),
                Catch::Contains( "--algorithm" )
                );
    }
    
    SECTION("sets all options with --nodes set")
    {
        const char *argv[] = {
            "app_name",
            "--help",
            "--nodes",
            "10",
            "--output-dir",
            "output",
            "--algorithm",
            "genetic",
            "--verbose"
        };
    
        auto argc = std::size(argv);
    
        tsp::Config sut{static_cast<int>(argc), const_cast<char **>(argv)};
    
        auto options = sut.get_options();

        REQUIRE(options.help);
        REQUIRE(options.nodes == 10);
        REQUIRE(!options.graph_file);
        REQUIRE(options.output_dir == std::string{"output"});
        REQUIRE(options.algorithm == tsp::Algorithm::genetic);
        REQUIRE(options.verbose);
    }
    
    SECTION("sets all options with --graph-file set")
    {
        const char *argv[] = {
            "app_name",
            "--help",
            "--graph-file",
            "gfile",
            "--output-dir",
            "output",
            "--algorithm",
            "genetic",
            "--verbose"
        };
    
        auto argc = std::size(argv);
    
        tsp::Config sut{static_cast<int>(argc), const_cast<char **>(argv)};
    
        auto options = sut.get_options();

        REQUIRE(options.help);
        REQUIRE(!options.nodes);
        REQUIRE(options.graph_file == std::string{"gfile"});
        REQUIRE(options.output_dir == std::string{"output"});
        REQUIRE(options.algorithm == tsp::Algorithm::genetic);
        REQUIRE(options.verbose);
    }
    
    SECTION("sets default options")
    {
        const char *argv[] = {
            "app_name",
            "--graph-file",
            "gfile"
        };
    
        int argc = std::size(argv);
    
        tsp::Config sut{argc, const_cast<char **>(argv)};
    
        auto options = sut.get_options();
    
        REQUIRE(!options.help);
        REQUIRE(!options.nodes);
        REQUIRE(options.graph_file == std::string{"gfile"});
        REQUIRE(!options.output_dir);
        REQUIRE(options.algorithm == tsp::Algorithm::all);
        REQUIRE(!options.verbose);
    }
    
    SECTION("sets desc")
    {
        const char *argv[] = { "app_name",  "-n", "10" };
        auto argc = std::size(argv);
    
        tsp::Config sut{static_cast<int>(argc), const_cast<char **>(argv)};
    
        const auto& desc = sut.desc();
    
        REQUIRE(!desc.empty());
    }

}
