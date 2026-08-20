#include "interpreter/core.hpp"

#include <stdexcept>
#include <type_traits>

namespace lang {

std::vector<Token> Scanner::scan(std::vector<Diagnostic>&) {
  return {{TokenType::eof_token, {source_.size(), source_.size(), 1, source_.size() + 1}, {}}};
}

std::optional<Expr> Parser::parse_expression(std::vector<Diagnostic>&) {
  if (tokens_.empty()) return std::nullopt;
  return Expr{LiteralExpr{Nil{}, tokens_.front().span}};
}

void Environment::define(std::string name, Value value) {
  values_.insert_or_assign(std::move(name), std::move(value));
}

std::optional<Value> Environment::get(std::string_view name) const {
  if (const auto found = values_.find(std::string{name}); found != values_.end()) return found->second;
  return enclosing_ ? enclosing_->get(name) : std::nullopt;
}

Value Interpreter::evaluate(const Expr& expression) {
  return std::visit([](const auto& node) -> Value {
    using T = std::decay_t<decltype(node)>;
    if constexpr (std::is_same_v<T, LiteralExpr>) return node.value;
    throw std::runtime_error("AST node is a starter interface, not implemented yet");
  }, expression);
}

std::optional<Value> VM::run(const Chunk& chunk, std::vector<Diagnostic>& diagnostics) {
  if (chunk.code.empty()) {
    diagnostics.push_back({DiagnosticPhase::runtime, {}, "empty bytecode chunk"});
    return std::nullopt;
  }
  return Nil{};
}

std::string display(const Value& value) {
  return std::visit([](const auto& item) -> std::string {
    using T = std::decay_t<decltype(item)>;
    if constexpr (std::is_same_v<T, Nil>) return "nil";
    if constexpr (std::is_same_v<T, bool>) return item ? "true" : "false";
    if constexpr (std::is_same_v<T, double>) return std::to_string(item);
    if constexpr (std::is_same_v<T, std::string>) return item;
    return "<object>";
  }, value);
}

}  // namespace lang
