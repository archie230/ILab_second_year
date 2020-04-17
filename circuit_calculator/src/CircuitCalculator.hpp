#pragma once

#include "matrix/matrix.hpp"
#include "parser/CircuitParser.hpp"
#include "matrix/GraphFunctions.hpp"

#include <iostream>
#include <vector>
#include <cassert>

using cxx_containers::Matrix;

namespace Circuit {

    class Calculator final {
        Parser parser;
        Matrix<double> resistors, adjacency, voltage_sources;

        std::pair<double, double> CycleParams(const Matrix<double>& cycle) const noexcept {
            double R = 0, V = 0;

            for (size_t i = 0; i < cycle.rows(); ++i)
                for (size_t j = 0; j < cycle.cols(); ++j)
                    if (cycle[i][j] != 0) {
                        R += resistors[i][j];
                        V += voltage_sources[i][j];
                    }

            return std::make_pair(R,V);
        }

        double CycleAddition(const Matrix<double>& main_cycle, const Matrix<double>& other) const {
            double R = 0;

            for (size_t i = 0; i < main_cycle.rows(); ++i)
                for (size_t j = 0; j < main_cycle.cols(); ++j)
                    if (main_cycle[i][j] != 0) {
                        if (other[i][j] != 0)
                            R += resistors[i][j];
                        else if (other[j][i] != 0)
                            R += -1 * resistors[j][i];
                    }

            return R;
        }

        Matrix<double> KirchhoffEquations(std::vector<Matrix<double>>& Loops) const {
            // Kirchhoff Equations matrix
            Matrix<double> KEmatrix({Loops.size(), Loops.size()});
            // Voltage matrix (KE rhs)
            Matrix<double> V({Loops.size(), 1});

            for (size_t i = 0; i < KEmatrix.rows(); ++i)
                for (size_t j = 0; j < KEmatrix.cols(); ++j) {
                    if (i == j)
                        std::tie(KEmatrix[i][j], V[i][0]) = CycleParams(Loops[i]);
                    else
                        KEmatrix[i][j] = CycleAddition(Loops[i], Loops[j]);
                }

            assert(KEmatrix.determinant() != 0);

            return cxx_containers::SolveSystem(KEmatrix, V);
        }

    public:
        explicit Calculator(std::istream* is)
            :
                parser(is),
                resistors(parser.resistors()),
                adjacency(parser.adjacency()),
                voltage_sources(parser.voltage_sources())
        {}

        void solve_circuit() {
            auto Loops = create_independ_cycles_set(adjacency);

            for (auto& Loop : Loops)
                set_cycle_orientation(Loop);

            auto LoopsCurrents = KirchhoffEquations(Loops);
            assert(LoopsCurrents.rows() == Loops.size());

            Matrix<double> currents({adjacency.rows(), adjacency.cols()}, 0);

            for (size_t i = 0; i < currents.rows(); ++i)
                for (size_t j = i+1; j < currents.cols(); ++j) {
                    for (size_t k = 0; k < LoopsCurrents.rows(); ++k) 
                        currents[i][j] += LoopsCurrents[k][0] *
                              ((Loops[k][i][j] == 0) ? (-1 * Loops[k][j][i]) : Loops[k][i][j]);
                    currents[j][i] = -1 * currents[i][j];
                }

            parser.parse_output(std::cout, currents);
        }
    };
}
