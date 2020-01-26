DELETE FROM `rbac_permissions` where `id` IN ("1022");
INSERT INTO `rbac_permissions` (`id`, `name`) values
('1022', 'Command: reload promotion_codes'); 

DELETE FROM `rbac_linked_permissions` where `linkedId` IN ('1022');
INSERT INTO `rbac_linked_permissions` (`id`, `linkedId`) values
('192','1022'); 