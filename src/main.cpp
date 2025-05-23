#include <iostream>
#include "../parser-master/parser.hpp"

using namespace aria::csv;

using namespace std;

int main() {
  std::ifstream f("../datas/dados-pequeno/miniratings.csv");
  CsvParser parser(f);
}