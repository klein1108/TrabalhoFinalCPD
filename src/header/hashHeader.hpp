#ifndef HASH_HEADER_HPP
#define HASH_HEADER_HPP

#include <iostream>
#include "constants.hpp"

using namespace std;

int insertMovieInHashTableById(vector<unique_ptr<MovieHash>>& hashTable, unique_ptr<MovieHash>& movieHash);
void addToMoviesHashTable(vector<unique_ptr<MovieHash>>& hashTable, MovieHash movie);

void addToUsersHashTable(vector<unique_ptr<UserHash>>& hashTable, UserHash user);
int insertUserInHashTableById(vector<unique_ptr<UserHash>>& hashTable, unique_ptr<UserHash>& userHash);

#endif