#include "../header/fileHeader.hpp"
#include "../header/constants.hpp"

vector<Movie> setAllMoviesFromFileToVector(){ 
  ifstream f(MOVIE_FILE_SMALL_DATA);
  CsvParser parser(f);

  vector<Movie> response;

  int movieCounting = 0;

  //REMOVE FIRST LINE
  int NUM_WORDS_TO_REMOVE = 4;
  int isEnd = false;
  auto field = parser.next_field();
  for(int i = 0; i < NUM_WORDS_TO_REMOVE; i++){
    field = parser.next_field();
  }

  while(!isEnd) {
    Movie movie;
    field = parser.next_field();
      switch (field.type) {
        case FieldType::DATA:
            movie.movieId = stoi(field.data);
            field = parser.next_field();

            movie.title = field.data;
            field = parser.next_field();

            movie.genres = field.data;
            movie.formatGenres = splitStringIntoNewVectorBySeparator(movie.genres, GENRES_SEPARATION);
            field = parser.next_field();

            movie.year = stoi(field.data);

            response.push_back(movie);
            movieCounting++;
          break;
        case FieldType::CSV_END: 
        isEnd = true;
      }
  }

  cout << "Succeeded mapping all the " << movieCounting << " movies from file!" << endl;
  
  return response;
}

vector<Review> setAllReviewsFromFileToVectorAndHandleRatings(vector<unique_ptr<MovieHash>>& hashTable){
  // ifstream f(MINIRATINGS_FILE_SMALL_DATA);
  ifstream f(RATINGS_FILE_BIG_DATA);
  CsvParser parser(f);

  vector<Review> response;

  int allRatingCounting = 0;

  //REMOVE FIRST LINE
  int NUM_WORDS_TO_REMOVE = 4;

  int isEnd = false;

  auto field = parser.next_field();
  for(int i = 0; i < NUM_WORDS_TO_REMOVE; i++){
    field = parser.next_field();
  }

  while(!isEnd) {
    Review review;
    field = parser.next_field();
      switch (field.type) {
        case FieldType::DATA:
            review.userId = stoi(field.data);
            field = parser.next_field();

            review.movieId = stoi(field.data);
            field = parser.next_field();

            review.rating = stof(field.data);
            field = parser.next_field();

            review.date = field.data;

            response.push_back(review);

            increaseHashMovieRatingValues(review, hashTable);

            allRatingCounting++;
          break;

        case FieldType::CSV_END: 
        isEnd = true;
      }
  }

  cout << "Succeeded mapping all the " << allRatingCounting << " ratings from file!" << endl;

  return response;
}

void setMovieHashTableRatingsBySumPerCounting(vector<unique_ptr<MovieHash>>& hashTable){
  for(int i = 0; i < hashTable.size(); i++){
    if(hashTable.at(i) && hashTable.at(i)->movieInfo.count > 0){
      hashTable.at(i)->movieInfo.rating = (float) hashTable.at(i)->movieInfo.globalRating / hashTable.at(i)->movieInfo.count;
    }
  }
}

void increaseHashMovieRatingValues(Review review, vector<unique_ptr<MovieHash>>& hashTable){
  int module = (int)review.movieId % MAX_MOVIE_HASH;
  
  MovieHash* current = hashTable[module].get();


  while (current != nullptr && current->movieInfo.movieId != review.movieId) {
    current = current->next;
  }
  
  if (current != nullptr) {
    current->movieInfo.globalRating += review.rating;
    current->movieInfo.count++;
  }

}


void printAllFileDataByName(char fileName[]){
  ifstream f(fileName);
  CsvParser parser(f);

  while(true) {
    auto field = parser.next_field();
    switch (field.type) {
      case FieldType::DATA:
        cout << field.data << " | ";
        break;
      case FieldType::ROW_END:
        cout <<endl;
        break;
      case FieldType::CSV_END:
        cout << endl;
        return;
    }
  }
  
}

vector<string> splitStringIntoNewVectorBySeparator(string s, string delimiter) {
  size_t pos_start = 0, pos_end, delim_len = delimiter.length();
  string token;
  vector<string> result;

  while ((pos_end = s.find(delimiter, pos_start)) != string::npos) {
      token = s.substr (pos_start, pos_end - pos_start);
      pos_start = pos_end + delim_len;
      result.push_back (token);
  }

  result.push_back (s.substr (pos_start));
  return result;
}
