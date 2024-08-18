#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

int main() 
{
    srand(time(0)); // Seed for random number generation

    char player1[20], player2[20];
    int health1, health2, energy1, energy2;
    char attack1 = '1', attack2 = '2';
    int rollPlayer1 = 0, rollPlayer2 = 0, damage, currentPlayer;
    char choice, playAgain;
    int previousRolls[12] = {0};

    do 
    {
        // Initialize for a new game
        health1 = health2 = 10; // Set initial health to 10
        energy1 = energy2 = 4; // Set initial energy to 4

        printf("Enter Player 1 name: ");
        scanf("%s", player1);

        printf("Enter Player 2 name: ");
        scanf("%s", player2);

        // Roll the dice to determine who goes first
        while (rollPlayer1 == rollPlayer2 || previousRolls[rollPlayer1] || previousRolls[rollPlayer2]) 
        {
            rollPlayer1 = rand() % 12 + 1;
            rollPlayer2 = rand() % 12 + 1;
        }
        previousRolls[rollPlayer1] = 1;
        previousRolls[rollPlayer2] = 1;

        printf("\n%s rolled a %d\n", player1, rollPlayer1);
        printf("%s rolled a %d\n", player2, rollPlayer2);

        if (rollPlayer1 > rollPlayer2) 
        {
            printf("\n%s goes first!\n", player1);
        } 
        else 
        {
            printf("\n%s goes first!\n", player2);
        }

        // Game loop
        currentPlayer = (rollPlayer1 > rollPlayer2) ? 1 : 2; // Higher roll goes first(obviously)
        while (health1 > 0 && health2 > 0) 
        {
            printf("\n%s's turn:\n", (currentPlayer == 1) ? player1 : player2);
            printf("1. Normal Attack (2 energy, 1 damage)\n2. Special Attack (3 energy, 1-3 damage)\n3. Forfeit\n");
            scanf(" %c%*c", &choice);

            // Process the chosen action
            if (choice == attack1) 
            {
                if ((currentPlayer == 1 && energy1 >= 2) || (currentPlayer == 2 && energy2 >= 2)) 
                {
                    damage = 1;
                    if (currentPlayer == 1) 
                    {
                        health2 -= damage;
                        energy1 -= 2;
                    } 
                    else 
                    {
                        health1 -= damage;
                        energy2 -= 2;
                    }
                    printf("%s dealt %d damage with Normal Attack!\n", (currentPlayer == 1) ? player1 : player2, damage);
                  
                    if (energy1 < 2 || energy2 < 2) 
                    {
                        currentPlayer = (currentPlayer == 1) ? 2 : 1; // Switch turns if the currentPlayer is out of energy or doesn't have enough energy to perform an attack
                        energy1 = energy2 = 4; // Reset energy for the next turn
                    }
                } 
                else 
                {
                    printf("Not enough energy for Normal Attack!\n");
                }
            } 
            else if (choice == attack2) 
            {
                if ((currentPlayer == 1 && energy1 >= 3) || (currentPlayer == 2 && energy2 >= 3)) 
                {
                    damage = rand() % 3 + 1;
                    if (currentPlayer == 1) 
                    {
                        health2 -= damage;
                        energy1 -= 3;
                    } 
                    else 
                    {
                        health1 -= damage;
                        energy2 -= 3;
                    }
                    printf("%s dealt %d damage with Special Attack!\n", (currentPlayer == 1) ? player1 : player2, damage);
                  
                    currentPlayer = (currentPlayer == 1) ? 2 : 1; // Switch turns after using special attack since there is no energy to perform a normal attack
                    energy1 = energy2 = 4; // Reset energy for the next turn
                } 
                else 
                {
                    printf("Not enough energy for Special Attack!\n");
                }
            } 
            else if (choice == '3') 
            {
                printf("%s forfeited. What a loser\n", (currentPlayer == 1) ? player1 : player2); // Whoever chooses to forfeit loses
                return 0;
            } 
            else 
            {
                printf("Invalid choice. Try again.\n");
            }

            // Print current status
            printf("\n%s: Health %d, Energy %d\n", player1, health1, energy1);
            printf("%s: Health %d, Energy %d\n", player2, health2, energy2);
        }

        // Determine the winner
        if (health1 <= 0) 
        {
            printf("\n%s wins!\n", player2);
        } 
        else 
        {
            printf("\n%s wins!\n", player1);
        }

        // Rematch option
        printf("Do you want to play again? (y/n): ");
        scanf(" %c%*c", &playAgain);
        playAgain = tolower(playAgain);

        if (playAgain != 'y') 
        {
            printf("Quitting the game.\n");
            return 0;
        }

    } while (1 && playAgain != 'n');

    return 0;
}
