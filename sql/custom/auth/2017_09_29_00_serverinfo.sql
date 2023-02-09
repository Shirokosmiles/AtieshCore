DELETE FROM `rbac_linked_permissions` WHERE `Id`=199 AND `linkedId` IN (725,718);
INSERT INTO `rbac_linked_permissions` (`id`, `linkedId`) VALUES ('199', '725');
INSERT INTO `rbac_linked_permissions` (`id`, `linkedId`) VALUES ('199', '718');