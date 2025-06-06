#include "../header/hashHeader.hpp"

vector<unique_ptr<MovieHash>> createMoviesHashTable(vector<Movie> movies){
  vector<unique_ptr<MovieHash>> response(MAX_MOVIE_HASH);
  
  int greatestTableSize = 0;

  for(int i = 0; i < movies.size(); i++){
    unique_ptr<MovieHash> movieHash = make_unique<MovieHash>();

    movieHash->next = nullptr;

    //Mapping Movie to MovieHash
    movieHash->movieInfo.movieId = movies.at(i).movieId;
    movieHash->movieInfo.title = movies.at(i).title;
    movieHash->movieInfo.genres = movies.at(i).formatGenres;
    movieHash->movieInfo.year = movies.at(i).year;

    movieHash->movieInfo.globalRating = 0;
    movieHash->movieInfo.count = 0;
    movieHash->movieInfo.rating = 0;

    int tableSize = insertMovieInHashTableById(response, movieHash);

    if(tableSize > greatestTableSize){
      greatestTableSize = tableSize;
    }

  }

  cout << "Hash table was created with success!" << endl;
  cout << "The greatest table was " << greatestTableSize << " pointer long!" << endl;

  return response;
}


unordered_map<int, unique_ptr<UserReviewHash>> createUserReviewHashTable(vector<Review> allReviews, vector<unique_ptr<MovieHash>>& moviesHashTable){
  unordered_map<int, unique_ptr<UserReviewHash>> response;

  for(int i = 0, j = 0, exit = false; i < allReviews.size(); i++){
    unique_ptr<UserReviewHash> userReview = make_unique<UserReviewHash>();
    userReview->next = nullptr;

    //Mapping
    userReview->review.date = allReviews.at(i).date;
    userReview->review.rating = allReviews.at(i).rating;
    userReview->review.userId = allReviews.at(i).userId;
    userReview->review.movieId = allReviews.at(i).movieId;

    int module = userReview->review.movieId % MAX_MOVIE_HASH;
    MovieHash* current = moviesHashTable[module].get();

    while (current->movieInfo.movieId != userReview->movieInfo.movieId && current->next != nullptr) {
      current = current->next;
    }

    if (current != nullptr) {
      userReview->movieInfo.count = current->movieInfo.count;
      userReview->movieInfo.genres = current->movieInfo.genres;
      userReview->movieInfo.globalRating = current->movieInfo.globalRating;
      userReview->movieInfo.movieId = current->movieInfo.movieId;
      userReview->movieInfo.rating = current->movieInfo.rating;
      userReview->movieInfo.title = current->movieInfo.title;
      userReview->movieInfo.year = current->movieInfo.year;
    }

    insertUserInHashLikeVector(response, userReview);
    
  }
  return response;
}

void insertUserInHashLikeVector(unordered_map<int, unique_ptr<UserReviewHash>>& userHashVector, unique_ptr<UserReviewHash>& userReview){
  int module = userReview->review.userId;

  if(!userHashVector[module]){
    userHashVector[module] = move(userReview);

  } else {
    UserReviewHash* current = userHashVector[module].get();

    while (current->next != nullptr) {
      current = current->next;
    }
    current->next = userReview.release();
    
  }

}

int insertMovieInHashTableById(vector<unique_ptr<MovieHash>>& hashTable, unique_ptr<MovieHash>& movieHash){
  int module = (int) movieHash->movieInfo.movieId % MAX_MOVIE_HASH;
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

