#include "../include/mysql_test.h"
#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void finish_with_error(MYSQL *con) {
  fprintf(stderr, "%s\n", mysql_error(con));
  mysql_close(con);
  exit(1);
}

MYSQL Connection_establish() {
  MYSQL *con = mysql_init(NULL);

  if (con == NULL) {
    fprintf(stderr, "mysql_init() failed\n");
    exit(1);
  }

  if (mysql_real_connect(con, "localhost", "peace", "2209",
                         "password_manager", 0, NULL, 0) == NULL) {
    finish_with_error(con);
  }
  return *con;
}

int insert_user(MYSQL *con, char username[50], char master_password_hash[255]) {
  char user_query[512];
  snprintf(
      user_query, sizeof(user_query),
      "INSERT INTO users(username, master_password_hash) VALUES('%s', '%s')",
      username, master_password_hash);

  if (mysql_query(con, user_query)) {
    finish_with_error(con);
  }

  int user_id = mysql_insert_id(con);
  printf("User data inserted successfully. User ID: %d\n", user_id);
  return user_id;
}