#ifndef FILE_HEADER_HPP
#define FILE_HEADER_HPP

#include <iostream>
#include "constants.hpp"

vector<Movie> setAllMoviesFromFileToVector(vector<unique_ptr<MovieHash>>& moviesHashTable);
vector<User> setAllReviewsFromFileToVector();
vector<string> splitStringIntoNewVectorBySeparator(string s, string delimiter);

#endif