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

	/**
	 * @brief: Heuristic: Calculer la somme des distances de Manhattan entre les pièces et leur position cible
	 * @return int
	 */
	int calcHeuristiqueMahattanDistance(std::vector<std::vector<int>> puzzle, std::vector<std::vector<int>> puzzleGoal) {
		int size = puzzle.size();
		int total = 0;
		for (int i = 0; i < size; ++i) {
			for (int j = 0; j < size; ++j) {
				if (puzzle[i][j] != 0) {
					std::pair<int, int> position = findValuePosition(puzzleGoal, puzzle[i][j]);
					total += abs(i - position.first) + abs(j - position.second);
				}
			}
		}
		return total;
	}


	/**
	 * @brief: Heuristic: Calculer la somme des distances de Euclidienne entre les pièces et leur position cible
	 * @return int
	 */
	int calcHeuristiqueEuclideanDistance(std::vector<std::vector<int>> puzzle, std::vector<std::vector<int>> puzzleGoal) {
		int size = puzzle.size();
		int total = 0;
		for (int i = 0; i < size; ++i) {
			for (int j = 0; j < size; ++j) {
				if (puzzle[i][j] != 0) {
					std::pair<int, int> position = findValuePosition(puzzleGoal, puzzle[i][j]);
					total += std::pow(i - position.first, 2) + std::pow(j - position.second, 2);
				}
			}
		}
		return total;
	}


	/**
	 * @brief: Heuristic: Calculer le nombre de pièces mal placées
	 * @return int
	 */
	int calcHeuristiqueGoodPlace(std::vector<std::vector<int>> puzzle, std::vector<std::vector<int>> puzzleGoal) {
		int size = puzzle.size();
		int total = 0;
		for (int i = 0; i < size; ++i) {
			for (int j = 0; j < size; ++j) {
				if (puzzle[i][j] != 0) {
					if (puzzle[i][j] != puzzleGoal[i][j]) {
						total++;
					}
				}
			}
		}
		return total;
	}


	int calcHeuristique(std::vector<std::vector<int>> puzzle, std::vector<std::vector<int>> puzzleGoal, Heuristique heuristique) {
		int value = 0;
		switch (heuristique) {
			case HEUR_MANHATTAN:
				value = calcHeuristiqueMahattanDistance(puzzle, puzzleGoal);
				break;
			case HEUR_GOOD_PLACE:
			value = calcHeuristiqueGoodPlace(puzzle, puzzleGoal);
				break;
			case HEUR_EUCLIDE:
			value = calcHeuristiqueEuclideanDistance(puzzle, puzzleGoal);
				break;
			default: value = 0;
		}
		return value * value;
	}


	std::string  puzzle_to_string(const std::vector<std::vector<int>> &puzzle) {
		std::string s = "";
		for (const auto &row : puzzle) {
			for (int val : row) {
				s += std::to_string(val) + ",";
			}
		}
		return s;
	};


	std::string searchTypeToString(SearchType search_type) {
		switch (search_type) {
			case SEARCH_ASTAR: 			return "A* Search     f(n) = g(n) + h(n)";
			case SEARCH_UNIFORM_COST: 	return "Uniform-Cost Search:   f(n) = g(n)";
			case SEARCH_GREEDY: 		return "Greedy Search:   f(n) = h(n)";
			default: return "Unknown Search Type";
		}
	}

	std::string heuristiqueToString(Heuristique heuristique) {
		switch (heuristique) {
			case HEUR_MANHATTAN: 	return "Manhattan Distance";
			case HEUR_GOOD_PLACE: 	return "The Good Place";
			case HEUR_EUCLIDE: 		return "Euclidean Distance";
			default: return "Unknown Heuristic";
		}
	}

}



