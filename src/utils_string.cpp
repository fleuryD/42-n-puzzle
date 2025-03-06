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
 * @brief:	Verifier si une chaîne contient uniquement des chiffres
 * @return bool
 */
bool stringIsPositiveDigit(const std::string& str) {
	for (char c : str) {
		if (!std::isdigit(c)) {
			return false;
		}
	}
	return true;
}

/**
 * @brief:	Diviser une chaîne en deux parties à partir du premier "#"
 * @return:	std::pair<std::string, std::string>
 */
std::pair<std::string, std::string> splitAtFirstHash(const std::string& str) {
	size_t pos = str.find('#'); // * Trouver le premier "#"
	// * Si aucun "#", retourner toute la chaîne dans la première partie
	if (pos == std::string::npos) {
		return {str, ""};
	}
	// * Diviser en deux parties : avant et après le "#"
	std::string before = str.substr(0, pos);
	std::string after = str.substr(pos + 1);
	return {before, after};
}

/**
 * @brief:	Diviser une chaîne en mots séparés par des espaces ou des tabulations
 * @return:	std::vector<std::string>
 */
std::vector<std::string> splitWords(const std::string& str) {
	const std::string& delimiters =  "[ \\t]+";
	std::vector<std::string> tokens;
	std::regex re(delimiters); // * Regex pour les délimiteurs
	std::sregex_token_iterator it(str.begin(), str.end(), re, -1);
	std::sregex_token_iterator end;

	while (it != end) {
		if (!it->str().empty()) { // * Ignorer les sous-chaînes vides
			tokens.push_back(*it);
		}
		++it;
	}

	return tokens;
}

/**
 * @brief: Supprimer les white-spaces de début et de fin d'une chaîne
 * @return std::string
 */
std::string trim(const std::string& str) {
	// * Trouver le premier caractère non-whitespace
	auto start = std::find_if_not(str.begin(), str.end(), [](unsigned char c) { return std::isspace(c); });
	// * Trouver le dernier caractère non-whitespace
	auto end = std::find_if_not(str.rbegin(), str.rend(), [](unsigned char c) { return std::isspace(c); }).base();
	return (start < end) ? std::string(start, end) : std::string();
}

