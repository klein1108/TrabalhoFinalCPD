#ifndef FILE_SERVICE_HPP
#define FILE_SERVICE_HPP

#include <iostream>
#include <string>
#include <vector>
#include "../../parser-master/parser.hpp"

#define MOVIE_FILE_SMALL_DATA "./datas/dados-pequeno/movies.csv"

#define GENRES_SEPARATION "|"

using namespace std;
using namespace aria::csv;

typedef struct typeMovieHash{
  int movieId;
  string title;
  string genres;
  vector<string> formatGenres;
  int year;

  int rate;
  int rateCounting;
  int rateSum;

  struct typeMovieHash *next;

} MovieHash;

void printAllFileDataByName(char fileName[]);
vector<MovieHash> setAllMoviesFromFileToVector();
vector<string> splitStringIntoNewVectorBySeparator(string s, string delimiter);


#endif