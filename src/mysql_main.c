#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/mysql_test.h"

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