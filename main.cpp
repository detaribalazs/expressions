#include "expressions.h"

using namespace expression;

int main(int argc, char* argv[]) {

  // Constant
  Expression* c = new Constant(5);
  Expression* c_d = c->derivate();
  std::cout << *c << std::endl;
  std::cout << *c_d << std::endl;
  delete c;
  delete c_d;

  // Variable
  Expression* v = new Variable{'y'};
  Expression* v_d = v->derivate('y');
  std::cout << *v << std::endl;
  std::cout << *v_d << std::endl;
  delete v;
  delete v_d;

  // Sum
  Expression *s = new Sum{new Constant{5}, new Variable('z')};
  Expression *s_d = s->derivate('z');
  std::cout << *s << std::endl;
  std::cout << *s_d << std::endl;
  std::cout << s->evaluate(10) << std::endl;
  delete s;
  delete s_d;

  // Product
  Expression *p = new Product{new Constant{5}, new Variable('z')};
  Expression *p_d = p->derivate('z');
  std::cout << *p << std::endl;
  std::cout << *p_d << std::endl;
  delete p;
  delete p_d;

  return 0;
}