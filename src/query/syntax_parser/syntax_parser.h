#ifndef YADB_SYNTAX_PARSER_H
#define YADB_SYNTAX_PARSER_H
#include <vector>
#include "query/token/token.h"

namespace query {
class SyntaxParser {
 private:
  const std::vector<Token> tokens;
 public:
  SyntaxParser(const std::vector<Token> tokens);

};
}

#endif //YADB_SYNTAX_PARSER_H
