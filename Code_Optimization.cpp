#include <iostream>
#include <string>
#include <map>
#include <stack>
#include <sstream>
using namespace std;
map<char, int> variables;
int evaluateExpression(const string &expr)
{
    stack<int> operands;
    stack<char> operators;
    istringstream iss(expr);
    char token;
    while (iss >> token)
    {
        if (isdigit(token))
        {
            operands.push(token - '0');
        }
        else if (isalpha(token))
        {
            operands.push(variables[token]);
        }
        else if (token == '+' || token == '-')
        {
            while (!operators.empty() && (operators.top() == '+' || operators.top() == '-' ||
                                          operators.top() == '*' || operators.top() == '/'))
            {
                char op = operators.top();
                operators.pop();
                int operand2 = operands.top();
                operands.pop();
                int operand1 = operands.top();
                operands.pop();
                if (op == '+')
                    operands.push(operand1 + operand2);
                else
                    operands.push(operand1 - operand2);
            }
            operators.push(token);
        }
        else if (token == '*' || token == '/')
        {
            while (!operators.empty() && (operators.top() == '*' || operators.top() == '/'))
            {
                char op = operators.top();
                operators.pop();
                int operand2 = operands.top();
                operands.pop();
                int operand1 = operands.top();
                operands.pop();
                if (op == '*')
                    operands.push(operand1 * operand2);
                else
                    operands.push(operand1 / operand2);
            }
            operators.push(token);
        }
    }
    while (!operators.empty())
    {
        char op = operators.top();
        operators.pop();
        int operand2 = operands.top();
        operands.pop();
        int operand1 = operands.top();
        operands.pop();
        if (op == '+')
            operands.push(operand1 + operand2);
        else if (op == '-')
            operands.push(operand1 - operand2);
        else if (op == '*')
            operands.push(operand1 * operand2);
        else
            operands.push(operand1 / operand2);
    }
    return operands.top();
}
int main()
{
    int numExpressions;
    cout << "Enter the number of expressions: ";
    cin >> numExpressions;
    cin.ignore();
    for (int i = 1; i <= numExpressions; ++i)
    {
        string expression;
        cout << "Enter expression " << i << ": ";
        getline(cin, expression);
        char variable = expression[0];
        string exprToEvaluate = expression.substr(expression.find('=') + 1);
        int result = evaluateExpression(exprToEvaluate);
        variables[variable] = result;
    }

    for (auto &pair : variables)
    {
        cout << pair.first << "=" << pair.second << endl;
    }
    return 0;
}