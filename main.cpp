#include "expressions.h"

using namespace expression;
/*here is a comment */
int main(int argc, char* argv[]) {

  // Constant
  auto c = std::unique_ptr<Expression>{new Constant(5)};
  auto c_d = c->derivate();
  std::cout << *c << std::endl;
  std::cout << *c_d << std::endl;

  // Variable
  auto v = std::unique_ptr<Expression>{new Variable{'y'}};
  auto v_d = v->derivate('y');
  std::cout << *v << std::endl;
  std::cout << *v_d << std::endl;

  // Sum
  auto s = std::unique_ptr<Expression>{new Sum{
                std::unique_ptr<Expression>{new Constant{5}},
                std::unique_ptr<Expression>{new Variable('z')}}
  };
  auto s_d = s->derivate('z');
  std::cout << *s << std::endl;
  std::cout << *s_d << std::endl;
  std::cout << s->evaluate(10) << std::endl;

  // Product
  auto p = std::unique_ptr<Product>{new Product{
                std::unique_ptr<Expression>{new Constant{5}},
                std::unique_ptr<Expression>{new Variable('z')}}
  };
  auto p_d = p->derivate('z');
  std::cout << *p << std::endl;
  std::cout << *p_d << std::endl;
  return 0;
}
