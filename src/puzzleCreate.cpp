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


	std::vector<std::vector<int>> createDynamicPuzzle(int size) {
		std::vector<std::vector<int>> vec(size, std::vector<int>(size));
		// * Remplir le tableau avec la valeur -1
		for (int i = 0; i < size; ++i) {
			for (int j = 0; j < size; ++j) {
				vec[i][j] = -1;
			}
		}
		return vec;
	}

	std::vector<std::vector<int>> createPuzzleFromFilename(std::string fileName ) {
		const std::string prefix = "./maps/";
		if (fileName.find(prefix) == 0) { // * `find` retourne 0 si le préfixe est au début
			fileName.erase(0, prefix.length()); // * Supprime les premiers caractères correspondant à `prefix`
		}

		std::cout << C_CYA;
		std::cout << " *   OPENING FILE  " << C_NOR << "\"./maps/"  << fileName << "\"\n";
		std::cout << C_NOR;
		std::ifstream file("./maps/" + fileName);
			std::string word;

		if (!file.is_open()) {
			std::cerr << C_RED << "Error: Unable to open the file." << C_NOR << std::endl;
			exit(1);
		}

		int size =	-1;
		std::string line;
		while (std::getline(file, line)) {
			if (file.fail()) {
				std::cerr << C_RED << "Error reading." << C_NOR << std::endl;
				break;
			}

			if (!line.empty()) {
				auto result = splitAtFirstHash(line);
				std::string trimedFirst = trim(result.first);

				if (!trimedFirst.empty()){
					if (!stringIsPositiveDigit(trimedFirst)) {
						std::cerr << C_RED << "\n      Problem with the map: the first non-commented line should be a number >= 2 (the size of the map).\n" << C_NOR;
						std::cerr << C_RED << "      Found : \"" << trimedFirst  << C_NOR << "\"\n\n";
						exit(1);
					}
					try {
						if (!result.second.empty()){
							std::cout << C_CYA << " *      Comment " << C_NOR << "#" << result.second  << std::endl;
						}
						int number = std::stoi(trimedFirst); // Conversion de string en int
						size = number;
						break;
					} catch (const std::invalid_argument& e) {
						std::cerr << C_RED << "      Error: The string is not a valid number." << C_NOR << std::endl;
						std::cerr << C_RED << "\n      Problem with the map: the first non-commented line should be a number >= 2 (the size of the map).\n" << C_NOR ;
						std::cerr << C_RED << "Found : \"" << trimedFirst  << C_NOR << "\"\n\n";
						exit(1);
					} catch (const std::out_of_range& e) {
						std::cerr << C_RED << "Error: The number is out of the range of int." << C_NOR << std::endl;
						std::cerr << C_RED << "\nProblem with the map: the first non-commented line should be a number >= 2 (the size of the map).\n" << C_NOR;
						std::cerr << C_RED << "Found : \"" << trimedFirst  << C_NOR << "\"\n\n";
						exit(1);
					}
					break;
				}
				if (!result.second.empty()){
					std::cout << C_CYA << " *      Comment " << C_NOR << "#" << result.second << C_NOR;
				}
				std::cout  << std::endl;
			}
		}

		if (size < 3)
			exit(1);



		std::vector<std::vector<int>> puzzle = createDynamicPuzzle(size);


		int i = 0;
		int j = 0;
		while (std::getline(file, line)) {
			if (file.fail()) {
				std::cerr << C_RED << "Error reading." << C_NOR << std::endl;
				break;
			}


			if (!line.empty()) {

				auto result = splitAtFirstHash(line);

				std::string trimedFirst = trim(result.first);

				if (!trimedFirst.empty()){
					std::vector<std::string> words = splitWords(trimedFirst);
					j = 0;
					for (const auto& word : words) {
						puzzle[i][j++] = std::stoi(word);
					}
					i++;
				}
				if (!result.second.empty()){
					std::cout << C_CYA << " *          Comment " << C_NOR << "#" << result.second << C_NOR << std::endl;
				}
			}

		}

		file.close();

		std::cout << C_CYA << " ***************************************************************************************\n" << C_NOR;

		return puzzle;
	}

	std::vector<std::vector<int>> getPuzzleFromFilesSelector(int gFileId) {

		// * Récupération des fichiers du dossier ./maps
		std::string folderPath = "./maps";
		std::vector<std::string> fileList;

		for (const auto& entry : fs::directory_iterator(folderPath)) {
			if (entry.is_regular_file()) {
				fileList.push_back(entry.path().filename().string());
			}
		}

		if (fileList.empty()) {
			std::cout << C_RED << "No file found in the folder ./maps." << C_NOR << "\n";
			exit(1);
		}

		int fileCount = fileList.size();

		std::cout << "\n      " << C_CYA << fileCount << " file(s) found in the ./maps folder:" << C_NOR << "\n";



		for (int i = 0; i < fileCount ; ++i) {
			std::cout << "      | " << C_CYA << std::setw(3) << i + 1 << C_NOR <<" : "  << fileList[i] << std::endl;

		}

		std::cout << std::endl;



		std::string mystr;
		int fileId = gFileId;
		while (fileId < 1 || fileId > fileCount) {
			std::cout << C_YEL << "      Enter the ID of the file to open (1-" << fileCount << ")   ?> " << C_NOR;
			getline(std::cin, mystr);
			std::stringstream(mystr) >> fileId;

			if (fileId < 1 || fileId > fileCount) {
				std::cout << C_RED << "      Invalid value: The file ID must be between 1 and " << fileCount << C_NOR << "\n";
			}
		}


		return createPuzzleFromFilename(fileList[fileId - 1]);

	}


	void randomizePuzzle(std::vector<std::vector<int>>& puzzle, int iterations) {
		int size = puzzle.size();

		std::random_device rd; // * Génère une graine unique
		std::mt19937 gen(rd()); // * Générateur basé sur Mersenne Twister
		std::uniform_int_distribution<> distrib(1, 4); // * Distribution uniforme entre 1 et 4

		std::pair<int, int> empty_pos;

		for (int i = 0; i < size; ++i) {
			for (int j = 0; j < size; ++j) {
				if (puzzle[i][j] == 0) {
					empty_pos = {i, j};
				}
			}
		}

		int previous_number = 0;
		while (iterations > 0) {
			int random_number = distrib(gen);


			if (random_number == 1 && previous_number != 2) {
				if (empty_pos.first > 0) {
					std::swap(puzzle[empty_pos.first][empty_pos.second], puzzle[empty_pos.first - 1][empty_pos.second]);
					empty_pos.first--;
					iterations--;
				}
			} else if (random_number == 2 && previous_number != 1) {
				if (empty_pos.first < size - 1) {
					std::swap(puzzle[empty_pos.first][empty_pos.second], puzzle[empty_pos.first + 1][empty_pos.second]);
					empty_pos.first++;
					iterations--;
				}
			} else if (random_number == 3 && previous_number != 4) {
				if (empty_pos.second > 0) {
					std::swap(puzzle[empty_pos.first][empty_pos.second], puzzle[empty_pos.first][empty_pos.second - 1]);
					empty_pos.second--;
					iterations--;
				}
			} else if (random_number == 4 && previous_number != 3) {
				if (empty_pos.second < size - 1) {
					std::swap(puzzle[empty_pos.first][empty_pos.second], puzzle[empty_pos.first][empty_pos.second + 1]);
					empty_pos.second++;
					iterations--;
				}
			}
		}


	}


	std::vector<std::vector<int>> generatePuzzle(int gSize) {


		std::cout << C_CYA <<" *   GENERATE A PUZZLE";
		if (gSize > 2)
			std::cout <<  " OF SIZE " << gSize << C_NOR;
		std::cout << "\n" << C_NOR;
		std::string mystr;
		int puzzleSize=0;

		if (gSize > 0) {
			puzzleSize = gSize;
		} else
		{
			do {
				std::cout << C_YEL << "        Width of the map    ?> " << C_NOR;
				getline(std::cin, mystr);
				std::stringstream(mystr) >> puzzleSize;

				if (puzzleSize < 2) {
					std::cerr << C_RED <<"           Invalid value: The width must be greater than or equal to 2.\n" << C_NOR;
				}
			} while (puzzleSize < 2);
		}


		std::vector<std::vector<int>> puzzle = createDynamicPuzzle(puzzleSize);


		fillPuzzleSolved(puzzle);

		randomizePuzzle(puzzle, puzzleSize * puzzleSize * puzzleSize);


		std::cout << C_CYA <<" ***************************************************************************************\n" << C_NOR;
		return puzzle;
	}


	std::vector<std::vector<int>> generatePuzzlePython(Arguments args) {



		std::cout << C_CYA;
		std::cout << " *   GENERATE A PUZZLE WITH  " << S_UNDER << GENERATOR_PY_FILENAME << C_NOR << C_CYA << "  FROM THE SUBJECT\n";
		std::cout << C_NOR;

		if (!std::filesystem::exists(GENERATOR_PY_FILENAME)) {
			std::cout  << C_RED << " *      File \"" << GENERATOR_PY_FILENAME << "\" is missing!\n";
			std::cout  << C_RED << " *      Copy the file from the subject into the root folder \n";
			std::cout  << C_RED << " *      Remove the duplicate code starting from line 97  \n" << C_NOR;
			exit(1);
		}


		std::string g42ParamsStr = "";

		for (size_t i = 0; i <  args.getParams().size(); ++i) {
			if (i > 0) {
				g42ParamsStr += " ";
			}
			g42ParamsStr += args.getParams()[i];
		}

		std::string filename = "gen_py_" + g42ParamsStr + ".txt";
		std::replace(filename.begin(), filename.end(), ' ', '_');

		std::string fullCmd = "py npuzzle-gen.py "  + g42ParamsStr + "  > ./maps/" + filename;


		std::cout << C_CYA << " *      " << C_NOR << fullCmd << std::endl;
		std::cout << C_RED;
		int result = system(fullCmd.c_str());
		std::cout << C_NOR;

		if (result != 0) {
			std::cerr << C_RED << "Error while generating the puzzle with npuzzle-gen.py." << C_NOR << std::endl;
			exit(1);
		}

		std::cout << C_CYA <<" ***************************************************************************************\n" << C_NOR;
		return createPuzzleFromFilename(filename);


	}

}


