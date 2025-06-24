#ifndef SEARCH_HEADER_HPP
#define SEARCH_HEADER_HPP

#include <iostream>
#include <cctype>
#include "constants.hpp"
#include "../header/fileHeader.hpp"
#include "../header/hashHeader.hpp"
#include "../header/sortHeader.hpp"

void printAllFileDataByName(char fileName[]);
void addRatingToRatingSum(const vector<unique_ptr<MovieHash>>& moviesHashTable, Review review);
vector<int> searchTags(unique_ptr<TagsTST>& root, const string& prefix);
void searchByTags(unique_ptr<TagsTST>& root, const string& tagsString, const vector<unique_ptr<MovieHash>>& moviesHashTable);
vector<string> separateBySingleQuotes(const string& input);
vector<int> tagsInCommon(const vector<vector<int>> moviesWithTags);
vector<MovieReviewed> idToMovie(const vector<int>& ids, const vector<unique_ptr<MovieHash>>& moviesHashTable);

//PRINT FUNCTIONS
void printTopXMoviesByGenre(vector<MovieReviewed>& movieReviewed, int& topX);
void print20Movies(vector<MovieReviewed> ordenedMovies);
void printUserById(const vector<unique_ptr<UserHash>>& usersHashTable, int searchId);
void printMovieById(const vector<unique_ptr<MovieHash>>& moviesHashTable, int movieId);
void printTop20RatingsByUserID(const vector<unique_ptr<UserHash>>& usersHashTable, const vector<unique_ptr<MovieHash>>& moviesHashTable, int userId);
void printAllTagsFiltered(const vector<int>& moviesWithTag, const vector<unique_ptr<MovieHash>>& moviesHashTable);
vector<MovieReviewed> filterMoviesByGenre(vector<Movie>& allMovies, vector<unique_ptr<MovieHash>>& hashTable, const string genre, int topX);
vector<MovieReviewed> orderByRatingMoviesFilteredByPrefix(vector<Movie>& moviesFiltered);
void getAllRatings(vector<Movie>& allMovies, vector<unique_ptr<MovieHash>>& movieHash);
vector<string> getUserCommand(int& programStage);
#endif