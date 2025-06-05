#ifndef FILE_HEADER_HPP
#define FILE_HEADER_HPP

#include <iostream>
#include "constants.hpp"
#include "../../parser-master/parser.hpp"

using namespace aria::csv;

void printAllFileDataByName(char fileName[]);
vector<Movie> setAllMoviesFromFileToVector();
vector<Review> setAllReviewsFromFileToVector();
vector<string> splitStringIntoNewVectorBySeparator(string s, string delimiter);



#endif