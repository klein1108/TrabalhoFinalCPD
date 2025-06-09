#include "header/fileHeader.hpp"
#include "header/hashHeader.hpp"
#include "header/searchHeader.hpp"
#include "header/constants.hpp"

int main(){
  
  auto start = chrono::high_resolution_clock::now(); // Start timer

  cout << "Welcome to the Movie Review System!" << endl;

  vector<unique_ptr<MovieHash>> moviesHashTable(MAX_MOVIE_HASH);
  vector<unique_ptr<UserHash>> usersHashTable(MAX_USER_HASH);
  
  vector<Movie> allMoviesFromFile = setAllMoviesFromFileToVector(moviesHashTable);
  
  vector<User> allUsersFromFile = setAllReviewsFromFileToVector(usersHashTable, moviesHashTable);

  auto end = chrono::high_resolution_clock::now(); // End timer
  chrono::duration<double> elapsed = end - start;
  cout << "Execution time: " << elapsed.count() << " seconds" << endl;

  //printUserById(usersHashTable, 54766);
  //printMovieById(moviesHashTable, 102107);

  return 0;
}