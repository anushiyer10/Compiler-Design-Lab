#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_TOKEN_LENGTH 100

// Function to check if a character is a delimiter
int isDelimiter(char ch) {
    return ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r';
}

// Function to check if a character is an operator
int isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '=';
}

// Function to check if a character is a parenthesis
int isParenthesis(char ch) {
    return ch == '(' || ch == ')' || ch=='{' || ch=='}';
}

// Function to check if a character is a digit
int isDigit(char ch) {
    return isdigit(ch);
}

// Function to check if a character is an alphabet
int isAlpha(char ch) {
    return isalpha(ch);
}

// Function to identify tokens from a given input
void tokenize(char *input) {
    int i = 0;
    int len = strlen(input);

    while (i < len) {
        if (isDelimiter(input[i])) {
            i++;
            continue;
        } else if (isOperator(input[i])) {
            printf("Operator: %c\n", input[i]);
            i++;
        } else if (isParenthesis(input[i])) {
            printf("Parenthesis: %c\n", input[i]);
            i++;
        } else if (isDigit(input[i])) {
            char token[MAX_TOKEN_LENGTH] = "";
            int j = 0;
            while (i < len && isDigit(input[i])) {
                token[j++] = input[i++];
            }
            token[j] = '\0';
            printf("Number: %s\n", token);
        } else if (isAlpha(input[i])) {
            char token[MAX_TOKEN_LENGTH] = "";
            int j = 0;
            while (i < len && (isAlpha(input[i]) || isDigit(input[i]))) {
                token[j++] = input[i++];
            }
            token[j] = '\0';
            printf("Identifier: %s\n", token);
        } else {
            printf("Invalid character: %c\n", input[i]);
            i++;
        }
    }
}

int main() {
    // Example of a simple statement stored in a linear array
    printf("CHARACTOR ARRAY USER INPUT\n\n");
     char statement[MAX_TOKEN_LENGTH];
    printf("Enter your statement: ");
    fgets(statement, sizeof(statement), stdin);

    // Tokenize the statement
    printf("Tokens from user input:\n\n");
    tokenize(statement);
    
     printf("\n\nTOKENS FROM FILE\n");
    // Small program stored in a text file
    FILE *file = fopen("program.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    printf("\nTokens from program.txt:\n");

    // Read line by line from the file and tokenize each line
    char line[MAX_TOKEN_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        tokenize(line);
    }

    fclose(file);
    
    printf("\n\nUSER PROGRAM ENTERING\n");
    // Small program input from user and stored in a text file
    printf("\nEnter your program (not exceeding 5 lines):\n");

    FILE *userFile = fopen("user_program.txt", "w");
    if (userFile == NULL) {
        perror("Error creating user_program.txt");
        return 1;
    }

    // Get program input from the user and write it to the file
    char userInput[5][MAX_TOKEN_LENGTH];
    for (int i = 0; i < 5; i++) {
        fgets(userInput[i], sizeof(userInput[i]), stdin);
        fputs(userInput[i], userFile);
    }

    fclose(userFile);

    // Read from the user input file and tokenize each line
    userFile = fopen("user_program.txt", "r");
    if (userFile == NULL) {
        perror("Error opening user_program.txt");
        return 1;
    }

    printf("\nTokens from user_program.txt:\n");

    while (fgets(line, sizeof(line), userFile)) {
        tokenize(line);
    }

    fclose(userFile);

    return 0;
}
