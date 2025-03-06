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

/**
 * @brief Construct a new Arguments:: Arguments object
 *
 */
Arguments::Arguments(void){
	g = false;
	gSize = 0;
	gPy = false;
	f = false;
	fId = 0;
	greedy = false;
	uniform = false;
	astar = false;
	hm = false;
	he = false;
	hg = false;
	anim = false;
	// animDuration = -1;
	timeOut = -1;
	fileName = "";
}


/**
 * @brief:	Set the search algorithms and heuristics based on the provided arguments.
 * @notes:	If no search algorithm is provided, the default is A*.
 * @notes:	If no heuristic is provided, the default is Manhattan.
 */
void Arguments::setSearchesAndHeuristiques(void) {

	if (astar)
		searches.push_back(SEARCH_ASTAR);
	if (greedy)
		searches.push_back(SEARCH_GREEDY);
	if (uniform)
		searches.push_back(SEARCH_UNIFORM_COST);
	if(searches.empty())
		searches.push_back(SEARCH_ASTAR);

	if (hm)
		heuristiques.push_back(HEUR_MANHATTAN);
	if (he)
		heuristiques.push_back(HEUR_EUCLIDE);
	if (hg)
		heuristiques.push_back(HEUR_GOOD_PLACE);
	if(heuristiques.empty())
		heuristiques.push_back(HEUR_MANHATTAN);


}

/**
 * @brief:	Print the arguments
 */
void Arguments::printArgs() {

	if (f){
		std::cout << C_CYA <<" *      " << C_NOR << "-f (Open a file with the assistant)";
		if (fId > 0)
			std::cout << " File Id: " << fId;
		std::cout << std::endl;
	}
	if (g){
		std::cout << C_CYA <<" *      " << C_NOR << "-g (Genererate puzzle)";
		if (gSize > 0)
			std::cout << " Size: " << gSize;
		std::cout << std::endl;
	}
	if (gPy)
		std::cout << C_CYA <<" *      " << C_NOR << "-gpy (Python generator from the subject)\n";
	if (greedy)
		std::cout << C_CYA <<" *      " << C_NOR << "-greedy (Greedy Search)\n";
	if (uniform)
		std::cout << C_CYA <<" *      " << C_NOR << "-uniform (Uniform Cost Search)\n";
	if (astar)
		std::cout << C_CYA <<" *      " << C_NOR << "-astar (A* Search)\n";
	if (hm)
		std::cout << C_CYA <<" *      " << C_NOR << "-hm (Heuristic: Manhattan)\n";
	if (he)
		std::cout << C_CYA <<" *      " << C_NOR << "-he (Heuristic: Euclidean)\n";
	if (hg)
		std::cout << C_CYA <<" *      " << C_NOR << "-hg (Heuristic: Good place)\n";
	if (anim)
		std::cout << C_CYA <<" *      " << C_NOR << "-anim (Play animation)\n";
	if (timeOut > -1)
		std::cout << C_CYA <<" *      " << C_NOR << "-to (TimeOut): " << timeOut << " seconds\n";
}

/**
 * @brief:	Manage the conflicts between the arguments
 */
void Arguments::manageConflicts(void) {

	std::string ignoredArgs = "";

	if (gPy || g){
		if (f){
			ignoredArgs += " -f";
			f = false;
			if (fId > 0){
				ignoredArgs += " " + std::to_string(fId);
				fId = 0;
			}
		}
	}
	if (gPy && g){
		ignoredArgs += " -g";
		g = false;
		if (gSize > 0){
			ignoredArgs += " " + std::to_string(gSize);
			gSize = false;
		}
	}

	printArgs();

	if (!ignoredArgs.empty())
		std::cout << C_CYA << " *      Ignored arguments: " << C_RED << ignoredArgs << std::endl;

	if (!g && !gPy && !f){
		if(params.empty()){
			std::cerr << C_RED << " *      No arguments to generate or open a puzzle file." << std::endl;
			exit(1);
		}
		fileName = params[0];
		std::cerr << C_CYA << " *      FileName: " << C_NOR << fileName << std::endl;
	}
	if (timeOut < 0){
		std::cout << C_CYA <<" *      " << C_NOR << "Default timeout: 20s\n";
		timeOut = 20;
	}
}


/**
 * @brief:	Parses the command line arguments and sets the corresponding member variables.
 */
void Arguments::parse(int argc, char* argv[]) {

	if (argc == 1)
		return;

	std::cout << C_CYA << " *   READING ARGUMENTS:\n" << C_NOR;

	for (int i = 1; i < argc; ++i) {
		std::string arg = argv[i];

		if (arg == "-f") {
			f = true;
			if (i + 1 < argc) {
				std::string fileIdStr = argv[i + 1];
				if (stringIsPositiveDigit(fileIdStr)) {
					fId = std::stoi(fileIdStr);
					i++;
				}
			}
		}
		else if (arg == "-g") {
			g = true;
			if (i + 1 < argc) {
				std::string sizeStr = argv[i + 1];
				if (stringIsPositiveDigit(sizeStr)) {
					gSize = std::stoi(sizeStr);
					i++;
				}
			}
		}
		else if (arg == "-to") {
			timeOut = 0;
			if (i + 1 < argc) {
				std::string sizeStr = argv[i + 1];
				if (stringIsPositiveDigit(sizeStr)) {
					timeOut = std::stoi(sizeStr);
					i++;
				}
			}
		}
		else if (arg == "-gpy")
			gPy = true;
		else if (arg == "-greedy")
			greedy = true;
		else if (arg == "-uniform")
			uniform = true;
		 else if (arg == "-astar")
			astar = true;
		else if (arg == "-hm")
			hm = true;
		else if (arg == "-he")
			he = true;
		else if (arg == "-hg")
			hg = true;
		else if (arg == "-anim")
			anim = true;
		else {
			params.push_back(arg);
		}
	}


	manageConflicts();

	setSearchesAndHeuristiques();

	std::cout << C_CYA;
	std::cout << " ***************************************************************************************\n";
	std::cout << C_NOR;

}

// * GETTEUR
bool	Arguments::getG() const {	return g;	    }
bool	Arguments::getGPy() const {	return gPy;	    }
bool	Arguments::getF() const {	return f;	    }
int		Arguments::getGSize() const {	return gSize;	    }
int		Arguments::getFId() const {	return fId;	    }
std::string Arguments::getFileName() const {	return fileName;	    }
bool	Arguments::getGreedy() const {	return greedy;	    }
bool	Arguments::getUniform() const {	return uniform;	    }
bool	Arguments::getAstar() const {	return astar;	    }
bool	Arguments::getHM() const {	return hm;	    }
bool	Arguments::getHE() const {	return he;	    }
bool	Arguments::getHG() const {	return hg;	    }
int		Arguments::getTimeOut() const {	return timeOut;	    }

const	std::vector<std::string>& Arguments::getParams() const {	return params;	    }
const	std::vector<enum SearchType>& Arguments::getSearches() const {	return searches;	    }
const	std::vector<enum Heuristique>& Arguments::getHeuristiques() const {	return heuristiques;	    }

bool	Arguments::getAnim() const {	return anim;	    }
