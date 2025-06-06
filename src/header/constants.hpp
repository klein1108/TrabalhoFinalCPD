#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <vector>
#include <string>
#include <memory>
#include <chrono>
#include <unordered_map>

//FILES
#define MOVIE_FILE_SMALL_DATA "./datas/dados-pequeno/movies.csv"
#define MINIRATINGS_FILE_SMALL_DATA "./datas/dados-pequeno/miniratings.csv"
#define RATINGS_FILE_SMALL_DATA "./datas/dados-pequeno/ratings.csv"
#define TAGS_FILE_SMALL_DATA "./datas/dados-pequeno/tags.csv"

#define MOVIE_FILE_BIG_DATA "./datas/dados-completo/movies.csv"
#define MINIRATINGS_FILE_BIG_DATA "./datas/dados-completo/miniratings.csv"
#define RATINGS_FILE_BIG_DATA "./datas/dados-completo/ratings.csv"
#define TAGS_FILE_BIG_DATA "./datas/dados-completo/tags.csv"

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

typedef struct typeReview{
  int userId;
  int movieId;
  float rating;
  string date;

} Review;


typedef struct typeMovieInfo{
  int movieId;
  string title;
  vector<string> genres;
  int year;

  float rating;
  int count;
  float globalRating;
} MovieInfo;

typedef struct typeUserReviewHash{
  struct typeReview review;
  struct typeMovieInfo movieInfo;
  struct typeUserReviewHash *next;

} UserReviewHash;

typedef struct typeMovieHash{
  struct typeMovieInfo movieInfo;
  struct typeMovieHash *next;

} MovieHash;

#endif