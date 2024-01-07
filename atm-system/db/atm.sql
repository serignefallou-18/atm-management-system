/*==============================================================*/
/* Nom de SGBD :  Sqlite3                                     */
/* Date de création :  06/01/2024 17:19:22                      */
/*==============================================================*/

-- Suppression des tables si elles existent déjà
DROP TABLE IF EXISTS records;
DROP TABLE IF EXISTS users;

-- Création de la table records
CREATE TABLE records (
    idaccount INTEGER PRIMARY KEY,
    login VARCHAR(254),
    ussername VARCHAR(254),
    datecreation DATETIME,
    country VARCHAR(254),
    phone INTEGER,
    balance INTEGER,
    type VARCHAR(254),
    FOREIGN KEY (login) REFERENCES users(login)
);

-- Création de la table users
CREATE TABLE users (
    login VARCHAR(254) PRIMARY KEY,
    password VARCHAR(254)
);
