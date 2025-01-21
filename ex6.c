/******************
Name: Shira Cababia
ID: 326153590
Assignment: ex6
*******************/

#include "ex6.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INT_BUFFER 128
#define BULBASAUR_ID 1
#define CHARMANDER_ID 4
#define SQUIRTLE_ID 7
#define POKEMONS_NUM 151

// ================================================
// Basic struct definitions from ex6.h assumed:
//   PokemonData { int id; char *name; PokemonType TYPE; int hp; int attack; EvolutionStatus CAN_EVOLVE; }
//   PokemonNode { PokemonData* data; PokemonNode* left, *right; }
//   OwnerNode   { char* ownerName; PokemonNode* pokedexRoot; OwnerNode *next, *prev; }
//   OwnerNode* ownerHead;
//   const PokemonData pokedex[];
// ================================================

// --------------------------------------------------------------
// 1) Safe integer reading
// --------------------------------------------------------------

void displayBFS(PokemonNode *root) {}
void preOrderTraversal(PokemonNode *root) {}
void inOrderTraversal(PokemonNode *root) {}
void postOrderTraversal(PokemonNode *root) {}
void displayAlphabetical(PokemonNode *root) {}
void freeAllOwners(void) {}
void deletePokedex() {}
void mergePokedexMenu() {}
void sortOwners() {}
void printOwnersCircular() {}

void trimWhitespace(char *str)
{
    // Remove leading spaces/tabs/\r
    int start = 0;
    while (str[start] == ' ' || str[start] == '\t' || str[start] == '\r')
        start++;

    if (start > 0)
    {
        int idx = 0;
        while (str[start])
            str[idx++] = str[start++];
        str[idx] = '\0';
    }

    // Remove trailing spaces/tabs/\r
    int len = (int)strlen(str);
    while (len > 0 && (str[len - 1] == ' ' || str[len - 1] == '\t' || str[len - 1] == '\r'))
    {
        str[--len] = '\0';
    }
}

char *myStrdup(const char *src)
{
    if (!src)
        return NULL;
    size_t len = strlen(src);
    char *dest = (char *)malloc(len + 1);
    if (!dest)
    {
        printf("Memory allocation failed in myStrdup.\n");
        return NULL;
    }
    strcpy(dest, src);
    return dest;
}

int readIntSafe(const char *prompt)
{
    char buffer[INT_BUFFER];
    int value;
    int success = 0;

    while (!success)
    {
        printf("%s", prompt);

        // If we fail to read, treat it as invalid
        if (!fgets(buffer, sizeof(buffer), stdin))
        {
            printf("Invalid input.\n");
            clearerr(stdin);
            continue;
        }

        // 1) Strip any trailing \r or \n
        //    so "123\r\n" becomes "123"
        size_t len = strlen(buffer);
        if (len > 0 && (buffer[len - 1] == '\n' || buffer[len - 1] == '\r'))
            buffer[--len] = '\0';
        if (len > 0 && (buffer[len - 1] == '\r' || buffer[len - 1] == '\n'))
            buffer[--len] = '\0';

        // 2) Check if empty after stripping
        if (len == 0)
        {
            printf("Invalid input.\n");
            continue;
        }

        // 3) Attempt to parse integer with strtol
        char *endptr;
        value = (int)strtol(buffer, &endptr, 10);

        // If endptr didn't point to the end => leftover chars => invalid
        // or if buffer was something non-numeric
        if (*endptr != '\0')
        {
            printf("Invalid input.\n");
        }
        else
        {
            // We got a valid integer
            success = 1;
        }
    }
    return value;
}

// --------------------------------------------------------------
// 2) Utility: Get type name from enum
// --------------------------------------------------------------
const char *getTypeName(PokemonType type)
{
    switch (type)
    {
    case GRASS:
        return "GRASS";
    case FIRE:
        return "FIRE";
    case WATER:
        return "WATER";
    case BUG:
        return "BUG";
    case NORMAL:
        return "NORMAL";
    case POISON:
        return "POISON";
    case ELECTRIC:
        return "ELECTRIC";
    case GROUND:
        return "GROUND";
    case FAIRY:
        return "FAIRY";
    case FIGHTING:
        return "FIGHTING";
    case PSYCHIC:
        return "PSYCHIC";
    case ROCK:
        return "ROCK";
    case GHOST:
        return "GHOST";
    case DRAGON:
        return "DRAGON";
    case ICE:
        return "ICE";
    default:
        return "UNKNOWN";
    }
}

