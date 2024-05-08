from enum import Enum

class TokenType(Enum):
    IDENTIFIER = 0
    KEYWORD = 1
    PLUS = 2
    MINUS = 3
    MULTIPLY = 4
    DIVIDE = 5
    LPAREN = 6
    RPAREN = 7
    SEMICOLON = 8
    NUMBER = 9
    ERROR = 10

class TokenizationError(Exception):
    def __init__(self, message, position):
        super().__init__(message)
        self.position = position

def is_keyword(string):
    """Checks if a string matches one of the reserved keywords."""
    return string in ("INPUT", "OUTPUT")

def get_token_type(char):
    """Determines the token type based on the first character."""
    if char.isdigit():
        return TokenType.NUMBER
    elif char.isalpha():
        return TokenType.IDENTIFIER
    elif char == "+":
        return TokenType.PLUS
    elif char == "-":
        return TokenType.MINUS
    elif char == "*":
        return TokenType.MULTIPLY
    elif char == "/":
        return TokenType.DIVIDE
    elif char == "(":
        return TokenType.LPAREN
    elif char == ")":
        return TokenType.RPAREN
    elif char == ";":
        return TokenType.SEMICOLON
    else:
        return TokenType.ERROR

def tokenize(input_string):
    """Tokenizes the input string into a list of tokens and errors."""
    tokens = []
    errors = []
    current_char = 0
    while current_char < len(input_string):
        # Skip whitespace
        while current_char < len(input_string) and input_string[current_char].isspace():
            current_char += 1

        if current_char == len(input_string):
            break

        token_value = ""
        # Check for unary minus or negative number
        if input_string[current_char] == "-":
            next_char = current_char + 1
            if next_char < len(input_string) and input_string[next_char].isdigit():
                # Negative number
                token_value = "-"
                current_char = next_char
                while current_char < len(input_string) and input_string[current_char].isdigit():
                    token_value += input_string[current_char]
                    current_char += 1
            else:
                # Unary minus
                token_value = "-"
                current_char += 1
        elif input_string[current_char] in ('+', '*', '/', '(', ')', ';'):
            # Single-character operators and symbols
            token_value = input_string[current_char]
            current_char += 1
        else:
            # Other characters
            while current_char < len(input_string) and not input_string[current_char].isspace() \
                    and input_string[current_char] not in ('+', '-', '*', '/', '(', ')', ';'):
                token_value += input_string[current_char]
                current_char += 1

        if token_value:
            token_type = get_token_type(token_value[0])
            if token_type == TokenType.ERROR and len(token_value) > 1:
                # Handle potential multi-character errors (e.g., unexpected symbols)
                errors.append(TokenizationError(f"Unexpected character(s): {token_value}", current_char - 1))
            else:
                tokens.append((token_type, token_value))

    # Add sentinel token
    tokens.append((TokenType.ERROR, None))
    return tokens, errors

# Example usage
input_string = "INPUT x; OUTPUT x + 2 * (y - 3);"
tokens, errors = tokenize(input_string)

if errors:
    for error in errors:
        print(f"Error at position {error.position}: {error}")
else:
    print("Tokenization successful!")
    for token_type, value in tokens:
        print(f"Token: type={token_type.name}, value={value}")
