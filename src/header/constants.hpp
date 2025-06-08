#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <vector>
#include <string> 
#include <chrono> // Timer

//FILES
#define MOVIE_FILE_BIG_DATA "./datas/dados-completo/movies.csv"
#define MINIRATINGS_FILE_BIG_DATA "./datas/dados-completo/miniratings.csv"
#define RATINGS_FILE_BIG_DATA "./datas/dados-completo/ratings.csv"
#define TAGS_FILE_BIG_DATA "./datas/dados-completo/tags.csv"

//UTILS
#define GENRES_SEPARATION "|"

//HASH
#define MAX_MOVIE_HASH 11131

using namespace std;

typedef struct typeMovie{
  int movieId;
  string title;
  string genres;
  vector<string> formatGenres;
  int year;
} Movie;

typedef struct typeReview{
  int userId;
  int movieId;
  float rating;
  string date;

} Review;

typedef struct typeMovieHash{
  Movie movie;

  int rating;
  int ratingCounting;
  int ratingSum;

  struct typeMovieHash *next;

} MovieHash;

#endif