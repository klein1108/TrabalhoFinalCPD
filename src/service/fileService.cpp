#include "../header/fileHeader.hpp"
#include "../header/hashHeader.hpp"
#include "../header/searchHeader.hpp"
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

vector<User> setAllReviewsFromFileToVector(vector<unique_ptr<UserHash>>& usersHashTable, vector<unique_ptr<MovieHash>>& moviesHashTable) {
    ifstream f(RATINGS_FILE_BIG_DATA);
    CsvParser parser(f);

    vector<User> response;
    int allRatingCounting = 0;

    // REMOVE FIRST LINE
    int NUM_WORDS_TO_REMOVE = 4;
    for(int i = 0; i < NUM_WORDS_TO_REMOVE; i++){
        parser.next_field();
    }

    int lastUserId = -1;
    UserHash user;

    while (true) {
        auto field = parser.next_field();
        if (field.type == FieldType::CSV_END) break;
        if (field.type != FieldType::DATA) continue;

        int userId = stoi(field.data);

        // If new user, push previous and start new
        if (userId != lastUserId && lastUserId != -1) {
            addToUsersHashTable(usersHashTable, user);
            response.push_back(user.user);
            user = UserHash();
        }
        user.user.userId = userId;
        lastUserId = userId;

        // MovieId
        field = parser.next_field();
        int movieId = stoi(field.data);

        // Rating
        field = parser.next_field();
        float rating = stof(field.data);

        // Date
        field = parser.next_field();
        string date = field.data;

        // Add review
        Review review;
        review.movieId = movieId;
        review.rating = rating;
        review.date = date;
        addRatintToRatingSum(moviesHashTable, review);
        user.user.reviews.push_back(review);

        allRatingCounting++;
    }

    // Push last user if any reviews were read
    if (!user.user.reviews.empty()) {
        response.push_back(user.user);
    }

    cout << "Succeeded mapping all the " << allRatingCounting << " ratings from file!" << endl;
    return response;
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
