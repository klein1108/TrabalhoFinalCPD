#ifndef HASH_HEADER_HPP
#define HASH_HEADER_HPP

#include <iostream>
#include "constants.hpp"
#include <memory>

using namespace std;

vector<unique_ptr<MovieHash>> createMoviesHashTable(vector<Movie> movies);
int insertPlayerInHashTableById(vector<unique_ptr<MovieHash>>& hashTable, unique_ptr<MovieHash>& movieHash);
void addToMoviesHashTable(vector<unique_ptr<MovieHash>>& hashTable, MovieHash movie);

#endif