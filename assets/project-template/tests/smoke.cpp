#include "interpreter/core.hpp"

#include <cassert>

int main() {
  lang::Environment environment;
  environment.define("answer", 42.0);
  const auto value = environment.get("answer");
  assert(value && std::get<double>(*value) == 42.0);
}
