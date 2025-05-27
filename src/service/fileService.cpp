#include "../headers/fileService.hpp"

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