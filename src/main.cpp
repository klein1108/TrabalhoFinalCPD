#include "header/fileHeader.hpp"
#include "header/hashHeader.hpp"
#include "header/searchHeader.hpp"
#include "header/treeHeader.hpp"
#include "header/constants.hpp"

int main(){
  
  auto start = chrono::high_resolution_clock::now(); // Start timer

  cout << "Welcome to the Movie Review System!" << endl;

  vector<unique_ptr<MovieHash>> moviesHashTable(MAX_MOVIE_HASH);
  vector<unique_ptr<UserHash>> usersHashTable(MAX_USER_HASH);
  
  //MOVIES  
  vector<Movie> allMoviesFromFile = setAllMoviesFromFileToVector(moviesHashTable);
  
  //RATINGS
  vector<User> allUsersFromFile = setAllReviewsFromFileToVector(usersHashTable, moviesHashTable);

  //TAGS
  vector<Tag> allTagsFromFile = setAllTagsFromFileToVector();

  //TERNARY SEARCH TREE MOVIES
  unique_ptr<TernarySearchTree> movieTree = setTernarySearchTreeByMovieNames(allMoviesFromFile);

  //TERNARY SEARCH TREE TAGS
  unique_ptr<TagsTST> tagTree = setTernarySearchTreeByTags(allTagsFromFile);

  auto end = chrono::high_resolution_clock::now(); // End timer
  chrono::duration<double> elapsed = end - start;
  cout << "Execution time: " << elapsed.count() << " seconds" << endl;

  getAllRatings(allMoviesFromFile, moviesHashTable);

  int programStage = GET_USER_COMMAND;

  do{
    vector<string> stringVector = getUserCommand(programStage);
    if(programStage != EXIT_COMMAND){
      
      if(programStage == GET_PREFIX_SEARCH){
          if(stringVector.size() >= 2){
            //FILTER TREE BY SUFIX
            const string prefix = stringVector.at(1); 
            vector<Movie> movies = searchMoviesByPrefix(movieTree.get(), prefix);
            vector<MovieReviewed> moviesOrdened = orderByRatingMoviesFilteredByPrefix(movies);
            printAllMovieNamesFilteredByPrefix(moviesOrdened);
          }
      } else if (programStage == GET_USER_SEARCH){
          if(stringVector.size() >= 2){
            int id = stoi(stringVector.at(1));
            printTop20RatingsByUserID(usersHashTable, moviesHashTable, id);
          }

      } else if (programStage == GET_TOP_GENRE_SEARCH){
          if(stringVector.size() >= 3){
            //FILTER TOP X MOVIES BY GENRE
            int topX = stoi(stringVector.at(1));
            const string genre = stringVector.at(2);
            vector<MovieReviewed> topXmoviesFilteredByGenre = filterMoviesByGenre(allMoviesFromFile, moviesHashTable, genre, topX);
            printTopXMoviesByGenre(topXmoviesFilteredByGenre, topX);
          }

      }else if (programStage == GET_TAGS_SEARCH){
        if(stringVector.size() >= 2){
          //FILTER TAGS TREE 
          string tagName = "";
          for(int i = 1; i < stringVector.size(); i++){
            tagName = tagName + stringVector.at(i) + 
            (i+1 != stringVector.size() ? " " : "");
          }

          searchByTags(tagTree, tagName, moviesHashTable);
        }
      }

    }
  } while (programStage != EXIT_COMMAND);

  cout << "Fim do programa!" << endl;
 
  return 0;
}