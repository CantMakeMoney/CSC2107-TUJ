/* Description: This program takes input and output file locations from the user
 *      and removes all comments from the input. The program will throw errors if
 *      one of the user's files does not exist or if there is a comment that has
 *      no end, in which case the user will be told which line contains the error.
 *      The comment removal adheres to the same spacing rules as gcc's preprocessor.
 * CSC2107 - TUJ Fall 2023
 * Instructor: Dr. Hani Karam
 * Author: Joshua Reynolds
 * Date: 10/2/2023
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#define BUF_SIZE 64

int main() {



    enum STATE {
        CODE,
        COMMENT,
        STRING,
    };

    char inputID[BUF_SIZE];
    printf("Please write input file location: ");
    //fgets(inputID, BUF_SIZE, stdin); fgets() did not work for me.
    scanf("%s", inputID);

    FILE *input = fopen(inputID, "r");

    if (errno == 2) { // If user's file is not found, throw error and end program
        perror("Error");
        printf("Exiting Program...\n");
        return 0;
    }

    char outputID[BUF_SIZE];
    printf("Please write output file location: ");
    //fgets(outputID, BUF_SIZE, stdin);
    scanf("%s", outputID);

    FILE *output = fopen(outputID, "w");
    if (errno == 2) { // If user's file is not found, throw error and end program
        perror("Error");
        printf("Exiting Program...\n");
        return 0;
    }

    char curr = fgetc(input); // Current character of input file.
    char temp, temp2;

    int lineNum = 1, errorLine = 0;


    enum STATE state = CODE;

    while (!feof(input)) { //Until the end of input is reached

        if (curr == '"' && state == STRING) { // Exit string state, return to code state
            state = CODE;
        }
        else if (curr == '"' && state == CODE) { // Exit code state, enter string state
            state = STRING;
        }
        if (curr == '/' && state == CODE) { // First check to enter comment state
            temp = curr; // store value in case next character is not '*'
            curr = fgetc(input);
            if (curr == '*') { // Exit code state, enter comment state
                state = COMMENT;
                errorLine = lineNum; // This is the line to refer to if end of comment is not found
                curr = fgetc(input);
                while (state == COMMENT) { // Skip all characters other than '*/' while in comment state
                    if (feof(input)) { // End of comment not found
                        printf("Error: Unterminated comment starts on Line %u\nExiting Program...\n", errorLine);
                        return 0;
                    }
                    if (curr == '\n') { // If new line exists within comment, maintain in output
                        lineNum++;
                        fputc('\n', output);
                    }
                    if (curr == '*') { // First check to exit comment state
                        temp = curr;
                        curr = fgetc(input);
                        if (curr == '/') { // Exit comment state, return to code state
                            curr = fgetc(input);
                            while (curr == ' ' || curr == '\t') { //Remove all white space between end of comment and start of next line or next code character
                                curr = fgetc(input);
                            }
                            state = CODE;
                            if (curr != '\n') { // If character after comment is code, add 1 space
                                fputc(' ', output);
                            }
                            continue;
                            //fputc(' ', output);
                        }
                    }
                    //fputc(' ', output);
                    curr = fgetc(input);
                }
            }
            else { // Second check not passed, add temp to output
                fputc(temp, output);
                continue;
            }
        }
        if (curr == '\n') {
            lineNum++;
            fputc('\n', output);
            curr = fgetc(input);
            continue;
        }
        temp = curr;
        curr = fgetc(input);
        fputc(temp, output);
    }

    fclose(input);
    fclose(output);

    printf("Comment removal complete.\n");

    return 0;
}
