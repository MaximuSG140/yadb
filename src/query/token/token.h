#ifndef YADB_TOKEN_H
#define YADB_TOKEN_H
#include <iostream>

namespace query {
enum class Type {
  Keyword,
  IntNumber,
  FloatNumber,
  String,
  OpeningRoundBracket,
  ClosingRoundBracket
};

class Token {
 private:
  const Type type;
  const char *begin;
  const char *end;
 public:
  Token(const Type type, const char *begin, const char *end);
  const Type getType();
  const pair<const char *, const char *> getPosition();
};

}

#endif //YADB_TOKEN_H
