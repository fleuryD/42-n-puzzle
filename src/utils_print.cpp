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

namespace{

	void printCharMultipleTimes(char c, int count) {
		for (int i = 0; i < count; ++i) {
			std::cout << c;
		}
	}

	void printPuzzle(std::vector<std::vector<int>> puzzle, std::vector<std::vector<int>> puzzleGoal, std::string title = "") {

		if (!title.empty()) {
			std::cout << " " << title << ":" << std::endl;
		}

		std::string gridColor = C_BLU;
		int size = puzzle.size();

		std::cout << gridColor << " +";
		printCharMultipleTimes('-', 5 * size + 1);
		std::cout << "+" << C_NOR << std::endl;

		for (int i = 0; i < size; ++i) {
			std::cout<< gridColor <<" |" << C_NOR;
			for (int j = 0; j < size; ++j) {
				if (puzzle[i][j] == 0)
					std::cout << B_CYA;
				else if (puzzle[i][j] == puzzleGoal[i][j])
					std::cout << C_GRE;
				std::cout << std::setw(4) << puzzle[i][j] << " ";
				std::cout << C_NOR;
			}
			std::cout << gridColor <<" |" << C_NOR << "\n";
		}


		std::cout << gridColor <<  " +";
		printCharMultipleTimes('-', 5 * size + 1);
		std::cout << "+" << C_NOR << std::endl;

	}

}

void printAppHeader() {
	std::cout << C_CYA;
	std::cout << "\n";
	std::cout << " ***************************************************************************************\n";
	std::cout << " *                                     _   _        _____               _              *\n";
	std::cout << " *            :::      ::::::::       | \\ | |      |  __ \\             | |             *\n";
	std::cout << " *          :+:      :+:    :+:       |  \\| |______| |__) _   _ _______| | ___         *\n";
	std::cout << " *        +:+ +:+         +:+         | . ` |______|  ___| | | |_  |_  | |/ _ \\        *\n";
	std::cout << " *      +#+  +:+       +#+            | |\\  |      | |   | |_| |/ / / /| |  __/        *\n";
	std::cout << " *    +#+#+#+#+#+   +#+               |_| \\_|      |_|    \\__,_/___/___|_|\\___|        *\n";
	std::cout << " *         #+#    #+#                                                                  *\n";
	std::cout << " *        ###   ########.fr           By   dfleury  <dfleury@student.42.fr>            *\n";
	std::cout << " *                                                                                     *\n";
	std::cout << " ***************************************************************************************\n";
	std::cout << " *   USAGE:                                                                            *\n";
	std::cout << " *      Open or generate a puzzle:                                                     *\n";
	std::cout << " *         " << C_NOR << "./maps/....            " << C_CYA << " > Open a file                                       *\n";
	std::cout << " *         " << C_NOR << "-f [id]                " << C_CYA << " > Open a file with the assistant                    *\n";
	std::cout << " *         " << C_NOR << "-g [size]              " << C_CYA << " > Generate a puzzle [of size size]                  *\n";
	std::cout << " *         " << C_NOR << "-gpy size [-s -u -i]   " << C_CYA << " > Generate a puzzle with " << S_UNDER << GENERATOR_PY_FILENAME << C_NOR << C_CYA << "             *\n";
	if (!std::filesystem::exists(GENERATOR_PY_FILENAME)) {
		std::cout << " *      " << C_RED << "                           The file \"" << GENERATOR_PY_FILENAME << "\" was not found!       "<< C_CYA <<"*\n";
		std::cout << " *      " << C_RED << "                           Copy the file from the subject to the root folder   "<< C_CYA <<"*\n";
		std::cout << " *      " << C_RED << "                           Remove duplicate code starting from line 97         "<< C_CYA <<"*\n";
	}
	std::cout << " *                                                                                     *\n";
	std::cout << " *      Add options:                                                                   *\n";
	std::cout << " *         " << C_NOR << "-greedy -uniform -astar" << C_CYA << " > Search type                                       *\n";
	std::cout << " *         " << C_NOR << "-hm -he -hg            " << C_CYA << " > Heuristic: Manhattan, Euclidean, Good place       *\n";
	std::cout << " *         " << C_NOR << "-to duration           " << C_CYA << " > Timeout in seconds (default: 20 / infinite: 0)    *\n";
	std::cout << " *         " << C_NOR << "-anim                  " << C_CYA << " > Play the animation                                *\n";
	std::cout << " ***************************************************************************************\n";

	std::cout << C_NOR;
}


// * Fonction pour effacer l'écran (compatible avec Linux)
void clearConsole() {
	std::cout << "\033[2J\033[1;1H"; // * Code ANSI pour effacer l'écran et repositionner le curseur
}


