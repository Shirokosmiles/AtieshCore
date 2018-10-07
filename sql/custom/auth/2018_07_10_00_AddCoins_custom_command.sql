-- Rbac AddCoin custom command
DELETE FROM `rbac_permissions` WHERE `Id` = 1114;
INSERT INTO `rbac_permissions` VALUES
('1114', 'Command: AddCoin');
DELETE FROM `rbac_linked_permissions` WHERE `linkedId` = 1114;
INSERT INTO `rbac_linked_permissions` VALUES
('192','1114');