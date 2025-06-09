#include "../header/hashHeader.hpp"

void addToMoviesHashTable(vector<unique_ptr<MovieHash>>& hashTable, MovieHash movie)
{
  unique_ptr<MovieHash> movieHash = make_unique<MovieHash>();

  movieHash->movie = movie.movie;

  movieHash->next = nullptr;

  insertMovieInHashTableById(hashTable, movieHash);

}

void addToUsersHashTable(vector<unique_ptr<UserHash>>& hashTable, UserHash user)
{
  unique_ptr<UserHash> userHash = make_unique<UserHash>();

  userHash->user = user.user;

  userHash->next = nullptr;

  insertUserInHashTableById(hashTable, userHash);

}

int insertMovieInHashTableById(vector<unique_ptr<MovieHash>>& hashTable, unique_ptr<MovieHash>& movieHash)
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

int insertUserInHashTableById(vector<unique_ptr<UserHash>>& hashTable, unique_ptr<UserHash>& userHash)
{
  int module = (int) userHash->user.userId % MAX_USER_HASH;
  int tableSize = 1;

  if(!hashTable.at(module)){
    hashTable[module] = move(userHash);

  } else {
    tableSize++;
    UserHash* current = hashTable[module].get();

    while (current->next != nullptr) {
      current = current->next;
      tableSize++;
    }
    current->next = userHash.release();
    
  }
  return tableSize;
}