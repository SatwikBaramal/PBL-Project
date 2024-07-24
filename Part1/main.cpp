#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a structure for the email node
struct EmailNode
{
    char subject[50];
    char sender[50];
    char message[200];
    struct EmailNode *next;
};

// Define a structure for the user
struct User
{
    char username[50];
    struct EmailNode *inbox;
};

// Function to find a user by username
struct User *findUser(struct User *users, int numUsers, const char *targetUsername)
{
    for (int i = 0; i < numUsers; ++i)
    {
        if (strcmp(users[i].username, targetUsername) == 0)
        {
            return &users[i];
        }
    }
    return NULL; // User not found
}

// Function to send an email from one user to another
void sendEmail(struct User *users, int numUsers, const char *senderUsername, const char *receiverUsername,
               const char *subject, const char *message)
{
    struct User *sender = findUser(users, numUsers, senderUsername);
    struct User *receiver = findUser(users, numUsers, receiverUsername);

    if (sender != NULL && receiver != NULL)
    {
        struct EmailNode *newEmail = (struct EmailNode *)malloc(sizeof(struct EmailNode));
        if (newEmail == NULL)
        {
            printf("Memory allocation error.\n");
            exit(EXIT_FAILURE);
        }

        strncpy(newEmail->subject, subject, sizeof(newEmail->subject) - 1);
        strncpy(newEmail->sender, senderUsername, sizeof(newEmail->sender) - 1);
        strncpy(newEmail->message, message, sizeof(newEmail->message) - 1);

        // Insert the new email at the beginning of the receiver's inbox
        newEmail->next = receiver->inbox;
        receiver->inbox = newEmail;
        printf("Email sent successfully from %s to %s\n", senderUsername, receiverUsername);
    }
    else
    {
        printf("User not found. Email not sent.\n");
    }
}

// Function to display the inbox of a specific user
void displayInbox(const struct User *user)
{
    printf("Inbox for user %s:\n", user->username);
    struct EmailNode *current = user->inbox;
    while (current != NULL)
    {
        printf("-----------------------------\n");
        printf("Subject: %s\n", current->subject);
        printf("Sender: %s\n", current->sender);
        printf("Message: %s\n", current->message);

        current = current->next;
    }
}

// Function to register a new user
void registerUser(struct User **users, int *numUsers, const char *newUsername)
{
    users = (struct User)realloc(*users, (*numUsers + 1) * sizeof(struct User));
    if (*users == NULL)
    {
        printf("Memory allocation error.\n");
        exit(EXIT_FAILURE);
    }

    strncpy((*users)[*numUsers].username, newUsername, sizeof((*users)[*numUsers].username) - 1);
    (*users)[*numUsers].inbox = NULL;

    printf("User %s registered successfully.\n", newUsername);
    (*numUsers)++;
}

// Function to get user input for strings
char *getUserInput(const char *prompt)
{
    char buffer[200];

    printf("%s", prompt);
    fflush(stdin); // Clear the input buffer
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = '\0'; // Remove newline character

    // Allocate memory for the string and copy the input
    char *userInput = (char *)malloc(strlen(buffer) + 1);
    if (userInput == NULL)
    {
        printf("Memory allocation error.\n");
        exit(EXIT_FAILURE);
    }
    strcpy(userInput, buffer);

    return userInput;
}

// Function to handle the main menu
int mainMenu()
{
    int choice;
    printf("\nMain Menu:\n");
    printf("1. Login\n");
    printf("2. Sign Up\n");
    printf("3. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    getchar(); // Consume the newline character in the buffer

    return choice;
}

// Function to handle the user menu
int userMenu()
{
    int choice;
    printf("\nUser Menu:\n");
    printf("1. View Messages\n");
    printf("2. Send Email\n");
    printf("3. Logout\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    getchar(); // Consume the newline character in the buffer

    return choice;
}

void clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

int main()
{
    struct User *users = NULL;
    int numUsers = 0;
    int mainChoice, userChoice;
    char *username;

    do
    {
        mainChoice = mainMenu();

        switch (mainChoice)
        {
        case 1:
        {
            clearScreen();
            username = getUserInput("Enter your username: ");
            struct User *currentUser = findUser(users, numUsers, username);
            if (currentUser != NULL)
            {
                do
                {
                    userChoice = userMenu();

                    switch (userChoice)
                    {
                    case 1:
                        clearScreen();
                        displayInbox(currentUser);
                        break;
                    case 2:
                    {
                        clearScreen();
                        char *receiver = getUserInput("Enter receiver's username: ");
                        char *subject = getUserInput("Enter email subject: ");
                        char *message = getUserInput("Enter email message: ");

                        sendEmail(users, numUsers, username, receiver, subject, message);

                        free(receiver);
                        free(subject);
                        free(message);
                        break;
                    }
                    case 3:
                        clearScreen();
                        printf("Logging out...\n");
                        break;
                    default:
                        clearScreen();
                        printf("Invalid choice. Please enter a valid option.\n");
                        break;
                    }
                } while (userChoice != 3);
            }
            else
            {
                clearScreen();
                printf("User not found. Please sign up.\n");
            }

            // Free the memory allocated for username
            free(username);
            break;
        }
        case 2:
        {
            clearScreen();
            char *newUsername = getUserInput("Enter a new username: ");
            registerUser(&users, &numUsers, newUsername);

            // Free the memory allocated for the new username
            free(newUsername);
            break;
        }
        case 3:
            clearScreen();
            printf("Exiting program.\n");
            break;
        default:
            clearScreen();
            printf("Invalid choice. Please enter a valid option.\n");
            break;
        }

    } while (mainChoice != 3);

    // Clean up allocated memory for emails (deallocate linked lists)
    for (int i = 0; i < numUsers; ++i)
    {
        struct EmailNode *current = users[i].inbox;
        while (current != NULL)
        {
            struct EmailNode *next = current->next;
            free(current);
            current = next;
        }
    }

    // Clean up allocated memory for users
    free(users);

        return 0;
}