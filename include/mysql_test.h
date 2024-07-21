#ifndef MYSQL_TEST_H
#define MYSQL_TEST_H

#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>


void finish_with_error(MYSQL *con); 
int insert_user(MYSQL *con);
void insert_password(MYSQL *con, int user_id);
void retrieve_user_password(MYSQL *con, int user_id);
int login_user(MYSQL *con);
 

#endif
