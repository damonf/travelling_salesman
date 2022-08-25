#include "graph.h"
#include "brute_force.h"
#include "stop_watch.h"
#include "config.h"
#include "graph_gen.h"
#include "genetic.h"
#include "make_injector.h"

#include <string>
#include <iostream>
#include <random>
#include <unistd.h> // for EXIT_FAILURE, EXIT_SUCCESS 
#include <regex>
#include <fstream>
#include <optional>
#include <filesystem>

template<typename T>
void check_fs(T& ofs, const std::string& filename) {
    if (!ofs.is_open()) {
        std::string err{"could not open file: "};
        err.append(filename).append("\n");
        throw std::logic_error(err);
    }
}

std::string load_graph(const std::string& filename) {

    std::ifstream ifs{filename, std::ios::in};

    check_fs(ifs, filename); 

    return {
        (std::istreambuf_iterator<char>(ifs)),
        (std::istreambuf_iterator<char>())
    };
}

void save_graph(
          const std::string& graph
        , const std::optional<std::string>& out_dir
        ) {
    
    auto filename{*out_dir + "/graph.txt"};
    std::ofstream ofs{filename, std::ios::out | std::ios::trunc};

    check_fs(ofs, filename);

    ofs << graph;
}

template<typename T>
void run_algorithm(
          T& algorithm
        , const tsp::Graph& graph
        , const std::string& name
        , const std::optional<std::string>& out_dir
        , bool verbose
        )
{
    StopWatch timer{};

    auto result = algorithm.shortest_path(graph);

    auto elapsed = timer.elapsed();

    if (verbose) {
        std::cout << "\n";
        std::cout << name << "\n";
        std::cout << "elapsed (ms): " << elapsed << "\n";
        std::cout << "shortest path: " << result.second << "\n";
    }

    for (auto node: result.first) {
        std::cout << node << " ";
    }

    std::cout << "\n";

    if (out_dir) {
        auto filename{*out_dir + "/" + name + "_path.txt"};
        std::ofstream ofs{filename, std::ios::out | std::ios::trunc};

        check_fs(ofs, filename);

        for (auto node: result.first) {
            ofs << node << "\n";
        }
    }
}

int main(int argc, char *argv[]) {

    try {
        const tsp::Config config{argc, argv};
        auto options = config.get_options();

        auto [help, nodes, graph_file, solution_file, algorithm, verbose] = options;

        if (help) {
            std::cout << config.desc();
            return EXIT_SUCCESS;
        }

        if (options.output_dir) {
            std::filesystem::create_directories(*options.output_dir);
        }

        auto injector = make_injector();
        std::string graph_string;

        if (options.nodes) {
            auto graph_gen = injector.create<tsp::GraphGen>();
            graph_string = graph_gen.Generate(*options.nodes);

            if (options.output_dir) {
                save_graph(graph_string, options.output_dir);
            }
        }
        else {
            graph_string = load_graph(*options.graph_file);
        }

        if (options.verbose) {
            std::cout << graph_string;
        }

        tsp::Graph graph{graph_string.c_str()};

        if (options.algorithm == tsp::Algorithm::all ||
            options.algorithm == tsp::Algorithm::brute) {
            tsp::BruteForce brute_force{};
            run_algorithm(brute_force, graph, "brute_force", options.output_dir, verbose);
        }

        if (options.algorithm == tsp::Algorithm::all ||
            options.algorithm == tsp::Algorithm::genetic) {

            auto genetic = injector.create<tsp::Genetic>();
            run_algorithm(genetic, graph, "genetic", options.output_dir, verbose);
        }

        return EXIT_SUCCESS;
    }
    catch (const std::exception& e) {
        std::cerr << e.what();
        return EXIT_FAILURE;
    }
}
