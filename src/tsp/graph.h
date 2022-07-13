#ifndef __GRAPH_H
#define __GRAPH_H

#include <string>
#include <vector>
#include <limits>
#include <regex>

namespace tsp {

    using std::size_t;
    using std::string;
    using std::regex;
    using std::vector;
    using Distance = double;
    using Edges = vector<Distance>;
    using Path = vector<size_t>;

    class Graph {
        public:
            Graph(const char* graph);
            [[nodiscard]] size_t num_vertices() const;
            [[nodiscard]] Distance edge(size_t i, size_t j) const;
            [[nodiscard]] Distance length(const Path& path) const;

            static constexpr Distance NoEdgeVal = std::numeric_limits<Distance>::max();

        private:
            void parse_graph(const char* graph);
            void check_dimensions() const;
            [[nodiscard]] Edges get_edges(const std::string& line) const;

            vector<Edges> graph_;

            static constexpr const char* const NoEdgeSymbol = "-";
            static constexpr const char* const NegativeSymbol = "-";
            static inline const regex ValidChars{ R"([0-9-.]+)" };
            static inline const regex InvalidChars{ R"([^0-9 -.])" };
            static inline const regex Number{ R"(^\d+\.?\d*$)" };
    };

}

#endif // __GRAPH_H

