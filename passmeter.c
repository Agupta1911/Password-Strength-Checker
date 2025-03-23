#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <time.h>
// Checks that the password is strong.
bool isStrongPassword(const char *username, const char *password) {
    int length = strlen(password);
    if (length < 8){ 
        return false; // Checks that it is atleast 8 characters
    }
    
    bool has_digit = false, has_upper = false, has_lower = false, has_consecutive_letters = false;
    int consecutive_letter_count = 0;
    
    for (int i = 0; i < length; i++) {
        if (isupper(password[i])){ 
            has_upper = true;
        }else if (islower(password[i])){ 
            has_lower = true;
        }else if (isdigit(password[i])){ 
            has_digit = true;
        }else{
            return false; // There is an invalid character in the password
        }
        
        if (isalpha(password[i])) {
            consecutive_letter_count++;
            if (consecutive_letter_count >= 4){ 
                has_consecutive_letters = true;
            }
        } else {
            consecutive_letter_count = 0;
        }
    }

    int name_length = strlen(username);
    for (int i = 0; i <= length-name_length; i++) {
        bool contains = true;
        for (int j = 0; j < name_length; j++) {
            if (tolower(password[i + j]) != tolower(username[j])) {
                contains = false;
                break;
            }
        }
        if (contains) {
            return false;
        } 
    }
    return has_upper && has_lower && has_digit && has_consecutive_letters;
}
// Checks if default password is valid
bool isStrongDefaultPassword(const char* username, const char* password) {
    int length = strlen(password);
    if (length < 8 || length > 15){ 
        return false;
    }
    
    bool has_upper = false, has_lower = false, has_digit = false;
    
    for (int i = 0; i < length; i++) {
        if (isupper(password[i])){ 
            has_upper = true;
        }else if (islower(password[i])){ 
            has_lower = true;
        }else if (isdigit(password[i])){ 
            has_digit = true;
        }else{
            return false; // There is an invalid character in the password
        }
    }
    int name_length = strlen(username);
    for (int i = 0; i <= length-name_length; i++) {
        bool contains = true;
        for (int j = 0; j < name_length; j++) {
            if (tolower(password[i + j]) != tolower(username[j])) {
                contains = false;
                break;
            }
        }
        if (contains){ 
            return false;
        } 
    }
    return has_upper && has_lower && has_digit;
}
// Generates a random default password
void generateDefaultPassword(char *default_pwd, const char *username) {
    const char valid_characters[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    int max_length = 8 + rand() % 8;
    
    do {
        for (int i = 0; i < max_length; i++) {
            int key = rand() % strlen(valid_characters);
            default_pwd[i] = valid_characters[key];
        }
        default_pwd[max_length] = '\0';
    } while (!isStrongDefaultPassword(username, default_pwd));
}

int main(void) {
    srand(time(NULL));
    
    char username[100];
    char password[100];
    char default_password[16];
    
    printf("Enter username: ");
    scanf("%s", username);
    
    printf("Enter new password: ");
    scanf("%s", password);
    
    if (!isStrongPassword(username, password)) {
        printf("Your password is weak. Try again!\n");
        generateDefaultPassword(default_password, username);
        printf("Generating a default password...\n");
        printf("Generated default password: %s\n", default_password);
    } else {
        printf("Strong password!\n");
    }
    
    char choice;
    printf("Do you want to make a new password? (y/n): ");
    scanf(" %c", &choice);
    
    if (choice == 'y' || choice == 'Y') {
        printf("Enter new password: ");
        scanf("%s", password);
        if (isStrongPassword(username, password)) {
            printf("Strong password!\n");
        } else {
            printf("Your password is weak.\n");
        }
    }
    
    return 0;
}
