#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <fstream> // * pour lire un fichier
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <cmath>
#include <filesystem>
#include <cctype>
#include <regex>
#include <utility> // * pour std::pair dans splitAtFirstHash
#include <optional> // * Pour std::optional
#include <random>
#include <chrono> // * Pour std::chrono
#include <thread> // * pour this_thread::sleep_for;

#define C_NOR "\x1b[m"
#define C_GRA "\x1b[30m"
#define C_RED "\x1b[31m"
#define C_GRE "\x1b[32m"
#define C_YEL "\x1b[33m"
#define C_BLU "\x1b[34m"
#define C_MAG "\x1b[35m"
#define C_CYA "\x1b[36m"
#define C_WHI "\x1b[37m"
#define B_GRA "\x1b[40m"
#define B_RED "\x1b[41m"
#define B_GRE "\x1b[42m"
#define B_YEL "\x1b[43m"
#define B_BLU "\x1b[44m"
#define B_MAG "\x1b[45m"
#define B_CYA "\x1b[46m"
#define B_WHI "\x1b[47m"
#define S_BOLD "\x1b[1m"
#define S_UNDER "\x1b[4m"
#define S_REV "\x1b[7m"

#define GENERATOR_PY_FILENAME "npuzzle-gen.py"

namespace fs = std::filesystem;

enum SearchType { SEARCH_ASTAR, SEARCH_UNIFORM_COST, SEARCH_GREEDY };
enum Heuristique { HEUR_MANHATTAN, HEUR_GOOD_PLACE, HEUR_EUCLIDE };

#include "Arguments.hpp"

struct State {
	std::vector<std::vector<int>> puzzle;
	int g; // * Coût depuis l'état initial
	int h; // * Distance heuristique
	std::pair<int, int> empty_pos;
	std::string path; // * Chemin pour arriver à cet état

	// * Opérateur pour le tri dans la priority_queue
	bool operator<(const State &other) const {
		return (g + h) > (other.g + other.h);
	}
};


// * utils_string.cpp:
bool stringIsPositiveDigit(const std::string& str);
std::pair<std::string, std::string> splitAtFirstHash(const std::string& str);
std::vector<std::string> splitWords(const std::string& str);
std::string trim(const std::string& str);

// * utils_print.cpp:
void printAppHeader();
void printPuzzleAndGoal(std::vector<std::vector<int>> puzzle, std::vector<std::vector<int>> puzzleGoal);
void printAnimatedSteps( std::vector<std::vector<int>> puzzle,std::vector<std::vector<int>> puzzleGoal, std::string path, int animDuration);

// * puzzleCreate.cpp:
void fillPuzzleSolved(std::vector<std::vector<int>>& puzzle);
std::vector<std::vector<int>> getPuzzleFromArguments(Arguments args);
std::pair<int, int> findValuePosition(const std::vector<std::vector<int>>& puzzle, int target);

// * puzzleSolve.cpp:
std::string solve(std::vector<std::vector<int>> puzzle, std::vector<std::vector<int>> puzzleGoal, SearchType search_type, Heuristique heuristique, int timeout);
bool isSolvable(const std::vector<std::vector<int>> &puzzle, const std::vector<std::vector<int>> &puzzleGoal);

