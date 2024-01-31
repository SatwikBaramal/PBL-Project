#include <iostream>
#include <string>

using namespace std;

// Structure for mail
struct Mail {
    string sender;
    string content;
    Mail* next;
};

// Structure for user
struct User {
    int id;
    Mail* inbox;
    User* next;
};

class MailSystem {
private:
    static const int MAX_USERS = 10;
    User* users[MAX_USERS];

public:
    MailSystem() {
        for (int i = 0; i < MAX_USERS; ++i) {
            users[i] = nullptr;
        }
    }

    // Function to add a new user
    void addUser(int userId) {
        if (users[userId] != nullptr) {
            cout << "User already exists." << endl;
            return;
        }
        User* newUser = new User;
        newUser->id = userId;
        newUser->inbox = nullptr;
        newUser->next = nullptr;
        users[userId] = newUser;
        cout << "User " << userId << " added." << endl;
    }

    // Function to delete a user
    void deleteUser(int userId) {
        if (users[userId] == nullptr) {
            cout << "User does not exist." << endl;
            return;
        }
        Mail* currentMail = users[userId]->inbox;
        while (currentMail != nullptr) {
            Mail* temp = currentMail;
            currentMail = currentMail->next;
            delete temp;
        }
        delete users[userId];
        users[userId] = nullptr;
        cout << "User " << userId << " deleted." << endl;
    }

    // Function to send a mail
    void sendMail(int senderId, int receiverId, const string& content) {
        if (users[senderId] == nullptr || users[receiverId] == nullptr) {
            cout << "Invalid sender or receiver." << endl;
            return;
        }
        Mail* newMail = new Mail;
        newMail->sender = to_string(senderId);
        newMail->content = content;
        newMail->next = nullptr;
        if (users[receiverId]->inbox == nullptr) {
            users[receiverId]->inbox = newMail;
        } else {
            Mail* currentMail = users[receiverId]->inbox;
            while (currentMail->next != nullptr) {
                currentMail = currentMail->next;
            }
            currentMail->next = newMail;
        }
        cout << "Mail sent from User " << senderId << " to User " << receiverId << endl;
    }

    // Function to check mails
    void checkMail(int userId) {
        if (users[userId] == nullptr) {
            cout << "User does not exist." << endl;
            return;
        }
        cout << "Inbox of User " << userId << ":" << endl;
        Mail* currentMail = users[userId]->inbox;
        while (currentMail != nullptr) {
            cout << "From: User " << currentMail->sender << ", Content: " << currentMail->content << endl;
            currentMail = currentMail->next;
        }
    }

    // Function to delete all mails of a user
    void deleteMail(int userId) {
        if (users[userId] == nullptr) {
            cout << "User does not exist." << endl;
            return;
        }
        Mail* currentMail = users[userId]->inbox;
        while (currentMail != nullptr) {
            Mail* temp = currentMail;
            currentMail = currentMail->next;
            delete temp;
        }
        users[userId]->inbox = nullptr;
        cout << "Inbox of User " << userId << " deleted." << endl;
    }
};

int main() {
    MailSystem mailSystem;

    // Adding users
    mailSystem.addUser(0);
    mailSystem.addUser(1);

    // Sending mails
    mailSystem.sendMail(0, 1, "Hello User 1!");
    mailSystem.sendMail(1, 0, "Hi User 0!");

    // Checking mails
    mailSystem.checkMail(0);
    mailSystem.checkMail(1);

    // Deleting user 0
    mailSystem.deleteUser(0);

    // Trying to send mail after deleting user 0
    mailSystem.sendMail(1, 0, "Trying to send mail to deleted user.");

    return 0;
}
