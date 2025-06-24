#ifndef SEARCH_HEADER_HPP
#define SEARCH_HEADER_HPP

#include <iostream>
#include "constants.hpp"
#include "../header/fileHeader.hpp"
#include "../header/hashHeader.hpp"
#include "../header/sortHeader.hpp"

void printAllFileDataByName(char fileName[]);
void print20Movies(vector<MovieReviewed> ordenedMovies);
void printUserById(const vector<unique_ptr<UserHash>>& usersHashTable, int searchId);
void printMovieById(const vector<unique_ptr<MovieHash>>& moviesHashTable, int movieId);
void addRatintToRatingSum(const vector<unique_ptr<MovieHash>>& moviesHashTable, Review review);
void printTop20RatingsByUserID(const vector<unique_ptr<UserHash>>& usersHashTable, const vector<unique_ptr<MovieHash>>& moviesHashTable, int userId);
vector<MovieReviewed> filterMoviesByGenre(vector<Movie>& allMovies, vector<unique_ptr<MovieHash>>& hashTable, const string genre, int topX);
#endif