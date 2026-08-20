#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <optional>
#include <string>
#include <string_view>
#include <unordered_map>
#include <variant>
#include <vector>

namespace lang {

struct Nil final {};
inline bool operator==(Nil, Nil) noexcept { return true; }

struct SourceSpan final {
  std::size_t begin{};
  std::size_t end{};
  std::size_t line{1};
  std::size_t column{1};
};

enum class DiagnosticPhase { lexical, syntactic, resolution, compilation, runtime };
struct Diagnostic final {
  DiagnosticPhase phase{};
  SourceSpan span{};
  std::string message;
};

enum class TokenType : std::uint16_t {
  left_paren, right_paren, plus, minus, star, slash,
  identifier, string, number, var_kw, print_kw, eof_token
};

using Literal = std::variant<std::monostate, double, std::string>;
struct Token final { TokenType type{}; SourceSpan span{}; Literal literal{}; };

class Scanner final {
 public:
  explicit Scanner(std::string_view source) : source_(source) {}
  [[nodiscard]] std::vector<Token> scan(std::vector<Diagnostic>& diagnostics);
 private:
  std::string_view source_;
};

struct Object;
using ObjectHandle = std::shared_ptr<Object>;
using Value = std::variant<Nil, bool, double, std::string, ObjectHandle>;

struct LiteralExpr final { Value value; SourceSpan span; };
struct UnaryExpr;
struct BinaryExpr;
using Expr = std::variant<LiteralExpr, std::unique_ptr<UnaryExpr>, std::unique_ptr<BinaryExpr>>;
struct UnaryExpr final { Token op; Expr right; };
struct BinaryExpr final { Expr left; Token op; Expr right; };

class Parser final {
 public:
  explicit Parser(const std::vector<Token>& tokens) : tokens_(tokens) {}
  [[nodiscard]] std::optional<Expr> parse_expression(std::vector<Diagnostic>& diagnostics);
 private:
  const std::vector<Token>& tokens_;
  std::size_t current_{};
};

class Environment final {
 public:
  explicit Environment(std::shared_ptr<Environment> enclosing = {})
      : enclosing_(std::move(enclosing)) {}
  void define(std::string name, Value value);
  [[nodiscard]] std::optional<Value> get(std::string_view name) const;
 private:
  std::unordered_map<std::string, Value> values_;
  std::shared_ptr<Environment> enclosing_;
};

class Interpreter final {
 public:
  [[nodiscard]] Value evaluate(const Expr& expression);
};

enum class OpCode : std::uint8_t { constant, add, subtract, multiply, divide, return_ };
struct Chunk final {
  std::vector<std::uint8_t> code;
  std::vector<Value> constants;
  std::vector<SourceSpan> source_map;
};

class VM final {
 public:
  [[nodiscard]] std::optional<Value> run(const Chunk& chunk,
                                         std::vector<Diagnostic>& diagnostics);
 private:
  std::vector<Value> stack_;
};

[[nodiscard]] std::string display(const Value& value);

}  // namespace lang
