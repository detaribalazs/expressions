#include <iostream>

namespace expression {

class Expression {
  public:
    Expression() = default;
    virtual ~Expression() {};
  public:
    double evaluate(double x) const {
      return do_evaluation(x);
    }
    std::ostream& print(std::ostream& os) const {
        return do_print(os);
    }
    Expression* clone() const {
        return do_clone();
    }
    Expression* derivate(char target='x') const {
        return do_derivate(target);
    }
  private:
    virtual double do_evaluation(double x) const = 0;
    virtual std::ostream& do_print(std::ostream& os) const = 0;
    virtual Expression* do_clone() const = 0;
    virtual Expression* do_derivate(char target) const = 0;
};

inline std::ostream& operator<<(std::ostream& os, const Expression& expression) {
    return expression.print(os);
}

class Constant final : public Expression {
  public:
    Constant(double _c) : c_{_c} {};

  private:
    double c_;
    virtual double do_evaluation(double) const override {
        return c_;
    }
    virtual std::ostream& do_print(std::ostream& os) const override {
        return os << c_;
    }
    virtual Constant* do_clone() const override {
        return new Constant{c_};
    }
    virtual Constant* do_derivate(char) const override {
        return new Constant{0};
    }
};

class Variable : public Expression {
  public:
    Variable(char _var = 'x') : var_{_var} {};
  
  private:
    char var_;
    virtual double do_evaluation(double x) const override {
        return x;
    };
    virtual std::ostream& do_print(std::ostream& os) const override {
        return os << var_;
    };
    virtual Variable* do_clone() const override {
        return new Variable{var_};
    }
    virtual Expression* do_derivate(char target) const override {
        if (target == var_)
            return new Constant{1};
        else 
            return new Variable{var_};
    }
};

class TwoOperand : public Expression {
  public:
    TwoOperand(Expression* lhs, Expression* rhs) 
    : lhs_{lhs}, rhs_{rhs} {}
    TwoOperand(TwoOperand& other) = delete;
    TwoOperand& operator=(TwoOperand&) = delete;
    TwoOperand() = delete;
    virtual ~TwoOperand() {
      delete rhs_;
      delete lhs_;
    }
  protected:
    Expression* lhs_;
    Expression* rhs_;
  protected:
    virtual double do_operation(double, double) const = 0;
    virtual char print_symbol() const = 0;
    virtual TwoOperand* do_specific_derivate(char) const = 0;
    virtual TwoOperand* do_specific_clone() const = 0;
  private:
    virtual double do_evaluation(double x) const override final{
      return do_operation(rhs_->evaluate(x), lhs_->evaluate(x));
    };
    virtual std::ostream& do_print(std::ostream& os) const override final {
        return os << *lhs_ << " " << print_symbol() << " " << *rhs_;
    }
    virtual TwoOperand* do_clone() const override final {
        return do_specific_clone(); 
    }
    virtual TwoOperand* do_derivate(char target) const override final {
        return do_specific_derivate(target);
    }
};

class Sum final : public TwoOperand {
  public: using TwoOperand::TwoOperand;
  private:
    virtual double do_operation(double rhs, double lhs) const override {
        return rhs + lhs;
    }
    virtual char print_symbol() const override {
        return '+';
    }
    virtual TwoOperand* do_specific_derivate(char target) const override {
        return new Sum{lhs_->derivate(target), rhs_->derivate(target)};
    }
    virtual TwoOperand* do_specific_clone() const override {
        return new Sum{lhs_->clone(), rhs_->clone()};
    }
};

class Product final: public TwoOperand {
  public: using TwoOperand::TwoOperand;
  private:
    virtual double do_operation(double rhs, double lhs) const override {
        return rhs * lhs;
    }
    virtual char print_symbol() const override {
        return '*';
    }
    virtual TwoOperand* do_specific_derivate(char target) const override {
        return new Sum{
            new Product{
                lhs_->derivate(target), rhs_->clone()
            },
            new Product{
                lhs_->clone(), rhs_->derivate(target)
            }
        };
    }
    virtual TwoOperand* do_specific_clone() const override {
        return new Product{lhs_->clone(), rhs_->clone()};
    }
};

} // end of namespace expression