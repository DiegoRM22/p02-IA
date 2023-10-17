#include <iostream>

class Square {
 public:

  Square() : identifier_(' ') {}
  Square(char identifier) : identifier_(identifier) {}
  char getIdentifier() const { return identifier_; }


 private:
  char identifier_;
};

