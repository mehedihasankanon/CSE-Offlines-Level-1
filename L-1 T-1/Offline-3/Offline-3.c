#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

// menu prototype

int ShowMenu(void);

// anagram prototypes and vars

char anag1[] = "listen";
char anag2[] = "earth";
char anag3[] = "binary";

void StartAnagram(void);
void Anagram(char *str);

// caesar cipher prototypes and vars

char phrase1[] = "There is a secret code";
char phrase2[] = "Attack at dawn";
char phrase3[] = "Meet me at the park";
char encrypted[1000] = {'\0'};
char decrypted[1000] = {'\0'};

void StartCaesar(void);
void Caesar(char *str);
void CaesarEncrypt(char *str, int len, int shift);
void CaesarDecrypt(char *str, int len, int shift);

// word guessing prototypes and vars

char word1[] = "network";
char word2[] = "program";
char word3[] = "science";

void StartWGuess(void);
void WGuess(char *str);
bool attempt(char *word);

// score

int score = 0;
int completed = 0;

// ===== FUNDAMENTAL FUNCTIONS FOR STRING ===== //

int strl(char *str)
{
    int len = 0;
    while (str[len] != '\0')
        len++;
    return len;
}

bool cmp(char *s1, char *s2)
{
    if (strl(s1) != strl(s2))
        return false;
    for (int i = 0; i < strl(s1); i++)
    {
        if (s1[i] != s2[i])
            return false;
    }
    return true;
}

void cpy(char *str, char *str2)
{
    for (int i = 0; i <= strl(str); i++)
        str2[i] = str[i];
    return;
}

bool sbstr(char *str1, char *str2)
{
    for (int i = 0; i < strl(str1); i++)
    {
        if (str1[i] == str2[0])
        {
            bool possible = true;
            for (int j = 0; j < strl(str2); j++)
            {
                if (str1[i + j] != str2[j])
                    possible = false;
            }
            if (possible)
                return true;
        }
    }
    return false;
}

// ===== main function ===== //

int main()
{
    if (ShowMenu() == 2)
        return 0;

    printf("\n");
    StartAnagram();

    printf("\n");
    StartCaesar();

    printf("\n");
    StartWGuess();

    printf("\n");
    if (completed == 3)
        score += 5;
    printf("Game Over!\nYour total score: %d points\n", score);

    return 0;
}

// ===== show menu ===== //

int ShowMenu(void)
{
    int choice;
    printf("Welcome to game world!\n");
    printf("1. start game \n2. exit\n");
    printf("Enter yout choice: ");
    scanf("%d", &choice);
    return choice;
}

// ===== anagram challenge ===== //

void StartAnagram(void)
{
    printf("Starting Anagram Challenge...\n");

    srand(time(NULL));
    int game = (rand() % 3) + 1;

    if (game == 1)
        Anagram(anag1);
    if (game == 2)
        Anagram(anag2);
    if (game == 3)
        Anagram(anag3);

    return;
}

void Anagram(char *str)
{
    // printf(str);

    char anagc[1000];
    cpy(str, anagc);
    int len = strl(str);
    for (int i = 0; i < len; i++)
    {
        srand(time(NULL));
        int j = rand() % len;
        while (i == j)
        {
            // srand(time(NULL));
            j = rand() % len;
        }

        char temp = anagc[i];
        anagc[i] = anagc[j];
        anagc[j] = temp;
    }
    printf("Scrambled Word: %s\n", anagc);
    int tries = 0;

    while (true)
    {
        char attempt[1000];
        printf("Your guess: ");
        scanf("%s", attempt);
        tries++;
        if (cmp(attempt, str))
        {
            score += 10 + (3 - tries) * 10;
            completed++;
            printf("Correct! You solved it in %d attempts\n", tries);
            return;
        }
        if (tries == 3)
        {
            printf("No tries left. \nCorrect answer: %s\n", str);
            return;
        }
        printf("Incorrect! Try again.\n");
    }

    return;
}

// ===== caesar cipher challenge ===== //

void StartCaesar()
{
    getchar();
    printf("Starting Caesar Cipher Challenge...\n");

    srand(time(NULL));
    int phrase = (rand()) % 3 + 1;

    if (phrase == 1)
        Caesar(phrase1);
    if (phrase == 2)
        Caesar(phrase2);
    if (phrase == 3)
        Caesar(phrase3);

    return;
}

