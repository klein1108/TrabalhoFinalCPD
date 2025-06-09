#include "../header/searchHeader.hpp"
#include "../header/fileHeader.hpp"
#include "../header/hashHeader.hpp"

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
            current->ratingSum += review.rating;
            current->ratingCounting++;
            current->rating = current->ratingSum / current->ratingCounting;
            return; // Rating added successfully
        }
        current = current->next;
    }
}

//PRINT FUNCTIONS

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

void printMovieById(const vector<unique_ptr<MovieHash>>& moviesHashTable, int movieId) {
    int index = movieId % MAX_MOVIE_HASH;
    MovieHash* current = moviesHashTable[index].get();
    while (current != nullptr) {
        if (current->movie.movieId == movieId) {
            cout << "Movie ID: " << current->movie.movieId << endl;
            cout << "Title: " << current->movie.title << endl;
            cout << "Genres: " << current->movie.genres << endl;
            cout << "Year: " << current->movie.year << endl;
            cout << "Average Rating: " << current->rating << endl;
            cout << "Number of Ratings: " << current->ratingCounting << endl;
            cout << "------------------------" << endl;
            return;
        }
        current = current->next;
    }
    cout << "Movie with ID " << movieId << " not found." << endl;
}