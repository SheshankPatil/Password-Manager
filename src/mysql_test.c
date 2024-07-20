#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void finish_with_error(MYSQL *con) 
{
    fprintf(stderr, "%s\n", mysql_error(con));
    mysql_close(con);
    exit(1);
}

int insert_user(MYSQL *con)
 {
    char username[50];
    char master_password_hash[255];

    // Input for users table
    printf("Enter username: ");
    scanf("%49s", username);
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

    int mode;
    printf("Enter mode (1 for register, 2 for retrieve): ");
    scanf("%d", &mode);

    switch (mode) {
        case 1: {
            int user_id = insert_user(con);
            int action;
            printf("Enter action (1 to insert password, 2 to retrieve password): ");
            scanf("%d", &action);
            switch (action) {
                case 1:
                    insert_password(con, user_id);
                    break;
                case 2:
                    retrieve_user_password(con, user_id);
                    break;
                default:
                    fprintf(stderr, "Invalid action entered.\n");
                    break;
            }
            break;
        }
        case 2: {
            int user_id;
            printf("Enter user ID to retrieve password: ");
            scanf("%d", &user_id);
            retrieve_user_password(con, user_id);
            break;
        }
        default:
            fprintf(stderr, "Invalid mode entered.\n");
            break;
    }

    mysql_close(con);

    return 0;
}
