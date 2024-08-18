#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main() 
{
    char *secretWord = malloc(11 * sizeof(char));
    char *guess = malloc(11 * sizeof(char));
    int secretWordLen, guessLen, chances = 3, correctCharacters = 0;

    printf("Enter the secret word (max 10 characters): ");
    scanf("%s", secretWord);
    secretWordLen = strlen(secretWord);

    // Ensure the word entered is not longer than 10 characters
    while (secretWordLen > 10) 
    {
        printf("The word you entered is longer than 10 characters. Please enter a word with 10 characters or less: ");
        scanf("%s", secretWord);
        secretWordLen = strlen(secretWord);
    }

    // Convert secret word to lowercase
    for (int i = 0; i < secretWordLen; i++) 
    {
        secretWord[i] = tolower(secretWord[i]);
    }

    while (chances > 0) 
    {
        printf("Enter your guess: ");
        scanf("%s", guess);
        guessLen = strlen(guess);

        // Ensure the guess entered is not longer than 10 characters
        while (guessLen > 10) 
        {
            printf("Your guess is longer than 10 characters. Please enter a guess with 10 characters or less: ");
            scanf("%s", guess);
            guessLen = strlen(guess);
        }

        // Convert guess to lowercase
        for (int i = 0; i < guessLen; i++) 
        {
            guess[i] = tolower(guess[i]);
        }

        correctCharacters = 0;
        printf("Your guess: ");
        for (int i = 0; i < secretWordLen; i++) 
        {
            if (strchr(guess, secretWord[i]) != NULL) 
            {
                printf("%c", secretWord[i]); // Print correctly guessed character
                correctCharacters++;
            } 
            else 
            {
                printf("_"); // Print placeholder for characters not guessed
            }
        }

        // Print remaining underscores if the guess is shorter than the secret word
        for (int i = secretWordLen; i < secretWordLen; i++) 
        {
            printf("_");
        }

        printf(" %d/%d characters are correct.\n", correctCharacters, secretWordLen);

        if (strcmp(secretWord, guess) == 0) 
        {
            printf("Congratulations! You guessed the word correctly: %s\n", secretWord);
            break;
        } 
        else 
        {
            chances--;
            if (chances > 0) 
            {
                printf("You have %d chances left.\n", chances);
            }
        }
    }

    if (chances == 0) 
    {
        printf("Sorry, you ran out of chances. The correct word was: %s\n", secretWord);
    }

    // Free dynamically allocated memory so your program doesn't become the new Chrome :) 
    free(secretWord);
    free(guess);

    return 0;
}
