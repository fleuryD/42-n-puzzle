#ifndef __ARGUMENTS_HPP__
# define __ARGUMENTS_HPP__

// # include "npuzzle.hpp"
# include <vector>
# include <string>

class Arguments {

	private:
		bool	g;		// * arg -g: use my puzzle generator
		int		gSize;	// * arg [size]: size of the puzzle to generate
		bool	gPy;	// * Utiliser le Generateur de puzzle du sujet: npuzzle-gen.py
		bool	f;		// * Ouvrir un fichier
		int		fId;	// * id du fichier a ouvrir
		bool	greedy;		// * Recherche Greedy
		bool	uniform;	// * Recherche Uniform Cost
		bool	astar;		// * Recherche A*
		bool	hm;	// * Heuristique: Distance de Manhattan
		bool	he;	// * Heuristique: Distance euclidienne
		bool	hg;	// * Heuristique: Nombre de pieces mal placees
		int		timeOut;	// * en secondes
		bool	anim;		// * play animation
		std::string						fileName;	// * Nom du fichier a ouvrir
		std::vector<std::string>		params;
		std::vector<enum SearchType>	searches;
		std::vector<enum Heuristique>	heuristiques;

		// * private methods
		void manageConflicts(void);
		void setSearchesAndHeuristiques(void) ;
		void printArgs();

	public:
		// * Constructeur par défaut
		Arguments(void);

		// * public methods
		void parse(int argc, char* argv[]);

		// * Accesseurs
		bool	getG() const;
		int		getGSize() const;
		bool	getGPy() const;
		bool	getF() const;
		int		getFId() const;
		std::string getFileName() const;
		bool	getGreedy() const;
		bool	getUniform() const;
		bool	getAstar() const;
		bool	getHM() const;
		bool	getHE() const;
		bool	getHG() const;
		int		getTimeOut() const;
		bool	getAnim() const;
		const std::vector<std::string>&			getParams() const;
		const std::vector<enum SearchType>&		getSearches() const;
		const std::vector<enum Heuristique>&	getHeuristiques() const;
};

#endif // ARGUMENTS_HPP