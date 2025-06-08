#include "../header/hashHeader.hpp"

void addToMoviesHashTable(vector<unique_ptr<MovieHash>>& hashTable, MovieHash movie)
{
  unique_ptr<MovieHash> movieHash = make_unique<MovieHash>();

  movieHash->movie = movie.movie;

  movieHash->next = nullptr;

  insertPlayerInHashTableById(hashTable, movieHash);

}

vector<unique_ptr<MovieHash>> createMoviesHashTable(vector<Movie> movies)
{
  vector<unique_ptr<MovieHash>> response(MAX_MOVIE_HASH);
  
  int greatestTableSize = 0;

  for(int i = 0; i < movies.size(); i++){
    unique_ptr<MovieHash> movieHash = make_unique<MovieHash>();

    movieHash->next = nullptr;

    //Mapping Movie to MovieHash
    movieHash->movie = movies.at(i);

    int tableSize = insertPlayerInHashTableById(response, movieHash);

    if(tableSize > greatestTableSize){
      greatestTableSize = tableSize;
    }

  }

  cout << "Hash table was created with success!" << endl;
  cout << "The greatest table was " << greatestTableSize << " pointer long!" << endl;

  return response;
}

int insertPlayerInHashTableById(vector<unique_ptr<MovieHash>>& hashTable, unique_ptr<MovieHash>& movieHash)
{
  int module = (int) movieHash->movie.movieId % MAX_MOVIE_HASH;
  int tableSize = 1;

  if(!hashTable.at(module)){
    hashTable[module] = move(movieHash);

  } else {
    tableSize++;
    MovieHash* current = hashTable[module].get();

    while (current->next != nullptr) {
      current = current->next;
      tableSize++;
    }
    current->next = movieHash.release();
    
  }
  return tableSize;
}