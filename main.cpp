#include <iostream>
#include<iomanip>
#include <cstring>
using namespace std;
// Define a struct for the email node
typedef struct EmailNode {
    char subject[50];
    char sender[50];
    char message[200];
    EmailNode* next;

    // Constructor to initialize the email node
    EmailNode(const char* _subject, const char* _sender, const char* _message)
        : next(nullptr) {
        strncpy(subject, _subject, sizeof(subject) - 1);
        strncpy(sender, _sender, sizeof(sender) - 1);
        strncpy(message, _message, sizeof(message) - 1);
    }
} EmailNode;

// Define a struct for the user
typedef struct User {
    char username[50];
    EmailNode* inbox;

    // Constructor to initialize the user
    User(const char* _username) : inbox(nullptr) {
        strncpy(username, _username, sizeof(username) - 1);
    }
} User;

// Function to find a user by username
User* findUser(User* users, int numUsers, const char* targetUsername) {
    for (int i = 0; i < numUsers; ++i) {
        if (strcmp(users[i].username, targetUsername) == 0) {
            return &users[i];
        }
    }
    return nullptr; // User not found
}

// Function to send an email from one user to another
void sendEmail(User* users, int numUsers, const char* senderUsername, const char* receiverUsername,
               const char* subject, const char* message) {
    User* sender = findUser(users, numUsers, senderUsername);
    User* receiver = findUser(users, numUsers, receiverUsername);

    if (sender != nullptr && receiver != nullptr) {
        EmailNode* newEmail = new EmailNode(subject, senderUsername, message);
        // Insert the new email at the beginning of the receiver's inbox
        newEmail->next = receiver->inbox;
        receiver->inbox = newEmail;
        std::cout << "Email sent successfully from " << senderUsername << " to " << receiverUsername << "\n";
    } else {
        std::cout << "User not found. Email not sent.\n";
    }
}

// Function to get user input for sending emails
void getUserInput(User* users, int numUsers) {
    char senderUsername[50];
    char receiverUsername[50];
    char subject[50];
    char message[200];

    // Get sender's username
    std::cout << "Enter sender's username: ";
    std::cin >> senderUsername;

    // Get receiver's username
    std::cout << "Enter receiver's username: ";
    std::cin >> receiverUsername;

    // Get email subject
    std::cout << "Enter email subject: ";
    std::cin.ignore(); // Clear the input buffer
    std::cin.getline(subject, sizeof(subject));

    // Get email message
    std::cout << "Enter email message: ";
    std::cin.getline(message, sizeof(message));

    // Send the email
    sendEmail(users, numUsers, senderUsername, receiverUsername, subject, message);
}

// Function to display the inbox of a specific user
void displayInbox(const User& user) {
    std::cout << "Inbox for user " << user.username << ":\n";
    EmailNode* current = user.inbox;
    while (current != nullptr) {
        std::cout << "Subject: " << current->subject << "\n";
        std::cout << "Sender: " << current->sender << "\n";
        std::cout << "Message: " << current->message << "\n";
        std::cout << "-----------------------------\n";
        current = current->next;
    }
}

int main() {
    const int numUsers = 3;
    User users[numUsers] = {{"Alice"}, {"Bob"}, {"Charlie"}};

    // Get user input for sending emails
    getUserInput(users, numUsers);

    // Display the inboxes after sending emails
    for (int i = 0; i < numUsers; ++i) {
        displayInbox(users[i]);
    }

    // Clean up allocated memory for emails (deallocate linked lists)
    for (int i = 0; i < numUsers; ++i) {
        EmailNode* current = users[i].inbox;
        while (current != nullptr) {
            EmailNode* next = current->next;
            delete current;
            current = next;
        }
    }

    return 0;
}