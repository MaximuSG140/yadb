#include "token.h"

namespace query {
Token::Token(const Type type, const char *begin, const char *end) {
  this->type = type;
  this->begin = begin;
  this->end = end;
}

const Type Token::getType() {
  return this->type;
}

const pair<const char *, const char *> Token::getPosition() {
  return make_pair(this->begin, this->end);
}
}