-- Rbac vip account
DELETE FROM `rbac_permissions` WHERE `Id` IN (1100, 1101, 1102, 1103, 1104, 1105, 1106, 1107, 1108, 1109, 1110, 1111, 1112, 1113);
INSERT INTO `rbac_permissions` VALUES
('1100', 'Command: Vip'),
('1101', 'Command: Vip debuff'),
('1102', 'Command: Vip bank'),
('1103', 'Command: Vip repair'),
('1104', 'Command: Vip resettalents'),
('1105', 'Command: Vip taxi'),
('1106', 'Command: Vip home'),
('1107', 'Command: Vip capital'),
('1108', 'Command: Vip mail'),
('1109', 'Command: Vip changerace'),
('1110', 'Command: Vip customize'),
('1111', 'Command: Vip appear'),
('1112', 'Command: Vip set'),
('1113', 'Command: Vip del');
DELETE FROM `rbac_linked_permissions` WHERE `linkedId` IN (1100, 1101, 1102, 1103, 1104, 1105, 1106, 1107, 1108, 1109, 1110, 1111, 1112, 1113);
INSERT INTO `rbac_linked_permissions` VALUES
('199','1100'),
('199','1101'),
('199','1102'),
('199','1103'),
('199','1104'),
('199','1105'),
('199','1106'),
('199','1107'),
('199','1108'),
('199','1109'),
('199','1110'),
('199','1111'),
('197','1112'),
('197','1113');