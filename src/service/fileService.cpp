#include "../header/fileHeader.hpp"
#include "../header/hashHeader.hpp"
#include "../header/constants.hpp"

vector<Movie> setAllMoviesFromFileToVector(vector<unique_ptr<MovieHash>>& moviesHashTable){ 
  ifstream f(MOVIE_FILE_BIG_DATA);
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
    MovieHash movie;
    field = parser.next_field();
      switch (field.type) {
        case FieldType::DATA:
            movie.movie.movieId = stoi(field.data);
            field = parser.next_field();

            movie.movie.title = field.data;
            field = parser.next_field();

            movie.movie.genres = field.data;
            movie.movie.formatGenres = splitStringIntoNewVectorBySeparator(movie.movie.genres, GENRES_SEPARATION);
            field = parser.next_field();

            movie.movie.year = stoi(field.data);

            response.push_back(movie.movie);
            movieCounting++;
            addToMoviesHashTable(moviesHashTable, movie);
          break;
        case FieldType::CSV_END: 
        isEnd = true;
      }
  }

  cout << "Succeeded mapping all the " << movieCounting << " movies from file!" << endl;
  
  return response;
}

vector<Review> setAllReviewsFromFileToVector(){
  ifstream f(MINIRATINGS_FILE_BIG_DATA);
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
            allRatingCounting++;
          break;

        case FieldType::CSV_END: 
        isEnd = true;
      }
  }

  cout << "Succeeded mapping all the " << allRatingCounting << " ratings from file!" << endl;

  return response;
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
