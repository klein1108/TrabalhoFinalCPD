#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <vector>
#include <iostream>
#include <string> 
#include <algorithm>
#include <iomanip>
#include <chrono> // Timer
#include "../../parser-master/parser.hpp" // CSV Parser
#include <memory> // For unique_ptr


//FILES
#define MOVIE_FILE_BIG_DATA "./datas/dados-completo/movies.csv"
#define MINIRATINGS_FILE_BIG_DATA "./datas/dados-completo/miniratings.csv"
#define RATINGS_FILE_BIG_DATA "./datas/dados-completo/ratings.csv"
#define TAGS_FILE_BIG_DATA "./datas/dados-completo/tags.csv"

//SEARCH
#define PREFIX_EXIT "exit"
#define PREFIX_SEARCH_ONE "prefixo"
#define PREFIX_SEARCH_TWO "user"
#define PREFIX_SEARCH_THREE "top"
#define PREFIX_SEARCH_FOUR "tags"

#define EXIT_COMMAND -1
#define GET_USER_COMMAND 0
#define GET_PREFIX_SEARCH 1
#define GET_USER_SEARCH 2
#define GET_TOP_GENRE_SEARCH 3
#define GET_TAGS_SEARCH 4

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

// Data Structures
// Movie, Review, User, Tag
typedef struct typeMovie{
  int movieId;
  string title;
  string genres;
  vector<string> formatGenres;
  int year;
  float rating;
  float ratingCounting;
  float ratingSum = 0;

} Movie;

typedef struct typeReview{
  int movieId;
  float rating;
  string date;

} Review;

typedef struct typeUser{
  int userId;
  vector<Review> reviews;

} User;

typedef struct typeTags{
  int userId;
  int movieId;
  string tag;
  string timestamp;

} Tag;

// Hash Structures

typedef struct typeMovieHash{
  Movie movie;
  struct typeMovieHash *next;

} MovieHash;

typedef struct typeUserHash{
  User user;
  struct typeUserHash *next;

} UserHash;

// MovieReviewed for sorting
typedef struct typeMovieReviewed{
  Movie movie;
  float userRating;

} MovieReviewed;

// Ternary Search Tree 

typedef struct typeTSTMovie{
  char letter;
  int movieId = NO_WORD_RELATED;
  struct typeTSTMovie *next;
  struct typeTSTMovie *left;
  struct typeTSTMovie *right;

  // teste para ver se da pra alocar o filme aqui e pegar as infos dele direto
  const Movie* movie;
} TernarySearchTree;

typedef struct typeTagsTST{
  char letter;
  bool leafFlag = false;
  unique_ptr<typeTagsTST> next;
  unique_ptr<typeTagsTST> left;
  unique_ptr<typeTagsTST> right;

  // teste para ver se da pra alocar o filme aqui e pegar as infos dele direto
  vector<int> movieIds;
} TagsTST;

#endif