/*#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <signal.h>
#include "hangman.h"

int H_getRandomNumber(int max)
{
    return rand() % max;
}

void H_printWord(const char *word, const char *guessedLetters)
{
    int length = strlen(word);
    printf("\nWord: ");
    for (int i = 0; i < length; i++)
    {
        if (strchr(guessedLetters, word[i]) != NULL)
        {
            printf("\033[1;32m %c \033[0m", word[i]); // Green for correctly guessed letters
        }
        else
        {
            printf("_ ");
        }
    }
    printf("\n");
}

int H_isGameWon(const char *word, const char *guessedLetters)
{
    int length = strlen(word);
    for (int i = 0; i < length; i++)
    {
        if (strchr(guessedLetters, word[i]) == NULL)
        {
            return 0; // Game is not won yet
        }
    }
    return 1; // Game is won
}

// Signal handler for Ctrl+C (SIGINT)
void H_sigintHandler(int signal)
{

    printf("\nExiting game.\n");
    exit(0);
}
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_WORD_LENGTH 20
#define MAX_WORDLIST_SIZE 250
#define MAX_LIVES 7

struct Stack
{
    char data[MAX_WORD_LENGTH];
    int top;
};

void initializeStack(struct Stack *stack)
{
    stack->top = -1;
}

void push(struct Stack *stack, char data)
{
    if (stack->top < MAX_WORD_LENGTH - 1)
    {
        stack->data[++stack->top] = data;
    }
}

int isLetterInStack(char letter, struct Stack *stack)
{
    for (int i = 0; i <= stack->top; i++)
    {
        if (stack->data[i] == letter)
        {
            return 1; // Letter is in the stack
        }
    }
    return 0; // Letter is not in the stack
}

void printWord(char *word, struct Stack *guessedLetters)
{
    int length = strlen(word);
    for (int i = 0; i < length; i++)
    {
        if (isLetterInStack(word[i], guessedLetters))
        {
            printf("\033[1;32m%c\033[0m ", word[i]);
        }
        else
        {
            printf("_ ");
        }
    }
    printf("\n");
}

int isGameWon(char *word, struct Stack *guessedLetters)
{
    int length = strlen(word);
    for (int i = 0; i < length; i++)
    {
        if (!isLetterInStack(word[i], guessedLetters))
        {
            return 0; // Game is not won yet
        }
    }
    return 1; // Game is won
}

/*int main()
{
    srand(time(NULL));

    char *wordList[MAX_WORDLIST_SIZE] = {
        "afghanistan", "albania", "algeria", "andorra", "angola", "antigua and barbuda", "argentina", "armenia", "australia", "austria",
        "azerbaijan", "bahamas", "bahrain", "bangladesh", "barbados", "belarus", "belgium", "belize", "benin", "bhutan",
        "bolivia", "bosnia and herzegovina", "botswana", "brazil", "brunei", "bulgaria", "burkina faso", "burundi", "cabo verde", "cambodia",
        "cameroon", "canada", "central african republic", "chad", "chile", "china", "colombia", "comoros", "congo", "costa rica",
        "croatia", "cuba", "cyprus", "czech republic (czechia)", "denmark", "djibouti", "dominica", "dominican republic",
        "east timor (timor-leste)", "ecuador", "egypt", "el salvador", "equatorial guinea", "eritrea", "estonia", "eswatini", "ethiopia",
        "fiji", "finland", "france", "gabon", "gambia", "georgia", "germany", "ghana", "greece", "grenada", "guatemala",
        "guinea", "guinea-bissau", "guyana", "haiti", "honduras", "hungary", "iceland", "india", "indonesia", "iran", "iraq",
        "ireland", "israel", "italy", "ivory coast", "jamaica", "japan", "jordan", "kazakhstan", "kenya", "kiribati",
        "korea, north (north korea)", "korea, south (south korea)", "kosovo", "kuwait", "kyrgyzstan", "laos", "latvia",
        "lebanon", "lesotho", "liberia", "libya", "liechtenstein", "lithuania", "luxembourg", "madagascar", "malawi",
        "malaysia", "maldives", "mali", "malta", "marshall islands", "mauritania", "mauritius", "mexico", "micronesia",
        "moldova", "monaco", "mongolia", "montenegro", "morocco", "mozambique", "myanmar (burma)", "namibia", "nauru",
        "nepal", "netherlands", "new zealand", "nicaragua", "niger", "nigeria", "north macedonia (formerly macedonia)", "norway",
        "oman", "pakistan", "palau", "panama", "papua new guinea", "paraguay", "peru", "philippines", "poland", "portugal",
        "qatar", "romania", "russia", "rwanda", "saint kitts and nevis", "saint lucia", "saint vincent and the grenadines", "samoa",
        "san marino", "sao tome and principe", "saudi arabia", "senegal", "serbia", "seychelles", "sierra leone", "singapore",
        "slovakia", "slovenia", "solomon islands", "somalia", "south africa", "south sudan", "spain", "sri lanka", "sudan",
        "suriname", "sweden", "switzerland", "syria", "taiwan", "tajikistan", "tanzania", "thailand", "togo", "tonga",
        "trinidad and tobago", "tunisia", "turkey", "turkmenistan", "tuvalu", "uganda", "ukraine", "united arab emirates",
        "united kingdom", "united states", "uruguay", "uzbekistan", "vanuatu", "vatican city", "venezuela", "vietnam", "yemen",
        "zambia", "zimbabwe"};

    int randomIndex = rand() % MAX_WORDLIST_SIZE;
    char *wordToGuess = wordList[randomIndex];

    struct Stack guessedLetters;
    initializeStack(&guessedLetters);

    int lives = MAX_LIVES;

    printf("Welcome to Hangman! You have %d lives.\n", lives);

    while (lives > 0)
    {
        printWord(wordToGuess, &guessedLetters);

        printf("Enter a letter: ");
        char guess;
        scanf(" %c", &guess);

        if (isLetterInStack(guess, &guessedLetters))
        {
            printf("You already guessed that letter. Try again.\n");
            continue;
        }

        push(&guessedLetters, guess);

        if (strchr(wordToGuess, guess) == NULL)
        {
            printf("Incorrect guess. You lose a life.\n");
            lives--;

            if (lives == 0)
            {
                printf("Out of lives! The correct word was: %s\n", wordToGuess);
                break; // Exit the loop, out of lives
            }
        }

        if (isGameWon(wordToGuess, &guessedLetters))
        {
            printf("Congratulations! You guessed the word: %s\n", wordToGuess);
            break; // Exit the loop, game won
        }

        printf("You have %d lives left.\n", lives);
    }

    // Additional cleanup or game-over logic can be added here

    return 0;
}*/