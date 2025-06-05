#ifndef HASH_HEADER_HPP
#define HASH_HEADER_HPP

#include <iostream>
#include "constants.hpp"
#include <memory>

#define MAX_MOVIE_HASH 503

using namespace std;

vector<unique_ptr<MovieHash>> createMoviesHashTable(vector<Movie> movies);
int insertPlayerInHashTableById(vector<unique_ptr<MovieHash>>& hashTable, unique_ptr<MovieHash>& movieHash);

#endif