DROP DATABASE IF EXISTS `sql_virtual_store`;
CREATE DATABASE `sql_virtual_store`;
USE `sql_virtual_store`;

SET NAMES utf8;
SET character_set_client = utf8mb4;

CREATE TABLE `products` (
	`id` INT PRIMARY KEY AUTO_INCREMENT,
	`name` VARCHAR(100) NOT NULL DEFAULT 'iaurt',
    `type` VARCHAR(100) NOT NULL DEFAULT 'produse lactate',
    `price` DOUBLE NOT NULL CHECK (`price` > 0.0) DEFAULT 4.63,
    `producer` VARCHAR(100) NOT NULL DEFAULT 'Danone',
    UNIQUE (`name`, `producer`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

INSERT INTO `products` (`name`, `type`, `price`, `producer`) VALUES
('rozmarin', 'condimente', 1.68, 'Kamis'),
('chipsuri', 'snacksuri', 9.1, 'Pringles'),
('suc', 'bauturi racoritoare', 15.5, 'Coca-Cola'),
('boia', 'condimente', 0.999, 'Delikat'),
('parmezan', 'condimente', 8.301, 'Delikat'),
('chipsuri', 'snacksuri', 1.53, 'Chio'),
('coriandru', 'condimente', 0.0471, 'Knorr'),
('iaurt', 'produse lactate', 5.013, 'Milka UK');

SELECT * FROM `products`;