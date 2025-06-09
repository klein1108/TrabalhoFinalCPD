#ifndef SEARCH_HEADER_HPP
#define SEARCH_HEADER_HPP

#include <iostream>
#include "constants.hpp"

void printAllFileDataByName(char fileName[]);
void printUserById(const vector<unique_ptr<UserHash>>& usersHashTable, int searchId);
void printMovieById(const vector<unique_ptr<MovieHash>>& moviesHashTable, int movieId);
void addRatintToRatingSum(const vector<unique_ptr<MovieHash>>& moviesHashTable, Review review);

#endif