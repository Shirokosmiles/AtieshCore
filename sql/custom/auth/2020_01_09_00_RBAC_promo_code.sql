DELETE FROM `rbac_permissions` where `id` IN ("1021");
INSERT INTO `rbac_permissions` (`id`, `name`) values
('1021', 'Command: reload promotion_codes'); 

DELETE FROM `rbac_linked_permissions` where `linkedId` IN ('1021');
INSERT INTO `rbac_linked_permissions` (`id`, `linkedId`) values
('192','1021'); 