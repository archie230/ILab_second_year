#pragma once

#include "matrix.hpp"
#include <vector>
#include <cassert>
#include <algorithm>

using cxx_containers::Matrix;


/**
 *
 * @tparam T
 * @param matrix
 * @return spanning tree adjacency matrix
 */
template <typename T>
Matrix<T> create_spanning_tree(const Matrix<T>& matrix) {
    assert(matrix.rows() == matrix.cols());
    std::vector<T> included(matrix.rows(), 0);
    included[0] = 1;

    Matrix<T> SpanTree(matrix.size());

    for (size_t i = 0; i < SpanTree.cols(); ++i)
        for (size_t j = 0; j < SpanTree.cols(); ++j) {
            if (matrix[i][j] == 1 && included[i] == 1 && included[j] == 0) {
                SpanTree[i][j] = 1;
                SpanTree[j][i] = 1;
                included[j] = 1;
            }

            if (matrix[i][j] == 1 && included[i] == 0 && included[j] == 1) {
                SpanTree[i][j] = 1;
                SpanTree[j][i] = 1;
                included[i] = 1;
            }
        }

    return SpanTree;
}

/**
 * removing all useless branches from cycle
 * @tparam T
 * @param Loop
 * @return
 */
template <typename T>
Matrix<T> prune(Matrix<T> Loop) {
    assert(Loop.rows() == Loop.cols());

    int pruned = 0;

    do {
        pruned = 0;
        for (size_t i = 0; i < Loop.cols(); ++i) {
            auto end = Loop[i] + Loop.cols();

            auto first_edge = std::find(Loop[i], end, 1);
            auto second_edge = std::find(first_edge + 1, end, 1);

            if (second_edge == end) {
                if (first_edge != end) {
                    Loop[i][std::distance(Loop[i], first_edge)] = 0;
                    Loop[std::distance(Loop[i], first_edge)][i] = 0;
                    pruned++;
                }
            }
        }
    } while (pruned != 0);

    return Loop;
}

/**
 *
 * @tparam T
 * @param adjacency
 * @param span_tree
 * @return
 */
template <typename T>
std::vector<Matrix<T>>
create_independ_cycles_set(const Matrix<T>& adjacency) {
    assert(adjacency.cols() == adjacency.rows());
    auto span_tree = create_spanning_tree(adjacency);

    std::vector<Matrix<T>> indep_cycles_set;
    auto discarded_edges = adjacency - span_tree;

    for (size_t i = 0 ; i < adjacency.rows() - 1; ++i)
        for (size_t j = i+1; j < adjacency.rows(); ++j)
            if (discarded_edges[i][j] == 1) {
                auto Loop = span_tree;
                Loop[i][j] = Loop[j][i] = 1;
                indep_cycles_set.push_back(prune(std::move(Loop)));
            }

    return indep_cycles_set;
}

/**
 * set fundamental cycle orientation
 * @tparam T
 * @param matrix must be adjacency matrix of fundamental cycle
 */
template <typename T>
void set_cycle_orientation(Matrix<T>& matrix) {
    assert(matrix.cols() == matrix.rows());

    // edge between [first, second] vertex in matrix
    std::pair<size_t, size_t> start_edge;
    std::pair<size_t, size_t> current_edge;

    // find cycle start
    for (start_edge.first = 0; start_edge.first < matrix.rows(); ++start_edge.first) {
        auto first = matrix[start_edge.first];
        auto last = first + matrix.cols();
        auto first_edge = std::find(first, last, 1);

        if (first_edge != last) {
            start_edge.second = std::distance(first, first_edge);
            auto second_edge = std::find(first_edge+1, last, 1);
            assert(second_edge != last);
            *second_edge = 0;
            break;
        }
    }

    current_edge = start_edge;

    do {
        matrix[current_edge.second][current_edge.first] = 0;
        auto first = matrix[current_edge.second];
        auto last = first + matrix.cols();
        auto edge = std::find(first, last, 1);
        assert(edge != last);

        current_edge.first = current_edge.second;
        current_edge.second = std::distance(first, edge);

    } while(current_edge != start_edge);
}