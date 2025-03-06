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


int main(int argc, char **argv) {

	printAppHeader();


	Arguments args;
	args.parse(argc, argv);

	std::optional<std::vector<std::vector<int>>> optionalPuzzle;
	optionalPuzzle = getPuzzleFromArguments(args);

	if (optionalPuzzle){

		std::vector<std::vector<int>> puzzle;
		std::vector<std::vector<int>> puzzleGoal;

		puzzle = optionalPuzzle.value();
		puzzleGoal = puzzle;
		fillPuzzleSolved(puzzleGoal);


		printPuzzleAndGoal(puzzle, puzzleGoal);


		if (!isSolvable(puzzle, puzzleGoal)){
			std::cout << C_CYA << " *      " << C_RED << "This puzzle is unsolvable !" << C_NOR "\n";
			exit(0);
		}
		std::cout << C_CYA << " *      " << C_GRE << "This puzzle is solvable !" << C_NOR "\n";

		std::cout << C_CYA << " ***************************************************************************************\n" << C_NOR;

		std::string bestSolucePath = "";
		std::string solucePath;

		for (auto search : args.getSearches()) {
			for (auto heur : args.getHeuristiques()) {
				solucePath = solve(puzzle,  puzzleGoal, search, heur, args.getTimeOut());
				if (bestSolucePath == "" || (solucePath != "" && solucePath.size() < bestSolucePath.size())){
					bestSolucePath = solucePath;
				}
			}
		}

		if (args.getAnim() && bestSolucePath != ""){
			std::string str;
			std::cout << C_CYA << " *   PLAY ANIMATION \n"<< C_NOR;
			std::cout << C_YEL << " *      Enter the duration in seconds (e.g. \"10\"). Otherwise, press [enter] to quit:\n"<< C_NOR;
			getline (std::cin, str);
			if (str.length() > 0 && stringIsPositiveDigit(str)) {
				int animDuration = std::stoi(str);
				printAnimatedSteps(puzzle, puzzleGoal, bestSolucePath, animDuration);
			}
		}
	}


	return 0;
}
