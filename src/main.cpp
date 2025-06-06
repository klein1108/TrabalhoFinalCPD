#include "header/fileHeader.hpp"
#include "header/hashHeader.hpp"
#include "header/constants.hpp"

int main(){
  auto start = chrono::high_resolution_clock::now();

  //Estrutura 1: Armazenando Dados Sobre filmes
  vector<Movie> allMoviesFromFile = setAllMoviesFromFileToVector();
  vector<unique_ptr<MovieHash>> moviesHashTable = createMoviesHashTable(allMoviesFromFile);  

  //Estrutura 2: Estrutura para buscas por strings de nomes

  //(...)

  //Estrutura 3: Estrutura para guardar revis˜ oes de usu´ arios
  vector<Review> allReviews = setAllReviewsFromFileToVectorAndHandleRatings(moviesHashTable);  // 35 segundos
  setMovieHashTableRatingsBySumPerCounting(moviesHashTable);

  auto end0 = chrono::high_resolution_clock::now();
  chrono::duration<double> duration0 = end0 - start;
  cout << duration0.count() << " segundos" << endl <<endl;


  //Estrutura 3: Estrutura para guardar revisões de usuários
  unordered_map<int, unique_ptr<UserReviewHash>> userReviewHashTable = createUserReviewHashTable(allReviews, moviesHashTable); // 76 segundos


  //Estrutura 4: Estrutura para guardar tags

  //(...)

  auto end1 = chrono::high_resolution_clock::now();
  chrono::duration<double> duration1 = end1 - end0;
  cout << duration1.count() << " segundos" << endl <<endl;

  auto endFinal = chrono::high_resolution_clock::now();
  chrono::duration<double> durationFinal = endFinal - start;
  cout << "Tempo de execucao de tudo: " << durationFinal.count() << " segundos" << endl <<endl;

  return 0;
}