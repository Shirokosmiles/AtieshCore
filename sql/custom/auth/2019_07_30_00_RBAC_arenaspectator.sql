DELETE FROM `rbac_permissions` where `id` IN ("1015","1016","1017","1018","1019");
INSERT INTO `rbac_permissions` (`id`, `name`) values
('1015', 'spectate'),
('1016', 'spectate player'),
('1017', 'spectate view'),
('1018', 'spectate reset'),
('1019', 'spectate leave'); 

DELETE FROM `rbac_linked_permissions` where `linkedId` IN ('1015','1016','1017','1018','1019');
INSERT INTO `rbac_linked_permissions` (`id`, `linkedId`) values
('195','1015'),
('195','1016'),
('195','1017'),
('195','1018'),
('195','1019'); 

