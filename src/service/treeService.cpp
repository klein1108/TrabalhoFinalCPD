#include "../header/treeHeader.hpp"

//MOVIE TERNARY SEARCH TREE

void insertTST(TernarySearchTree*& node, const Movie& movie, int pos) {
  if (!node) {
    node = new TernarySearchTree();
    node->letter = tolower(movie.title[pos]);
    node->left = node->next = node->right = nullptr;
    node->movieId = NO_WORD_RELATED;
    node->movie = nullptr;
  }

  char c = tolower(movie.title[pos]);
  if (c < node->letter) {
      insertTST(node->left, movie, pos);
  } else if (c > node->letter) {
      insertTST(node->right, movie, pos);
  } else {
    if (pos + 1 == movie.title.size()) {
      node->movieId = movie.movieId;
      node->movie = &movie;
      // cout << "FILME -> " << node->movie->title << endl;
    } else {
      // cout << "LETRA: " << node->letter << endl;
      insertTST(node->next, movie, pos + 1);
    }
  }
}

// Função principal para criar a TST a partir do vetor de filmes
unique_ptr<TernarySearchTree> setTernarySearchTreeByMovieNames(const vector<Movie>& movies) {
  TernarySearchTree* root = nullptr;

  for (const Movie& movie : movies) {
      if (!movie.title.empty()) {
        insertTST(root, movie, 0);
      }
  }

  cout << "All the movie names were successfuly allocated" << endl;
  return unique_ptr<TernarySearchTree>(root);
}

// Função auxiliar para coletar todos os filmes a partir de um nó
void collectMovies(TernarySearchTree* node, vector<Movie>& results) {
  if (!node) return;

  collectMovies(node->left, results);

  if (node->movieId != NO_WORD_RELATED && node->movie != nullptr) {
      results.push_back(*(node->movie));
  }

  collectMovies(node->next, results);
  collectMovies(node->right, results);
}

// Função principal de busca por prefixo, retorna vector<Movie>
vector<Movie> searchMoviesByPrefix(TernarySearchTree* root, const string& prefix) {
  vector<Movie> results;
  TernarySearchTree* node = root;
  int pos = 0;

  while (node && pos < prefix.size()) {
    char c = tolower(prefix[pos]);

    if (c < node->letter) {
      node = node->left;

    } else if (c > node->letter) {
      node = node->right;

    } else {
      if (pos + 1 == prefix.size()) {
        if (node->movieId != NO_WORD_RELATED && node->movie != nullptr) {
          results.push_back(*(node->movie));
        }

        collectMovies(node->next, results);
        break;
      }
      node = node->next;
      pos++;
    }
  }
  return results;
}

void printAllMovieNamesFilteredByPrefix(vector<Movie> moviesFilteredByPrefix){

  for (const auto& movie : moviesFilteredByPrefix) {
    cout << movie.movieId << " | " 
    << movie.title << " | " 
    << movie.genres << " | " 
    << movie.year << " | " 
    << endl;
  }
}

//TAGS TERNARY SEARCH TREE
//=======================================================================================================================

// Função para criar a TST de tags
unique_ptr<TagsTST> setTernarySearchTreeByTags(const vector<Tag>& tags) {
  unique_ptr<TagsTST> root = nullptr;

  for (const Tag& tag : tags) {
      if (!tag.tag.empty()) {
        insertTagsTst(root, tag, 0);
      }
  }

  cout << "All the tags were successfuly allocated" << endl;
  return root;
}

// Função auxiliar para inserir tags na TST
void insertTagsTst(unique_ptr<TagsTST>& node, const Tag& tag, int pos) {
  char c = tolower(tag.tag[pos]);
  
  if (!node) {
    node = make_unique<TagsTST>();
    node->letter = c;
    node->leafFlag = false;
  }
  if (c < node->letter) {
    insertTagsTst(node->left, tag, pos);
} else if (c > node->letter) {
    insertTagsTst(node->right, tag, pos);
} else {
    if (pos + 1 == tag.tag.size()) {
        node->leafFlag = true;
        node->movieIds.push_back(tag.movieId);
    } else {
        insertTagsTst(node->next, tag, pos + 1);
    }
}
}
