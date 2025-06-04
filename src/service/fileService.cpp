#include "../headers/fileService.hpp"

vector<MovieHash> setAllMoviesFromFileToVector(){ 
  ifstream f(MOVIE_FILE_SMALL_DATA);
  CsvParser parser(f);

  vector<MovieHash> response;

  int movieCounting = 0;

  //REMOVE FIRST LINE
  int NUM_WORDS_TO_REMOVE = 4;
  int end = true;
  auto field = parser.next_field();
  for(int i = 0; i < NUM_WORDS_TO_REMOVE; i++){
    field = parser.next_field();
  }

  while(end) {
    MovieHash movie;
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
          break;
        case FieldType::ROW_END:
          response.push_back(movie);
          movieCounting++;
          break;
        case FieldType::CSV_END: 
          end = false;
      }
  }

  cout << "Succeeded mapping all the " << movieCounting << " movies from file!" << endl;
  
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
