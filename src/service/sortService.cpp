#include "../header/sortHeader.hpp"

int partitionReviews(vector<Review>& arr, int low, int high) {
    auto pivot = arr[high].rating; 
    int i = low - 1; 

    for (int j = low; j < high; j++) {
        
        if (arr[j].rating > pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }

    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

int partitionMovies(vector<MovieReviewed>& arr, int low, int high) {
    auto pivot = arr[high].movie.rating; 
    int i = low - 1; 

    for (int j = low; j < high; j++) {
        
        if (arr[j].movie.rating > pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }

    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

void firstSort(vector<Review>& reviews, int low, int high) {
    if (low < high) {
        int pi = partitionReviews(reviews, low, high);

        // Recursivamente ordena os subvetores
        firstSort(reviews, low, pi - 1);
        firstSort(reviews, pi + 1, high);
    }
}

void secondSort(vector<MovieReviewed>& movieR) {
    int low = 0, high = 1;
    while (high < movieR.size()) {
        if(movieR[low].userRating == movieR[high].userRating) {
            high++;
        } else {
            quickSortMovies(movieR, low, high - 1);
            low = high;
            high++;
        }
    }
}

void quickSortMovies(vector<MovieReviewed>& movieR, int low, int high) {
    if (low < high) {
        int pi = partitionMovies(movieR, low, high);

        // Recursivamente ordena os subvetores
        quickSortMovies(movieR, low, pi - 1);
        quickSortMovies(movieR, pi + 1, high);
    }
}