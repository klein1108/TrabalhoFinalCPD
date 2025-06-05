#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <vector>
#include <string>

//FILES
#define MOVIE_FILE_SMALL_DATA "./datas/dados-pequeno/movies.csv"

//UTILS
#define GENRES_SEPARATION "|"

//HASH
#define MAX_MOVIE_HASH 503

using namespace std;

typedef struct typeMovie{
  int movieId;
  string title;
  string genres;
  vector<string> formatGenres;
  int year;
} Movie;

typedef struct typeMovieHash{
  int movieId;
  string title;
  vector<string> genres;
  int year;

  int rate;
  int rateCounting;
  int rateSum;

  struct typeMovieHash *next;

} MovieHash;

#endif