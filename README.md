# Grammar for Parser
Grammar for a simple language that performs basic input, output, and arithmetic functions:

## Terminals:

- NUMBER: Any sequence of digits (e.g., 123, -45)
- IDENTIFIER: A sequence of letters starting with a letter (e.g., x, total)
- INPUT: Keyword for input operation
- OUTPUT: Keyword for output operation
- PLUS: "+" symbol for addition
- MINUS: "-" symbol for subtraction
- MULTIPLY: "*" symbol for multiplication
- DIVIDE: "/" symbol for division
- LPAREN: "(" left parenthesis
- RPAREN: ")" right parenthesis
- ;: Semicolon used as statement terminator

## Non-Terminals:

- Program: The entire program
- Statement: A single line of code within the program
- InputStatement: A statement for getting input
- OutputStatement: A statement for displaying output
- Expression: A mathematical expression
- Term: A component of the expression containing multiplication or division
- Factor: A basic building block of the expression (number, variable, or expression in parentheses)

## Grammar Rules:

### Program -> Statement ; { Statement ; }

- A program consists of one or more statements separated by semicolons.
### Statement -> InputStatement | OutputStatement | Expression ;

- A statement can be for input, output, or an expression followed by a semicolon.
### InputStatement -> INPUT IDENTIFIER ;

- Input statement uses the INPUT keyword followed by an identifier (variable name) to store the input value.
### OutputStatement -> OUTPUT Expression ;

- Output statement uses the OUTPUT keyword followed by an expression to be displayed.
### Expression -> Term { ( PLUS | MINUS ) Term }

- An expression is formed by one or more terms connected by addition or subtraction operators.
### Term -> Factor { ( MULTIPLY | DIVIDE ) Factor }

- A term is formed by one or more factors connected by multiplication or division operators.
### Factor -> NUMBER | IDENTIFIER | ( Expression )

- A factor can be a number, an identifier (variable name), or an expression enclosed in parentheses.
