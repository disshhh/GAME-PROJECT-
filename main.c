#include <stdio.h>
#include <stdlib.h>
#include "connect.h"
#include "tictactoe.h"
#include "hangman.h"
#include "connectgame.h"

#include <time.h>
#include <signal.h>
#include <string.h>

char T_board[T_SIZE][T_SIZE];
char T_humanPlayer = 'X';
char T_computerPlayer = 'O';
char board[C_ROWS][C_COLS];
int currentPlayer = 1;

struct Stack
{
    char data[MAX_WORD_LENGTH];
    int top;
};

typedef struct Node
{
    int lifeNumber;
    struct Node *next;
} NODE;

typedef struct llist
{
    NODE *head;
} LLIST;

// Function prototypes
void initList(LLIST *pl);
void addLife(LLIST *pl, int lifeNumber);
void removeLife(LLIST *pl);
void displayLives(LLIST *pl);

void displayMenu();
void playTicTacToe(int *level, LLIST *pl);
void playConnectFour(int *level, LLIST *pl);
void playHangman(int *level, LLIST *pl);

void initializeStack(struct Stack *stack);
void push(struct Stack *stack, char data);
int isLetterInStack(char letter, struct Stack *stack);
void printWord(char *word, struct Stack *guessedLetters);
int isGameWon(char *word, struct Stack *guessedLetters);

void initList(LLIST *pl)
{
    pl->head = NULL;
}

// add life
void addLife(LLIST *pl, int lifeNumber)
{
    struct Node *temp = (struct Node *)malloc(sizeof(struct Node));
    temp->lifeNumber = lifeNumber;
    temp->next = NULL;

    if (pl->head == NULL)
    {
        pl->head = temp;
        return;
    }

    NODE *p = pl->head;
    while (p->next != NULL)
    {
        p = p->next;
    }
    p->next = temp;
}

// remove life
void removeLife(LLIST *pl)
{
    NODE *p = pl->head;
    NODE *q = NULL;
    if (p->next == NULL)
    {
        pl->head = NULL;
        free(p);
        return;
    }

    while (p->next != NULL)
    {
        q = p;
        p = p->next;
    }
    q->next = NULL;
    free(p);
}

// display remaining lives
void displayLives(LLIST *pl)
{
    printf("Current lives: ");
    NODE *p = pl->head;
    if (pl->head == NULL)
    {
        printf("Out of lives\n");
        return;
    }
    while (p->next != NULL)
    {
        p = p->next;
    }
    printf("%d ", p->lifeNumber);
    printf("\n");
}

int main()
{
    LLIST obj;
    initList(&obj);
    int choice;
    int level = 1; // Initial level
    for (int i = 1; i <= 3; ++i)
    {
        addLife(&obj, i);
    }

    do
    {
        displayMenu();
        printf("Current level: %d\n", level);
        displayLives(&obj);
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            playTicTacToe(&level, &obj);
            if (obj.head->lifeNumber)
                displayLives(&obj);
            else
                printf("Out of lives\n");

            break;

        case 2:

            if (level >= 2)
            {
                playConnectFour(&level, &obj);
            }
            else
            {
                printf("You need to pass level 1 to unlock this level!\n");
            }
            if (obj.head->lifeNumber)
                displayLives(&obj);
            else
                printf("Out of lives\n");
            break;

        case 3:

            if (level >= 3)
            {
                playHangman(&level, &obj);
            }
            else
            {
                printf("You need to pass level 2 to unlock this level!\n");
            }

            if (obj.head->lifeNumber)
                displayLives(&obj);
            else
                printf("Out of lives\n");

            break;

        case 4:
            printf("Thanks for playing! Exiting...\n");
            break;

        default:
            printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 4 && level <= 3 && obj.head->lifeNumber);

    printf("Game Over\n");

    return 0;
}

void displayMenu()
{
    printf("\n----- Game Menu -----\n");
    printf("1. Level 1: Tic-Tac-Toe\n");
    printf("2. Level 2: Connect Four\n");
    printf("3. Level 3: Hangman\n");
    printf("4. Quit\n");
}

void playTicTacToe(int *level, LLIST *pl)
{
    //  tic-tac-toe game
    printf("Tic-Tac-Toe game is under construction.\n");
    for (int i = 0; i < T_SIZE; i++)
    {
        for (int j = 0; j < T_SIZE; j++)
        {
            T_board[i][j] = ' ';
        }
    }
    printf("Welcome to Tic-Tac-Toe!\n");
    printf("You are playing as 'X'.\n");
    printf("Enter the row and column (1-3) to make your move.\n");

    while (!T_isGameOver())
    {
        printT_Board();
        int row, col;
        printf("Enter your move (row column): ");
        scanf("%d %d", &row, &col);
        row--;
        col--;

        while (!T_isValidMove(row, col))
        {
            printf("Invalid move. Try again: ");
            scanf("%d %d", &row, &col);
            row--;
            col--;
        }

        T_board[row][col] = T_humanPlayer;

        if (T_isGameOver())
            break;

        T_computerMove();
    }

    printT_Board();
    int result = T_evaluate();
    if (result > 0)
    {
        printf("Computer ('O') wins!\n");
        if (pl->head->next == NULL)
        {
            pl->head->lifeNumber--;
        }
        else
        {
            removeLife(pl);
        }
    }
    else if (result < 0)
    {
        printf("Player ('X') wins!\n");
    }
    else
    {
        printf("It's a draw!\n");
    }
    // return 0;
    (*level) = 2;
}

void playConnectFour(int *level, LLIST *pl)
{

    srand(time(NULL));

    CONinitializeBoard();
    CONprintBoard();

    while (1)
    {
        // Player's move
        CONplayerMove();
        CONprintBoard();
        if (CONcheckWin('X'))
        {
            printf("Congratulations! You win!\n");
            break;
        }
        else if (CONisBoardFull())
        {
            printf("It's a draw!\n");
            break;
        }

        // Computer's move
        int computerMoveCol = CONfindBestMove();
        printf("Computer's move: %d\n", computerMoveCol);
        for (int i = C_ROWS - 1; i >= 0; --i)
        {
            if (C_board[i][computerMoveCol] == ' ')
            {
                C_board[i][computerMoveCol] = 'O';
                break;
            }
        }

        CONprintBoard();
        if (CONcheckWin('O'))
        {
            printf("Sorry, you lose. Try again!\n");
            if (pl->head->next == NULL)
            {
                pl->head->lifeNumber--;
            }
            else
            {
                removeLife(pl);
            }
            break;
        }
        else if (CONisBoardFull())
        {
            printf("It's a draw!\n");
            break;
        }
    }
    // return 0;
    (*level) = 3;
}

void playHangman(int *level, LLIST *pl)
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

                if (pl->head->next == NULL)
                {
                    pl->head->lifeNumber--;
                }
                else
                {
                    removeLife(pl);
                }

                break; // out of lives
            }
        }

        if (isGameWon(wordToGuess, &guessedLetters))
        {
            printf("Congratulations! You guessed the word: %s\n", wordToGuess);
            break; // Exit the loop
        }

        printf("You have %d lives left.\n", lives);
    }
}