// --------------------------------------------------------------
// Utility: getDynamicInput (for reading a line into malloc'd memory)
// --------------------------------------------------------------
char *getDynamicInput()
{
    char *input = NULL;
    size_t size = 0, capacity = 1;
    input = (char *)malloc(capacity);
    if (!input)
    {
        printf("Memory allocation failed.\n");
        return NULL;
    }

    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
        if (size + 1 >= capacity)
        {
            capacity *= 2;
            char *temp = (char *)realloc(input, capacity);
            if (!temp)
            {
                printf("Memory reallocation failed.\n");
                free(input);
                return NULL;
            }
            input = temp;
        }
        input[size++] = (char)c;
    }
    input[size] = '\0';

    // Trim any leading/trailing whitespace or carriage returns
    trimWhitespace(input);

    return input;
}

// Function to print a single Pokemon node
void printPokemonNode(PokemonNode *node)
{
    if (!node)
        return;
    printf("ID: %d, Name: %s, Type: %s, HP: %d, Attack: %d, Can Evolve: %s\n",
           node->data->id,
           node->data->name,
           getTypeName(node->data->TYPE),
           node->data->hp,
           node->data->attack,
           (node->data->CAN_EVOLVE == CAN_EVOLVE) ? "Yes" : "No");
}

// --------------------------------------------------------------
// Display Menu
// --------------------------------------------------------------
void displayMenu(OwnerNode *owner)
{
    if (!owner->pokedexRoot)
    {
        printf("Pokedex is empty.\n");
        return;
    }

    printf("Display:\n");
    printf("1. BFS (Level-Order)\n");
    printf("2. Pre-Order\n");
    printf("3. In-Order\n");
    printf("4. Post-Order\n");
    printf("5. Alphabetical (by name)\n");

    int choice = readIntSafe("Your choice: ");

    switch (choice)
    {
    case 1:
        displayBFS(owner->pokedexRoot);
        break;
    case 2:
        preOrderTraversal(owner->pokedexRoot);
        break;
    case 3:
        inOrderTraversal(owner->pokedexRoot);
        break;
    case 4:
        postOrderTraversal(owner->pokedexRoot);
        break;
    case 5:
        displayAlphabetical(owner->pokedexRoot);
        break;
    default:
        printf("Invalid choice.\n");
    }
}

// --------------------------------------------------------------
// Sub-menu for existing Pokedex - CASE 2
// --------------------------------------------------------------

void enterExistingPokedexMenu()
{
    // Printing the list of owners
    printf("\nExisting Pokedexes:\n");
    int i = 1, ownerChoice = 0;
    OwnerNode *currentOwner = ownerHead;
    while (currentOwner)
    {
        printf("%d. %s\n", i, currentOwner->ownerName);
        if (currentOwner->next == ownerHead)
        {
            break;
        }
        currentOwner = currentOwner->next;
        i++;
    }
    // "Catching" the owner chosen by the user.
    ownerChoice = readIntSafe("Choose a Pokedex by number: ");
    currentOwner = ownerHead;
    OwnerNode *chosenOwner;
    for (int i = 0; i < ownerChoice; i++)
    {
        if (i + 1 == ownerChoice)
        {
            chosenOwner = currentOwner;
            break;
        }
        currentOwner = currentOwner->next;
    }
    printf("\nEntering %s's Pokedex...\n", chosenOwner->ownerName);
    int subChoice;
    do
    {
        printf("\n-- %s's Pokedex Menu --\n", chosenOwner->ownerName);
        printf("1. Add Pokemon\n");
        printf("2. Display Pokedex\n");
        printf("3. Release Pokemon (by ID)\n");
        printf("4. Pokemon Fight!\n");
        printf("5. Evolve Pokemon\n");
        printf("6. Back to Main\n");

        subChoice = readIntSafe("Your choice: ");

        switch (subChoice)
        {
        case 1:
            addPokemon(chosenOwner);
            break;
        case 2:
            displayMenu(chosenOwner);
            break;
        case 3:
            freePokemon(chosenOwner);
            break;
        case 4:
            pokemonFight(chosenOwner);
            break;
        case 5:
            evolvePokemon(chosenOwner);
            break;
        case 6:
            printf("Back to Main Menu.\n");
            break;
        default:
            printf("Invalid choice.\n");
        }
    } while (subChoice != 6);
}

