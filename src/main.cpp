#include "header/fileHeader.hpp"
#include "header/hashHeader.hpp"
#include "header/searchHeader.hpp"
#include "header/treeHeader.hpp"
#include "header/constants.hpp"

int main(){
  
  auto start = chrono::high_resolution_clock::now(); // Start timer

  cout << "Welcome to the Movie Review System!" << endl;

  vector<unique_ptr<MovieHash>> moviesHashTable(MAX_MOVIE_HASH);
  vector<unique_ptr<UserHash>> usersHashTable(MAX_USER_HASH);

  //MOVIES  
  vector<Movie> allMoviesFromFile = setAllMoviesFromFileToVector(moviesHashTable);
  
  //RATINGS
  vector<User> allUsersFromFile = setAllReviewsFromFileToVector(usersHashTable, moviesHashTable);

  //TERNARY SEARCH TREE
  unique_ptr<TernarySearchTree> movieTree = setTernarySearchTreeByMovieNames(allMoviesFromFile);

  //FILTER TREE BY SUFIX
  const string prefix = "toy"; 
  vector<Movie> movies = searchMoviesByPrefix(movieTree.get(), prefix);
  printAllMovieNamesFilteredByPrefix(movies);

  auto end = chrono::high_resolution_clock::now(); // End timer
  chrono::duration<double> elapsed = end - start;
  cout << "Execution time: " << elapsed.count() << " seconds" << endl;

  //printTop20RatingsByUserID(usersHashTable, moviesHashTable, 54766);

  return 0;
}