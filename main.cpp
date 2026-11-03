#include <iostream>
#include <stdexcept>
#include <string>
#include <sstream>
#include <vector>
#include <cctype>
using namespace std;
class StackEmpty : public runtime_error {
public:
    StackEmpty() : runtime_error("Stack is empty") {}
};
class StackFull : public runtime_error {
public:
    StackFull() : runtime_error("Stack is full") {}
};
template <typename E>
class ArrayStack {
    E* S;
    int cap;
    int t;
public:
    ArrayStack(int c = 1000) : cap(c), t(-1) {
        if (cap < 1) throw invalid_argument("Capacity must be positive");
        S = new E[cap];
    }
    ArrayStack(const ArrayStack<E>& other) : cap(other.cap), t(other.t) {
        S = new E[cap];
        for (int i = 0; i <= t; i++) S[i] = other.S[i];
    }
    ArrayStack<E>& operator=(const ArrayStack<E>& other) {
        if (this != &other) {
            E* newS = new E[other.cap];
            for (int i = 0; i <= other.t; i++) newS[i] = other.S[i];
            delete[] S;
            S = newS;
            cap = other.cap;
            t = other.t;
        }
        return *this;
    }
    ~ArrayStack() { delete[] S; }
    int size() const { return t + 1; }
    bool empty() const { return t < 0; }
    bool full() const { return t == cap - 1; }
    int capacity() const { return cap; }
    E& top() {
        if (empty()) throw StackEmpty();
        return S[t];
    }
    void push(const E& e) {
        if (full()) throw StackFull();
        S[++t] = e; // Move top up one cell before storing the new item
    }
    void pop() {
        if (empty()) throw StackEmpty();
        t--; // Remove top from the stack by moving t down one cell
    }
};
template <typename E>
class LinkedStack {
    struct Node {
        E elem;
        Node* next;
        Node(const E& e, Node* n) : elem(e), next(n) {}
    };
    Node* head;
    int n;
public:
    LinkedStack() : head(nullptr), n(0) {}
    ~LinkedStack() { while (!empty()) pop(); }
    int size() const { return n; }
    bool empty() const { return n == 0; }
    E& top() {
        if (empty()) throw StackEmpty();
        return head->elem;
    }
    void push(const E& e) {
        head = new Node(e, head); // New node becomes TOP.
        n++;
    }
    void pop() {
        if (empty()) throw StackEmpty();
        Node* old = head;
        head = head->next; // Move TOP to the next node.
        delete old; // Delete the old TOP node.
        n--;
    }
};
bool isOpening(char ch) {
    return ch == '(' || ch == '[' || ch == '{';
}
bool isClosing(char ch) {
    return ch == ')' || ch == ']' || ch == '}';
}
bool isMatch(char open, char close) {
    return (open == '(' && close == ')') ||
           (open == '[' && close == ']') ||
           (open == '{' && close == '}');
}
bool isBalanced(const string& expr) {
    LinkedStack<char> S;
    for (char ch : expr) {
        if (isOpening(ch)) {
            S.push(ch); //Save an opening bracket for its matchig close
        } else if (isClosing(ch)) {
            if (S.empty()) return false;
            char open = S.top();
            S.pop(); //Remove the opening bracket to check its match.
            if (!isMatch(open, ch)) return false;
        }
    }
    return S.empty();
}
// LAB A Problem 2
int safe_pop(ArrayStack<int>& S) {
    try {
        int value = S.top();
        S.pop(); // Remove TOP after saving its value.
        return value;
    } catch (StackEmpty&) {
        cout << "Error: stack is empty" << endl;
        return -1;
    }
}
void safe_push(ArrayStack<int>& S, int value) {
    try {
        S.push(value); // Push the value if there is room.
    } catch (StackFull&) {
        cout << "Error: stack is full" << endl;
    }
}
// LAB A Problem 3
int countElements(ArrayStack<int> S) {
    ArrayStack<int> temp(S.capacity());
    int count = 0;
    while (!S.empty()) {
        temp.push(S.top()); // Copy TOP to the temporary stack for counting.
        S.pop(); // Remove the copied value from the local stack.
        count++;
    }
    while (!temp.empty()) {
        S.push(temp.top()); // Restore the local stack's original order.
        temp.pop(); // Remove TOP after restoring it.
    }
    return count;
}
// LAB A Problem 4
void reverseVector(vector<int>& v) {
    if (v.empty()) return;
    ArrayStack<int> S((int)v.size());
    for (int i = 0; i < (int)v.size(); i++) {
        S.push(v[i]); // Save values so the last value is popped first.
    }
    for (int i = 0; i < (int)v.size(); i++) {
        v[i] = S.top();
        S.pop(); // Remove TOP after writing it into the vector.
    }
}
// LAB B Problem 1
void stress_test(int n) {
    cout << "ArrayStack test, n = " << n << ", capacity = 500" << endl;
    ArrayStack<int> A(500);
    try {
        for (int i = 1; i <= n; i++) {
            A.push(i); // Push each number until the array is full.
        }
    } catch (StackFull&) {
        cout << "StackFull: array capacity reached" << endl;
    }
    while (!A.empty()) A.pop(); // Empty the array stack.
    LinkedStack<int> L;
    for (int i = 1; i <= n; i++) {
        L.push(i); // Add each number as a linked node.
    }
    while (!L.empty()) L.pop(); // Remove all linked nodes from TOP.
    cout << "LinkedStack pushed and popped " << n << " values." << endl;
    try {
        A.pop(); // Test pop on an empty array stack.
    } catch (StackEmpty&) {
        cout << "ArrayStack: StackEmpty caught" << endl;
    }
    try {
        L.pop(); // Test pop on an empty linked stack.
    } catch (StackEmpty&) {
        cout << "LinkedStack: StackEmpty caught" << endl;
    }
}
// LAB B Problem 2
int countMatchedPairs(const string& expr) {
    LinkedStack<char> S;
    int count = 0;
    for (char ch : expr) {
        if (isOpening(ch)) {
            S.push(ch); // Save an opening bracket for matching.
        } else if (isClosing(ch)) {
            if (S.empty()) return -1;
            char open = S.top();
            S.pop(); // Remove TOP to check the bracket pair.
            if (!isMatch(open, ch)) return -1;
            count++;
        }
    }
    if (!S.empty()) return -1;
    return count;
}
// LAB B Problem 3
bool checkLines(const vector<string>& lines) {
    LinkedStack<char> brackets;
    LinkedStack<int> lineNumbers;
    LinkedStack<int> positions;
    for (int i = 0; i < (int)lines.size(); i++) {
        for (int j = 0; j < (int)lines[i].size(); j++) {
            char ch = lines[i][j];
            if (isOpening(ch)) {
                brackets.push(ch); // Save the opening bracket.
                lineNumbers.push(i + 1); // Save its line number.
                positions.push(j + 1); // Save its character position.
            } else if (isClosing(ch)) {
                if (brackets.empty()) {
                    cout << "Not balanced. Extra closing bracket at line "
                         << i + 1 << ", position " << j + 1 << endl;
                    return false;
                }
                char open = brackets.top();
                if (!isMatch(open, ch)) {
                    cout << "Not balanced. Mismatched bracket at line "
                         << i + 1 << ", position " << j + 1 << endl;
                    return false;
                }
                brackets.pop(); // Remove the matching opening bracket.
                lineNumbers.pop(); // Remove its saved line number.
                positions.pop(); // Remove its saved position.
            }
        }
    }
    if (!brackets.empty()) {
        cout << "Not balanced. Unmatched bracket at line "
             << lineNumbers.top() << ", position " << positions.top() << endl;
        return false;
    }
    cout << "Balanced" << endl;
    return true;
}
// LAB B Problem 4
bool isPalindrome(const string& s) {
    LinkedStack<char> S;
    int n = (int)s.length();
    for (int i = 0; i < n / 2; i++) {
        S.push(s[i]); // Save the first half for reverse-order comparison.
    }
    int start = n / 2;
    if (n % 2 == 1) start++; // Skip the middle character for odd lengths.
    for (int i = start; i < n; i++) {
        if (S.empty()) return false;
        char ch = S.top();
        S.pop(); // Remove TOP after retrieving it for comparison.
        if (ch != s[i]) return false;
    }
    return S.empty();
}
// LAB C Problem 1
int applyOperator(int left, int right, char op) {
    if (op == '+') return left + right;
    if (op == '-') return left - right;
    if (op == '*') return left * right;
    if (op == '/') {
        if (right == 0) throw runtime_error("Division by zero");
        return left / right;
    }
    throw runtime_error("Unknown operator");
}
int evaluatePostfix(const string& expr) {
    stringstream ss(expr);
    string token;
    LinkedStack<int> values;
    bool foundToken = false;
    while (ss >> token) {
        foundToken = true;
        if (token.size() == 1 &&
            string("+-*/").find(token[0]) != string::npos) {
            if (values.size() < 2)
                throw runtime_error("Invalid postfix expression");
            int right = values.top();
            values.pop(); // First pop is the right operand.
            int left = values.top();
            values.pop(); // Second pop is the left operand.
            values.push(applyOperator(left, right, token[0])); // Save result.
        } else {
            size_t used = 0;
            int number = stoi(token, &used);
            if (used != token.size())
                throw runtime_error("Invalid token in postfix expression");
            values.push(number); // Save this number until an operator needs it.
        }
    }
    if (!foundToken || values.size() != 1)
        throw runtime_error("Invalid postfix expression");
    int answer = values.top();
    values.pop(); // Remove th final result after saving it.
    return answer;
}
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}
vector<string> tokenizeInfix(const string& expr) {
    vector<string> tokens;
    for (int i = 0; i < (int)expr.size();) {
        if (isspace((unsigned char)expr[i])) {
            i++;
        } else if (isdigit((unsigned char)expr[i])) {
            string number;
            while (i < (int)expr.size() &&
                   isdigit((unsigned char)expr[i])) {
                number += expr[i];
                i++;
            }
            tokens.push_back(number);
        } else if (isalpha((unsigned char)expr[i]) ||
                   expr[i] == '(' || expr[i] == ')' ||
                   string("+-*/").find(expr[i]) != string::npos) {
            tokens.push_back(string(1, expr[i]));
            i++;
        } else {
            throw runtime_error("Invalid character in expression");
        }
    }
    return tokens;
}
// LAB C Problem 2 and Problem 3
string infixToPostfix(const string& expr) {
    vector<string> tokens = tokenizeInfix(expr);
    LinkedStack<char> opStack;
    string output;
    for (const string& token : tokens) {
        char ch = token[0];
        if (token.size() > 1 || isalnum((unsigned char)ch)) {
            if (!output.empty()) output += " ";
            output += token;
        } else if (ch == '(') {
            opStack.push(ch); // Keep '(' as a boundary for operators.
        } else if (ch == ')') {
            bool foundOpen = false;
            while (!opStack.empty()) {
                char op = opStack.top();
                opStack.pop(); // Output operators until '(' is found.
                if (op == '(') {
                    foundOpen = true;
                    break;
                }
                if (!output.empty()) output += " ";
                output += op;
            }
            if (!foundOpen)
                throw runtime_error("Unmatched closing parenthesis");
        } else if (string("+-*/").find(ch) != string::npos) {
            while (!opStack.empty() && opStack.top() != '(' &&
                   precedence(opStack.top()) >= precedence(ch)) {
                char op = opStack.top();
                opStack.pop(); // Output operators with higher or equal precedence.
                if (!output.empty()) output += " ";
                output += op;
            }
            opStack.push(ch); // Save this operator until its operands are output.
        }
    }
    while (!opStack.empty()) {
        char op = opStack.top();
        opStack.pop(); // Output each remaining operator.
        if (op == '(')
            throw runtime_error("Unmatched opening parenthesis");
        if (!output.empty()) output += " ";
        output += op;
    }
    return output;
}
// LAB C Problem 4
int evaluateInfix(const string& expr) {
    return evaluatePostfix(infixToPostfix(expr));
}
// Call simulator required by submission
void callSimulator() {
    LinkedStack<string> calls;
    calls.push("main"); // Record that main has started.
    calls.push("functionA"); // Record functionA calling from main.
    calls.push("functionB"); // Record functionB calling functionA.
    cout << "Call: " << calls.top() << endl;
    calls.pop(); // Return from functionB to functionA.
    cout << "Return to: " << calls.top() << endl;
    calls.pop(); // Return from functionA to main.
    cout << "Return to: " << calls.top() << endl;
    calls.pop(); // Finish the simulated main call.
}
// LAB A Problem 1
// int main() {
//     ArrayStack<int> S(5);
//     S.push(3); // Put 3 at TOP.
//     cout << "After push(3): t = " << S.size() - 1
//          << ", top = " << S.top() << endl;
//     S.push(7); // Put 7 above 3.
//     cout << "After push(7): t = " << S.size() - 1
//          << ", top = " << S.top() << endl;
//     S.push(1); // Put 1 above 7.
//     cout << "After push(1): t = " << S.size() - 1
//          << ", top = " << S.top() << endl;
//     S.pop(); // Remove 1 from the active stack.
//     cout << "After pop(): t = " << S.size() - 1
//          << ", top = " << S.top() << endl;
//     cout << "top() = " << S.top() << endl; // top() does not remove anything.
//     S.push(9); // Put 9 into the cell freed by pop().
//     S.push(5); // Put 5 above 9.
//     S.push(2); // Put 2 above 5; the stack is now full.
//     cout << "Final: t = " << S.size() - 1
//          << ", size = " << S.size()
//          << ", full = " << boolalpha << S.full()
//          << ", top = " << S.top() << endl;
//     return 0;
// }

