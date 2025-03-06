// ***************************************************************************************
// *                                     _   _        _____               _              *
// *            :::      ::::::::       | \ | |      |  __ \             | |             *
// *          :+:      :+:    :+:       |  \| |______| |__) _   _ _______| | ___         *
// *        +:+ +:+         +:+         | . ` |______|  ___| | | |_  |_  | |/ _ \        *
// *      +#+  +:+       +#+            | |\  |      | |   | |_| |/ / / /| |  __/        *
// *    +#+#+#+#+#+   +#+               |_| \_|      |_|    \__,_/___/___|_|\___|        *
// *         #+#    #+#                                                                  *
// *        ###   ########.fr           By   dfleury  <dfleury@student.42.fr>            *
// *                                                                                     *
// ***************************************************************************************

#include "../include/npuzzle.hpp"


namespace {


	std::vector<int> flatten(const std::vector<std::vector<int>> &puzzle) {
		int N = puzzle.size();
		std::vector<int> flatPuzzle;
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < N; ++j) {
				flatPuzzle.push_back(puzzle[i][j]);
			}
		}
		return flatPuzzle;
	}


	int findValuePositionInFlatPuzzle(const std::vector<int>& flatPuzzle, int value) {
		for (size_t i = 0; i < flatPuzzle.size(); ++i) {
			if (flatPuzzle[i] == value) {
				return i;
			}
		}
		return -1; // * La valeur n'existe pas dans le tableau
	}

	int countInversions(const std::vector<int> &flatPuzzle, const std::vector<int> &flatPuzzleGoal) {
		int inversions = 0;
		for (size_t i = 0; i < flatPuzzle.size(); ++i) {
			int value = flatPuzzle[i];
			int flatPuzzleGoalId = findValuePositionInFlatPuzzle(flatPuzzleGoal, value);

			if (flatPuzzle[i] == 0) continue; // * Ignorer la case vide
			for (size_t j = i + 1; j < flatPuzzle.size(); ++j) {
				int otherflatPuzzleGoalId = findValuePositionInFlatPuzzle(flatPuzzleGoal, flatPuzzle[j]);
				if (flatPuzzle[j] != 0 && (flatPuzzleGoalId > otherflatPuzzleGoalId )) {
					++inversions;
				}
			}
		}
		return inversions;
	}

}

/**
 * @brief: Vérifier si un puzzle est solvable
 * @return bool
 */
bool isSolvable(const std::vector<std::vector<int>> &puzzle, const std::vector<std::vector<int>> &puzzleGoal) {

	// *** https://www.cs.princeton.edu/courses/archive/spring21/cos226/assignments/8puzzle/specification.php

	int N = puzzle.size();
	std::vector<int> flatPuzzle;
	std::vector<int> flatPuzzleGoal;

	flatPuzzle = flatten(puzzle);	// * Aplatir le tableau en 1D
	flatPuzzleGoal = flatten(puzzleGoal);
	int empty_row_from_top = 0;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			if (puzzle[i][j] == 0) {
				empty_row_from_top = i;
			}
		}
	}

	int inversions = countInversions(flatPuzzle,  flatten(puzzleGoal));
	if (N % 2 != 0) {
		// * Pour les puzzles impairs (ODD), le nombre d'inversions doit être pair
		return inversions % 2 == 0;
	} else {
		// * Pour les puzzles pairs (EVEN), le nombre d'inversions + la Row de la vase vide  doit être impaire
		bool solvable =  (inversions + empty_row_from_top)  % 2 != 0;
		// * On a des inversion une fois sur 2 donc :
		return N % 4 == 0 ? !solvable : solvable;
	}

}
