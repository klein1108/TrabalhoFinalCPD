#include "header/fileHeader.hpp"
#include "header/hashHeader.hpp"
#include "header/constants.hpp"

int main(){

  vector<Movie> allMoviesFromFile = setAllMoviesFromFileToVector();
  vector<unique_ptr<MovieHash>> moviesHashTable = createMoviesHashTable(allMoviesFromFile);

  cout << "MOVIES HASH TABLE SIZE: " << moviesHashTable.size() << endl; 

  return 0;
}