// LAB A Problem 2
// int main() {
//     ArrayStack<int> S(2);
//     cout << "safe_pop empty = " << safe_pop(S) << endl;
//     safe_push(S, 10);
//     safe_push(S, 20);
//     safe_push(S, 30);
//     cout << "safe_pop = " << safe_pop(S) << endl;
//     cout << "safe_pop = " << safe_pop(S) << endl;
//     cout << "safe_pop empty = " << safe_pop(S) << endl;
//     return 0;
// }


// LAB A Problem 3
//int main() {
//     ArrayStack<int> S(5);
//     S.push(4); // Save 4 for counting.
//     S.push(7); // Save 7 above 4.
//     S.push(2); // Save 2 as TOP.
//     cout << "Count = " << countElements(S) << endl;
//     cout << "Original top still = " << S.top() << endl;
//     ArrayStack<int> emptyStack(2);
//     cout << "Empty stack count = " << countElements(emptyStack) << endl;
//     return 0;
// }


// LAB A Problem 4
// int main() {
//     vector<int> v = {1, 2, 3, 4, 5};
//     reverseVector(v);
//     cout << "Reversed: ";
//     for (int x : v) cout << x << " ";
//     cout << endl;
//     vector<int> one = {8};
//     reverseVector(one);
//     cout << "Single element: " << one[0] << endl;
//     return 0;
// }


