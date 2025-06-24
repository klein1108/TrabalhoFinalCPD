#include "../header/searchHeader.hpp"

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

void addRatintToRatingSum(const vector<unique_ptr<MovieHash>>& moviesHashTable, Review review) {
    int movieId = review.movieId;
    int index = movieId % MAX_MOVIE_HASH;
    MovieHash* current = moviesHashTable[index].get();
    while (current != nullptr) {
        if (current->movie.movieId == movieId) {
            current->movie.ratingSum += review.rating;
            current->movie.ratingCounting++;
            current->movie.rating = current->movie.ratingSum / current->movie.ratingCounting;
            return; // Rating added successfully
        }
        current = current->next;
    }
}

//PRINT FUNCTIONS

void printTop20RatingsByUserID(const vector<unique_ptr<UserHash>>& usersHashTable, const vector<unique_ptr<MovieHash>>& moviesHashTable, int userId) {
    int index = userId % MAX_USER_HASH; 
    UserHash* current = usersHashTable[index].get();

    vector<MovieReviewed> ordenedMovies;

    while (current != nullptr) {
        if (current->user.userId == userId) {
            cout << "User ID: " << current->user.userId << endl;
            cout << "Top 20 Ratings: " << endl;
              vector<Review> ordenedReviews = current->user.reviews;

              firstSort(ordenedReviews, 0, ordenedReviews.size() - 1);
              
              for (const auto& review : ordenedReviews) {
                  ordenedMovies.push_back({moviesHashTable[review.movieId % MAX_MOVIE_HASH]->movie, review.rating});
              }

              secondSort(ordenedMovies);
              print20Movies(ordenedMovies);
            
            return;
        }
        current = current->next;
    }
}

void printUserById(const vector<unique_ptr<UserHash>>& usersHashTable, int searchId) {
    int index = searchId % MAX_USER_HASH;
    UserHash* current = usersHashTable[index].get();
    while(current != nullptr) {
        if (current->user.userId == searchId) {
            cout << "User ID: " << current->user.userId << endl;
            cout << "Reviews: " << endl;
            for (const auto& review : current->user.reviews) {
                cout << "  Movie ID: " << review.movieId << ", Rating: " << review.rating << ", Date: " << review.date << endl;
            }
            cout << "------------------------" << endl;
            return;
        }
        current = current->next;
    }
}

void print20Movies(vector<MovieReviewed> ordenedMovies) {
    int count = 0;
    for (const auto& movieReviewed : ordenedMovies) {
        if (count < 20) {
            cout << "Movie ID: " << movieReviewed.movie.movieId 
                 << ", Title: " << movieReviewed.movie.title 
                 << ", Genres: " << movieReviewed.movie.genres
                 << ", Year: " << movieReviewed.movie.year
                 << ", Global Rating: " << movieReviewed.movie.rating
                 << ", Count: " << movieReviewed.movie.ratingCounting
                 << ", Rating: " << movieReviewed.userRating  
                 << endl;
            count++;
        } else {
            break; // Stop after printing 20 movies
        }
    }
    cout << "------------------------" << endl;
}

void printMovieById(const vector<unique_ptr<MovieHash>>& moviesHashTable, int movieId) {
    int index = movieId % MAX_MOVIE_HASH;
    MovieHash* current = moviesHashTable[index].get();
    while (current != nullptr) {
        if (current->movie.movieId == movieId) {
            cout << "Movie ID: " << current->movie.movieId << endl;
            cout << "Title: " << current->movie.title << endl;
            cout << "Genres: " << current->movie.genres << endl;
            cout << "Year: " << current->movie.year << endl;
            cout << "Average Rating: " << current->movie.rating << endl;
            cout << "Number of Ratings: " << current->movie.ratingCounting << endl;
            cout << "------------------------" << endl;
            return;
        }
        current = current->next;
    }
    cout << "Movie with ID " << movieId << " not found." << endl;
}

vector<MovieReviewed> filterMoviesByGenre(vector<Movie>& allMovies, vector<unique_ptr<MovieHash>>& movieHash, const string genre, int topX){
    vector<MovieReviewed> allMoviesReviewed;
    vector<MovieReviewed> response;
    int index = 0;
    static const size_t npos = -1;
    for(int i = 0; i < allMovies.size(); i++){
        MovieReviewed teste;
        int genrePos = allMovies.at(i).genres.find(genre);
        if(genrePos != npos){
            teste.movie = allMovies.at(i);
            index = teste.movie.movieId % MAX_MOVIE_HASH; 
            
            MovieHash* current = movieHash[index].get();
            while(current->movie.movieId != teste.movie.movieId && current->next != nullptr){
                current = current->next;
            }
            teste.movie.rating = current->movie.rating;
            teste.userRating = teste.movie.rating;

            allMoviesReviewed.push_back(teste);
        }

    }

    quickSortMovies(allMoviesReviewed, 0, allMoviesReviewed.size()-1);

    for(int i = 0; i < topX && i <= response.size(); i++){
        response.push_back(allMoviesReviewed.at(i));
        cout << i+1 << " - FILME: " << response.at(i).movie.movieId << " -> RATING: " << response.at(i).movie.rating << endl;
    }
    

    return response;
}