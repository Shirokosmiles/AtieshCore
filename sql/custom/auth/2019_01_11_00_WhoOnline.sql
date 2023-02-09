DELETE FROM `rbac_linked_permissions` WHERE `Id`=199 AND `linkedId` IN (28);
INSERT INTO `rbac_linked_permissions` (`id`, `linkedId`) VALUES ('199', '28');