std::string solve(std::vector<std::vector<int>> puzzle, std::vector<std::vector<int>> puzzleGoal, SearchType search_type, Heuristique heuristique, int timeOut) {


	std::cout << C_CYA;
	std::cout << " *   PUZZLE SOLVING\n";
	std::cout << " *            Search type: " << C_NOR << searchTypeToString(search_type) << C_CYA << std::endl;
	std::cout << " *              Heuristic: " << C_NOR << heuristiqueToString(heuristique) << C_CYA << std::endl;
	std::cout << C_NOR;


	// * Point de départ du chronomètre
	auto start = std::chrono::high_resolution_clock::now();

	std::priority_queue<State> open_set;
	std::unordered_map<std::string, int> visited;
	int size = puzzle.size();
	std::pair<int, int> empty_pos = findValuePosition(puzzle, 0);

	// * État initial
	State initial{puzzle, 0, calcHeuristique(puzzle, puzzleGoal, heuristique), empty_pos, ""};
	open_set.push(initial);

	int complexityInTime = 0; // * Total number of states ever selected in the "opened" set;
	long unsigned int complexityInSize = 0; // * Maximum number of states ever represented in memory at the same time during the search;

	int oldTick = 0;

	while (!open_set.empty()) {

		if (visited.size()+ open_set.size() > complexityInSize)
			complexityInSize = visited.size() + open_set.size();

		State current = open_set.top();
		open_set.pop();
		complexityInTime ++;

		if (complexityInTime % 100 == 0){
			auto end = std::chrono::high_resolution_clock::now();
			auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
			int sec = duration.count() / 1000;
			if (sec >= oldTick + 5){
				oldTick = sec;
				std::cout  << C_CYA << " *       " << C_NOR << sec << " sec     " << "Complexity in time: " << complexityInTime << std::endl;
			}
			if (timeOut != 0 && sec >= timeOut){
				std::cout << C_CYA << " *       " << C_RED << "TIMEOUT (" << timeOut << " s)" << std::endl;
				std::cout << C_CYA << " *       " << C_RED << "Try with:  -to 0" << std::endl;
				std::cout << C_CYA << " ***************************************************************************************\n" << C_NOR;
				return "";
			}

		}

		// * Vérifier si l'état est la solution
		if (current.puzzle == puzzleGoal) {

			std::cout << "\n";
			std::cout << C_CYA;
			std::cout << " *   " << C_GRE << "PUZZLE SOLVED " << C_CYA << "\n";

			auto end = std::chrono::high_resolution_clock::now();
			auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
			std::cout << " *             Duration: " << C_NOR << duration.count() << " ms" << C_CYA << std::endl;
			std::cout << " *   Complexity in time: " << C_NOR << complexityInTime << C_CYA << " (total number of states selected in the open set)"<< std::endl;
			std::cout << " *  Complexity in space: " << C_NOR << complexityInSize << C_CYA << " (maximum number of states at the same time)"<< std::endl;
			std::cout << " *      Number of moves: " << C_NOR << current.path.size() << C_CYA << std::endl;
			std::cout << " *                Moves: \"" << C_NOR << current.path <<  C_CYA << "\"" << std::endl;
			std::cout << " *\n";
			std::cout << " ***************************************************************************************\n" << C_NOR;
			return current.path;
		}

		// * Générer une clé unique pour l'état courant
		std::string board_str = puzzle_to_string(current.puzzle);


		if (visited.find(board_str) != visited.end() && visited[board_str] <= current.g) {
			continue;
		}
		visited[board_str] = current.g;


		// * Générer les voisins
		std::vector<std::pair<int, int>> moves = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
		for (auto [dx, dy] : moves) {
			int nx = current.empty_pos.first + dx;
			int ny = current.empty_pos.second + dy;

			if (nx >= 0 && nx < size && ny >= 0 && ny < size) {
				State neighbor = current;
				std::swap(neighbor.puzzle[current.empty_pos.first][current.empty_pos.second], neighbor.puzzle[nx][ny]);
				neighbor.empty_pos = {nx, ny};

				if (search_type == SEARCH_GREEDY) {
					neighbor.g = 0;
				} else {
					neighbor.g = current.g + 1;
				}

				// * Modifier h(x) selon le type de recherche
				if (search_type == SEARCH_UNIFORM_COST) {
					neighbor.h = 0; // * h(x) = 0 pour Uniform-Cost
				} else {
					neighbor.h = calcHeuristique(neighbor.puzzle, puzzleGoal, heuristique);
				}

				// * Ajouter la direction du mouvement au chemin
				if (dx == -1 && dy == 0) neighbor.path += "U";
				if (dx == 1 && dy == 0) neighbor.path += "D";
				if (dx == 0 && dy == -1) neighbor.path += "L";
				if (dx == 0 && dy == 1) neighbor.path += "R";
				open_set.push(neighbor);
			}
		}
	}
	std::cout << C_CYA << " *   "<< C_RED << "No solution found\n";
	std::cout << C_CYA << " ***************************************************************************************\n" << C_NOR;
	return "";
}
