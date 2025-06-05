#include "header/fileHeader.hpp"
#include "header/hashHeader.hpp"
#include "header/constants.hpp"

int main(){

  vector<Movie> allMoviesFromFile = setAllMoviesFromFileToVector();
  vector<unique_ptr<MovieHash>> moviesHashTable = createMoviesHashTable(allMoviesFromFile);

  
  vector<Review> allReviewsFromFile = setAllReviewsFromFileToVector();

  

  return 0;
}