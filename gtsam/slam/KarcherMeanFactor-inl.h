/* ----------------------------------------------------------------------------

 * GTSAM Copyright 2010, Georgia Tech Research Corporation,
 * Atlanta, Georgia 30332-0415
 * All Rights Reserved
 * Authors: Frank Dellaert, et al. (see THANKS for the full author list)

 * See LICENSE for the license information

 * -------------------------------------------------------------------------- */

/*
 * @file KarcherMeanFactor.cpp
 * @author Frank Dellaert
 * @date March 2019
 */

#pragma once

#include <gtsam/nonlinear/GaussNewtonOptimizer.h>
#include <gtsam/nonlinear/NonlinearFactorGraph.h>
#include <gtsam/slam/KarcherMeanFactor.h>
#include <gtsam/slam/PriorFactor.h>

using namespace std;

namespace gtsam {

template <class T, class ALLOC>
T FindKarcherMeanImpl(const vector<T, ALLOC>& rotations) {
  // Cost function C(R) = \sum PriorFactor(R_i)::error(R)
  // No closed form solution.
  NonlinearFactorGraph graph;
  static const Key kKey(0);
  for (const auto& R : rotations) {
    graph.emplace_shared<PriorFactor<T> >(kKey, R);
  }
  Values initial;
  initial.insert<T>(kKey, T());
  auto result = GaussNewtonOptimizer(graph, initial).optimize();
  return result.at<T>(kKey);
}

template <class T,
        typename = typename std::enable_if< std::is_same<gtsam::Rot3, T>::value >::type >
T FindKarcherMean(const std::vector<T>& rotations) {
  return FindKarcherMeanImpl(rotations);
}

template <class T>
T FindKarcherMean(const std::vector<T, Eigen::aligned_allocator<T>>& rotations) {
  return FindKarcherMeanImpl(rotations);
}

template <class T>
T FindKarcherMean(std::initializer_list<T>&& rotations) {
  return FindKarcherMeanImpl(std::vector<T, Eigen::aligned_allocator<T> >(rotations));
}

template <class T>
template <typename CONTAINER>
KarcherMeanFactor<T>::KarcherMeanFactor(const CONTAINER& keys, int d)
    : NonlinearFactor(keys) {
  if (d <= 0) {
    throw std::invalid_argument(
        "KarcherMeanFactor needs dimension for dynamic types.");
  }
  // Create the constant Jacobian made of D*D identity matrices,
  // where D is the dimensionality of the manifold.
  const auto I = Eigen::MatrixXd::Identity(d, d);
  std::map<Key, Matrix> terms;
  for (Key j : keys) {
    terms[j] = I;
  }
  jacobian_ =
      boost::make_shared<JacobianFactor>(terms, Eigen::VectorXd::Zero(d));
}
}  // namespace gtsam