void Caesar(char *str)
{
    srand(time(NULL));
    int shift = rand() % 25 + 1;
    printf("Shift: %d\n", shift);
    CaesarEncrypt(str, strl(str), shift); // random shift
    printf("Encrypted phrase: %s\n", encrypted);
    int attempts = 0;

    do
    {
        printf("Your guess: ");
        fgets(decrypted, 1000, stdin);
        decrypted[strl(decrypted) - 1] = '\0';
        attempts++;
        // CaesarDecrypt(decrypted, strl(str), shift);

        if (cmp(decrypted, str))
        {
            score += 10 + (3 - attempts) * 10;
            completed++;
            printf("Correct! You decrypted it in %d attempts.\n", attempts);
            return;
        }
        printf("Incorrect! Try again.\n");
    } while (attempts < 3);
    printf("No tries left. Correct answer: %s\n", str);

    return;
}

void CaesarEncrypt(char *str, int len, int shift)
{
    // forward shift random chars
    for (int i = 0; i < len; i++)
    {
        if (str[i] >= 'A' && str[i] <= 'Z')
        {
            encrypted[i] = 'A' + (str[i] - 'A' + shift) % 26;
        }
        else if (str[i] >= 'a' && str[i] <= 'z')
        {
            encrypted[i] = 'a' + (str[i] - 'a' + shift) % 26;
        }
        else
        {
            encrypted[i] = str[i];
        }
    }
    return;
}

void CaesarDecrypt(char *str, int len, int shift)
{
    // backward shift 3 chars
    for (int i = 0; i < len; i++)
    {
        if (str[i] >= 'A' && str[i] <= 'Z')
        {
            decrypted[i] = 'A' + (str[i] - 'A' + 26 - shift) % 26;
        }
        else if (str[i] >= 'a' && str[i] <= 'z')
        {
            decrypted[i] = 'a' + (str[i] - 'a' + 26 - shift) % 26;
        }
        else
        {
            decrypted[i] = str[i];
        }
    }
    return;
}

// ===== word guessing challenge ===== //

void StartWGuess()
{
    printf("Starting Word Guessing Challenge...\n");
    srand(time(NULL));
    int word = rand() % 3 + 1;
    if (word == 1)
        WGuess(word1);
    if (word == 2)
        WGuess(word2);
    if (word == 3)
        WGuess(word3);
    return;
}

void WGuess(char *word)
{
    printf("Hint: ");
    for (int i = 0; i < 3; i++)
        printf("%c", word[i]);
    for (int i = 3; i < strl(word); i++)
        printf("_");

    printf("\nSelect an option: 1. Write answer 2: check substring 3: check length\n");
    int tries = 0, used = 0;
    bool used2 = false, used3 = false;

    while (true)
    {
        int choice;
        scanf("%d", &choice);

        if (choice == 1)
        {
            tries++;
            if (attempt(word))
            {
                score += 10 + (3 - tries) * 10 - (used) * 2;
                completed++;
                printf("Correct! You guessed it in %d attempt(s) using %d utility functions.\n", tries, used);
                return;
            }
            else
            {
                if (tries == 3)
                    printf("Wrong. Correct answer: %s\n.\n", word);
                else
                    printf("Wrong. Retry.\n");
            }
        }
        else if (choice == 2)
        {
            if (used2)
            {
                printf("Error: Utility func already used.\n");
                continue;
            }
            printf("Enter Substring: ");
            char ss[1000];
            scanf("%s", &ss);
            if (sbstr(word, ss))
            {
                printf("Yes\n");
            }
            else
            {
                printf("No\n");
            }
            used2 = true;
            used++;
        }
        else
        {
            if (used3)
            {
                printf("Error: Utility func already used.\n");
                continue;
            }
            printf("Enter length: ");
            int guess;
            scanf("%d", &guess);
            if (guess == strl(word))
                printf("Yes\n");
            else
                printf("No\n");
            used3 = true;
            used++;
        }
        if (tries == 3)
            break;
    }
}

bool attempt(char *word)
{
    printf("Enter your guess: ");
    char guess[1000];
    scanf("%s", guess);
    if (cmp(word, guess))
        return true;
    else
        return false;
}
