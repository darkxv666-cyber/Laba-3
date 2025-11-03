#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <sstream>
#include <locale>

class ILoggable {
public:
    virtual void logToScreen() = 0;
    virtual void logToFile(const std::string& filename) = 0;
    virtual ~ILoggable() = default;
};

class IShuffle {
public:
    virtual void shuffle() = 0;
    virtual void shuffle(size_t i, size_t j) = 0;
    virtual ~IShuffle() = default;
};

class ExpressionEvaluator : public ILoggable {
protected:
    double* operands;
    size_t count;

    std::string numberToString(double num) const {
        std::ostringstream oss;
        if (num == static_cast<int>(num)) {
            oss << static_cast<int>(num);
        }
        else {
            oss << std::fixed << std::setprecision(1);
            oss << num;
        }

        std::string result = oss.str();
        if (num < 0) {
            return "(" + result + ")";
        }
        return result;
    }

public:
    ExpressionEvaluator(size_t n = 20) : count(n) {
        operands = new double[n];
        for (size_t i = 0; i < n; ++i) {
            operands[i] = 0.0;
        }
    }

    virtual ~ExpressionEvaluator() {
        delete[] operands;
    }

    void setOperand(size_t pos, double value) {
        if (pos < count) {
            operands[pos] = value;
        }
    }

    void setOperands(double ops[], size_t n) {
        size_t copyCount = std::min(n, count);
        for (size_t i = 0; i < copyCount; ++i) {
            operands[i] = ops[i];
        }
    }

    virtual double calculate() = 0;
};

class Divisor : public ExpressionEvaluator {
public:
    Divisor(size_t n = 20) : ExpressionEvaluator(n) {}

    double calculate() override {
        if (count == 0) return 0;
        double result = operands[0];
        for (size_t i = 1; i < count; ++i) {
            if (operands[i] == 0) return 0;
            result /= operands[i];
        }
        return result;
    }

    void logToScreen() override {
        std::string expr = getExpressionString();
        std::cout << expr << " < Total " << count << " >" << std::endl;
    }

    void logToFile(const std::string& filename) override {
        std::ofstream file(filename, std::ios::app);
        std::string expr = getExpressionString();
        file << expr << " < Total " << count << " >" << std::endl;
        file.close();
    }

private:
    std::string getExpressionString() const {
        if (count == 0) return "";
        std::string result = numberToString(operands[0]);
        for (size_t i = 1; i < count; ++i) {
            result += " / " + numberToString(operands[i]);
        }
        return result;
    }
};

class CustomExpressionEvaluator : public ExpressionEvaluator, public IShuffle {
public:
    CustomExpressionEvaluator(size_t n = 20) : ExpressionEvaluator(n) {}

    double calculate() override {
        if (count == 0) return 0;
        double result = operands[0];
        for (size_t i = 1; i < count - 1; i += 2) {
            result += operands[i] * operands[i + 1];
        }
        return result;
    }

    void logToScreen() override {
        std::string expr = getExpressionString();
        std::cout << expr << " < Total " << count << " >" << std::endl;
    }

    void logToFile(const std::string& filename) override {
        std::ofstream file(filename, std::ios::app);
        std::string expr = getExpressionString();
        file << expr << " < Total " << count << " >" << std::endl;
        file.close();
    }

    void shuffle() override {
        std::sort(operands, operands + count);
    }

    void shuffle(size_t i, size_t j) override {
        if (i >= count || j >= count) return;
        double i_fract = std::abs(operands[i] - std::floor(std::abs(operands[i])));
        double j_fract = std::abs(operands[j] - std::floor(std::abs(operands[j])));
        if (i_fract > 0 || j_fract > 0) {
            std::swap(operands[i], operands[j]);
        }
    }

private:
    std::string getExpressionString() const {
        if (count == 0) return "";
        std::string result = numberToString(operands[0]);
        for (size_t i = 1; i < count - 1; i += 2) {
            result += " + " + numberToString(operands[i]) + "*" +
                numberToString(operands[i + 1]);
        }
        return result;
    }
};

class Multiplier : public ExpressionEvaluator, public IShuffle {
public:
    Multiplier(size_t n = 20) : ExpressionEvaluator(n) {}

    double calculate() override {
        double result = 1.0;
        for (size_t i = 0; i < count; ++i) {
            result *= operands[i];
        }
        return result;
    }

    void logToScreen() override {
        std::string expr = getExpressionString();
        std::cout << expr << " < Total " << count << " >" << std::endl;
    }

    void logToFile(const std::string& filename) override {
        std::ofstream file(filename, std::ios::app);
        std::string expr = getExpressionString();
        file << expr << " < Total " << count << " >" << std::endl;
        file.close();
    }

    void shuffle() override {
        std::sort(operands, operands + count);
    }

    void shuffle(size_t i, size_t j) override {
        if (i >= count || j >= count) return;
        double i_fract = std::abs(operands[i] - std::floor(std::abs(operands[i])));
        double j_fract = std::abs(operands[j] - std::floor(std::abs(operands[j])));
        if (i_fract > 0 || j_fract > 0) {
            std::swap(operands[i], operands[j]);
        }
    }

private:
    std::string getExpressionString() const {
        if (count == 0) return "";
        std::string result = numberToString(operands[0]);
        for (size_t i = 1; i < count; ++i) {
            result += " * " + numberToString(operands[i]);
        }
        return result;
    }
};

int main() {
    setlocale(LC_ALL, "Russian");

    ExpressionEvaluator* evaluators[3];

    evaluators[0] = new Divisor(4);
    evaluators[0]->setOperand(0, 150);
    evaluators[0]->setOperand(1, -3);
    evaluators[0]->setOperand(2, 10);
    evaluators[0]->setOperand(3, -2.5);

    evaluators[1] = new CustomExpressionEvaluator(5);
    double custom_ops[] = { 5, 16, -3, 10, 12 };
    evaluators[1]->setOperands(custom_ops, 5);

    evaluators[2] = new Multiplier(5);
    double mult_ops[] = { 1.5, 4, -2.5, -8, -15 };
    evaluators[2]->setOperands(mult_ops, 5);

    std::cout << "\nВыражения:\n";
    for (size_t i = 0; i < 3; ++i) {
        evaluators[i]->logToFile("expressions.log");
        evaluators[i]->logToScreen();
        std::cout << "< Result " << evaluators[i]->calculate() << " >\n\n";
    }

    std::cout << "Выражения после перемешивания :\n";
    for (size_t i = 0; i < 3; ++i) {
        IShuffle* shuffleable = dynamic_cast<IShuffle*>(evaluators[i]);
        if (shuffleable) {
            shuffleable->shuffle();
            evaluators[i]->logToScreen();
            std::cout << "< Result " << evaluators[i]->calculate() << " >\n\n";
        }
    }

    for (size_t i = 0; i < 3; ++i) {
        delete evaluators[i];
    }

    return 0;
}