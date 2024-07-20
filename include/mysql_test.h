#ifndef MYSQL_TEST_H
#define MYSQL_TEST_H

#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

MYSQL Connection_establish();
void finish_with_error(MYSQL *con);
int insert_user(MYSQL *con, char *username, char *password);

#ifdef __cplusplus
}
#endif

#endif
