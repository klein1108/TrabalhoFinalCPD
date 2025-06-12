#ifndef TREE_HEADER_HPP
#define TREE_HEADER_HPP

#include "constants.hpp"
#include <cctype>

unique_ptr<TernarySearchTree> setTernarySearchTreeByMovieNames(const vector<Movie>& movies);
vector<Movie> searchMoviesByPrefix(TernarySearchTree* root, const string& prefix);
void insertTST(TernarySearchTree*& node, const Movie& movie, int pos);
void collectMovies(TernarySearchTree* node, vector<Movie>& results);
void printAllMovieNamesFilteredByPrefix(vector<Movie> moviesFilteredByPrefix);



#endif

