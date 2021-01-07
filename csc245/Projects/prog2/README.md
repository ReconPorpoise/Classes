# Project 2: Binary Expression Trees Program
----------------------------------------------------------------------------------------------------------------
The Binary Expression Trees Program is a program that is able to take user input for Prefix, Infix, or Postfix expressions, and prints all 3 traversals of that expression.

This program allows for input of any one-length character, and are pushed to the Binary Expression Tree as a char value.

To accomplish creating the Binary Expression Trees, a few specific methods had to be implemented. 

## Algorithm Design:
### Insert Operand:
In the implementation file (bet.cpp), there is a void method called insertOperand( char token ) that inserts operands into the BET. The process is the same for both post and prefix notations because operands don't need to worry about having specific children.

The operand pointer gets an info.whichType value of OPERAND, and the info.theContent.variable (.variable for operands, .opsymbol for operators) is equal to the character "token". The left and right children of it become null. then the value is pushed to the stack.

### Insert Postfix Operator:
Inserting an operator for prefix and postfix are done slightly differently. For postfix, the info.whichType for the pointer has to be OPERATOR and the info.theContent.opsymbol has to be the token. The difference becomes how the children are assigned.

For postfix, the right child must be the operand on the top of the stack, so op->right becomes s.top();, but then the stack needs to be popped (s.pop());, to assign op->left to s.top();. The operator is then pushed to the stack, then is made into the root of the tree.

### Insert Prefix Operator:
The algorithm for insertPrefixOperator is exactly the same as postfix, except the op->left must be s.top(); then s.pop();, then the next stack item becomes op->right (s.top()). Op is then again pushed to the stack then made into the root of the tree.

### Build Postfix Tree:
To build the postfix tree in the client file, a BET returning method is used that takes in the user-input expression as a parameter. The expression is parsed to look for operators, and uses .insertPostfixOperator( string[index] ); to push values to the BET. If the value is an operand, call .insertOperand( string[index] ); After the loop, return the tree.

### Build Prefix Tree:
This is exactly the same as postfix, but .insertPostfixOperator() is replaced with .insertPrefixOperator().

### Build Infix Tree:
A BET, in this case, should not be built from an infix expression. To create a tree, however, the infix expression is converted to postfix, then calls the build postfix tree method. To convert, a blank string is created to house the postfix expression. As the string is parsed, check if it's an operator, operand, or open/closed parenthesis.

If the value is an opening parenthesis, push it to the stack. If its an operator, call the precedence method to see if the operator is less than the one in the stack. While it is true, append the operator to the stack, then pop it. After that loop finishes, push the operator to the stack.

If it is a closing parenthesis, keep adding the stack values to the postfix string, then pop the stack, until an opening parenthesis is reached. Then, pop the top of the stack. 

For the else branch, which should only be operands, append them to the postfix string.

Afterwards, return the BET produced from the call to build postfix tree of the postfix string.
