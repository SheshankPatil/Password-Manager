CREATE TABLE IF NOT EXISTS passwords (
    id INT NOT NULL AUTO_INCREMENT,
    user_id INT NOT NULL,
    site_name VARCHAR(100) NOT NULL,
    site_username VARCHAR(100) NOT NULL,
    encrypted_password VARCHAR(255) NOT NULL,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    PRIMARY KEY (id),
    FOREIGN KEY (user_id) REFERENCES users(user_id)
);
