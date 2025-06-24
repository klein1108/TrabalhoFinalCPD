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

void addRatingToRatingSum(const vector<unique_ptr<MovieHash>>& moviesHashTable, Review review) {
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
                 << ", Global Rating: " << fixed << setprecision(6) << movieReviewed.movie.rating
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
            cout << current->movie.movieId;
            cout << "| " << current->movie.title;
            cout << "| Genres: " << current->movie.genres;
            cout << "| Year: " << current->movie.year;
            cout << "| Average Rating: " << fixed << setprecision(6) << current->movie.rating;
            cout << "| Number of Ratings: " << current->movie.ratingCounting << endl;
            return;
        }
        current = current->next;
    }
    cout << "Movie with ID " << movieId << " not found." << endl;
}

//TAGS SEARCH FUNCTIONS
//=======================================================================================================================

void searchByTags(unique_ptr<TagsTST>& root, const string& tagsString, const vector<unique_ptr<MovieHash>>& moviesHashTable) {
    int numberOfTags = 0;
    for (char c : tagsString) if (c == '\'') numberOfTags++;

    if (numberOfTags == 0) { //Nao encontrou tags
        cout << "No tags found in the input string." << endl;
        return;
    }

    if( numberOfTags == 1) // Apenas uma tag
    { 
      vector<int> moviesWithTag = searchTags(root, tagsString);
      if (!moviesWithTag.empty()) {
          printAllTagsFiltered(moviesWithTag, moviesHashTable);
      } else {
          cout << "No movies found with the tag: " << tagsString << endl;
      }
      return;
    } else {
        vector<string> tags = separarPorAspasSimples(tagsString);
        vector<vector<int>> moviesWithTags;
        for (const string& tag : tags) {
            moviesWithTags.push_back(searchTags(root, tag));
        }
        vector<int> commonMovies = tagsInCommon(moviesWithTags);
        if (commonMovies.empty()) {
            cout << "No movies found with all specified tags." << endl;
            return;
        }
        vector<MovieReviewed> movies = idToMovie(commonMovies, moviesHashTable);

        quickSortMovies(movies, 0, movies.size() - 1);

        for(const auto& movie : movies) printMovieById(moviesHashTable, movie.movie.movieId);
    }
}


vector<MovieReviewed> idToMovie(const vector<int>& ids, const vector<unique_ptr<MovieHash>>& moviesHashTable) {
    vector<MovieReviewed> movies;
    for (int id : ids) {
        int index = id % MAX_MOVIE_HASH;
        MovieHash* current = moviesHashTable[index].get();
        while (current) {
            if (current->movie.movieId == id) {
                movies.push_back({current->movie, 0.000f});
                break;
            }
            current = current->next;
        }
    }
    return movies;
}

vector<int> tagsInCommon(vector<vector<int>> moviesWithTags) {
    if (moviesWithTags.empty()) return {};

    for(auto& vec : moviesWithTags) {
        quickSort(vec, 0, vec.size() - 1);
        auto last = unique(vec.begin(), vec.end()); // remove duplicatas consecutivas
        vec.erase(last, vec.end()); // apaga elementos repetidos
    }
    vector<int> commonMovies = moviesWithTags[0];

    // Intersecta com os demais vetores
    for (size_t i = 1; i < moviesWithTags.size(); ++i) {
        vector<int> temp;
        size_t a = 0, b = 0;
        while (a < commonMovies.size() && b < moviesWithTags[i].size()) {
            if (commonMovies[a] < moviesWithTags[i][b]) {
                ++a;
            } else if (commonMovies[a] > moviesWithTags[i][b]) {
                ++b;
            } else {
                temp.push_back(commonMovies[a]);
                ++a;
                ++b;
            }
        }
        commonMovies = move(temp);

        // Se em algum ponto a interseção estiver vazia, pode parar
        if (commonMovies.empty()) break;
    }
    
    return commonMovies;
}

vector<string> separarPorAspasSimples(const string& input) {
    vector<string> resultado;
    bool dentroDeAspas = false;
    string palavraAtual;

    for (char c : input) {
        if (c == '\'') {
            if (dentroDeAspas) {
                // Fecha uma palavra
                resultado.push_back(palavraAtual);
                palavraAtual.clear();
            }
            // Alterna o estado
            dentroDeAspas = !dentroDeAspas;
        } else if (dentroDeAspas) {
            palavraAtual += c;
        }
    }

    return resultado;
}

// Função de busca por prefixo na TST de tags
vector<int> searchTags(unique_ptr<TagsTST>& root, const string& word) {
  TagsTST* node = root.get();
  int pos = 0;

  while (node && pos < word.size()) {
    char c = tolower(word[pos]);

    if (c < node->letter) {
      node = node->left.get();
    } else if (c > node->letter) {
      node = node->right.get();
    } else {
      pos++;
      if (pos == word.size()) break;
      node = node->next.get();
    }
  }

  if (node && node->leafFlag && pos == word.size()) {
    return node->movieIds;
  }

  return {};
}

// Função para imprimir todas as tags filtradas
void printAllTagsFiltered(const vector<int>& moviesWithTag, const vector<unique_ptr<MovieHash>>& moviesHashTable) {
  for (int movieId : moviesWithTag) {
      int index = movieId % MAX_MOVIE_HASH;
      MovieHash* current = moviesHashTable[index].get();
      while (current) {
          if (current->movie.movieId == movieId) {
              const Movie& movie = current->movie;
              cout << "Movie ID: " << movieId << " | Title: " << movie.title << " | Genres: " << movie.genres << endl;
              break;
          }
          current = current->next;
      }
  }
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