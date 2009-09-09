/**
 * @file    smallExample.h
 * @brief   Create small example with two poses and one landmark
 * @brief   smallExample
 * @author  Carlos Nieto
 */

// \callgraph


#pragma once

#include <boost/shared_ptr.hpp>
#include "ConstrainedNonlinearFactorGraph.h"
#include "ConstrainedChordalBayesNet.h"
#include "ConstrainedLinearFactorGraph.h"
#include "NonlinearFactorGraph.h"
#include "FGConfig.h"

// \namespace

namespace gtsam {

	/**
	 * Create small example for non-linear factor graph
	 */
	boost::shared_ptr<const NonlinearFactorGraph> sharedNonlinearFactorGraph();
	NonlinearFactorGraph createNonlinearFactorGraph();

	/**
	 * Create small example constrained factor graph
	 */
	ConstrainedLinearFactorGraph createConstrainedLinearFactorGraph();

	/**
	 * Create small example constrained nonlinear factor graph
	 */
	ConstrainedNonlinearFactorGraph createConstrainedNonlinearFactorGraph();

	/**
	 * Create configuration to go with it
	 * The ground truth configuration for the example above
	 */
	FGConfig createConfig();

	/**
	 * Create configuration for constrained example
	 * This is the ground truth version
	 */
	FGConfig createConstrainedConfig();

	/**
	 * create a noisy configuration for a nonlinear factor graph
	 */
	boost::shared_ptr<const FGConfig> sharedNoisyConfig();
	FGConfig createNoisyConfig();

	/**
	 * Zero delta config
	 */
	FGConfig createZeroDelta();

	/**
	 * Delta config that, when added to noisyConfig, returns the ground truth
	 */
	FGConfig createCorrectDelta();

	/**
	 * create a linear factor graph
	 * The non-linear graph above evaluated at NoisyConfig
	 */
	LinearFactorGraph createLinearFactorGraph();

	/**
	 * create small Chordal Bayes Net x <- y
	 */
	ChordalBayesNet createSmallChordalBayesNet();

	/**
	 * create small Constrained Chordal Bayes Net (from other constrained example)
	 */
	ConstrainedChordalBayesNet createConstrainedChordalBayesNet();

	/**
	 * Create really non-linear factor graph (cos/sin)
	 */
	boost::shared_ptr<const NonlinearFactorGraph> sharedReallyNonlinearFactorGraph();
	NonlinearFactorGraph createReallyNonlinearFactorGraph();

	/**
	 * Create a noisy configuration for linearization
	 */
	FGConfig createConstrainedLinConfig();

	/**
	 * Create the correct delta configuration
	 */
	FGConfig createConstrainedCorrectDelta();
}
