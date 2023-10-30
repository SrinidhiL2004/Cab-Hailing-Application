#ifndef LOGIN_H
#define LOGIN_H

#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 20
#define MAX_PASSWORD_LENGTH 20

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

User users[20];  // Array to store user data
int userCount = 0;  // Number of registered users

void signup() {
    if (userCount == 10) {
        printf("Maximum number of users reached. Signup is not available.\n");
        return;
    }

    User newUser;

    printf("Enter username: ");
    scanf("%s", newUser.username);

    // Check if the username is already taken
    for (int i = 0; i < userCount; i++) {
        if (strcmp(newUser.username, users[i].username) == 0) {
            printf("Username already taken. Please choose a different username.\n");
            return;
        }
    }

    printf("Enter password: ");
    scanf("%s", newUser.password);

    printf("Repeat password: ");
    char repeatPassword[MAX_PASSWORD_LENGTH];
    scanf("%s", repeatPassword);

    // Check if the passwords match
    if (strcmp(newUser.password, repeatPassword) != 0) {
        printf("Passwords do not match. Signup failed.\n");
        return;
    }

    // Add the new user to the array
    users[userCount++] = newUser;

    printf("Signup successful!\n");
}

char current_user[MAX_USERNAME_LENGTH];

int Login() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter username: ");
    scanf("%s", username);

    printf("Enter password: ");
    scanf("%s", password);

    // Check if the username and password match
    for (int i = 0; i < userCount; i++) {
        if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0) {
            strcpy(current_user, username);
            return 1;  // Login successful
        }
    }

    return 0;  // Login failed
}

#endif // LOGIN_H
