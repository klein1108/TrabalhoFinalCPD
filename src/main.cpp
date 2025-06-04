#include "headers/fileService.hpp"


#define MAX_MOVIE_HASH 503

using namespace std;
using namespace aria::csv;

int main(){
  // printAllFileDataByName(MOVIE_FILE_SMALL_DATA);
  vector<MovieHash> allMoviesFromFile = setAllMoviesFromFileToVector();

  // teste para Vector STRUCT -> VECTOR É ALOCACAO DINAMICA DE MEMORIA AUTOMATICA
  // "The vector uses dynamic memory allocation internally."

  MovieHash movie1;
  movie1.movieId = 1;
  movie1.year = 1995;
  movie1.title = "Toy Story";
  movie1.genres = "Adventure|Animation|Children|Comedy|Fantasy";

  cout << "movieId: " << movie1.movieId << endl
        << "title: " << movie1.title << endl
        << "genres: " << movie1.genres << endl
        << "year: " << movie1.year << endl;

  movie1.formatGenres = splitStringIntoNewVectorBySeparator(movie1.genres, "|");

  for(int i = 0; i < movie1.formatGenres.size(); i++){
      cout << i + 1 << " -> " << movie1.formatGenres.at(i) << endl;
  }


  return 0;
}