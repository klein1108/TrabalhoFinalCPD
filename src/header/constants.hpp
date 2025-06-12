#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <vector>
#include <iostream>
#include <string> 
#include <chrono> // Timer
#include "../../parser-master/parser.hpp" // CSV Parser
#include <memory> // For unique_ptr


//FILES
#define MOVIE_FILE_BIG_DATA "./datas/dados-completo/movies.csv"
#define MINIRATINGS_FILE_BIG_DATA "./datas/dados-completo/miniratings.csv"
#define RATINGS_FILE_BIG_DATA "./datas/dados-completo/ratings.csv"
#define TAGS_FILE_BIG_DATA "./datas/dados-completo/tags.csv"

//UTILS
#define GENRES_SEPARATION "|"
#define UPPERCASE_ASCII_START 65
#define UPPERCASE_ASCII_END 90
#define UPPERCASE_SUM_TO_LOWERCASE 32
#define NO_WORD_RELATED 0

//HASH
#define MAX_MOVIE_HASH 11131
#define MAX_USER_HASH 79999

using namespace std;
using namespace aria::csv;

typedef struct typeMovie{
  int movieId;
  string title;
  string genres;
  vector<string> formatGenres;
  int year;

} Movie;

typedef struct typeMovieHash{
  Movie movie;

  float rating;
  float ratingCounting;
  float ratingSum = 0;

  struct typeMovieHash *next;

} MovieHash;

typedef struct typeReview{
  int movieId;
  float rating;
  string date;

} Review;

typedef struct typeUser{
  int userId;
  vector<Review> reviews;

} User;

typedef struct typeUserHash{
  User user;
  struct typeUserHash *next;

} UserHash;

typedef struct typeTernarySearchTree{
  char letter;
  int movieId = NO_WORD_RELATED;
  struct typeTernarySearchTree *next;
  struct typeTernarySearchTree *left;
  struct typeTernarySearchTree *right;

  // teste para ver se da pra alocar o filme aqui e pegar as infos dele direto
  const Movie* movie;
} TernarySearchTree;

#endif