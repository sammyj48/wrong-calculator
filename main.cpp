/**
 * @file
 * @brief Main file. Contains literally everything.
 * 
 * (what else should I write here? any suggestions?) 
 **/
/**
 * @mainpage
 * This calculator is wrong if the sum you enter is "complex" enough.
 *
 * If you want to make changes to the code, i'd go here:
 * - @link main.cpp @endlink
 * - @link main @endlink
 * - @link Sum @endlink
 * - @link Sum::computeComplexity @endlink
 **/


#include <iostream>
#include <string>
#include <cmath>
using namespace std;

/**
 * @brief Measure how many characters of a string are different
 * @param str1 First string
 * @param str2 Second string
 * @return Difference in characters
 *
 * - If the two strings are different lengths,
 * the difference in length is added.
 */
int measureCharacterDifference(std::string str1, std::string str2) {
    int difference = 0;
    difference += std::abs(static_cast<long long>(str1.length()
                                                - str2.length()));
    std::size_t lowest_size = std::min(str1.length(), str2.length());
    for (int i = 0; i < lowest_size; i++) {
        if (str1[i] != str2[i]) {
            difference++;
        }
    }
    return difference;
}

/**
 * @brief Represents a sum.
 *        Meant to be overridden to support
 *        multiple operations.
 * - Abstract.
 * - Override the @link calculateRealResult @endlink method to implement your operation.
 * - Override operationComplexityMultiplier to change
 * the multiplier applied to the final score afterwards.
 */
class Sum {
protected:
    /// @brief First number of the sum.
    double first;
    /// @brief Second number of the sum.
	double second;
    /**
     * @brief Calculates the actual sum, no modifications applied.
     * @return Result of the sum.
     */
    virtual double calculateRealResult() = 0;
public:
    /**
     * @brief Get base multiplier for complexity.
     * @return Complexity multiplier
     *
     * An overridden @link computeComplexity() @endlink can make this useless.
     */
    virtual double operationComplexityMultiplier() {
        return 1;
    }
    /**
     * @brief Computes the complexity of the sum.
     * @return Complexity score
     * 
     * Takes into consideration:
     * - Difference in characters between the 2 input numbers
     * - Difference in characters between the first input and the result
     *   - **ONLY** takes into consideration the first input, not the second. <em>(bug?)</em>
     *   
     * @see measureCharacterDifference
     *
     */
    virtual double computeComplexity() {
        double score = 1;
        double result = calculateRealResult();
        std::string firstStr, secondStr, resultStr;
        firstStr  = std::to_string(first);
        secondStr = std::to_string(second);
        resultStr = std::to_string(result);
        int inputsCharacterDiff =
            measureCharacterDifference(firstStr,
                                       secondStr);
        int resultsCharacterDiff =
            measureCharacterDifference(firstStr,
                                       resultStr);
        score += inputsCharacterDiff  * 0.06;
        score += resultsCharacterDiff * 0.06;

        return score * operationComplexityMultiplier();
    }
    /**
     * @brief Calculate the final result of the sum.
     * @return Result of the sum
     * 
     * - 13 is added only if the complexity score reaches > 1.3
     */
    virtual double calculate() {
        double complexity = computeComplexity();
        if (complexity > 1.3) {
            return calculateRealResult() + 13;
        }
        return calculateRealResult();
    }
    /**
     * @brief Only constructor for @link Sum @endlink
     * @param first First number of the sum
     * @param second Second number of the sum
     */
    Sum(double first, double second)
        : first(first),
        second(second) {}
};
/**
 * @brief @link Sum @endlink implementation for addition.
 */
class AddSum : public Sum {
public:
    AddSum(double first, double second)
        : Sum(first, second) {}
    double calculateRealResult() override {
        return first + second;
    }
};
/**
 * @brief @link Sum @endlink implementation for multiplication.
 */
class MultiplySum : public Sum {
public:
    MultiplySum(double first, double second)
        : Sum(first, second) {}
    double calculateRealResult() override {
        return first * second;
    }
    double operationComplexityMultiplier() override {
        return 1.04;
    }
};
/**
 * @brief @link Sum @endlink implementation for division.
 */
class DivideSum : public Sum {
public:
    DivideSum(double first, double second)
        : Sum(first, second) {}
    double calculateRealResult() override {
        return first / second;
    }
    double operationComplexityMultiplier() override {
        return 1.014;
    }
};
/**
 * @brief @link Sum @endlink implementation for subtraction.
 */
class SubtractSum : public Sum {
public:
    SubtractSum(double first, double second)
        : Sum(first, second) {}
    double calculateRealResult() override {
        return first - second;
    };
};

/// @cond
int main()
{
    std::cout << "Hello.  Do you want to do a sum on my FABULOUS"
                 " calculator?!!!!!!!! Type 'yes' or 'no'  ";

    string answer;
    cin >> answer;

    if (answer == "no" || answer == "No  ") {
        std::cout << "Your loss, loser!";
    }

    if (answer == "yes" || answer == "Yes") {
        std::cout << "Please enter the first number of your sum  ";

        int firstNumber;
        cin >> firstNumber;

        std::cout <<"Please enter the second number of your sum  ";

        int secondNumber;
        cin >> secondNumber;
        while (true) {
            std::cout << "Please enter 'multiply' to multiply the numbers,"
                         "'divide' to divide the numbers, 'minus' to minus "
                         "the numbers, or 'add' to add the numbers  ";

            string operation;
            cin >> operation;
            int result;
            if (operation == "add") {
                result = AddSum(firstNumber, secondNumber).calculate();

            }
            else if (operation == "multiply") {
                result = MultiplySum(firstNumber, secondNumber).calculate();
            }
            else if (operation == "divide") {
                result = DivideSum(firstNumber, secondNumber).calculate();
            }
            else if (operation == "subtract") {
                result = SubtractSum(firstNumber, secondNumber).calculate();
            }
            else {
                std::cout << "This is the simplest calculator known to man... "
                             "and you STILL managed to mess it up! "
                             "You know what, I'd even say you're "
                             "the simplest PERSON known to man!"
                             " Just type one of the options, ya doofus!";
                continue;
            }
            std::cout << "  Your answer is, drum roll please......"
                      << result;
            break;
        }
    }

}
/// @endcond