// LAB B Problem 1
// int main() {
//     stress_test(1000);
//     stress_test(3);
//     ArrayStack<int> exact(3);
//     exact.push(1); // Test capacity exactly equal to n.
//     exact.push(2); // Push second value.
//     exact.push(3); // Fill the last available cell.
//     cout << "Capacity exactly n: full = "
//          << boolalpha << exact.full() << endl;
//     return 0;
// }


// LAB B Problem 2
// int main() {
//     cout << "({[a+b]}) matched pairs = "
//          << countMatchedPairs("({[a+b]})") << endl;
//     cout << "({[}]) result = "
//          << countMatchedPairs("({[}])"
//          ) << " (-1 means not balanced)" << endl;
//     cout << "Empty expression matched pairs = "
//          << countMatchedPairs("") << endl;
//     cout << "([)] result = " << countMatchedPairs("([)]")
//          << " (-1 means not balanced)" << endl;
//     return 0;
// }


// LAB B Problem 3
// int main() {
//     vector<string> good = {"int main() {", "if (x > 0) {", "}", "}"};
//     vector<string> bad = {"int main() {", " if (x > 0 {", "}"};
//     cout << "Balanced example:" << endl;
//     checkLines(good);
//     cout << "Unbalanced example:" << endl;
//     checkLines(bad);
//     return 0;
// }


