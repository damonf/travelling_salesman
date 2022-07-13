#include "graph.h"

#include <stdexcept>
#include <regex>

namespace tsp {

Graph::Graph(const char* const graph)
    : graph_{} {

    parse_graph(graph);
    check_dimensions();
}

size_t Graph::num_vertices() const {
    return graph_.size();
}

Distance Graph::edge(const size_t i, const size_t j) const {
    return graph_.at(i).at(j);
}

Distance Graph::length(const Path& path) const {

    if (path.size() < 2) {
        return 0;
    }

    Distance total_distance = 0;

    for (size_t j = 1; j < path.size(); j++) {

        const auto distance = edge(path[j - 1], path[j]);

        if (distance == NoEdgeVal) {
            return NoEdgeVal;
        }

        total_distance += distance;
    }

    return total_distance;
}

void Graph::parse_graph(const char* const graph) {

    std::istringstream ss{graph};
    std::string line;

    while (std::getline(ss, line)) {

        if (std::regex_search(line, InvalidChars)) {
            throw std::logic_error(
                    "graph contains invalid characters"
                    );
        }

        auto vertices = get_edges(line);

        graph_.push_back(std::move(vertices));
    }
}

Edges Graph::get_edges(const std::string& line) const {

    const auto line_begin =
        std::sregex_iterator(line.begin(), line.end(), ValidChars);

    const auto line_end = std::sregex_iterator();

    Edges edges;

    for (auto i = line_begin; i != line_end; ++i) {

        auto match = *i;
        auto match_str = match.str();

        if (match_str == NoEdgeSymbol) {
            edges.push_back(NoEdgeVal);
        }
        else {
            if (match_str.find(NegativeSymbol) != std::string::npos) {
                throw std::logic_error(
                        match_str + " is not a valid positive number"
                        );
            }

            if (!std::regex_search(match_str, Number)) {
                throw std::logic_error(
                        match_str + " is not a valid number"
                        );
            }

            auto num = std::stod(match_str);
            edges.push_back(num);
        }
    }   

    return edges;
}

void Graph::check_dimensions() const {

    if (auto len = graph_.size();
            len < 2
            ||
            std::any_of(
                graph_.cbegin(),
                graph_.cend(),
                [len] (const Edges& row) {
                    return row.size() != len;
                })
       ) {
        throw std::logic_error("graph is malformed");
    }
}

}