void printArrowUp(char dir) {
	if (dir == 'U'){
		std::cout << "    /\\    \n";
		std::cout << "   /  \\    \n";
		std::cout << "  /    \\   \n";
		std::cout << " /      \\   \n";
		std::cout << "\n";
	}
	else if (dir == 'D'){
		std::cout << "\n";
		std::cout << " \\      /   \n";
		std::cout << "  \\    /   \n";
		std::cout << "   \\  /    \n";
		std::cout << "    \\/    \n";
	}
	else if (dir == 'R'){
		std::cout << "     #    \n";
		std::cout << "      #   \n";
		std::cout << "       #  \n";
		std::cout << "      #   \n";
		std::cout << "     #    \n";
	}
	else if (dir == 'L'){
		std::cout << "    #  \n";
		std::cout << "   #   \n";
		std::cout << "  #    \n";
		std::cout << "   #   \n";
		std::cout << "    #  \n";
	}

}

void printAnimatedSteps( std::vector<std::vector<int>> puzzle,std::vector<std::vector<int>> puzzleGoal, std::string path, int animDuration){

	int speed = path.size() > 0 ? animDuration * 1000 / path.size() : 0;
	std::pair<int, int> empty_pos = findValuePosition(puzzle, 0);


	for (size_t i = 0; i < path.size(); ++i) {

		clearConsole();
		std::cout << C_NOR << " " << path.substr(0, i) << B_BLU << path[i] << C_NOR <<   path.substr(i+1) << "\n";
		std::string title =  "Step " + std::to_string(i+1) +  "/:" + std::to_string( path.size()) +  ":  '" + path[i]+"'";

		printArrowUp(path[i]);

		if (path[i] == 'U') {
			std::swap(puzzle[empty_pos.first][empty_pos.second], puzzle[empty_pos.first - 1][empty_pos.second]);
			empty_pos.first --;
		}
		else if (path[i] == 'D') {
			std::swap(puzzle[empty_pos.first][empty_pos.second], puzzle[empty_pos.first + 1][empty_pos.second]);
			empty_pos.first ++;
		}
		else if (path[i] == 'L') {
			std::swap(puzzle[empty_pos.first][empty_pos.second], puzzle[empty_pos.first][empty_pos.second - 1]);
			empty_pos.second --;
		}
		else if (path[i] == 'R') {
			std::swap(puzzle[empty_pos.first][empty_pos.second], puzzle[empty_pos.first][empty_pos.second + 1]);
			empty_pos.second ++;
		}
		printPuzzle(puzzle, puzzleGoal, "");


		std::this_thread::sleep_for(std::chrono::milliseconds(speed));
	}
}



void printPuzzleAndGoal(std::vector<std::vector<int>> puzzle, std::vector<std::vector<int>> puzzleGoal) {


	std::cout << C_CYA << " *   DISPLAYING THE PUZZLE:\n"<< C_NOR;
	std::cout << C_CYA << " *\n" << C_NOR;

	std::string gridColor = C_BLU;

	int size = puzzle.size();

	std::cout << C_CYA << " *   " << C_NOR;
	std::cout << " " << std::setw(5 * size + 3) << "Puzzle";
	std::cout << "    " << std::setw(5 * size + 3) << "Goal";
	std::cout << std::endl;

	std::cout << C_CYA << " *   " << C_NOR;
	std::cout << gridColor << " +";
	printCharMultipleTimes('-', 5 * size + 1);
	std::cout << "+" << C_NOR ;

	std::cout << gridColor << "    +";
	printCharMultipleTimes('-', 5 * size + 1);
	std::cout << "+" << C_NOR  << "\n";


	for (int i = 0; i < size; ++i) {

		// *** puzzle
		std::cout << C_CYA << " *   " << C_NOR;
		std::cout<< gridColor <<" |" << C_NOR;
		for (int j = 0; j < size; ++j) {
			if (puzzle[i][j] == 0)
				std::cout << C_CYA;
			else if (puzzle[i][j] == puzzleGoal[i][j])
				std::cout << C_GRE;
			std::cout << std::setw(4) << puzzle[i][j] << " ";
			std::cout << C_NOR;

		}

		std::cout << gridColor <<" |" << C_NOR << "   ";

		// *** puzzleGoal
		std::cout<< gridColor <<" |" << C_NOR;
		for (int j = 0; j < size; ++j) {
			if (puzzleGoal[i][j] == 0)
				std::cout << C_CYA;
			else if (puzzle[i][j] == puzzleGoal[i][j])
				std::cout << C_GRE;
			std::cout << std::setw(4) << puzzleGoal[i][j] << " ";
			std::cout << C_NOR;
		}
		std::cout << gridColor <<" |" << C_NOR << "\n";
	}



	std::cout << C_CYA << " *   " << C_NOR;
	std::cout << gridColor << " +";
	printCharMultipleTimes('-', 5 * size + 1);
	std::cout << "+" << C_NOR ;

	std::cout << gridColor << "    +";
	printCharMultipleTimes('-', 5 * size + 1);
	std::cout << "+" << C_NOR << std::endl;

	std::cout << C_CYA << " *\n" << C_NOR;

}

