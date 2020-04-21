#pragma once

#include "../matrix/matrix.hpp"
#include "parser.hh"

#include <iostream>
#include <FlexLexer.h>
#include <unordered_map>
#include <map>
#include <algorithm>

using cxx_containers::Matrix;

namespace Circuit {

    class Parser final {
        struct edge {
            double resistance;
            double voltage;
        };

        using adjaceny_list_t = std::map<int, std::unordered_map<int, edge>>;
        using token_t = yy::GraphParser::token_type;

        yyFlexLexer plex;
        adjaceny_list_t adjacency_list;
    public:
        explicit Parser(std::istream* stream)
            :
                plex(stream),
                adjacency_list()
        {
            yy::GraphParser parser(*this);
            if (parser.parse() != 0)
                throw std::runtime_error("parser.parse() != 0");

            // graph vertexes should create a sequnce 1 2 3 ...
            int i = 1;
            auto it = std::find_if(adjacency_list.begin(), adjacency_list.end(),
                    [i] (auto& elem) mutable
                    {
                        return elem.first != i++;
                    });

            if (it != adjacency_list.end())
                throw std::runtime_error("it != adjacency_list.end()");
        }

        token_t yylex(yy::GraphParser::semantic_type* yylval) {
            auto tt = static_cast<token_t>(plex.yylex());

            switch(tt) {
                case token_t::TVERTEX:
                    *yylval = std::stoi(std::string(plex.YYText(), plex.YYLeng()));
                    break;

                case token_t::TVOLTAGE:
                    *yylval = std::stod(std::string(plex.YYText(), plex.YYLeng()-1));
                    break;

                case token_t::TRESISTANCE:
                    *yylval = std::stod(std::string(plex.YYText(), plex.YYLeng()));
                    break;
            }

            return tt;
        }

        void add_edge (int lhs_vert, int rhs_vert, double R, double V = 0.0) {
            // loops aren't allowed
            if (lhs_vert == rhs_vert || lhs_vert < 0)
                throw std::logic_error("lhs_vert == rhs_vert || lhs_vert < 0");

            auto find_edge = [this] (int lhs_vert, int rhs_vert) {
                auto it = adjacency_list.find(lhs_vert); 
                if (it != adjacency_list.end()) 
                    if (it -> second.find(rhs_vert) != it -> second.end())
                        throw std::logic_error("edge already exists");
            };

            find_edge(lhs_vert, rhs_vert);
            find_edge(rhs_vert, lhs_vert);

            adjacency_list[lhs_vert][rhs_vert] = {R, V};
            adjacency_list[rhs_vert];
        }

        Matrix<double> resistors() const {
            Matrix<double> resistors({adjacency_list.size(), adjacency_list.size()});

            for (int i = 0; i < resistors.rows(); ++i) {
                auto it = adjacency_list.find(i+1);
                for (int j = 0; j < resistors.cols(); ++j) {
                    auto jt = it -> second.find(j+1);
                    if (jt != it -> second.end()) {
                        resistors[i][j] = jt->second.resistance;
                        resistors[j][i] = resistors[i][j];
                    }
                }
            }

            return resistors;
        }

        Matrix<double> adjacency() const {
            Matrix<double> adjacency({adjacency_list.size(), adjacency_list.size()});

            for (int i = 0; i < adjacency.rows(); ++i) {
                auto it = adjacency_list.find(i+1);
                for (int j = 0; j < adjacency.cols(); ++j) {
                    auto jt = it -> second.find(j+1);
                    if (jt != it -> second.end()) {
                        adjacency[i][j] = 1;
                        adjacency[j][i] = 1;
                    }
                }
            }

            return adjacency;
        }

        Matrix<double> voltage_sources() const {
            Matrix<double> V({adjacency_list.size(), adjacency_list.size()});

            for (int i = 0; i < V.rows(); ++i) {
                auto it = adjacency_list.find(i+1);
                for (int j = 0; j < V.cols(); ++j) {
                    auto jt = it -> second.find(j+1);
                    if (jt != it -> second.end()) {
                        V[i][j] = jt -> second.voltage;
                        V[j][i] = -1 * V[i][j];
                    }
                }
            }

            return V;
        }

        void parse_output(std::ostream& os, const Matrix<double>& currents) const {
            assert(currents.rows() == currents.cols());

            for (const auto& lhs_vertex : adjacency_list)
                for (const auto& rhs_vertex : lhs_vertex.second) {
                    os << lhs_vertex.first << " -- " << rhs_vertex.first << ": "
                        << currents[lhs_vertex.first-1][rhs_vertex.first-1] << " A" << std::endl;
                }
        }
    };
}