// CASE 2 - PART 1 :

/* The function adds a new Pokemon to a given owner's Pokedex. The function ensures the Pokemon is inserted at the
correct position in the binary search tree and prevents duplicate entries. */
void addPokemon(OwnerNode *owner)
{
    PokemonNode *newPokemonRoot;
    // Getting the pokemonID from the user and checking validation
    int pokemonId;
    pokemonId = readIntSafe("Enter ID to add: ");
    if (pokemonId < 1 || pokemonId > POKEMONS_NUM)
    {
        printf("Invalid ID.\n");
        return;
    }
    // Checking if the pokemonID have already inserted.
    if (searchPokemonBST(owner->pokedexRoot, pokemonId))
    {
        printf("Pokemon with ID %d is already in the Pokedex. No changes made.\n", pokemonId);
    }
    else
    {
        // If the owner is empty from pokemons
        if (!owner->pokedexRoot)
        {
            createPokemonNode(&owner->pokedexRoot, (pokemonId - 1));
            printf("Pokemon %s (ID %d) added.\n", owner->pokedexRoot->data->name, pokemonId);
            return;
        }
        // Creating pokemon connected to the newPokemonRoot.
        createPokemonNode(&newPokemonRoot, (pokemonId - 1));
        // Inserting the newPokemonRoot to the right place in pokedexRoot of the chosen owner.
        insertPokemonNode(owner->pokedexRoot, newPokemonRoot);
        printf("Pokemon %s (ID %d) added.\n", newPokemonRoot->data->name, pokemonId);
    }
}

// The function searches for a Pokemon by a given ID in a Binary Search Tree (BST)
PokemonNode *searchPokemonBST(PokemonNode *root, int id)
{
    if (!root)
    {
        return NULL;
    }
    if (root->data->id > id)
    {
        return searchPokemonBST(root->left, id);
    }
    if (root->data->id < id)
    {
        return searchPokemonBST(root->right, id);
    }
    // if (root->data->id == id)
    return root;
}

// The function inserts a new PokemonNode to the correct "leaf" from the given root according to the id.
PokemonNode *insertPokemonNode(PokemonNode *root, PokemonNode *newNode)
{
    if (!root)
    {
        return newNode;
    }
    if (root->data->id > newNode->data->id)
    {
        root->left = insertPokemonNode(root->left, newNode);
    }
    else if (root->data->id < newNode->data->id)
    {
        root->right = insertPokemonNode(root->right, newNode);
    }
    return root;
}

//
void freePokemonNode(PokemonNode *node) {}
void pokemonFight(OwnerNode *owner) {}
void evolvePokemon(OwnerNode *owner) {}
void freePokemon(OwnerNode *owner) {}

// CASE 1 :

