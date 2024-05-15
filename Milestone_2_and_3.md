# Expression Evaluator (Milestone 2 & 3)

This Python script provides a simple expression evaluator GUI using PySimpleGUI. It evaluates arithmetic expressions entered by the user.

## Getting Started

To run the script, make sure you have Python installed on your system. Install PySimpleGUI if you haven't already:

bash
pip install PySimpleGUI

python expression_evaluator.py

# Expression Evaluator

## Usage

1. Run the script using the provided command.
2. Enter an arithmetic expression in the input field.
3. Click the "Evaluate" button to calculate the result.
4. The result will be displayed below the input field.

## Supported Operations

- Addition (+)
- Subtraction (-)
- Multiplication (\*)
- Division (/)

## Example

Input: 10+5\*(4-3)
Output: Result: 15.0

## Code Structure

- `Parser` class: Responsible for parsing arithmetic expressions.
- `tokenize` function: Tokenizes input expressions.
- `main` function: Handles the GUI interaction and expression evaluation.

## Contributing

Contributions are welcome! If you have any suggestions, bug reports, or improvements, feel free to open an issue or create a pull request.

## License

This project is licensed under the MIT License - see the LICENSE file for details.
