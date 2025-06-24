#ifndef FILE_HEADER_HPP
#define FILE_HEADER_HPP

#include <iostream>
#include "constants.hpp"
#include "../header/hashHeader.hpp"
#include "../header/searchHeader.hpp"
#include "../header/constants.hpp"

vector<Movie> setAllMoviesFromFileToVector(vector<unique_ptr<MovieHash>>& moviesHashTable);
vector<User> setAllReviewsFromFileToVector(vector<unique_ptr<UserHash>>& usersHashTable, vector<unique_ptr<MovieHash>>& moviesHashTable);
vector<Tag> setAllTagsFromFileToVector();
vector<string> splitStringIntoNewVectorBySeparator(string s, string delimiter);

#endif