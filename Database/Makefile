DB_USER=root
DB_PASSWORD=password
DB_NAME=password_manager

.PHONY: all create_db create_tables clean

all: create_db create_tables

create_db:
	@mysql -u$(DB_USER) -p$(DB_PASSWORD) -e "CREATE DATABASE IF NOT EXISTS $(DB_NAME);"

create_tables: create_users_table create_passwords_table

create_users_table:
	@mysql -u$(DB_USER) -p$(DB_PASSWORD) $(DB_NAME) < create_users_table.sql

create_passwords_table:
	@mysql -u$(DB_USER) -p$(DB_PASSWORD) $(DB_NAME) < create_passwords_table.sql

clean:
	@mysql -u$(DB_USER) -p$(DB_PASSWORD) -e "DROP DATABASE IF EXISTS $(DB_NAME);"