// The function creates a new owner and assigns a starter Pokemon to the root.
void openPokedexMenu()
{
    int choice;
    // Allocate memory for a new OwnerNode.
    OwnerNode *newOwner = (OwnerNode *)malloc(sizeof(OwnerNode));
    if (!newOwner)
    {
        printf("Memory allocation failed\n");
        exit(1);
    }
    // Get the new owner name from the user.
    printf("Your name: ");
    newOwner->ownerName = getDynamicInput();
    OwnerNode *currentOwner = ownerHead;
    // Going throuth all the owners list and check duplication of the entered name.
    while (currentOwner)
    {
        // If there's already an owner with that name.
        if (strcmp(newOwner->ownerName, currentOwner->ownerName) == 0)
        {
            printf("Owner '%s' already exists. Not creating a new Pokedex.\n", newOwner->ownerName);
            free(newOwner->ownerName);
            free(newOwner);
            return;
        }
        currentOwner = currentOwner->next;
        // If we got to the beginning, get out since we're done checking.
        if (currentOwner == ownerHead)
        {
            break;
        }
    }
    printf("Choose Starter:\n"
           "1. Bulbasaur\n"
           "2. Charmander\n"
           "3. Squirtle\n");
    choice = readIntSafe("Your choice: ");
    // Check if the choice is valid.
    if (choice < 1 || choice > 3)
    {
        free(newOwner->ownerName);
        free(newOwner);
        printf("Invalid choice.\n");
        return;
    }
    newOwner->pokedexRoot = NULL;
    // Save the Pokemon-ID based on the user's choice.
    int pokemonId = 0;
    if (choice == 1)
    {
        pokemonId = BULBASAUR_ID;
    }
    else if (choice == 2)
    {
        pokemonId = CHARMANDER_ID;
    }
    else if (choice == 3)
    {
        pokemonId = SQUIRTLE_ID;
    }
    // Create the correct pokedex in the newOwner.
    createPokemonNode(&newOwner->pokedexRoot, (pokemonId - 1));
    // If the owners list is empty, initialize it with the new owner.
    if (ownerHead == NULL)
    {
        ownerHead = newOwner;
        newOwner->next = newOwner;
        newOwner->prev = newOwner;
        printf("New Pokedex created for %s with starter %s.\n", newOwner->ownerName, newOwner->pokedexRoot->data->name);
        return;
    }
    // Add the new owner to the "end" of the circular linked list.
    currentOwner = ownerHead;
    while (currentOwner->next != ownerHead)
    {
        currentOwner = currentOwner->next;
    }
    currentOwner->next = newOwner;
    newOwner->next = ownerHead;
    ownerHead->prev = newOwner;
    newOwner->prev = currentOwner;
    printf("New Pokedex created for %s with starter %s.\n", newOwner->ownerName, newOwner->pokedexRoot->data->name);
}

// The function createz a new Pokemon (node) and initialize it with the data from the pokedex with the given id.
PokemonNode *createPokemonNode(PokemonNode **pokemonRoot, int pokemonIndx)
{
    // Allocate memory for a new PokemonNode.
    PokemonNode *newPokemon = (PokemonNode *)malloc(sizeof(PokemonNode));
    if (!newPokemon)
    {
        printf("Memory allocation failed\n");
        exit(1);
    }
    // Allocate memory for the PokemonData inside the new pokemon.
    newPokemon->data = (PokemonData *)malloc(sizeof(PokemonData));
    if (!newPokemon->data)
    {
        printf("Memory allocation failed\n");
        free(newPokemon->data);
        free(newPokemon);
        exit(1);
    }
    // Copy the data from the fit pokedex into the new PokemonData.
    newPokemon->data->attack = pokedex[pokemonIndx].attack;
    newPokemon->data->CAN_EVOLVE = pokedex[pokemonIndx].CAN_EVOLVE;
    newPokemon->data->hp = pokedex[pokemonIndx].hp;
    newPokemon->data->id = pokedex[pokemonIndx].id;
    newPokemon->data->name = myStrdup(pokedex[pokemonIndx].name);
    newPokemon->data->TYPE = pokedex[pokemonIndx].TYPE;
    // Set the left and right to NULL (initially no children).
    newPokemon->left = NULL;
    newPokemon->right = NULL;
    // Assign the new pokemon as the given pokemonRoot.
    *pokemonRoot = newPokemon;
}

// --------------------------------------------------------------
// Main Menu
// --------------------------------------------------------------
void mainMenu()
{
    int choice;
    do
    {
        printf("\n=== Main Menu ===\n");
        printf("1. New Pokedex\n");
        printf("2. Existing Pokedex\n");
        printf("3. Delete a Pokedex\n");
        printf("4. Merge Pokedexes\n");
        printf("5. Sort Owners by Name\n");
        printf("6. Print Owners in a direction X times\n");
        printf("7. Exit\n");
        choice = readIntSafe("Your choice: ");

        switch (choice)
        {
        case 1:
        {
            openPokedexMenu();
            break;
        }
        case 2:
            enterExistingPokedexMenu();
            break;
        case 3:
            deletePokedex();
            break;
        case 4:
            mergePokedexMenu();
            break;
        case 5:
            sortOwners();
            break;
        case 6:
            printOwnersCircular();
            break;
        case 7:
            printf("Goodbye!\n");
            break;
        default:
            printf("Invalid.\n");
        }
    } while (choice != 7);
}

int main()
{
    mainMenu();
    freeAllOwners();
    return 0;
}