// LAB B Problem 4
// int main() {
//     cout << "racecar = " << boolalpha << isPalindrome("racecar") << endl;
//     cout << "hello = " << isPalindrome("hello") << endl;
//     cout << "Empty = " << isPalindrome("") << endl;
//     cout << "Single character = " << isPalindrome("a") << endl;
//     return 0;
// }


// LAB C Problem 1
// int main() {
//     cout << "5 3 * 2 + 6 4 * + = "
//          << evaluatePostfix("5 3 * 2 + 6 4 * +") << endl;
//     cout << "Single token 7 = " << evaluatePostfix("7") << endl;
//     cout << "6 2 / = " << evaluatePostfix("6 2 /") << endl;
//     return 0;
// }


// LAB C Problem 2
// int main() {
//     cout << "A + B * C - D = "
//          << infixToPostfix("A + B * C - D") << endl;
//     cout << "A - B - C = " << infixToPostfix("A - B - C") << endl;
//     return 0;
// }


// LAB C Problem 3
// int main() {
//     cout << "(A + B) * (C - D) = "
//          << infixToPostfix("(A + B) * (C - D)") << endl;
//     cout << "((A + B)) = " << infixToPostfix("((A + B))") << endl;
//     try {
//         cout << infixToPostfix("A + B)") << endl;
//     } catch (exception& e) {
//         cout << "Error caught: " << e.what() << endl;
//     }
//     return 0;
// }


// LAB C Problem 4
// int main() {
//     cout << "(5 + 3) * 2 - 6 / 3 = "
//          << evaluateInfix("(5 + 3) * 2 - 6 / 3") << endl;
//     cout << "(2 + 3) * (4 - 1) = "
//          << evaluateInfix("(2 + 3) * (4 - 1)") << endl;
//     cout << "8 / 2 / 2 = " << evaluateInfix("8 / 2 / 2") << endl;
//     cout << "10 / (2 + 3) = "
//          << evaluateInfix("10 / (2 + 3)") << endl;
//     return 0;
// }






// Calling Simulator
int main() {
    callSimulator();
    return 0;
}
