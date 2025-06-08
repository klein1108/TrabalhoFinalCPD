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

void printUserById(const vector<User>& users, int searchId) {
    for (const auto& user : users) {
        if (user.userId == searchId) {
            cout << "User ID: " << user.userId << endl;
            cout << "Reviews:" << endl;
            for (const auto& review : user.reviews) {
                cout << "  Movie ID: " << review.movieId
                     << ", Rating: " << review.rating
                     << ", Date: " << review.date << endl;
            }
            cout << "------------------------" << endl;
            return;
        }
    }
    cout << "User with ID " << searchId << " not found." << endl;
}