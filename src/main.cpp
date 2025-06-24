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

  //TAGS
  vector<Tag> allTagsFromFile = setAllTagsFromFileToVector();

  //TERNARY SEARCH TREE MOVIES
  unique_ptr<TernarySearchTree> movieTree = setTernarySearchTreeByMovieNames(allMoviesFromFile);

  //TERNARY SEARCH TREE TAGS
  unique_ptr<TagsTST> tagTree = setTernarySearchTreeByTags(allTagsFromFile);

  auto end = chrono::high_resolution_clock::now(); // End timer
  chrono::duration<double> elapsed = end - start;
  cout << "Execution time: " << elapsed.count() << " seconds" << endl;

  //FILTER TREE BY SUFIX
  const string prefix = "America"; 
  vector<Movie> movies = searchMoviesByPrefix(movieTree.get(), prefix);
  //printAllMovieNamesFilteredByPrefix(movies);

  //FILTER TAGS TREE 
  const string tagName = "'feel-good' 'predictable'";
  searchByTags(tagTree, tagName, moviesHashTable);
  printTop20RatingsByUserID(usersHashTable, moviesHashTable, 54766);

  //FILTER MOVIES BY GENRE
  const string genre = "Animation";
  vector<MovieReviewed> topXmoviesFilteredByGenre = filterMoviesByGenre(allMoviesFromFile, moviesHashTable, genre, 20);

  return 0;
}