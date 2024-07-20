#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Error handling function
void finish_with_error(MYSQL *con) {
    fprintf(stderr, "%s\n", mysql_error(con));
    mysql_close(con);
    exit(1);
}

// Function to insert a new user
int insert_user(MYSQL *con) {
    char username[50];
    char master_password_hash[255];
    MYSQL_RES *result;
    MYSQL_ROW row;

    while (1) {
        // Input for users table
        printf("Enter username: ");
        scanf("%49s", username);

        // Check if username already exists
        char check_query[256];
        snprintf(check_query, sizeof(check_query), "SELECT user_id FROM users WHERE username='%s'", username);

        if (mysql_query(con, check_query)) {
            finish_with_error(con);
        }

        result = mysql_store_result(con);

        if (result == NULL) {
            finish_with_error(con);
        }

        row = mysql_fetch_row(result);
        mysql_free_result(result);

        if (row) {
            printf("Username already taken. Please enter a different username.\n");
        } else {
            break;
        }
    }

    printf("Enter master password hash: ");
    scanf("%254s", master_password_hash);

    char user_query[512];
    snprintf(user_query, sizeof(user_query),
             "INSERT INTO users(username, master_password_hash) VALUES('%s', '%s')",
             username, master_password_hash);

    if (mysql_query(con, user_query)) {
        finish_with_error(con);
    }

    int user_id = mysql_insert_id(con);
    printf("User data inserted successfully. User ID: %d\n", user_id);

    return user_id;
}

// Function to insert a new password entry for a user
void insert_password(MYSQL *con, int user_id) {
    char site_name[100];
    char site_username[100];
    char encrypted_password[255];

    // Input for passwords table
    printf("Enter site name: ");
    scanf("%99s", site_name);
    printf("Enter site username: ");
    scanf("%99s", site_username);
    printf("Enter encrypted password: ");
    scanf("%254s", encrypted_password);

    char password_query[1024];
    int n = snprintf(password_query, sizeof(password_query),
             "INSERT INTO passwords(user_id, site_name, site_username, encrypted_password) VALUES(%d, '%s', '%s', '%s')",
             user_id, site_name, site_username, encrypted_password);

    if (n >= sizeof(password_query) || n < 0) {
        fprintf(stderr, "Query string too long or encoding error occurred.\n");
        mysql_close(con);
        exit(1);
    }

    if (mysql_query(con, password_query)) {
        finish_with_error(con);
    }

    printf("Password data inserted successfully.\n");
}

// Function to retrieve a user's password entry based on site name and username
void retrieve_user_password(MYSQL *con, int user_id) {
    char site_name[100];
    char site_username[100];

    // Input for site name and username
    printf("Enter site name: ");
    scanf("%99s", site_name);
    printf("Enter site username: ");
    scanf("%99s", site_username);

    char query[512];
    snprintf(query, sizeof(query),
             "SELECT encrypted_password FROM passwords WHERE user_id = %d AND site_name = '%s' AND site_username = '%s'",
             user_id, site_name, site_username);

    if (mysql_query(con, query)) {
        finish_with_error(con);
    }

    MYSQL_RES *result = mysql_store_result(con);

    if (result == NULL) {
        finish_with_error(con);
    }

    MYSQL_ROW row = mysql_fetch_row(result);

    if (row) {
        printf("Encrypted password: %s\n", row[0]);
    } else {
        printf("No password found for the given site and username.\n");
    }

    mysql_free_result(result);
}

// Function to handle user login
int login_user(MYSQL *con) {
    char username[50];
    char master_password_hash[255];
    MYSQL_RES *result;
    MYSQL_ROW row;

    printf("Enter username: ");
    scanf("%49s", username);
    printf("Enter master password hash: ");
    scanf("%254s", master_password_hash);

    char login_query[512];
    snprintf(login_query, sizeof(login_query),
             "SELECT user_id FROM users WHERE username='%s' AND master_password_hash='%s'",
             username, master_password_hash);

    if (mysql_query(con, login_query)) {
        finish_with_error(con);
    }

    result = mysql_store_result(con);

    if (result == NULL) {
        finish_with_error(con);
    }

    row = mysql_fetch_row(result);
    mysql_free_result(result);

    if (row) {
        printf("Login successful. User ID: %s\n", row[0]);
        return atoi(row[0]);
    } else {
        printf("Invalid username or master password hash.\n");
        return -1;
    }
}

// Main function
int main() {
    MYSQL *con = mysql_init(NULL);

    if (con == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        exit(1);
    }

    if (mysql_real_connect(con, "localhost", "peace", "2209",
                           "password_manager", 0, NULL, 0) == NULL) {
        finish_with_error(con);
    }

    int exit_program = 0;

    while (!exit_program) {
        int mode;
        printf("\nEnter mode (1 for register, 2 for login, 3 to exit): ");
        scanf("%d", &mode);

        switch (mode) {
            case 1:
                insert_user(con);
                break;
            case 2: {
                int user_id = login_user(con);
                if (user_id != -1) {
                    int action;
                    printf("Enter action (1 to insert password, 2 to retrieve password, 3 to logout): ");
                    scanf("%d", &action);
                    switch (action) {
                        case 1:
                            insert_password(con, user_id);
                            break;
                        case 2:
                            retrieve_user_password(con, user_id);
                            break;
                        case 3:
                            printf("Logging out...\n");
                            break;
                        default:
                            fprintf(stderr, "Invalid action entered.\n");
                            break;
                    }
                }
                break;
            }
            case 3:
                exit_program = 1;
                break;
            default:
                fprintf(stderr, "Invalid mode entered.\n");
                break;
        }
    }

    mysql_close(con);

    return 0;
}
