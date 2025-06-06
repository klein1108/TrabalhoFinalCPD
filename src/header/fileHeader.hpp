#ifndef FILE_HEADER_HPP
#define FILE_HEADER_HPP

#include <iostream>
#include "constants.hpp"
#include "../../parser-master/parser.hpp"

using namespace aria::csv;

void printAllFileDataByName(char fileName[]);
vector<Movie> setAllMoviesFromFileToVector();
void increaseHashMovieRatingValues(Review review, vector<unique_ptr<MovieHash>>& hashTable);
vector<Review> setAllReviewsFromFileToVectorAndHandleRatings(vector<unique_ptr<MovieHash>>& hashTable);
vector<string> splitStringIntoNewVectorBySeparator(string s, string delimiter);
void setMovieHashTableRatingsBySumPerCounting(vector<unique_ptr<MovieHash>>& hashTable);

#endif