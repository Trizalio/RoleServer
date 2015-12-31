#include "sqlconnector.h"
#include <QtCore/QDebug>


#include <mysql_connection.h>

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

void CreateTables()
{

    stmt = con->createStatement();
    stmt->execute("DROP TABLE IF EXISTS test");
    stmt->execute("CREATE TABLE test(id INT)");
    delete stmt;

    /* '?' is the supported placeholder syntax */
    pstmt = con->prepareStatement("INSERT INTO test(id) VALUES (?)");
    for (int i = 1; i <= 10; i++) {
      pstmt->setInt(1, i);
      pstmt->executeUpdate();
    }
    delete pstmt;
}

SqlConnector::SqlConnector()
{

    qDebug();
    qDebug() << "Running 'SELECT 'Hello World!' AS _message'...";

    try {
      sql::Driver *driver;
      sql::Connection *con;
      sql::Statement *stmt;
      sql::ResultSet *res;

      /* Create a connection */
      driver = get_driver_instance();
      con = driver->connect("tcp://127.0.0.1:3306", "root", "3421Dark");
      /* Connect to the MySQL test database */
      con->setSchema("space_base");

      stmt = con->createStatement();
      res = stmt->executeQuery("SELECT 'Hello World!' AS _message");
      while (res->next()) {
        qDebug() << "\t... MySQL replies: ";
        /* Access column data by alias or column name */
        qDebug() << res->getString("_message").c_str();
        qDebug() << "\t... MySQL says it again: ";
        /* Access column fata by numeric offset, 1 is the first column */
        qDebug() << res->getString(1).c_str();
      }
      delete res;
      delete stmt;
      delete con;

    } catch (sql::SQLException &e) {
      qDebug() << "# ERR: SQLException in " << __FILE__;
      qDebug() << "(" << __FUNCTION__ << ") on line " << __LINE__;
      qDebug() << "# ERR: " << e.what();
      qDebug() << " (MySQL error code: " << e.getErrorCode();
      qDebug() << ", SQLState: " << e.getSQLState().c_str() << " )";
    }

    qDebug();

    /*
-- ---
-- Globals
-- ---

-- SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";
-- SET FOREIGN_KEY_CHECKS=0;

-- ---
-- Table 'Users'
--
-- ---

DROP TABLE IF EXISTS `Users`;

CREATE TABLE `Users` (
  `id` INTEGER NULL AUTO_INCREMENT DEFAULT NULL,
  `name` VARCHAR(50) NOT NULL,
  `surname` VARCHAR(50) NOT NULL,
  `patronymic` VARCHAR NOT NULL,
  `birth_date` DATE NOT NULL,
  `profession` VARCHAR(50) NOT NULL,
  `discription` VARCHAR NOT NULL,
  PRIMARY KEY (`id`)
);

-- ---
-- Table 'Players'
--
-- ---

DROP TABLE IF EXISTS `Players`;

CREATE TABLE `Players` (
  `id` INTEGER NOT NULL AUTO_INCREMENT,
  `fk_User_id` INTEGER NOT NULL,
  `name` VARCHAR(50) NOT NULL,
  `surname` VARCHAR(50) NOT NULL,
  `patronymic` VARCHAR(50) NOT NULL,
  `quenta` MEDIUMTEXT NOT NULL,
  `nick` VARCHAR NOT NULL,
  `birth_date` DATE NOT NULL,
  PRIMARY KEY (`id`),
KEY (`fk_User_id`)
);

-- ---
-- Table 'Credentials'
--
-- ---

DROP TABLE IF EXISTS `Credentials`;

CREATE TABLE `Credentials` (
  `id` INTEGER NULL AUTO_INCREMENT DEFAULT NULL,
  `Login` VARCHAR(50) NOT NULL,
  `PasswordHash` VARCHAR(50) NOT NULL,
  PRIMARY KEY (`id`)
);

-- ---
-- Table 'Messages'
--
-- ---

DROP TABLE IF EXISTS `Messages`;

CREATE TABLE `Messages` (
  `id` INTEGER NULL AUTO_INCREMENT DEFAULT NULL,
  `fk_User_id_from` INTEGER NOT NULL,
  `fk_Users_id_to` INTEGER NOT NULL,
  `subject` VARCHAR NOT NULL,
  `text` MEDIUMTEXT NOT NULL,
  `anonymously` bit NOT NULL DEFAULT False,
  PRIMARY KEY (`id`),
KEY (`fk_User_id_from`),
KEY (`fk_Users_id_to`)
);

-- ---
-- Table 'Groups'
--
-- ---

DROP TABLE IF EXISTS `Groups`;

CREATE TABLE `Groups` (
  `id` INTEGER NULL AUTO_INCREMENT DEFAULT NULL,
  `fk_Groups_id_parent` INTEGER NULL DEFAULT NULL,
  `name` VARCHAR NOT NULL,
  `Discription` MEDIUMTEXT NOT NULL,
  PRIMARY KEY (`id`),
KEY (`fk_Groups_id_parent`)
);

-- ---
-- Table 'News'
--
-- ---

DROP TABLE IF EXISTS `News`;

CREATE TABLE `News` (
  `id` INTEGER NULL AUTO_INCREMENT DEFAULT NULL,
  `fk_RoleDistribution_id` INTEGER NOT NULL,
  `created` DATETIME NOT NULL,
  `subject` VARCHAR NOT NULL,
  `text` MEDIUMTEXT NOT NULL,
  `anonymously` bit NOT NULL DEFAULT False,
  PRIMARY KEY (`id`),
KEY (`fk_RoleDistribution_id`)
);

-- ---
-- Table 'Roles'
--
-- ---

DROP TABLE IF EXISTS `Roles`;

CREATE TABLE `Roles` (
  `id` INTEGER NULL AUTO_INCREMENT DEFAULT NULL,
  `fk_Groups_id` INTEGER NOT NULL,
  `administrator` bit NULL DEFAULT NULL,
  PRIMARY KEY (`id`),
KEY (`fk_Groups_id`)
);

-- ---
-- Table 'RolesDistribution'
--
-- ---

DROP TABLE IF EXISTS `RolesDistribution`;

CREATE TABLE `RolesDistribution` (
  `id` INTEGER NOT NULL AUTO_INCREMENT,
  `fk_Users_id` INTEGER NOT NULL,
  `fk_Roles_id` INTEGER NOT NULL,
  PRIMARY KEY (`id`),
KEY (`fk_Roles_id`),
KEY (`fk_Users_id`)
);

-- ---
-- Table 'Payments'
--
-- ---

DROP TABLE IF EXISTS `Payments`;

CREATE TABLE `Payments` (
  `id` INTEGER NULL AUTO_INCREMENT DEFAULT NULL,
  `fk_Players_id_payer` INTEGER NULL,
  `fk_Players_id_controller` INTEGER NOT NULL,
  `datetime` DATETIME NOT NULL,
  `value` INTEGER NOT NULL,
  PRIMARY KEY (`id`),
KEY (`fk_Players_id_payer`),
KEY (`fk_Players_id_controller`)
);

-- ---
-- Foreign Keys
-- ---

ALTER TABLE `Players` ADD FOREIGN KEY (id) REFERENCES `Credentials` (`id`);
ALTER TABLE `Players` ADD FOREIGN KEY (id) REFERENCES `Payments` (`fk_Players_id_payer`);
ALTER TABLE `Players` ADD FOREIGN KEY (id) REFERENCES `Payments` (`fk_Players_id_controller`);
ALTER TABLE `Players` ADD FOREIGN KEY (fk_User_id) REFERENCES `Users` (`id`);
ALTER TABLE `Messages` ADD FOREIGN KEY (fk_User_id_from) REFERENCES `Users` (`id`);
ALTER TABLE `Messages` ADD FOREIGN KEY (fk_Users_id_to) REFERENCES `Users` (`id`);
ALTER TABLE `Groups` ADD FOREIGN KEY (id) REFERENCES `Roles` (`fk_Groups_id`);
ALTER TABLE `Groups` ADD FOREIGN KEY (fk_Groups_id_parent) REFERENCES `Groups` (`id`);
ALTER TABLE `RolesDistribution` ADD FOREIGN KEY (id) REFERENCES `News` (`fk_RoleDistribution_id`);
ALTER TABLE `RolesDistribution` ADD FOREIGN KEY (fk_Users_id) REFERENCES `Users` (`id`);
ALTER TABLE `RolesDistribution` ADD FOREIGN KEY (fk_Roles_id) REFERENCES `Roles` (`id`);

-- ---
-- Table Properties
-- ---

-- ALTER TABLE `Users` ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
-- ALTER TABLE `Players` ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
-- ALTER TABLE `Credentials` ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
-- ALTER TABLE `Messages` ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
-- ALTER TABLE `Groups` ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
-- ALTER TABLE `News` ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
-- ALTER TABLE `Roles` ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
-- ALTER TABLE `RolesDistribution` ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
-- ALTER TABLE `Payments` ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin;

-- ---
-- Test Data
-- ---

-- INSERT INTO `Users` (`id`,`name`,`surname`,`patronymic`,`birth_date`,`profession`,`discription`) VALUES
-- ('','','','','','','');
-- INSERT INTO `Players` (`id`,`fk_User_id`,`name`,`surname`,`patronymic`,`quenta`,`nick`,`birth_date`) VALUES
-- ('','','','','','','','');
-- INSERT INTO `Credentials` (`id`,`Login`,`PasswordHash`) VALUES
-- ('','','');
-- INSERT INTO `Messages` (`id`,`fk_User_id_from`,`fk_Users_id_to`,`subject`,`text`,`anonymously`) VALUES
-- ('','','','','','');
-- INSERT INTO `Groups` (`id`,`fk_Groups_id_parent`,`name`,`Discription`) VALUES
-- ('','','','');
-- INSERT INTO `News` (`id`,`fk_RoleDistribution_id`,`created`,`subject`,`text`,`anonymously`) VALUES
-- ('','','','','','');
-- INSERT INTO `Roles` (`id`,`fk_Groups_id`,`administrator`) VALUES
-- ('','','');
-- INSERT INTO `RolesDistribution` (`id`,`fk_Users_id`,`fk_Roles_id`) VALUES
-- ('','','');
-- INSERT INTO `Payments` (`id`,`fk_Players_id_payer`,`fk_Players_id_controller`,`datetime`,`value`) VALUES
-- ('','','','','');
*/
}
