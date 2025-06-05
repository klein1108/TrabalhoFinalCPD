#include "../header/hashHeader.hpp"

vector<unique_ptr<MovieHash>> createMoviesHashTable(vector<Movie> movies){
  vector<unique_ptr<MovieHash>> response(MAX_MOVIE_HASH);
  
  int greatestTableSize = 0;

  for(int i = 0; i < movies.size(); i++){
    unique_ptr<MovieHash> movieHash = make_unique<MovieHash>();

    movieHash->next = nullptr;

    //Mapping Movie to MovieHash
    movieHash->movieId = movies.at(i).movieId;
    movieHash->title = movies.at(i).title;
    movieHash->genres = movies.at(i).formatGenres;
    movieHash->year = movies.at(i).year;

    int tableSize = insertPlayerInHashTableById(response, movieHash);

    if(tableSize > greatestTableSize){
      greatestTableSize = tableSize;
    }

  }

  cout << "Hash table was created with success!" << endl;
  cout << "The greatest table was " << greatestTableSize << " pointer long!" << endl;

  return response;
}

int insertPlayerInHashTableById(vector<unique_ptr<MovieHash>>& hashTable, unique_ptr<MovieHash>& movieHash){
  int module = (int) movieHash->movieId % MAX_MOVIE_HASH;
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