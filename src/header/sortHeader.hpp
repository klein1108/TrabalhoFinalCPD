#ifndef SORT_HEADER_HPP
#define SORT_HEADER_HPP

#include <iostream>
#include "constants.hpp"

int partitionReviews(vector<Review>& arr, int low, int high);
void firstSort(vector<Review>& reviews, int low, int high);

void secondSort(vector<MovieReviewed>& movieR);
int partitionMovies(vector<MovieReviewed>& arr, int low, int high);
void quickSortMovies(vector<MovieReviewed>& movieR, int low, int high);

#endif