std::pair<int, int> findValuePosition(const std::vector<std::vector<int>>& puzzle, int target) {
	for (size_t i = 0; i < puzzle.size(); ++i) {
		for (size_t j = 0; j < puzzle[i].size(); ++j) {
			if (puzzle[i][j] == target) {
				return {static_cast<int>(i), static_cast<int>(j)}; // * Retourne la position
			}
		}
	}
	return {-1, -1}; // * Valeur non trouvée
}

/**
 * @brief: Remplir le puzzle avec les bonnes valeurs.
 */
void fillPuzzleSolved(std::vector<std::vector<int>>& puzzle) {
		int size = puzzle.size();
		int val = 1;
		int i = 0;
		int j = 0;
		char dir = 'R';

		// * Remplir le tableau avec la valeur -1
		for (int ii = 0; ii < size; ++ii) {
			for (int jj = 0; jj < size; ++jj) {
				puzzle[ii][jj] = -1;
			}
		}

		while (val < size * size) {
			if (i < size && j < size )
				puzzle[i][j] = val;

			if (dir == 'R'){
				if (j == size - 1 || puzzle[i][j+1] != -1 ) {
					i++;
					j--;
					dir = 'D';
				}
				j++;
			}
			else if (dir == 'D'){
				if (i == size - 1 || puzzle[i+1][j] != -1 ) {
					j--;
					i--;
					dir = 'L';
				}
				i++;
			}
			else if (dir == 'L'  ){
				if (j == 0  || puzzle[i][j-1] != -1  ) {
					j++;
					i--;
					dir = 'U';
				}
				j--;
			}
			else if (dir == 'U'){
				if (i == 0  || puzzle[i-1][j] != -1  ) {
					j++;
					i++;
					dir = 'R';
				}
				i--;
			}


			val++;
		}
		puzzle[i][j] = 0;
}


/**
 * @brief Get the Puzzle From input Arguments
 * @return std::vector<std::vector<int>>
 */
std::vector<std::vector<int>> getPuzzleFromArguments(Arguments args) {
	std::vector<std::vector<int>> puzzle;
	std::string mystr;

	if (args.getGPy() )
		return generatePuzzlePython(args);

	if (!args.getFileName().empty())
		return createPuzzleFromFilename(args.getFileName());

	if (args.getG() )
		return generatePuzzle(args.getGSize());

	if (args.getF() )
		return getPuzzleFromFilesSelector(args.getFId());

	std::cout << C_RED << "   NO ARGUMENT " << C_NOR << "\n";
	exit (1);

}

