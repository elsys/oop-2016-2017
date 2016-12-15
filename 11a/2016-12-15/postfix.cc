#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

class CalculatorError {
    string message_;
public:
    CalculatorError(string message)
            : message_(message) {
    }

    string get_message() const {
        return message_;
    }
};

class Context {
    vector<double> values;
public:
    double pop() {
        if (values.empty()) {
            throw CalculatorError("stack empty");
        }
        double value = values.back();
        values.pop_back();
        return value;
    }
    void push(double val) {
        values.push_back(val);
    }
    int size() const {
        return values.size();
    }

    double peek() const {
        return values.back();
    }
};

class Operation {
    string symbol_;
public:
    Operation(string symbol)
            : symbol_(symbol) {
    }
    virtual ~Operation() {

    }

    virtual void execute(Context& context) const = 0;

    string get_symbol() const {
        return symbol_;
    }
};

class UnaryOperation: public Operation {
public:
    UnaryOperation(string symbol)
            : Operation(symbol) {
    }
};

class BinaryOperation: public Operation {
public:
    BinaryOperation(string symbol)
            : Operation(symbol) {
    }

    void execute(Context& context) const {
        if (context.size() < 2) {
            throw CalculatorError("not enough values...");
        }
        double value1 = context.pop();
        double value2 = context.pop();
        context.push(eval(value1, value2));
    }

protected:
    virtual double eval(double value1, double value2) const = 0;
};

class Plus: public BinaryOperation {
public:
    Plus()
            : BinaryOperation("+") {
    }
protected:
    double eval(double value1, double value2) const {
        return value1 + value2;
    }
};

class Minus: public BinaryOperation {
public:
    Minus()
            : BinaryOperation("-") {
    }
protected:
    double eval(double value1, double value2) const {
        return value1 - value2;
    }
};

class Calculator {
// 1. easily switch to different input streams
// 2. easily add new operations
    vector<Operation*> operations_;
    Context context;

    Operation* get_operation(string symbol) {
        for (vector<Operation*>::iterator it = operations_.begin();
                it != operations_.end(); it++) {
            if ((*it)->get_symbol() == symbol) {
                return *it;
            }
        }
        return 0;
    }

public:

    void run(istream& in, ostream& out) {
        while (1) {
            out << "values(" << context.size() << "): ";
            string input;
            in >> input;

            if (!in) {
                break;
            }

            Operation* operation = get_operation(input);
            if (operation) {
                try {
                    operation->execute(context);
                    cout << "res> " << context.peek() << endl;

                } catch (const CalculatorError& ex) {
                    cerr << ">>> error in executing "
                            << operation->get_symbol()
                            << "; "
                            << ex.get_message()
                            << endl;
                }
            } else {
                // is it a double?
                double new_value;
                stringstream istr(input);
                istr >> new_value;
                if (istr) {
                    context.push(new_value);
                } else {
                    throw CalculatorError("unknown operation...");
                }
            }
        }
    }

    void addOperation(Operation* operation) {
        operations_.push_back(operation);
    }
};

int main() {
    Calculator calc;
    calc.addOperation(new Plus());
    calc.addOperation(new Minus());
    try {
        calc.run(cin, cout);
    } catch (CalculatorError err) {
        cout << err.get_message() << endl;
    }
    return 0;
}

