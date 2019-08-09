DELETE FROM `rbac_permissions` where `id` IN ("1020");
INSERT INTO `rbac_permissions` (`id`, `name`) values
('1020', 'gprogress'); 

DELETE FROM `rbac_linked_permissions` where `linkedId` IN ('1020');
INSERT INTO `rbac_linked_permissions` (`id`, `linkedId`) values
('195','1020'); 