#ifndef HASH_HEADER_HPP
#define HASH_HEADER_HPP

#include <iostream>
#include "constants.hpp"

#define MAX_MOVIE_HASH 503

using namespace std;

vector<unique_ptr<MovieHash>> createMoviesHashTable(vector<Movie> movies);
int insertMovieInHashTableById(vector<unique_ptr<MovieHash>>& hashTable, unique_ptr<MovieHash>& movieHash);
unordered_map<int, unique_ptr<UserReviewHash>> createUserReviewHashTable(vector<Review> allReviews, vector<unique_ptr<MovieHash>>& moviesHashTable);
void insertUserInHashLikeVector(unordered_map<int, unique_ptr<UserReviewHash>>& userHashVector, unique_ptr<UserReviewHash>& userReview);
void insertUserInHashLikeVector(vector<unique_ptr<UserReviewHash>>& userHashVector, unique_ptr<UserReviewHash>& userReview);

#endif