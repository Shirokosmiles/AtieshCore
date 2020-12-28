DELETE FROM `creature` WHERE `guid` between 300000 and 300714;
DELETE FROM `creature` WHERE `id` = 30739 AND map = 571;
DELETE FROM `creature` WHERE `id` = 30740 AND map = 571;
DELETE FROM `creature` WHERE `id` = 30400 AND map = 571;
DELETE FROM `creature` WHERE `id` = 30499 AND map = 571;

-- remove all towers and builds from DB
-- Walls
DELETE FROM `gameobject` WHERE `id` = 190219 AND map = 571;
DELETE FROM `gameobject` WHERE `id` = 190220 AND map = 571;
DELETE FROM `gameobject` WHERE `id` = 191795 AND map = 571;
DELETE FROM `gameobject` WHERE `id` = 191796 AND map = 571;
DELETE FROM `gameobject` WHERE `id` = 191799 AND map = 571;
DELETE FROM `gameobject` WHERE `id` = 191800 AND map = 571;
DELETE FROM `gameobject` WHERE `id` = 191801 AND map = 571;
DELETE FROM `gameobject` WHERE `id` = 191802 AND map = 571;
DELETE FROM `gameobject` WHERE `id` = 191803 AND map = 571;
DELETE FROM `gameobject` WHERE `id` = 191804 AND map = 571;
DELETE FROM `gameobject` WHERE `id` = 191806 AND map = 571;
DELETE FROM `gameobject` WHERE `id` = 191807 AND map = 571;
DELETE FROM `gameobject` WHERE `id` = 191808 AND map = 571;
DELETE FROM `gameobject` WHERE `id` = 191809 AND map = 571;
DELETE FROM `gameobject` WHERE `id` = 190369 AND map = 571;
DELETE FROM `gameobject` WHERE `id` = 190370 AND map = 571;
DELETE FROM `gameobject` WHERE `id` = 190371 AND map = 571;
DELETE FROM `gameobject` WHERE `id` = 190372 AND map = 571;
DELETE FROM `gameobject` WHERE `id` = 190374 AND map = 571;
DELETE FROM `gameobject` WHERE `id` = 190376 AND map = 571;

-- Walls Tower of keep
DELETE FROM `gameobject` WHERE `id` = 190221 AND map = 571;
DELETE FROM `gameobject` WHERE `id` = 190373 AND map = 571;
DELETE FROM `gameobject` WHERE `id` = 190377 AND map = 571;
DELETE FROM `gameobject` WHERE `id` = 190378 AND map = 571;

-- Wall
DELETE FROM `gameobject` WHERE `id` = 191797 AND map = 571;
DELETE FROM `gameobject` WHERE `id` = 191798 AND map = 571;
DELETE FROM `gameobject` WHERE `id` = 191805 AND map = 571;

-- South tower
DELETE FROM `gameobject` WHERE `id` = 190356 AND map = 571;
DELETE FROM `gameobject` WHERE `id` = 190357 AND map = 571;
DELETE FROM `gameobject` WHERE `id` = 190358 AND map = 571;

-- fortress and vault
DELETE FROM `gameobject` WHERE `id` = 190375 AND map = 571;
DELETE FROM `gameobject` WHERE `id` = 191810 AND map = 571;
-- end remove buildings from DB

-- west tower banner
DELETE FROM `gameobject` WHERE `guid` = 66682;
DELETE FROM `gameobject` WHERE `guid` = 75176;
DELETE FROM `gameobject` WHERE `guid` = 66681;
DELETE FROM `gameobject` WHERE `guid` = 75175;
-- west tower banner tower
DELETE FROM `gameobject` WHERE `guid` = 76047;
DELETE FROM `gameobject` WHERE `guid` = 7155;
DELETE FROM `gameobject` WHERE `guid` = 76048;
DELETE FROM `gameobject` WHERE `guid` = 7157;
DELETE FROM `gameobject` WHERE `guid` = 76046;
DELETE FROM `gameobject` WHERE `guid` = 7151;
DELETE FROM `gameobject` WHERE `guid` = 76045;
DELETE FROM `gameobject` WHERE `guid` = 7150;

-- south tower
DELETE FROM `gameobject` WHERE `guid` = 75171;
DELETE FROM `gameobject` WHERE `guid` = 75172;
DELETE FROM `gameobject` WHERE `guid` = 67263;
DELETE FROM `gameobject` WHERE `guid` = 75189;
DELETE FROM `gameobject` WHERE `guid` = 67249;
DELETE FROM `gameobject` WHERE `guid` = 75191;
DELETE FROM `gameobject` WHERE `guid` = 75182;
DELETE FROM `gameobject` WHERE `guid` = 75183;
DELETE FROM `gameobject` WHERE `guid` = 75188;
DELETE FROM `gameobject` WHERE `guid` = 74700;
DELETE FROM `gameobject` WHERE `guid` = 75170;
DELETE FROM `gameobject` WHERE `guid` = 75179;
DELETE FROM `gameobject` WHERE `guid` = 75190;
DELETE FROM `gameobject` WHERE `guid` = 75187;
DELETE FROM `gameobject` WHERE `guid` = 75168;
DELETE FROM `gameobject` WHERE `guid` = 75169;
-- south tower banner
DELETE FROM `gameobject` WHERE `guid` = 7144;
DELETE FROM `gameobject` WHERE `guid` = 76044;
DELETE FROM `gameobject` WHERE `guid` = 7142;
DELETE FROM `gameobject` WHERE `guid` = 76043;
DELETE FROM `gameobject` WHERE `guid` = 7169;
DELETE FROM `gameobject` WHERE `guid` = 76053;
DELETE FROM `gameobject` WHERE `guid` = 7172;
DELETE FROM `gameobject` WHERE `guid` = 76054;

-- east tower
DELETE FROM `gameobject` WHERE `guid` = 75180;
DELETE FROM `gameobject` WHERE `guid` = 75181;
-- east tower banner
DELETE FROM `gameobject` WHERE `guid` = 7161;
DELETE FROM `gameobject` WHERE `guid` = 76050;
DELETE FROM `gameobject` WHERE `guid` = 7159;
DELETE FROM `gameobject` WHERE `guid` = 76049;
DELETE FROM `gameobject` WHERE `guid` = 7167;
DELETE FROM `gameobject` WHERE `guid` = 76052;
DELETE FROM `gameobject` WHERE `guid` = 7164;
DELETE FROM `gameobject` WHERE `guid` = 76051;

-- workshop GO
DELETE FROM `gameobject` WHERE `guid` = 71387;
DELETE FROM `gameobject` WHERE `guid` = 71388;
DELETE FROM `gameobject` WHERE `guid` = 71386;
DELETE FROM `gameobject` WHERE `guid` = 71385;

-- SE workshop
DELETE FROM `gameobject` WHERE `guid` = 67252;
DELETE FROM `gameobject` WHERE `guid` = 75193;
DELETE FROM `gameobject` WHERE `guid` = 67250;
DELETE FROM `gameobject` WHERE `guid` = 75192;
DELETE FROM `gameobject` WHERE `guid` = 66678;
DELETE FROM `gameobject` WHERE `guid` = 75173;
DELETE FROM `gameobject` WHERE `guid` = 67254;
DELETE FROM `gameobject` WHERE `guid` = 75194;

-- SW workshop
DELETE FROM `gameobject` WHERE `guid` = 75177;
DELETE FROM `gameobject` WHERE `guid` = 75178;
DELETE FROM `gameobject` WHERE `guid` = 66679;
DELETE FROM `gameobject` WHERE `guid` = 75174;
DELETE FROM `gameobject` WHERE `guid` = 67264;
DELETE FROM `gameobject` WHERE `guid` = 75184;
DELETE FROM `gameobject` WHERE `guid` = 67242;
DELETE FROM `gameobject` WHERE `guid` = 75185;
DELETE FROM `gameobject` WHERE `guid` = 67244;
DELETE FROM `gameobject` WHERE `guid` = 75186;

-- NW workshop
DELETE FROM `gameobject` WHERE `guid` = 17798;
DELETE FROM `gameobject` WHERE `guid` = 17794;
DELETE FROM `gameobject` WHERE `guid` = 17797;
DELETE FROM `gameobject` WHERE `guid` = 17793;
DELETE FROM `gameobject` WHERE `guid` = 17799;
DELETE FROM `gameobject` WHERE `guid` = 17795;
DELETE FROM `gameobject` WHERE `guid` = 17799;
DELETE FROM `gameobject` WHERE `guid` = 17795;
DELETE FROM `gameobject` WHERE `guid` = 17796;
DELETE FROM `gameobject` WHERE `guid` = 17792;

-- NE workshop
DELETE FROM `gameobject` WHERE `guid` = 17785;
DELETE FROM `gameobject` WHERE `guid` = 17791;
DELETE FROM `gameobject` WHERE `guid` = 17788;
DELETE FROM `gameobject` WHERE `guid` = 17782;
DELETE FROM `gameobject` WHERE `guid` = 17789;
DELETE FROM `gameobject` WHERE `guid` = 17783;
DELETE FROM `gameobject` WHERE `guid` = 17790;
DELETE FROM `gameobject` WHERE `guid` = 17784;
DELETE FROM `gameobject` WHERE `guid` = 17786;
DELETE FROM `gameobject` WHERE `guid` = 17780;
DELETE FROM `gameobject` WHERE `guid` = 17787;
DELETE FROM `gameobject` WHERE `guid` = 17781;


-- KEEP
-- NW outside
DELETE FROM `gameobject` WHERE `guid` = 75949;
DELETE FROM `gameobject` WHERE `guid` = 76014;
DELETE FROM `gameobject` WHERE `guid` = 75982;
DELETE FROM `gameobject` WHERE `guid` = 7135;
DELETE FROM `gameobject` WHERE `guid` = 75980;
DELETE FROM `gameobject` WHERE `guid` = 74685;
DELETE FROM `gameobject` WHERE `guid` = 75948;
DELETE FROM `gameobject` WHERE `guid` = 74687;
-- NW inside
DELETE FROM `gameobject` WHERE `guid` = 75963;
DELETE FROM `gameobject` WHERE `guid` = 74759;
DELETE FROM `gameobject` WHERE `guid` = 75962;
DELETE FROM `gameobject` WHERE `guid` = 74757;
DELETE FROM `gameobject` WHERE `guid` = 75961;
DELETE FROM `gameobject` WHERE `guid` = 74755;
DELETE FROM `gameobject` WHERE `guid` = 75959;
DELETE FROM `gameobject` WHERE `guid` = 74753;
DELETE FROM `gameobject` WHERE `guid` = 75960;
DELETE FROM `gameobject` WHERE `guid` = 74751;
DELETE FROM `gameobject` WHERE `guid` = 75943;
DELETE FROM `gameobject` WHERE `guid` = 74743;
DELETE FROM `gameobject` WHERE `guid` = 75956;
DELETE FROM `gameobject` WHERE `guid` = 74741;
DELETE FROM `gameobject` WHERE `guid` = 75955;
DELETE FROM `gameobject` WHERE `guid` = 74739;
DELETE FROM `gameobject` WHERE `guid` = 75958;
DELETE FROM `gameobject` WHERE `guid` = 74737;

-- KEEP
DELETE FROM `gameobject` WHERE `guid` = 75940;
DELETE FROM `gameobject` WHERE `guid` = 74747;
-- SW outside
DELETE FROM `gameobject` WHERE `guid` = 75947;
DELETE FROM `gameobject` WHERE `guid` = 74689;
DELETE FROM `gameobject` WHERE `guid` = 75977;
DELETE FROM `gameobject` WHERE `guid` = 74691;
DELETE FROM `gameobject` WHERE `guid` = 75973;
DELETE FROM `gameobject` WHERE `guid` = 74693;
DELETE FROM `gameobject` WHERE `guid` = 7138;
DELETE FROM `gameobject` WHERE `guid` = 74695;
DELETE FROM `gameobject` WHERE `guid` = 75941;
DELETE FROM `gameobject` WHERE `guid` = 74697;
DELETE FROM `gameobject` WHERE `guid` = 75166;
DELETE FROM `gameobject` WHERE `guid` = 74699;
-- SW inside
DELETE FROM `gameobject` WHERE `guid` = 75964;
DELETE FROM `gameobject` WHERE `guid` = 74765;
DELETE FROM `gameobject` WHERE `guid` = 75966;
DELETE FROM `gameobject` WHERE `guid` = 74767;
DELETE FROM `gameobject` WHERE `guid` = 75945;
DELETE FROM `gameobject` WHERE `guid` = 74769;

-- SE outside
DELETE FROM `gameobject` WHERE `guid` = 75167;
DELETE FROM `gameobject` WHERE `guid` = 74701;
DELETE FROM `gameobject` WHERE `guid` = 75942;
DELETE FROM `gameobject` WHERE `guid` = 74703;
DELETE FROM `gameobject` WHERE `guid` = 7141;
DELETE FROM `gameobject` WHERE `guid` = 74705;
DELETE FROM `gameobject` WHERE `guid` = 75974;
DELETE FROM `gameobject` WHERE `guid` = 74707;
DELETE FROM `gameobject` WHERE `guid` = 75978;
DELETE FROM `gameobject` WHERE `guid` = 74709;
DELETE FROM `gameobject` WHERE `guid` = 75950;
DELETE FROM `gameobject` WHERE `guid` = 74711;
-- SE inside
DELETE FROM `gameobject` WHERE `guid` = 75946;
DELETE FROM `gameobject` WHERE `guid` = 74771;
DELETE FROM `gameobject` WHERE `guid` = 75967;
DELETE FROM `gameobject` WHERE `guid` = 74761;
DELETE FROM `gameobject` WHERE `guid` = 75965;
DELETE FROM `gameobject` WHERE `guid` = 74763;

-- NE outside
DELETE FROM `gameobject` WHERE `guid` = 75951;
DELETE FROM `gameobject` WHERE `guid` = 74713;
DELETE FROM `gameobject` WHERE `guid` = 75979;
DELETE FROM `gameobject` WHERE `guid` = 74715;
DELETE FROM `gameobject` WHERE `guid` = 75981;
DELETE FROM `gameobject` WHERE `guid` = 74717;
DELETE FROM `gameobject` WHERE `guid` = 75952;
DELETE FROM `gameobject` WHERE `guid` = 74719;
-- NE inside
DELETE FROM `gameobject` WHERE `guid` = 75970;
DELETE FROM `gameobject` WHERE `guid` = 74721;
DELETE FROM `gameobject` WHERE `guid` = 75969;
DELETE FROM `gameobject` WHERE `guid` = 74723;
DELETE FROM `gameobject` WHERE `guid` = 75968;
DELETE FROM `gameobject` WHERE `guid` = 74725;
DELETE FROM `gameobject` WHERE `guid` = 75971;
DELETE FROM `gameobject` WHERE `guid` = 74727;
DELETE FROM `gameobject` WHERE `guid` = 75972;
DELETE FROM `gameobject` WHERE `guid` = 74729;
DELETE FROM `gameobject` WHERE `guid` = 75944;
DELETE FROM `gameobject` WHERE `guid` = 74745;
DELETE FROM `gameobject` WHERE `guid` = 75954;
DELETE FROM `gameobject` WHERE `guid` = 74731;
DELETE FROM `gameobject` WHERE `guid` = 75953;
DELETE FROM `gameobject` WHERE `guid` = 74733;
DELETE FROM `gameobject` WHERE `guid` = 75957;
DELETE FROM `gameobject` WHERE `guid` = 74735;
DELETE FROM `gameobject` WHERE `guid` = 75939;
DELETE FROM `gameobject` WHERE `guid` = 74749;

-- keep GO east
DELETE FROM `gameobject` WHERE `guid` = 71443;
DELETE FROM `gameobject` WHERE `guid` = 71439;
DELETE FROM `gameobject` WHERE `guid` = 71442;

-- keep GO east hoodo master (horde)
DELETE FROM `gameobject` WHERE `guid` = 71418;
DELETE FROM `gameobject` WHERE `guid` = 71421;
DELETE FROM `gameobject` WHERE `guid` = 71424;
DELETE FROM `gameobject` WHERE `guid` = 71420;
DELETE FROM `gameobject` WHERE `guid` = 71425;
DELETE FROM `gameobject` WHERE `guid` = 71419;
DELETE FROM `gameobject` WHERE `guid` = 71423;
DELETE FROM `gameobject` WHERE `guid` = 71422;

-- keep GO the eastest
DELETE FROM `gameobject` WHERE `guid` = 71438;
DELETE FROM `gameobject` WHERE `guid` = 71437;
DELETE FROM `gameobject` WHERE `guid` = 71436;
DELETE FROM `gameobject` WHERE `guid` = 71434;
DELETE FROM `gameobject` WHERE `guid` = 71435;

-- keep GO west
DELETE FROM `gameobject` WHERE `guid` = 71440;
DELETE FROM `gameobject` WHERE `guid` = 71444;
DELETE FROM `gameobject` WHERE `guid` = 71441;

-- keep GO west kaylana (alliance)
DELETE FROM `gameobject` WHERE `guid` = 71409;
DELETE FROM `gameobject` WHERE `guid` = 71417;
DELETE FROM `gameobject` WHERE `guid` = 71410;
DELETE FROM `gameobject` WHERE `guid` = 71407;
DELETE FROM `gameobject` WHERE `guid` = 71412;
DELETE FROM `gameobject` WHERE `guid` = 71414;
DELETE FROM `gameobject` WHERE `guid` = 71416;
DELETE FROM `gameobject` WHERE `guid` = 71411;
DELETE FROM `gameobject` WHERE `guid` = 71415;
DELETE FROM `gameobject` WHERE `guid` = 71413;
DELETE FROM `gameobject` WHERE `guid` = 71408;

-- keep GO the westest
DELETE FROM `gameobject` WHERE `guid` = 71403;
DELETE FROM `gameobject` WHERE `guid` = 71406;

SET @CGUID := 300000;
INSERT INTO `creature`(`guid`, `id`, `map`, `zoneId`, `areaId`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `wander_distance`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`, `ScriptName`, `VerifiedBuild`) VALUES 
-- Turret
-- Keep Cannons defense
(@CGUID+000, 28366, 571, 0, 0, 1, 1, 0, 0, 5391.19, 3060.80, 419.616,  1.69557, 300, 0, 0, 50000, 0, 0, 0, 0, 0, 'npc_wg_NW_cannon', 0),
(@CGUID+001, 28366, 571, 0, 0, 1, 1, 0, 0, 5266.75, 2976.50, 421.067,  3.20354, 300, 0, 0, 50000, 0, 0, 0, 0, 0, 'npc_wg_NW_cannon', 0),
(@CGUID+002, 28366, 571, 0, 0, 1, 1, 0, 0, 5352.28, 3061.44, 421.102,  1.56815, 300, 0, 0, 50000, 0, 0, 0, 0, 0, 'npc_wg_NW_cannon', 0),

(@CGUID+003, 28366, 571, 0, 0, 1, 1, 0, 0, 5265.02, 2704.63, 421.700,  3.12507, 300, 0, 0, 50000, 0, 0, 0, 0, 0, 'npc_wg_NE_cannon', 0),
(@CGUID+004, 28366, 571, 0, 0, 1, 1, 0, 0, 5350.87, 2616.03, 421.243,  4.72729, 300, 0, 0, 50000, 0, 0, 0, 0, 0, 'npc_wg_NE_cannon', 0),
(@CGUID+005, 28366, 571, 0, 0, 1, 1, 0, 0, 5390.95, 2615.50, 421.126,  4.64090, 300, 0, 0, 50000, 0, 0, 0, 0, 0, 'npc_wg_NE_cannon', 0),

(@CGUID+006, 28366, 571, 0, 0, 1, 1, 0, 0, 5234.86, 2948.80, 420.880,  1.61311, 300, 0, 0, 50000, 0, 0, 0, 0, 0, 'npc_wg_SW_cannon', 0),
(@CGUID+007, 28366, 571, 0, 0, 1, 1, 0, 0, 5236.20, 2732.68, 421.649,  4.72336, 300, 0, 0, 50000, 0, 0, 0, 0, 0, 'npc_wg_SE_cannon', 0),

(@CGUID+008, 28366, 571, 0, 0, 1, 1, 0, 0, 5323.05, 2923.70, 421.645,  1.58170, 300, 0, 0, 50000, 0, 0, 0, 0, 0, 'npc_wg_fortress_cannon', 0),
(@CGUID+009, 28366, 571, 0, 0, 1, 1, 0, 0, 5363.82, 2923.87, 421.709,  1.60527, 300, 0, 0, 50000, 0, 0, 0, 0, 0, 'npc_wg_fortress_cannon', 0),
(@CGUID+010, 28366, 571, 0, 0, 1, 1, 0, 0, 5264.04, 2861.34, 421.587,  3.21142, 300, 0, 0, 50000, 0, 0, 0, 0, 0, 'npc_wg_fortress_cannon', 0),
(@CGUID+011, 28366, 571, 0, 0, 1, 1, 0, 0, 5264.68, 2819.78, 421.656,  3.15645, 300, 0, 0, 50000, 0, 0, 0, 0, 0, 'npc_wg_fortress_cannon', 0),
(@CGUID+012, 28366, 571, 0, 0, 1, 1, 0, 0, 5322.16, 2756.69, 421.646,  4.69978, 300, 0, 0, 50000, 0, 0, 0, 0, 0, 'npc_wg_fortress_cannon', 0),
(@CGUID+013, 28366, 571, 0, 0, 1, 1, 0, 0, 5363.78, 2756.77, 421.629,  4.78226, 300, 0, 0, 50000, 0, 0, 0, 0, 0, 'npc_wg_fortress_cannon', 0),

(@CGUID+014, 28366, 571, 0, 0, 1, 1, 0, 0, 5148.80, 2820.24, 421.621,  3.16043, 300, 0, 0, 50000, 0, 0, 0, 0, 0, 'npc_wg_fortress_gate_cannon', 0),
(@CGUID+015, 28366, 571, 0, 0, 1, 1, 0, 0, 5147.98, 2861.93, 421.630,  3.18792, 300, 0, 0, 50000, 0, 0, 0, 0, 0, 'npc_wg_fortress_gate_cannon', 0),

--  middle tower Cannons
(@CGUID+016, 28366, 571, 0, 0, 1, 1, 0, 0, '4421.08', '2845.96', '412.631', '0.718666', 300, 0, 0, 50000, 0, 0, 0, 0, 0, 'wg_st_assault_cannon', 0),
(@CGUID+017, 28366, 571, 0, 0, 1, 1, 0, 0, '4374.81', '2845.05', '412.631', '2.49366', 300, 0, 0, 50000, 0, 0, 0, 0, 0, 'wg_st_assault_cannon', 0),
(@CGUID+018, 28366, 571, 0, 0, 1, 1, 0, 0, '4375.26', '2798.64', '412.632', '3.79743', 300, 0, 0, 50000, 0, 0, 0, 0, 0, 'wg_st_assault_cannon', 0),
(@CGUID+019, 28366, 571, 0, 0, 1, 1, 0, 0, '4421.41', '2800.27', '412.631', '5.45854', 300, 0, 0, 50000, 0, 0, 0, 0, 0, 'wg_st_assault_cannon', 0),
(@CGUID+020, 28366, 571, 0, 0, 1, 1, 0, 0, '4373.19', '2822', '436.283', '3.20051', 300, 0, 0, 50000, 0, 0, 0, 0, 0, 'wg_st_assault_cannon', 0),
(@CGUID+021, 28366, 571, 0, 0, 1, 1, 0, 0, '4398.79', '2797.73', '436.283', '4.61815', 300, 0, 0, 50000, 0, 0, 0, 0, 0, 'wg_st_assault_cannon', 0),
(@CGUID+022, 28366, 571, 0, 0, 1, 1, 0, 0, '4424.14', '2822.92', '436.283', '6.22821', 300, 0, 0, 50000, 0, 0, 0, 0, 0, 'wg_st_assault_cannon', 0),
(@CGUID+023, 28366, 571, 0, 0, 1, 1, 0, 0, '4397.69', '2848.08', '436.284', '1.48441', 300, 0, 0, 50000, 0, 0, 0, 0, 0, 'wg_st_assault_cannon', 0),

--  west tower Cannons
(@CGUID+024, 28366, 571, 0, 0, 1, 1, 0, 0, '4559.74', '3599.02', '426.539', '4.72344', 300, 0, 0, 50000, 0, 0, 0, 0, 0, 'wg_wt_assault_cannon', 0),
(@CGUID+025, 28366, 571, 0, 0, 1, 1, 0, 0, '4582.66', '3626.71', '426.539', '0.0817274', 300, 0, 0, 50000, 0, 0, 0, 0, 0, 'wg_wt_assault_cannon', 0),
(@CGUID+026, 28366, 571, 0, 0, 1, 1, 0, 0, '4554.56', '3648.51', '426.539', '1.70357', 300, 0, 0, 50000, 0, 0, 0, 0, 0, 'wg_wt_assault_cannon', 0),
(@CGUID+027, 28366, 571, 0, 0, 1, 1, 0, 0, '4531.93', '3621.39', '426.54', '3.1919', 300, 0, 0, 50000, 0, 0, 0, 0, 0, 'wg_wt_assault_cannon', 0),
(@CGUID+028, 28366, 571, 0, 0, 1, 1, 0, 0, '4532.15', '3644.1', '402.888', '2.4183', 300, 0, 0, 50000, 0, 0, 0, 0, 0, 'wg_wt_assault_cannon', 0),
(@CGUID+029, 28366, 571, 0, 0, 1, 1, 0, 0, '4577.52', '3648.83', '402.887', '0.851427', 300, 0, 0, 50000, 0, 0, 0, 0, 0, 'wg_wt_assault_cannon', 0),
(@CGUID+030, 28366, 571, 0, 0, 1, 1, 0, 0, '4582.54', '3603.52', '402.886', '5.56382', 300, 0, 0, 50000, 0, 0, 0, 0, 0, 'wg_wt_assault_cannon', 0),
(@CGUID+031, 28366, 571, 0, 0, 1, 1, 0, 0, '4537', '3599.09', '402.888', '4.0048', 300, 0, 0, 50000, 0, 0, 0, 0, 0, 'wg_wt_assault_cannon', 0),

--  east tower Cannons
(@CGUID+032, 28366, 571, 0, 0, 1, 1, 0, 0, '4437', '1954.47', '465.647', '2.67985', 300, 0, 0, 50000, 0, 0, 0, 0, 0, 'wg_et_assault_cannon', 0),
(@CGUID+033, 28366, 571, 0, 0, 1, 1, 0, 0, '4448.94', '1922.01', '465.648', '4.26635', 300, 0, 0, 50000, 0, 0, 0, 0, 0, 'wg_et_assault_cannon', 0),
(@CGUID+034, 28366, 571, 0, 0, 1, 1, 0, 0, '4481.2', '1934.17', '465.647', '5.85049', 300, 0, 0, 50000, 0, 0, 0, 0, 0, 'wg_et_assault_cannon', 0),
(@CGUID+035, 28366, 571, 0, 0, 1, 1, 0, 0, '4469.57', '1967.05', '465.647', '1.10669', 300, 0, 0, 50000, 0, 0, 0, 0, 0, 'wg_et_assault_cannon', 0),
(@CGUID+036, 28366, 571, 0, 0, 1, 1, 0, 0, '4447.76', '1974.82', '441.995', '1.85674', 300, 0, 0, 50000, 0, 0, 0, 0, 0, 'wg_et_assault_cannon', 0),
(@CGUID+037, 28366, 571, 0, 0, 1, 1, 0, 0, '4428.84', '1932.95', '441.995', '3.46681', 300, 0, 0, 50000, 0, 0, 0, 0, 0, 'wg_et_assault_cannon', 0),
(@CGUID+038, 28366, 571, 0, 0, 1, 1, 0, 0, '4470.59', '1913.44', '441.996', '5.04781', 300, 0, 0, 50000, 0, 0, 0, 0, 0, 'wg_et_assault_cannon', 0),
(@CGUID+039, 28366, 571, 0, 0, 1, 1, 0, 0, '4489.5', '1955.43', '441.996', '0.234904', 300, 0, 0, 50000, 0, 0, 0, 0, 0, 'wg_et_assault_cannon', 0),

-- Guards
-- West tower
-- Alliance
(@CGUID+040, 30740, 571, 0, 0, 1, 1, 0, 1, 4417.82, 3541.51, 360.429, 4.52072, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_wt_standing_guard', 0),
(@CGUID+041, 30740, 571, 0, 0, 1, 1, 0, 1, 4430.11, 3536.81, 360.665, 4.33616, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_wt_standing_guard', 0),
(@CGUID+042, 30740, 571, 0, 0, 1, 1, 0, 1, 4502.74, 3625, 391.651, 3.32692, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_wt_standing_guard', 0),
(@CGUID+043, 30740, 571, 0, 0, 1, 1, 0, 1, 4506.16, 3605.45, 391.955, 3.4251, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_wt_standing_guard', 0),
(@CGUID+044, 30740, 571, 0, 0, 1, 1, 0, 1, 4550.46, 3576.47, 393.666, 4.69744, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_wt_standing_guard', 0),
(@CGUID+045, 30740, 571, 0, 0, 1, 1, 0, 1, 4571.51, 3575.88, 392.759, 4.74456, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_wt_standing_guard', 0),
(@CGUID+046, 30740, 571, 0, 0, 1, 1, 0, 1, 4547.53, 3475.31, 363.624, 5.07835, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_wt_standing_guard', 0),
(@CGUID+047, 30740, 571, 0, 0, 1, 1, 0, 1, 4566.11, 3476.61, 363.287, 4.94202, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_wt_standing_guard', 0),

-- Roaming guard
(@CGUID+048, 30740, 571, 0, 0, 1, 1, 0, 1, 4530.82, 3621.01, 400.186, 3.21305, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_wt_roaming_guard', 0),
(@CGUID+049, 30740, 571, 0, 0, 1, 1, 0, 1, 4554.54, 3651.08, 400.187, 1.67368, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_wt_roaming_guard', 0),
(@CGUID+050, 30740, 571, 0, 0, 1, 1, 0, 1, 4584.08, 3626.85, 400.188, 0.102887, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_wt_roaming_guard', 0),
(@CGUID+051, 30740, 571, 0, 0, 1, 1, 0, 1, 4560.06, 3597.03, 400.188, 5.05482, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_wt_roaming_guard', 0),
(@CGUID+052, 30740, 571, 0, 0, 1, 1, 0, 1, 4555.46, 3491.6, 367.081, 4.83507, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_wt_roaming_guard', 0),
(@CGUID+053, 30740, 571, 0, 0, 1, 1, 0, 1, 4433.77, 3556.49, 364.11, 4.19496, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_wt_roaming_guard', 0),

-- Horde
(@CGUID+054, 30739, 571, 0, 0, 1, 1, 0, 1, 4417.82, 3541.51, 360.429, 4.52072, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_wt_standing_guard', 0),
(@CGUID+055, 30739, 571, 0, 0, 1, 1, 0, 1, 4430.11, 3536.81, 360.665, 4.33616, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_wt_standing_guard', 0),
(@CGUID+056, 30739, 571, 0, 0, 1, 1, 0, 1, 4502.74, 3625, 391.651, 3.32692, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_wt_standing_guard', 0),
(@CGUID+057, 30739, 571, 0, 0, 1, 1, 0, 1, 4506.16, 3605.45, 391.955, 3.4251, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_wt_standing_guard', 0),
(@CGUID+058, 30739, 571, 0, 0, 1, 1, 0, 1, 4550.46, 3576.47, 393.666, 4.69744, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_wt_standing_guard', 0),
(@CGUID+059, 30739, 571, 0, 0, 1, 1, 0, 1, 4571.51, 3575.88, 392.759, 4.74456, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_wt_standing_guard', 0),
(@CGUID+060, 30739, 571, 0, 0, 1, 1, 0, 1, 4547.53, 3475.31, 363.624, 5.07835, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_wt_standing_guard', 0),
(@CGUID+061, 30739, 571, 0, 0, 1, 1, 0, 1, 4566.11, 3476.61, 363.287, 4.94202, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_wt_standing_guard', 0),

-- Roaming guard
(@CGUID+062, 30739, 571, 0, 0, 1, 1, 0, 1, 4530.82, 3621.01, 400.186, 3.21305, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_wt_roaming_guard', 0),
(@CGUID+063, 30739, 571, 0, 0, 1, 1, 0, 1, 4554.54, 3651.08, 400.187, 1.67368, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_wt_roaming_guard', 0),
(@CGUID+064, 30739, 571, 0, 0, 1, 1, 0, 1, 4584.08, 3626.85, 400.188, 0.102887, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_wt_roaming_guard', 0),
(@CGUID+065, 30739, 571, 0, 0, 1, 1, 0, 1, 4560.06, 3597.03, 400.188, 5.05482, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_wt_roaming_guard', 0),
(@CGUID+066, 30739, 571, 0, 0, 1, 1, 0, 1, 4555.46, 3491.6, 367.081, 4.83507, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_wt_roaming_guard', 0),
(@CGUID+067, 30739, 571, 0, 0, 1, 1, 0, 1, 4433.77, 3556.49, 364.11, 4.19496, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_wt_roaming_guard', 0),

-- South tower
-- Alliance
(@CGUID+068, 30740, 571, 0, 0, 1, 1, 0, 1, 4473.29, 2707.56, 379.086, 4.62448, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_st_standing_guard', 0),
(@CGUID+069, 30740, 571, 0, 0, 1, 1, 0, 1, 4459.2, 2703.75, 377.924, 4.82083, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_st_standing_guard', 0),
(@CGUID+070, 30740, 571, 0, 0, 1, 1, 0, 1, 4474.69, 2640.58, 360.853, 4.85225, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_st_standing_guard', 0),
(@CGUID+071, 30740, 571, 0, 0, 1, 1, 0, 1, 4461.07, 2639.28, 360.383, 4.83655, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_st_standing_guard', 0),
(@CGUID+072, 30740, 571, 0, 0, 1, 1, 0, 1, 4463.81, 2830.34, 398.331, 0.179125, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_st_standing_guard', 0),
(@CGUID+073, 30740, 571, 0, 0, 1, 1, 0, 1, 4462.41, 2812.31, 399.42, 0.186979, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_st_standing_guard', 0),
(@CGUID+074, 30740, 571, 0, 0, 1, 1, 0, 1, 4387.74, 2860.16, 405.727, 1.44755, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_st_standing_guard', 0),
(@CGUID+075, 30740, 571, 0, 0, 1, 1, 0, 1, 4407.21, 2860.87, 405.768, 1.56143, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_st_standing_guard', 0),
(@CGUID+076, 30740, 571, 0, 0, 1, 1, 0, 1, 4363.03, 2829.85, 407.499, 2.92804, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_st_standing_guard', 0),
(@CGUID+077, 30740, 571, 0, 0, 1, 1, 0, 1, 4362.03, 2812.47, 407.305, 2.98303, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_st_standing_guard', 0),
(@CGUID+078, 30740, 571, 0, 0, 1, 1, 0, 1, 4409.04, 2781.95, 403.996, 5.0015, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_st_standing_guard', 0),
(@CGUID+079, 30740, 571, 0, 0, 1, 1, 0, 1, 4387.65, 2781.06, 404.271, 4.67163, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_st_standing_guard', 0),
(@CGUID+080, 30740, 571, 0, 0, 1, 1, 0, 1, 4442.26, 2814.31, 404.495, 0.00636673, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_st_standing_guard', 0),
(@CGUID+081, 30740, 571, 0, 0, 1, 1, 0, 1, 4442.55, 2831.53, 403.726, 6.27777, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_st_standing_guard', 0),
(@CGUID+082, 30740, 571, 0, 0, 1, 1, 0, 1, 4392.77, 2885.75, 396.271, 1.5693, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_st_standing_guard', 0),
(@CGUID+083, 30740, 571, 0, 0, 1, 1, 0, 1, 4407.23, 2883.48, 397.427, 1.61249, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_st_standing_guard', 0),
(@CGUID+084, 30740, 571, 0, 0, 1, 1, 0, 1, 4404.19, 2942.41, 377.133, 1.63209, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_st_standing_guard', 0),
(@CGUID+085, 30740, 571, 0, 0, 1, 1, 0, 1, 4415.46, 2940.66, 378.295, 1.41611, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_st_standing_guard', 0),
(@CGUID+086, 30740, 571, 0, 0, 1, 1, 0, 1, 4404.21, 2980.69, 367.383, 1.7813, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_st_standing_guard', 0),
(@CGUID+087, 30740, 571, 0, 0, 1, 1, 0, 1, 4418.54, 2982.15, 366.785, 1.52603, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_st_standing_guard', 0),

(@CGUID+088, 30740, 571, 0, 0, 1, 1, 0, 1, 4360.02, 2909.95, 381.082, 3.32907, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_st_roaming_guard', 0),
(@CGUID+089, 30740, 571, 0, 0, 1, 1, 0, 1, 4410.99, 2981.58, 367.592, 1.61689, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_st_roaming_guard', 0),
(@CGUID+090, 30740, 571, 0, 0, 1, 1, 0, 1, 4409.93, 2944.61, 376.849, 1.65616, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_st_roaming_guard', 0),
(@CGUID+091, 30740, 571, 0, 0, 1, 1, 0, 1, 4399.83, 2884.8, 396.646, 1.49123, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_st_roaming_guard', 0),
(@CGUID+092, 30740, 571, 0, 0, 1, 1, 0, 1, 4439.68, 2898.7, 390.265, 2.64972, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_st_roaming_guard', 0),
(@CGUID+093, 30740, 571, 0, 0, 1, 1, 0, 1, 4481.73, 2869.64, 389.465, 1.56587, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_st_roaming_guard', 0),
(@CGUID+094, 30740, 571, 0, 0, 1, 1, 0, 1, 4399.02, 2784.01, 404.361, 4.60143, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_st_roaming_guard', 0),
(@CGUID+095, 30740, 571, 0, 0, 1, 1, 0, 1, 4365.28, 2821.28, 407.405, 3.20343, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_st_roaming_guard', 0),
(@CGUID+096, 30740, 571, 0, 0, 1, 1, 0, 1, 4399.24, 2859.21, 405.627, 1.45593, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_st_roaming_guard', 0),
(@CGUID+097, 30740, 571, 0, 0, 1, 1, 0, 1, 4433.55, 2823.87, 406.075, 6.11726, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_st_roaming_guard', 0),
(@CGUID+098, 30740, 571, 0, 0, 1, 1, 0, 1, 4456.66, 2822.24, 400.321, 6.2076, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_st_roaming_guard', 0),
(@CGUID+099, 30740, 571, 0, 0, 1, 1, 0, 1, 4526.83, 2814.23, 390.628, 0.183594, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_st_roaming_guard', 0),
(@CGUID+100, 30740, 571, 0, 0, 1, 1, 0, 1, 4511.19, 2766.54, 389.407, 0.859037, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_st_roaming_guard', 0),
(@CGUID+101, 30740, 571, 0, 0, 1, 1, 0, 1, 4484.56, 2742.89, 390.827, 4.76247, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_st_roaming_guard', 0),
(@CGUID+102, 30740, 571, 0, 0, 1, 1, 0, 1, 4463.47, 2714.99, 381.307, 4.82529, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_st_roaming_guard', 0),
(@CGUID+103, 30740, 571, 0, 0, 1, 1, 0, 1, 4467.7, 2650.52, 362.547, 4.69962, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_st_roaming_guard', 0),

-- Horde
(@CGUID+104, 30739, 571, 0, 0, 1, 1, 0, 1, 4473.29, 2707.56, 379.086, 4.62448, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_st_standing_guard', 0),
(@CGUID+105, 30739, 571, 0, 0, 1, 1, 0, 1, 4459.2, 2703.75, 377.924, 4.82083, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_st_standing_guard', 0),
(@CGUID+106, 30739, 571, 0, 0, 1, 1, 0, 1, 4474.69, 2640.58, 360.853, 4.85225, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_st_standing_guard', 0),
(@CGUID+107, 30739, 571, 0, 0, 1, 1, 0, 1, 4461.07, 2639.28, 360.383, 4.83655, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_st_standing_guard', 0),
(@CGUID+108, 30739, 571, 0, 0, 1, 1, 0, 1, 4463.81, 2830.34, 398.331, 0.179125, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_st_standing_guard', 0),
(@CGUID+109, 30739, 571, 0, 0, 1, 1, 0, 1, 4462.41, 2812.31, 399.42, 0.186979, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_st_standing_guard', 0),
(@CGUID+110, 30739, 571, 0, 0, 1, 1, 0, 1, 4387.74, 2860.16, 405.727, 1.44755, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_st_standing_guard', 0),
(@CGUID+111, 30739, 571, 0, 0, 1, 1, 0, 1, 4407.21, 2860.87, 405.768, 1.56143, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_st_standing_guard', 0),
(@CGUID+112, 30739, 571, 0, 0, 1, 1, 0, 1, 4363.03, 2829.85, 407.499, 2.92804, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_st_standing_guard', 0),
(@CGUID+113, 30739, 571, 0, 0, 1, 1, 0, 1, 4362.03, 2812.47, 407.305, 2.98303, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_st_standing_guard', 0),
(@CGUID+114, 30739, 571, 0, 0, 1, 1, 0, 1, 4409.04, 2781.95, 403.996, 5.0015, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_st_standing_guard', 0),
(@CGUID+115, 30739, 571, 0, 0, 1, 1, 0, 1, 4387.65, 2781.06, 404.271, 4.67163, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_st_standing_guard', 0),
(@CGUID+116, 30739, 571, 0, 0, 1, 1, 0, 1, 4442.26, 2814.31, 404.495, 0.00636673, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_st_standing_guard', 0),
(@CGUID+117, 30739, 571, 0, 0, 1, 1, 0, 1, 4442.55, 2831.53, 403.726, 6.27777, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_st_standing_guard', 0),
(@CGUID+118, 30739, 571, 0, 0, 1, 1, 0, 1, 4392.77, 2885.75, 396.271, 1.5693, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_st_standing_guard', 0),
(@CGUID+119, 30739, 571, 0, 0, 1, 1, 0, 1, 4407.23, 2883.48, 397.427, 1.61249, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_st_standing_guard', 0),
(@CGUID+120, 30739, 571, 0, 0, 1, 1, 0, 1, 4404.19, 2942.41, 377.133, 1.63209, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_st_standing_guard', 0),
(@CGUID+121, 30739, 571, 0, 0, 1, 1, 0, 1, 4415.46, 2940.66, 378.295, 1.41611, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_st_standing_guard', 0),
(@CGUID+122, 30739, 571, 0, 0, 1, 1, 0, 1, 4404.21, 2980.69, 367.383, 1.7813, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_st_standing_guard', 0),
(@CGUID+123, 30739, 571, 0, 0, 1, 1, 0, 1, 4418.54, 2982.15, 366.785, 1.52603, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_st_standing_guard', 0),

(@CGUID+124, 30739, 571, 0, 0, 1, 1, 0, 1, 4360.02, 2909.95, 381.082, 3.32907, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_st_roaming_guard', 0),
(@CGUID+125, 30739, 571, 0, 0, 1, 1, 0, 1, 4410.99, 2981.58, 367.592, 1.61689, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_st_roaming_guard', 0),
(@CGUID+126, 30739, 571, 0, 0, 1, 1, 0, 1, 4409.93, 2944.61, 376.849, 1.65616, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_st_roaming_guard', 0),
(@CGUID+127, 30739, 571, 0, 0, 1, 1, 0, 1, 4399.83, 2884.8, 396.646, 1.49123, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_st_roaming_guard', 0),
(@CGUID+128, 30739, 571, 0, 0, 1, 1, 0, 1, 4439.68, 2898.7, 390.265, 2.64972, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_st_roaming_guard', 0),
(@CGUID+129, 30739, 571, 0, 0, 1, 1, 0, 1, 4481.73, 2869.64, 389.465, 1.56587, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_st_roaming_guard', 0),
(@CGUID+130, 30739, 571, 0, 0, 1, 1, 0, 1, 4399.02, 2784.01, 404.361, 4.60143, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_st_roaming_guard', 0),
(@CGUID+131, 30739, 571, 0, 0, 1, 1, 0, 1, 4365.28, 2821.28, 407.405, 3.20343, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_st_roaming_guard', 0),
(@CGUID+132, 30739, 571, 0, 0, 1, 1, 0, 1, 4399.24, 2859.21, 405.627, 1.45593, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_st_roaming_guard', 0),
(@CGUID+133, 30739, 571, 0, 0, 1, 1, 0, 1, 4433.55, 2823.87, 406.075, 6.11726, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_st_roaming_guard', 0),
(@CGUID+134, 30739, 571, 0, 0, 1, 1, 0, 1, 4456.66, 2822.24, 400.321, 6.2076, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_st_roaming_guard', 0),
(@CGUID+135, 30739, 571, 0, 0, 1, 1, 0, 1, 4526.83, 2814.23, 390.628, 0.183594, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_st_roaming_guard', 0),
(@CGUID+136, 30739, 571, 0, 0, 1, 1, 0, 1, 4511.19, 2766.54, 389.407, 0.859037, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_st_roaming_guard', 0),
(@CGUID+137, 30739, 571, 0, 0, 1, 1, 0, 1, 4484.56, 2742.89, 390.827, 4.76247, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_st_roaming_guard', 0),
(@CGUID+138, 30739, 571, 0, 0, 1, 1, 0, 1, 4463.47, 2714.99, 381.307, 4.82529, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_st_roaming_guard', 0),
(@CGUID+139, 30739, 571, 0, 0, 1, 1, 0, 1, 4467.7, 2650.52, 362.547, 4.69962, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_st_roaming_guard', 0),

-- East tower
-- Alliance
(@CGUID+140, 30740, 571, 0, 0, 1, 1, 0, 1, 4426.51, 1968.77, 434.559, 2.61205, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_et_standing_guard', 0),
(@CGUID+141, 30740, 571, 0, 0, 1, 1, 0, 1, 4419.42, 1952.54, 434.614, 2.5453, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_et_standing_guard', 0),
(@CGUID+142, 30740, 571, 0, 0, 1, 1, 0, 1, 4433.1, 1910.69, 433.971, 4.32815, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_et_standing_guard', 0),
(@CGUID+143, 30740, 571, 0, 0, 1, 1, 0, 1, 4451.45, 1905.29, 435.122, 4.1318, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_et_standing_guard', 0),
(@CGUID+144, 30740, 571, 0, 0, 1, 1, 0, 1, 4491.14, 1917.12, 434.578, 5.80078, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_et_standing_guard', 0),
(@CGUID+145, 30740, 571, 0, 0, 1, 1, 0, 1, 4498.12, 1938.26, 435.408, 5.94607, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_et_standing_guard', 0),
(@CGUID+146, 30740, 571, 0, 0, 1, 1, 0, 1, 4465.84, 1985.04, 434.43, 0.919513, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_et_standing_guard', 0),
(@CGUID+147, 30740, 571, 0, 0, 1, 1, 0, 1, 4485.66, 1978.56, 433.354, 1.15121, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_et_standing_guard', 0),
(@CGUID+148, 30740, 571, 0, 0, 1, 1, 0, 1, 4479.69, 2027.91, 422.093, 1.11587, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_et_standing_guard', 0),
(@CGUID+149, 30740, 571, 0, 0, 1, 1, 0, 1, 4494.81, 2021.29, 423.214, 1.31615, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_et_standing_guard', 0),
(@CGUID+150, 30740, 571, 0, 0, 1, 1, 0, 1, 4510.57, 2072.7, 401.764, 1.44573, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_et_standing_guard', 0),
(@CGUID+151, 30740, 571, 0, 0, 1, 1, 0, 1, 4524.34, 2071.5, 401.386, 1.66564, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_et_standing_guard', 0),
(@CGUID+152, 30740, 571, 0, 0, 1, 1, 0, 1, 4520.87, 2127.04, 383.307, 1.33969, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_et_standing_guard', 0),
(@CGUID+153, 30740, 571, 0, 0, 1, 1, 0, 1, 4528.58, 2123.97, 383.488, 1.19439, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_et_standing_guard', 0),
(@CGUID+154, 30740, 571, 0, 0, 1, 1, 0, 1, 4542.1, 2174.28, 370.017, 1.44573, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_et_standing_guard', 0),
(@CGUID+155, 30740, 571, 0, 0, 1, 1, 0, 1, 4556.36, 2174.07, 368.205, 1.51249, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_et_standing_guard', 0),

(@CGUID+156, 30740, 571, 0, 0, 1, 1, 0, 1, 4545.38, 2128.81, 381.641, 1.50468, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_et_roaming_guard', 0),
(@CGUID+157, 30740, 571, 0, 0, 1, 1, 0, 1, 4493.43, 2110.35, 387.129, 3.01264, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_et_roaming_guard', 0),
(@CGUID+158, 30740, 571, 0, 0, 1, 1, 0, 1, 4424.52, 1999.73, 434.232, 0.204843, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_et_roaming_guard', 0),
(@CGUID+159, 30740, 571, 0, 0, 1, 1, 0, 1, 4444.98, 2006.27, 434.561, 5.10181, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_et_roaming_guard', 0),
(@CGUID+160, 30740, 571, 0, 0, 1, 1, 0, 1, 4523.79, 2026.57, 423.475, 1.82277, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_et_roaming_guard', 0),
(@CGUID+161, 30740, 571, 0, 0, 1, 1, 0, 1, 4425.68, 1960.13, 434.614, 2.58852, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_et_roaming_guard', 0),
(@CGUID+162, 30740, 571, 0, 0, 1, 1, 0, 1, 4443.35, 1911.04, 434.842, 4.25749, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_et_roaming_guard', 0),
(@CGUID+163, 30740, 571, 0, 0, 1, 1, 0, 1, 4492.29, 1928.93, 434.996, 5.87148, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_et_roaming_guard', 0),
(@CGUID+164, 30740, 571, 0, 0, 1, 1, 0, 1, 4475.31, 1980.57, 434.041, 1.22977, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_et_roaming_guard', 0),
(@CGUID+165, 30740, 571, 0, 0, 1, 1, 0, 1, 4487.66, 2027.04, 422.302, 1.31224, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_et_roaming_guard', 0),
(@CGUID+166, 30740, 571, 0, 0, 1, 1, 0, 1, 4517.27, 2071.35, 401.63, 1.41042, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_et_roaming_guard', 0),
(@CGUID+167, 30740, 571, 0, 0, 1, 1, 0, 1, 4524.48, 2126.22, 383.135, 1.33581, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_et_roaming_guard', 0),
(@CGUID+168, 30740, 571, 0, 0, 1, 1, 0, 1, 4547.01, 2171.86, 369.989, 1.08055, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_et_roaming_guard', 0),

-- Horde
(@CGUID+169, 30739, 571, 0, 0, 1, 1, 0, 1, 4426.51, 1968.77, 434.559, 2.61205, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_et_standing_guard', 0),
(@CGUID+170, 30739, 571, 0, 0, 1, 1, 0, 1, 4419.42, 1952.54, 434.614, 2.5453, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_et_standing_guard', 0),
(@CGUID+171, 30739, 571, 0, 0, 1, 1, 0, 1, 4433.1, 1910.69, 433.971, 4.32815, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_et_standing_guard', 0),
(@CGUID+172, 30739, 571, 0, 0, 1, 1, 0, 1, 4451.45, 1905.29, 435.122, 4.1318, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_et_standing_guard', 0),
(@CGUID+173, 30739, 571, 0, 0, 1, 1, 0, 1, 4491.14, 1917.12, 434.578, 5.80078, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_et_standing_guard', 0),
(@CGUID+174, 30739, 571, 0, 0, 1, 1, 0, 1, 4498.12, 1938.26, 435.408, 5.94607, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_et_standing_guard', 0),
(@CGUID+175, 30739, 571, 0, 0, 1, 1, 0, 1, 4465.84, 1985.04, 434.43, 0.919513, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_et_standing_guard', 0),
(@CGUID+176, 30739, 571, 0, 0, 1, 1, 0, 1, 4485.66, 1978.56, 433.354, 1.15121, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_et_standing_guard', 0),
(@CGUID+177, 30739, 571, 0, 0, 1, 1, 0, 1, 4479.69, 2027.91, 422.093, 1.11587, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_et_standing_guard', 0),
(@CGUID+178, 30739, 571, 0, 0, 1, 1, 0, 1, 4494.81, 2021.29, 423.214, 1.31615, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_et_standing_guard', 0),
(@CGUID+179, 30739, 571, 0, 0, 1, 1, 0, 1, 4510.57, 2072.7, 401.764, 1.44573, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_et_standing_guard', 0),
(@CGUID+180, 30739, 571, 0, 0, 1, 1, 0, 1, 4524.34, 2071.5, 401.386, 1.66564, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_et_standing_guard', 0),
(@CGUID+181, 30739, 571, 0, 0, 1, 1, 0, 1, 4520.87, 2127.04, 383.307, 1.33969, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_et_standing_guard', 0),
(@CGUID+182, 30739, 571, 0, 0, 1, 1, 0, 1, 4528.58, 2123.97, 383.488, 1.19439, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_et_standing_guard', 0),
(@CGUID+183, 30739, 571, 0, 0, 1, 1, 0, 1, 4542.1, 2174.28, 370.017, 1.44573, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_et_standing_guard', 0),
(@CGUID+184, 30739, 571, 0, 0, 1, 1, 0, 1, 4556.36, 2174.07, 368.205, 1.51249, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_et_standing_guard', 0),

(@CGUID+185, 30739, 571, 0, 0, 1, 1, 0, 1, 4545.38, 2128.81, 381.641, 1.50468, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_et_roaming_guard', 0),
(@CGUID+186, 30739, 571, 0, 0, 1, 1, 0, 1, 4493.43, 2110.35, 387.129, 3.01264, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_et_roaming_guard', 0),
(@CGUID+187, 30739, 571, 0, 0, 1, 1, 0, 1, 4424.52, 1999.73, 434.232, 0.204843, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_et_roaming_guard', 0),
(@CGUID+188, 30739, 571, 0, 0, 1, 1, 0, 1, 4444.98, 2006.27, 434.561, 5.10181, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_et_roaming_guard', 0),
(@CGUID+189, 30739, 571, 0, 0, 1, 1, 0, 1, 4523.79, 2026.57, 423.475, 1.82277, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_et_roaming_guard', 0),
(@CGUID+190, 30739, 571, 0, 0, 1, 1, 0, 1, 4425.68, 1960.13, 434.614, 2.58852, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_et_roaming_guard', 0),
(@CGUID+191, 30739, 571, 0, 0, 1, 1, 0, 1, 4443.35, 1911.04, 434.842, 4.25749, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_et_roaming_guard', 0),
(@CGUID+192, 30739, 571, 0, 0, 1, 1, 0, 1, 4492.29, 1928.93, 434.996, 5.87148, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_et_roaming_guard', 0),
(@CGUID+193, 30739, 571, 0, 0, 1, 1, 0, 1, 4475.31, 1980.57, 434.041, 1.22977, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_et_roaming_guard', 0),
(@CGUID+194, 30739, 571, 0, 0, 1, 1, 0, 1, 4487.66, 2027.04, 422.302, 1.31224, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_et_roaming_guard', 0),
(@CGUID+195, 30739, 571, 0, 0, 1, 1, 0, 1, 4517.27, 2071.35, 401.63, 1.41042, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_et_roaming_guard', 0),
(@CGUID+196, 30739, 571, 0, 0, 1, 1, 0, 1, 4524.48, 2126.22, 383.135, 1.33581, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_et_roaming_guard', 0),
(@CGUID+197, 30739, 571, 0, 0, 1, 1, 0, 1, 4547.01, 2171.86, 369.989, 1.08055, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_et_roaming_guard', 0),

--  east bridge
--  Alliance
(@CGUID+198, 30740, 571, 0, 0, 1, 1, 0, 1, 4570.48, 2357.21, 373.802, 3.52746, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_east_bridge_guard', 0),
(@CGUID+199, 30740, 571, 0, 0, 1, 1, 0, 1, 4576.93, 2345.09, 374.002, 3.53924, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_east_bridge_guard', 0),
(@CGUID+200, 30740, 571, 0, 0, 1, 1, 0, 1, 4636.85, 2373.85, 375.277, 0.448702, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_east_bridge_guard', 0),
(@CGUID+201, 30740, 571, 0, 0, 1, 1, 0, 1, 4629.74, 2385.16, 375.656, 0.378016, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_east_bridge_guard', 0),
(@CGUID+202, 30740, 571, 0, 0, 1, 1, 0, 1, 4687.39, 2390, 369.981, 0.354454, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_east_bridge_guard', 0),
(@CGUID+203, 30740, 571, 0, 0, 1, 1, 0, 1, 4678.95, 2409.24, 369.974, 0.35839, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_east_bridge_guard', 0),
(@CGUID+204, 30740, 571, 0, 0, 1, 1, 0, 1, 4539.24, 2324.37, 370.493, 3.62564, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_east_bridge_guard', 0),
(@CGUID+205, 30740, 571, 0, 0, 1, 1, 0, 1, 4527.74, 2349.6, 370.689, 3.30362, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_east_bridge_guard', 0),

(@CGUID+206, 30740, 571, 0, 0, 1, 1, 0, 1, 4682.32, 2398.43, 369.88, 0.358373, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_east_roaming_bridge_guard', 0),
(@CGUID+207, 30740, 571, 0, 0, 1, 1, 0, 1, 4633.22, 2380.01, 375.441, 0.429058, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_east_roaming_bridge_guard', 0),
(@CGUID+208, 30740, 571, 0, 0, 1, 1, 0, 1, 4572.72, 2352.29, 373.819, 3.48819, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_east_roaming_bridge_guard', 0),
(@CGUID+209, 30740, 571, 0, 0, 1, 1, 0, 1, 4536.25, 2336.92, 370.354, 3.5039, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_east_roaming_bridge_guard', 0),
--  Horde
(@CGUID+210, 30739, 571, 0, 0, 1, 1, 0, 1, 4570.48, 2357.21, 373.802, 3.52746, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_east_bridge_guard', 0),
(@CGUID+211, 30739, 571, 0, 0, 1, 1, 0, 1, 4576.93, 2345.09, 374.002, 3.53924, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_east_bridge_guard', 0),
(@CGUID+212, 30739, 571, 0, 0, 1, 1, 0, 1, 4636.85, 2373.85, 375.277, 0.448702, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_east_bridge_guard', 0),
(@CGUID+213, 30739, 571, 0, 0, 1, 1, 0, 1, 4629.74, 2385.16, 375.656, 0.378016, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_east_bridge_guard', 0),
(@CGUID+214, 30739, 571, 0, 0, 1, 1, 0, 1, 4687.39, 2390, 369.981, 0.354454, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_east_bridge_guard', 0),
(@CGUID+215, 30739, 571, 0, 0, 1, 1, 0, 1, 4678.95, 2409.24, 369.974, 0.35839, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_east_bridge_guard', 0),
(@CGUID+216, 30739, 571, 0, 0, 1, 1, 0, 1, 4539.24, 2324.37, 370.493, 3.62564, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_east_bridge_guard', 0),
(@CGUID+217, 30739, 571, 0, 0, 1, 1, 0, 1, 4527.74, 2349.6, 370.689, 3.30362, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_east_bridge_guard', 0),

(@CGUID+218, 30739, 571, 0, 0, 1, 1, 0, 1, 4682.32, 2398.43, 369.88, 0.358373, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_east_roaming_bridge_guard', 0),
(@CGUID+219, 30739, 571, 0, 0, 1, 1, 0, 1, 4633.22, 2380.01, 375.441, 0.429058, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_east_roaming_bridge_guard', 0),
(@CGUID+220, 30739, 571, 0, 0, 1, 1, 0, 1, 4572.72, 2352.29, 373.819, 3.48819, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_east_roaming_bridge_guard', 0),
(@CGUID+221, 30739, 571, 0, 0, 1, 1, 0, 1, 4536.25, 2336.92, 370.354, 3.5039, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_east_roaming_bridge_guard', 0),

--  middle bridge
--  Alliance
(@CGUID+222, 30740, 571, 0, 0, 1, 1, 0, 1, 4965.33, 2882.56, 384.007, 6.0172, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_middle_bridge_guard', 0),
(@CGUID+223, 30740, 571, 0, 0, 1, 1, 0, 1, 4962.21, 2870, 383.754, 6.06433, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_middle_bridge_guard', 0),
(@CGUID+224, 30740, 571, 0, 0, 1, 1, 0, 1, 4886.76, 2881.1, 378.494, 6.00935, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_middle_bridge_guard', 0),
(@CGUID+225, 30740, 571, 0, 0, 1, 1, 0, 1, 4889.33, 2892.71, 378.705, 6.08396, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_middle_bridge_guard', 0),
(@CGUID+226, 30740, 571, 0, 0, 1, 1, 0, 1, 4806.79, 2885.77, 373.6, 0.146347, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_middle_bridge_guard', 0),
(@CGUID+227, 30740, 571, 0, 0, 1, 1, 0, 1, 4804.27, 2903.23, 373.396, 0.177763, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_middle_bridge_guard', 0),
(@CGUID+228, 30740, 571, 0, 0, 1, 1, 0, 1, 4740.46, 2868.47, 382.687, 0.33877, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_middle_bridge_guard', 0),
(@CGUID+229, 30740, 571, 0, 0, 1, 1, 0, 1, 4735.37, 2882.78, 382.626, 0.33877, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_middle_bridge_guard', 0),
(@CGUID+230, 30740, 571, 0, 0, 1, 1, 0, 1, 4680.75, 2874.11, 388.371, 0.209159, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_middle_bridge_guard', 0),
(@CGUID+231, 30740, 571, 0, 0, 1, 1, 0, 1, 4685.97, 2850.29, 388.752, 0.1424, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_middle_bridge_guard', 0),
(@CGUID+232, 30740, 571, 0, 0, 1, 1, 0, 1, 4529.43, 2840.79, 388.775, 3.35862, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_middle_bridge_guard', 0),
(@CGUID+233, 30740, 571, 0, 0, 1, 1, 0, 1, 4535.16, 2821.36, 388.68, 3.24081, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_middle_bridge_guard', 0),

(@CGUID+234, 30740, 571, 0, 0, 1, 1, 0, 1, 4963.25, 2876.64, 384.001, 5.94259, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_middle_roaming_bridge_guard', 0),
(@CGUID+235, 30740, 571, 0, 0, 1, 1, 0, 1, 4880.61, 2887.92, 377.293, 6.0761, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_middle_roaming_bridge_guard', 0),
(@CGUID+236, 30740, 571, 0, 0, 1, 1, 0, 1, 4803.46, 2894.41, 373.804, 0.165982, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_middle_roaming_bridge_guard', 0),
(@CGUID+237, 30740, 571, 0, 0, 1, 1, 0, 1, 4732.3, 2873.74, 383.795, 0.236668, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_middle_roaming_bridge_guard', 0),
(@CGUID+238, 30740, 571, 0, 0, 1, 1, 0, 1, 4677.94, 2863.43, 388.728, 0.158128, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_middle_roaming_bridge_guard', 0),
(@CGUID+239, 30740, 571, 0, 0, 1, 1, 0, 1, 4604.2, 2846.43, 396.897, 0.150274, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_middle_roaming_bridge_guard', 0),
--  Horde
(@CGUID+240, 30739, 571, 0, 0, 1, 1, 0, 1, 4965.33, 2882.56, 384.007, 6.0172, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_middle_bridge_guard', 0),
(@CGUID+241, 30739, 571, 0, 0, 1, 1, 0, 1, 4962.21, 2870, 383.754, 6.06433, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_middle_bridge_guard', 0),
(@CGUID+242, 30739, 571, 0, 0, 1, 1, 0, 1, 4886.76, 2881.1, 378.494, 6.00935, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_middle_bridge_guard', 0),
(@CGUID+243, 30739, 571, 0, 0, 1, 1, 0, 1, 4889.33, 2892.71, 378.705, 6.08396, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_middle_bridge_guard', 0),
(@CGUID+244, 30739, 571, 0, 0, 1, 1, 0, 1, 4806.79, 2885.77, 373.6, 0.146347, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_middle_bridge_guard', 0),
(@CGUID+245, 30739, 571, 0, 0, 1, 1, 0, 1, 4804.27, 2903.23, 373.396, 0.177763, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_middle_bridge_guard', 0),
(@CGUID+246, 30739, 571, 0, 0, 1, 1, 0, 1, 4740.46, 2868.47, 382.687, 0.33877, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_middle_bridge_guard', 0),
(@CGUID+247, 30739, 571, 0, 0, 1, 1, 0, 1, 4735.37, 2882.78, 382.626, 0.33877, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_middle_bridge_guard', 0),
(@CGUID+248, 30739, 571, 0, 0, 1, 1, 0, 1, 4680.75, 2874.11, 388.371, 0.209159, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_middle_bridge_guard', 0),
(@CGUID+249, 30739, 571, 0, 0, 1, 1, 0, 1, 4685.97, 2850.29, 388.752, 0.1424, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_middle_bridge_guard', 0),
(@CGUID+250, 30739, 571, 0, 0, 1, 1, 0, 1, 4529.43, 2840.79, 388.775, 3.35862, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_middle_bridge_guard', 0),
(@CGUID+251, 30739, 571, 0, 0, 1, 1, 0, 1, 4535.16, 2821.36, 388.68, 3.24081, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_middle_bridge_guard', 0),

(@CGUID+252, 30739, 571, 0, 0, 1, 1, 0, 1, 4963.25, 2876.64, 384.001, 5.94259, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_middle_roaming_bridge_guard', 0),
(@CGUID+253, 30739, 571, 0, 0, 1, 1, 0, 1, 4880.61, 2887.92, 377.293, 6.0761, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_middle_roaming_bridge_guard', 0),
(@CGUID+254, 30739, 571, 0, 0, 1, 1, 0, 1, 4803.46, 2894.41, 373.804, 0.165982, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_middle_roaming_bridge_guard', 0),
(@CGUID+255, 30739, 571, 0, 0, 1, 1, 0, 1, 4732.3, 2873.74, 383.795, 0.236668, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_middle_roaming_bridge_guard', 0),
(@CGUID+256, 30739, 571, 0, 0, 1, 1, 0, 1, 4677.94, 2863.43, 388.728, 0.158128, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_middle_roaming_bridge_guard', 0),
(@CGUID+257, 30739, 571, 0, 0, 1, 1, 0, 1, 4604.2, 2846.43, 396.897, 0.150274, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_middle_roaming_bridge_guard', 0),

--  west bridge
--  Alliance
(@CGUID+258, 30740, 571, 0, 0, 1, 1, 0, 1, 4760.28, 3285.06, 366.428, 5.99247, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_west_bridge_guard', 0),
(@CGUID+259, 30740, 571, 0, 0, 1, 1, 0, 1, 4765.07, 3301.67, 366.431, 6.01603, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_west_bridge_guard', 0),
(@CGUID+260, 30740, 571, 0, 0, 1, 1, 0, 1, 4712.12, 3309.1, 372.353, 5.98069, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_west_bridge_guard', 0),
(@CGUID+261, 30740, 571, 0, 0, 1, 1, 0, 1, 4709.69, 3301.57, 372.374, 5.90215, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_west_bridge_guard', 0),
(@CGUID+262, 30740, 571, 0, 0, 1, 1, 0, 1, 4654.22, 3329.31, 369.124, 2.90586, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_west_bridge_guard', 0),
(@CGUID+263, 30740, 571, 0, 0, 1, 1, 0, 1, 4651.31, 3317.19, 369.265, 2.90586, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_west_bridge_guard', 0),
(@CGUID+264, 30740, 571, 0, 0, 1, 1, 0, 1, 4617.48, 3346.49, 366.018, 2.75664, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_west_bridge_guard', 0),
(@CGUID+265, 30740, 571, 0, 0, 1, 1, 0, 1, 4610.95, 3323.81, 366.629, 2.94121, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_west_bridge_guard', 0),

(@CGUID+266, 30740, 571, 0, 0, 1, 1, 0, 1, 4758.13, 3291.52, 366.482, 6.10242, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_west_roaming_bridge_guard', 0),
(@CGUID+267, 30740, 571, 0, 0, 1, 1, 0, 1, 4711.77, 3307.15, 372.307, 5.95712, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_west_roaming_bridge_guard', 0),
(@CGUID+268, 30740, 571, 0, 0, 1, 1, 0, 1, 4653.5, 3322.36, 369.371, 5.89822, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_west_roaming_bridge_guard', 0),
(@CGUID+269, 30740, 571, 0, 0, 1, 1, 0, 1, 4619.5, 3335.14, 366.44, 2.82732, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_west_roaming_bridge_guard', 0),
--  Horde
(@CGUID+270, 30739, 571, 0, 0, 1, 1, 0, 1, 4760.28, 3285.06, 366.428, 5.99247, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_west_bridge_guard', 0),
(@CGUID+271, 30739, 571, 0, 0, 1, 1, 0, 1, 4765.07, 3301.67, 366.431, 6.01603, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_west_bridge_guard', 0),
(@CGUID+272, 30739, 571, 0, 0, 1, 1, 0, 1, 4712.12, 3309.1, 372.353, 5.98069, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_west_bridge_guard', 0),
(@CGUID+273, 30739, 571, 0, 0, 1, 1, 0, 1, 4709.69, 3301.57, 372.374, 5.90215, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_west_bridge_guard', 0),
(@CGUID+274, 30739, 571, 0, 0, 1, 1, 0, 1, 4654.22, 3329.31, 369.124, 2.90586, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_west_bridge_guard', 0),
(@CGUID+275, 30739, 571, 0, 0, 1, 1, 0, 1, 4651.31, 3317.19, 369.265, 2.90586, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_west_bridge_guard', 0),
(@CGUID+276, 30739, 571, 0, 0, 1, 1, 0, 1, 4617.48, 3346.49, 366.018, 2.75664, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_west_bridge_guard', 0),
(@CGUID+277, 30739, 571, 0, 0, 1, 1, 0, 1, 4610.95, 3323.81, 366.629, 2.94121, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_west_bridge_guard', 0),

(@CGUID+278, 30739, 571, 0, 0, 1, 1, 0, 1, 4758.13, 3291.52, 366.482, 6.10242, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_west_roaming_bridge_guard', 0),
(@CGUID+279, 30739, 571, 0, 0, 1, 1, 0, 1, 4711.77, 3307.15, 372.307, 5.95712, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_west_roaming_bridge_guard', 0),
(@CGUID+280, 30739, 571, 0, 0, 1, 1, 0, 1, 4653.5, 3322.36, 369.371, 5.89822, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_west_roaming_bridge_guard', 0),
(@CGUID+281, 30739, 571, 0, 0, 1, 1, 0, 1, 4619.5, 3335.14, 366.44, 2.82732, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_west_roaming_bridge_guard', 0),

--  SE workshop start =============================================================================
--  SE workshop (horde)
(@CGUID+282, 30499, 571, 0, 0, 1, 1, 0, 0, 4357.67, 2357.99, 382.007, 1.67552, 180, 0, 0, 1, 0, 0, 0, 0, 0, 'wg_se_workshop_mechanic', 0),
--  SE workshop (alliance)
(@CGUID+283, 30400, 571, 0, 0, 1, 1, 0, 0, 4357.67, 2357.99, 382.007, 1.67552, 180, 0, 0, 1, 0, 0, 0, 0, 0, 'wg_se_workshop_mechanic', 0),

--  SE workshop horde guard
(@CGUID+284, 30739, 571, 0, 0, 1, 1, 0, 1, 4397.63, 2323.44, 376.212, 0.348455, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_se_workshop_standing_guard', 0),
(@CGUID+285, 30739, 571, 0, 0, 1, 1, 0, 1, 4393.61, 2383.39, 376.319, 5.98762, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_se_workshop_standing_guard', 0),
(@CGUID+286, 30739, 571, 0, 0, 1, 1, 0, 1, 4451.51, 2334.29, 367.513, 6.15256, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_se_workshop_standing_guard', 0),
(@CGUID+287, 30739, 571, 0, 0, 1, 1, 0, 1, 4450.81, 2323.66, 366.931, 6.0858, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_se_workshop_standing_guard', 0),
(@CGUID+288, 30739, 571, 0, 0, 1, 1, 0, 1, 4386.11, 2353.75, 376.318, 0.00290155, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_se_workshop_standing_guard', 0),
(@CGUID+289, 30739, 571, 0, 0, 1, 1, 0, 1, 4388.06, 2339.76, 376.316, 6.03869, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_se_workshop_standing_guard', 0),

(@CGUID+290, 30739, 571, 0, 0, 1, 1, 0, 1, 4449.17, 2329.48, 367.552, 5.913, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_se_workshop_roaming_guard', 0),
(@CGUID+291, 30739, 571, 0, 0, 1, 1, 0, 1, 4371.42, 2398.62, 376.209, 1.80144, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_se_workshop_roaming_guard', 0),
(@CGUID+292, 30739, 571, 0, 0, 1, 1, 0, 1, 4391.13, 2318.41, 376.279, 0.470187, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_se_workshop_roaming_guard', 0),
(@CGUID+293, 30739, 571, 0, 0, 1, 1, 0, 1, 4394.96, 2347.31, 376.175, 0.0107336, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_se_workshop_roaming_guard', 0),
--  SE workshop alliance guard
(@CGUID+294, 30740, 571, 0, 0, 1, 1, 0, 1, 4397.63, 2323.44, 376.212, 0.348455, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_se_workshop_standing_guard', 0),
(@CGUID+295, 30740, 571, 0, 0, 1, 1, 0, 1, 4393.61, 2383.39, 376.319, 5.98762, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_se_workshop_standing_guard', 0),
(@CGUID+296, 30740, 571, 0, 0, 1, 1, 0, 1, 4451.51, 2334.29, 367.513, 6.15256, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_se_workshop_standing_guard', 0),
(@CGUID+297, 30740, 571, 0, 0, 1, 1, 0, 1, 4450.81, 2323.66, 366.931, 6.0858, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_se_workshop_standing_guard', 0),
(@CGUID+298, 30740, 571, 0, 0, 1, 1, 0, 1, 4386.11, 2353.75, 376.318, 0.00290155, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_se_workshop_standing_guard', 0),
(@CGUID+299, 30740, 571, 0, 0, 1, 1, 0, 1, 4388.06, 2339.76, 376.316, 6.03869, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_se_workshop_standing_guard', 0),

(@CGUID+300, 30740, 571, 0, 0, 1, 1, 0, 1, 4449.17, 2329.48, 367.552, 5.913, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_se_workshop_roaming_guard', 0),
(@CGUID+301, 30740, 571, 0, 0, 1, 1, 0, 1, 4371.42, 2398.62, 376.209, 1.80144, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_se_workshop_roaming_guard', 0),
(@CGUID+302, 30740, 571, 0, 0, 1, 1, 0, 1, 4391.13, 2318.41, 376.279, 0.470187, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_se_workshop_roaming_guard', 0),
(@CGUID+303, 30740, 571, 0, 0, 1, 1, 0, 1, 4394.96, 2347.31, 376.175, 0.0107336, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_se_workshop_roaming_guard', 0),
--  SE workshop end =============================================================================

--  NE workshop start =============================================================================
--  NE workshop
(@CGUID+304, 30499, 571, 0, 0, 1, 1, 0, 0, 4939.76, 2389.06, 326.153, 3.26377, 180, 0, 0, 1, 0, 0, 0, 0, 0, 'wg_ne_workshop_mechanic', 0),
(@CGUID+305, 30400, 571, 0, 0, 1, 1, 0, 0, 4939.76, 2389.06, 326.153, 3.26377, 180, 0, 0, 1, 0, 0, 0, 0, 0, 'wg_ne_workshop_mechanic', 0),

--  NE workshop horde guard
(@CGUID+306, 30739, 571, 0, 0, 1, 1, 0, 1, 5016.53, 2524.13, 341.319, 1.06554, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_ne_workshop_standing_guard', 0),
(@CGUID+307, 30739, 571, 0, 0, 1, 1, 0, 1, 5005.08, 2528.71, 340.452, 1.38755, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_ne_workshop_standing_guard', 0),
(@CGUID+308, 30739, 571, 0, 0, 1, 1, 0, 1, 4782.36, 2433.88, 344.534, 3.30784, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_ne_workshop_standing_guard', 0),
(@CGUID+309, 30739, 571, 0, 0, 1, 1, 0, 1, 4783.54, 2422.68, 344.582, 3.15862, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_ne_workshop_standing_guard', 0),
(@CGUID+310, 30739, 571, 0, 0, 1, 1, 0, 1, 4843.77, 2403.85, 322.302, 2.84446, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_ne_workshop_standing_guard', 0),
(@CGUID+311, 30739, 571, 0, 0, 1, 1, 0, 1, 4846.54, 2422.04, 322.583, 3.14291, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_ne_workshop_standing_guard', 0),
(@CGUID+312, 30739, 571, 0, 0, 1, 1, 0, 1, 4946, 2424.06, 320.177, 1.32367, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_ne_workshop_standing_guard', 0),
(@CGUID+313, 30739, 571, 0, 0, 1, 1, 0, 1, 4965.72, 2421.54, 320.207, 1.5004, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_ne_workshop_standing_guard', 0),
(@CGUID+314, 30739, 571, 0, 0, 1, 1, 0, 1, 4965.48, 2468.05, 323.652, 0.895629, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_ne_workshop_standing_guard', 0),
(@CGUID+315, 30739, 571, 0, 0, 1, 1, 0, 1, 4976.01, 2461.58, 324.205, 0.89287, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_ne_workshop_standing_guard', 0),

(@CGUID+316, 30739, 571, 0, 0, 1, 1, 0, 1, 4781.14, 2425.94, 345.204, 3.3275, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_ne_workshop_roaming_guard', 0),
(@CGUID+317, 30739, 571, 0, 0, 1, 1, 0, 1, 4855.66, 2416.05, 321.383, 3.23325, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_ne_workshop_roaming_guard', 0),
(@CGUID+318, 30739, 571, 0, 0, 1, 1, 0, 1, 4905.34, 2460.59, 320.467, 3.47673, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_ne_workshop_roaming_guard', 0),
(@CGUID+319, 30739, 571, 0, 0, 1, 1, 0, 1, 4954.51, 2429.28, 320.178, 1.44254, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_ne_workshop_roaming_guard', 0),
(@CGUID+320, 30739, 571, 0, 0, 1, 1, 0, 1, 4971.93, 2468.57, 324.354, 0.979156, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_ne_workshop_roaming_guard', 0),
(@CGUID+321, 30739, 571, 0, 0, 1, 1, 0, 1, 5009.71, 2522.72, 339.699, 1.12838, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_ne_workshop_roaming_guard', 0),
--  NE workshop alliance guard
(@CGUID+322, 30740, 571, 0, 0, 1, 1, 0, 1, 5016.53, 2524.13, 341.319, 1.06554, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_ne_workshop_standing_guard', 0),
(@CGUID+323, 30740, 571, 0, 0, 1, 1, 0, 1, 5005.08, 2528.71, 340.452, 1.38755, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_ne_workshop_standing_guard', 0),
(@CGUID+324, 30740, 571, 0, 0, 1, 1, 0, 1, 4782.36, 2433.88, 344.534, 3.30784, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_ne_workshop_standing_guard', 0),
(@CGUID+325, 30740, 571, 0, 0, 1, 1, 0, 1, 4783.54, 2422.68, 344.582, 3.15862, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_ne_workshop_standing_guard', 0),
(@CGUID+326, 30740, 571, 0, 0, 1, 1, 0, 1, 4843.77, 2403.85, 322.302, 2.84446, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_ne_workshop_standing_guard', 0),
(@CGUID+327, 30740, 571, 0, 0, 1, 1, 0, 1, 4846.54, 2422.04, 322.583, 3.14291, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_ne_workshop_standing_guard', 0),
(@CGUID+328, 30740, 571, 0, 0, 1, 1, 0, 1, 4946, 2424.06, 320.177, 1.32367, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_ne_workshop_standing_guard', 0),
(@CGUID+329, 30740, 571, 0, 0, 1, 1, 0, 1, 4965.72, 2421.54, 320.207, 1.5004, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_ne_workshop_standing_guard', 0),
(@CGUID+330, 30740, 571, 0, 0, 1, 1, 0, 1, 4965.48, 2468.05, 323.652, 0.895629, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_ne_workshop_standing_guard', 0),
(@CGUID+331, 30740, 571, 0, 0, 1, 1, 0, 1, 4976.01, 2461.58, 324.205, 0.89287, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_ne_workshop_standing_guard', 0),

(@CGUID+332, 30740, 571, 0, 0, 1, 1, 0, 1, 4781.14, 2425.94, 345.204, 3.3275, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_ne_workshop_roaming_guard', 0),
(@CGUID+333, 30740, 571, 0, 0, 1, 1, 0, 1, 4855.66, 2416.05, 321.383, 3.23325, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_ne_workshop_roaming_guard', 0),
(@CGUID+334, 30740, 571, 0, 0, 1, 1, 0, 1, 4905.34, 2460.59, 320.467, 3.47673, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_ne_workshop_roaming_guard', 0),
(@CGUID+335, 30740, 571, 0, 0, 1, 1, 0, 1, 4954.51, 2429.28, 320.178, 1.44254, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_ne_workshop_roaming_guard', 0),
(@CGUID+336, 30740, 571, 0, 0, 1, 1, 0, 1, 4971.93, 2468.57, 324.354, 0.979156, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_ne_workshop_roaming_guard', 0),
(@CGUID+337, 30740, 571, 0, 0, 1, 1, 0, 1, 5009.71, 2522.72, 339.699, 1.12838, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_ne_workshop_roaming_guard', 0),
--  NE workshop end =============================================================================

--  SW workshop start =============================================================================
--  SW workshop
(@CGUID+338, 30499, 571, 0, 0, 1, 1, 0, 0, 4354.15, 3312.82, 378.046, 1.67552, 180, 0, 0, 1, 0, 0, 0, 0, 0, 'wg_sw_workshop_mechanic', 0),
(@CGUID+339, 30400, 571, 0, 0, 1, 1, 0, 0, 4354.15, 3312.82, 378.046, 1.67552, 180, 0, 0, 1, 0, 0, 0, 0, 0, 'wg_sw_workshop_mechanic', 0),

--  SW workshop alliance guard
(@CGUID+340, 30740, 571, 0, 0, 1, 1, 0, 1, 4392.6, 3375.58, 364.757, 1.43785, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_sw_workshop_standing_guard', 0),
(@CGUID+341, 30740, 571, 0, 0, 1, 1, 0, 1, 4381.9, 3371.63, 366.301, 1.5753, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_sw_workshop_standing_guard', 0),
(@CGUID+342, 30740, 571, 0, 0, 1, 1, 0, 1, 4371.68, 3224.95, 368.408, 4.65406, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_sw_workshop_standing_guard', 0),
(@CGUID+343, 30740, 571, 0, 0, 1, 1, 0, 1, 4384.65, 3225.38, 368.327, 4.80721, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_sw_workshop_standing_guard', 0),
(@CGUID+344, 30740, 571, 0, 0, 1, 1, 0, 1, 4377.84, 3288.74, 372.429, 5.93186, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_sw_workshop_standing_guard', 0),
(@CGUID+345, 30740, 571, 0, 0, 1, 1, 0, 1, 4382.47, 3306.09, 372.429, 6.18711, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_sw_workshop_standing_guard', 0),
(@CGUID+346, 30740, 571, 0, 0, 1, 1, 0, 1, 4449.18, 3323.92, 360.524, 0.269141, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_sw_workshop_standing_guard', 0),
(@CGUID+347, 30740, 571, 0, 0, 1, 1, 0, 1, 4456.21, 3312.13, 359.754, 0.339827, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_sw_workshop_standing_guard', 0),

(@CGUID+348, 30740, 571, 0, 0, 1, 1, 0, 1, 4387.08, 3369.63, 366.507, 1.44177, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_sw_workshop_roaming_guard', 0),
(@CGUID+349, 30740, 571, 0, 0, 1, 1, 0, 1, 4405.18, 3335.3, 372.305, 1.08834, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_sw_workshop_roaming_guard', 0),
(@CGUID+350, 30740, 571, 0, 0, 1, 1, 0, 1, 4428.78, 3275.72, 372.37, 0.232247, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_sw_workshop_roaming_guard', 0),
(@CGUID+351, 30740, 571, 0, 0, 1, 1, 0, 1, 4377.95, 3229.73, 369.446, 4.63048, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_sw_workshop_roaming_guard', 0),
(@CGUID+352, 30740, 571, 0, 0, 1, 1, 0, 1, 4384.36, 3298.64, 372.428, 5.98528, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_sw_workshop_roaming_guard', 0),
(@CGUID+353, 30740, 571, 0, 0, 1, 1, 0, 1, 4446.89, 3317.03, 361.504, 0.271519, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_sw_workshop_roaming_guard', 0),
--  SW workshop horde guard
(@CGUID+354, 30739, 571, 0, 0, 1, 1, 0, 1, 4392.6, 3375.58, 364.757, 1.43785, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_sw_workshop_standing_guard', 0),
(@CGUID+355, 30739, 571, 0, 0, 1, 1, 0, 1, 4381.9, 3371.63, 366.301, 1.5753, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_sw_workshop_standing_guard', 0),
(@CGUID+356, 30739, 571, 0, 0, 1, 1, 0, 1, 4371.68, 3224.95, 368.408, 4.65406, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_sw_workshop_standing_guard', 0),
(@CGUID+357, 30739, 571, 0, 0, 1, 1, 0, 1, 4384.65, 3225.38, 368.327, 4.80721, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_sw_workshop_standing_guard', 0),
(@CGUID+358, 30739, 571, 0, 0, 1, 1, 0, 1, 4377.84, 3288.74, 372.429, 5.93186, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_sw_workshop_standing_guard', 0),
(@CGUID+359, 30739, 571, 0, 0, 1, 1, 0, 1, 4382.47, 3306.09, 372.429, 6.18711, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_sw_workshop_standing_guard', 0),
(@CGUID+360, 30739, 571, 0, 0, 1, 1, 0, 1, 4449.18, 3323.92, 360.524, 0.269141, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_sw_workshop_standing_guard', 0),
(@CGUID+361, 30739, 571, 0, 0, 1, 1, 0, 1, 4456.21, 3312.13, 359.754, 0.339827, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_sw_workshop_standing_guard', 0),

(@CGUID+362, 30739, 571, 0, 0, 1, 1, 0, 1, 4387.08, 3369.63, 366.507, 1.44177, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_sw_workshop_roaming_guard', 0),
(@CGUID+363, 30739, 571, 0, 0, 1, 1, 0, 1, 4405.18, 3335.3, 372.305, 1.08834, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_sw_workshop_roaming_guard', 0),
(@CGUID+364, 30739, 571, 0, 0, 1, 1, 0, 1, 4428.78, 3275.72, 372.37, 0.232247, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_sw_workshop_roaming_guard', 0),
(@CGUID+365, 30739, 571, 0, 0, 1, 1, 0, 1, 4377.95, 3229.73, 369.446, 4.63048, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_sw_workshop_roaming_guard', 0),
(@CGUID+366, 30739, 571, 0, 0, 1, 1, 0, 1, 4384.36, 3298.64, 372.428, 5.98528, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_sw_workshop_roaming_guard', 0),
(@CGUID+367, 30739, 571, 0, 0, 1, 1, 0, 1, 4446.89, 3317.03, 361.504, 0.271519, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_sw_workshop_roaming_guard', 0),
--  SW workshop end =============================================================================

--  NW workshop start =============================================================================
--  NW workshop
(@CGUID+368, 30499, 571, 0, 0, 1, 1, 0, 0, 4964.89, 3383.06, 382.911, 6.12611, 180, 0, 0, 1, 0, 0, 0, 0, 0, 'wg_nw_workshop_mechanic', 0),
(@CGUID+369, 30400, 571, 0, 0, 1, 1, 0, 0, 4964.89, 3383.06, 382.911, 6.12611, 180, 0, 0, 1, 0, 0, 0, 0, 0, 'wg_nw_workshop_mechanic', 0),

--  NW workshop alliance guard
(@CGUID+370, 30740, 571, 0, 0, 1, 1, 0, 1, 5019.27, 3287.78, 370.23, 5.4614, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_nw_workshop_standing_guard', 0),
(@CGUID+371, 30740, 571, 0, 0, 1, 1, 0, 1, 5010.93, 3280.21, 370.568, 5.26898, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_nw_workshop_standing_guard', 0),
(@CGUID+372, 30740, 571, 0, 0, 1, 1, 0, 1, 4953.69, 3352.94, 376.877, 4.44037, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_nw_workshop_standing_guard', 0),
(@CGUID+373, 30740, 571, 0, 0, 1, 1, 0, 1, 4937.44, 3360.38, 376.877, 4.27152, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_nw_workshop_standing_guard', 0),
(@CGUID+374, 30740, 571, 0, 0, 1, 1, 0, 1, 4861.92, 3314.75, 368.926, 3.4979, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_nw_workshop_standing_guard', 0),
(@CGUID+375, 30740, 571, 0, 0, 1, 1, 0, 1, 4859.9, 3328.47, 370.357, 3.27013, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_nw_workshop_standing_guard', 0),

(@CGUID+376, 30740, 571, 0, 0, 1, 1, 0, 1, 5008.68, 3293.53, 373.181, 5.38601, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_nw_workshop_roaming_guard', 0),
(@CGUID+377, 30740, 571, 0, 0, 1, 1, 0, 1, 4906.66, 3290.53, 377.695, 3.20653, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_nw_workshop_roaming_guard', 0),
(@CGUID+378, 30740, 571, 0, 0, 1, 1, 0, 1, 4961.54, 3297.42, 377.512, 1.04275, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_nw_workshop_roaming_guard', 0),
(@CGUID+379, 30740, 571, 0, 0, 1, 1, 0, 1, 4944.6, 3349.69, 376.876, 4.71057, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_nw_workshop_roaming_guard', 0),
(@CGUID+380, 30740, 571, 0, 0, 1, 1, 0, 1, 4904.11, 3340.72, 374.903, 3.69739, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_nw_workshop_roaming_guard', 0),
(@CGUID+381, 30740, 571, 0, 0, 1, 1, 0, 1, 4864.22, 3324.81, 370.705, 3.49398, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_nw_workshop_roaming_guard', 0),
--  NW workshop horde guard
(@CGUID+382, 30739, 571, 0, 0, 1, 1, 0, 1, 5019.27, 3287.78, 370.23, 5.4614, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_nw_workshop_standing_guard', 0),
(@CGUID+383, 30739, 571, 0, 0, 1, 1, 0, 1, 5010.93, 3280.21, 370.568, 5.26898, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_nw_workshop_standing_guard', 0),
(@CGUID+384, 30739, 571, 0, 0, 1, 1, 0, 1, 4953.69, 3352.94, 376.877, 4.44037, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_nw_workshop_standing_guard', 0),
(@CGUID+385, 30739, 571, 0, 0, 1, 1, 0, 1, 4937.44, 3360.38, 376.877, 4.27152, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_nw_workshop_standing_guard', 0),
(@CGUID+386, 30739, 571, 0, 0, 1, 1, 0, 1, 4861.92, 3314.75, 368.926, 3.4979, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_nw_workshop_standing_guard', 0),
(@CGUID+387, 30739, 571, 0, 0, 1, 1, 0, 1, 4859.9, 3328.47, 370.357, 3.27013, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_nw_workshop_standing_guard', 0),

(@CGUID+388, 30739, 571, 0, 0, 1, 1, 0, 1, 5008.68, 3293.53, 373.181, 5.38601, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_nw_workshop_roaming_guard', 0),
(@CGUID+389, 30739, 571, 0, 0, 1, 1, 0, 1, 4906.66, 3290.53, 377.695, 3.20653, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_nw_workshop_roaming_guard', 0),
(@CGUID+390, 30739, 571, 0, 0, 1, 1, 0, 1, 4961.54, 3297.42, 377.512, 1.04275, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_nw_workshop_roaming_guard', 0),
(@CGUID+391, 30739, 571, 0, 0, 1, 1, 0, 1, 4944.6, 3349.69, 376.876, 4.71057, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_nw_workshop_roaming_guard', 0),
(@CGUID+392, 30739, 571, 0, 0, 1, 1, 0, 1, 4904.11, 3340.72, 374.903, 3.69739, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_nw_workshop_roaming_guard', 0),
(@CGUID+393, 30739, 571, 0, 0, 1, 1, 0, 1, 4864.22, 3324.81, 370.705, 3.49398, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_nw_workshop_roaming_guard', 0),
--  NW workshop end =============================================================================

--  Fortress new cannons
(@CGUID+394, 28366, 571, 0, 0, 1, 1, 0, 0, 5281.18, 3072.23, 438.5, 1.51015, 300, 0, 0, 50000, 0, 0, 0, 0, 0, 'npc_wg_NW_cannon', 0),
(@CGUID+395, 28366, 571, 0, 0, 1, 1, 0, 0, 5254.99, 3047.82, 438.5, 3.12807, 300, 0, 0, 50000, 0, 0, 0, 0, 0, 'npc_wg_NW_cannon', 0),
(@CGUID+396, 28366, 571, 0, 0, 1, 1, 0, 0, 5163.61, 2959.83, 439.845, 1.60438, 300, 0, 0, 50000, 0, 0, 0, 0, 0, 'npc_wg_SW_cannon', 0),
(@CGUID+397, 28366, 571, 0, 0, 1, 1, 0, 0, 5137.9, 2935.27, 439.847, 3.11627, 300, 0, 0, 50000, 0, 0, 0, 0, 0, 'npc_wg_SW_cannon', 0),
(@CGUID+398, 28366, 571, 0, 0, 1, 1, 0, 0, 5138.63, 2747.59, 439.844, 3.07937, 300, 0, 0, 50000, 0, 0, 0, 0, 0, 'npc_wg_SE_cannon', 0),
(@CGUID+399, 28366, 571, 0, 0, 1, 1, 0, 0, 5163.91, 2722.57, 439.844, 4.68944, 300, 0, 0, 50000, 0, 0, 0, 0, 0, 'npc_wg_SE_cannon', 0),
(@CGUID+400, 28366, 571, 0, 0, 1, 1, 0, 0, 5253.62, 2632.15, 439.755, 3.07545, 300, 0, 0, 50000, 0, 0, 0, 0, 0, 'npc_wg_NE_cannon', 0),
(@CGUID+401, 28366, 571, 0, 0, 1, 1, 0, 0, 5278.1, 2606.33, 439.755, 4.57948, 300, 0, 0, 50000, 0, 0, 0, 0, 0, 'npc_wg_NE_cannon', 0),

--  keep tower NW guards
(@CGUID+402, 30740, 571, 0, 0, 1, 1, 0, 1, 5400.77, 3034.5, 409.391, 4.79248, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_nw_standing_guard', 0),
(@CGUID+403, 30740, 571, 0, 0, 1, 1, 0, 1, 5384.47, 3034.04, 409.191, 3.20205, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_nw_standing_guard', 0),
(@CGUID+404, 30740, 571, 0, 0, 1, 1, 0, 1, 5366.7, 2977.27, 409.192, 3.08032, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_nw_standing_guard', 0),
(@CGUID+405, 30740, 571, 0, 0, 1, 1, 0, 1, 5366.73, 2993.81, 409.192, 3.07246, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_nw_standing_guard', 0),
(@CGUID+406, 30740, 571, 0, 0, 1, 1, 0, 1, 5345.45, 2915.63, 409.192, 1.52915, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_nw_standing_guard', 0),
(@CGUID+407, 30740, 571, 0, 0, 1, 1, 0, 1, 5340.47, 2915.78, 409.192, 1.46239, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_nw_standing_guard', 0),
(@CGUID+408, 30740, 571, 0, 0, 1, 1, 0, 1, 5292.97, 2986.82, 409.192, 1.46632, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_nw_standing_guard', 0),
(@CGUID+409, 30740, 571, 0, 0, 1, 1, 0, 1, 5293.34, 2966.89, 409.191, 4.7218, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_nw_standing_guard', 0),
(@CGUID+410, 30740, 571, 0, 0, 1, 1, 0, 1, 5341.97, 3034.46, 409.192, 3.24525, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_nw_standing_guard', 0),
(@CGUID+411, 30740, 571, 0, 0, 1, 1, 0, 1, 5363.03, 3034.86, 409.192, 6.21012, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_nw_standing_guard', 0),
(@CGUID+412, 30740, 571, 0, 0, 1, 1, 0, 1, 5299.66, 3013.27, 408.943, 5.42867, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_nw_standing_guard', 0),
(@CGUID+413, 30740, 571, 0, 0, 1, 1, 0, 1, 5314.49, 3027.74, 409.123, 5.46794, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_nw_standing_guard', 0),
(@CGUID+414, 30740, 571, 0, 0, 1, 1, 0, 1, 5308.14, 3019.06, 409.06, 5.5347, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_nw_standing_guard', 0),

(@CGUID+415, 30739, 571, 0, 0, 1, 1, 0, 1, 5400.77, 3034.5, 409.391, 4.79248, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_nw_standing_guard', 0),
(@CGUID+416, 30739, 571, 0, 0, 1, 1, 0, 1, 5384.47, 3034.04, 409.191, 3.20205, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_nw_standing_guard', 0),
(@CGUID+417, 30739, 571, 0, 0, 1, 1, 0, 1, 5366.7, 2977.27, 409.192, 3.08032, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_nw_standing_guard', 0),
(@CGUID+418, 30739, 571, 0, 0, 1, 1, 0, 1, 5366.73, 2993.81, 409.192, 3.07246, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_nw_standing_guard', 0),
(@CGUID+419, 30739, 571, 0, 0, 1, 1, 0, 1, 5345.45, 2915.63, 409.192, 1.52915, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_nw_standing_guard', 0),
(@CGUID+420, 30739, 571, 0, 0, 1, 1, 0, 1, 5340.47, 2915.78, 409.192, 1.46239, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_nw_standing_guard', 0),
(@CGUID+421, 30739, 571, 0, 0, 1, 1, 0, 1, 5292.97, 2986.82, 409.192, 1.46632, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_nw_standing_guard', 0),
(@CGUID+422, 30739, 571, 0, 0, 1, 1, 0, 1, 5293.34, 2966.89, 409.191, 4.7218, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_nw_standing_guard', 0),
(@CGUID+423, 30739, 571, 0, 0, 1, 1, 0, 1, 5341.97, 3034.46, 409.192, 3.24525, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_nw_standing_guard', 0),
(@CGUID+424, 30739, 571, 0, 0, 1, 1, 0, 1, 5363.03, 3034.86, 409.192, 6.21012, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_nw_standing_guard', 0),
(@CGUID+425, 30739, 571, 0, 0, 1, 1, 0, 1, 5299.66, 3013.27, 408.943, 5.42867, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_nw_standing_guard', 0),
(@CGUID+426, 30739, 571, 0, 0, 1, 1, 0, 1, 5314.49, 3027.74, 409.123, 5.46794, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_nw_standing_guard', 0),
(@CGUID+427, 30739, 571, 0, 0, 1, 1, 0, 1, 5308.14, 3019.06, 409.06, 5.5347, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_nw_standing_guard', 0),

(@CGUID+428, 30740, 571, 0, 0, 1, 1, 0, 1, 5275.82, 3069.91, 412.148, 1.84166, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_nw_standing_guard', 0),
(@CGUID+429, 30740, 571, 0, 0, 1, 1, 0, 1, 5285.28, 3071.04, 412.148, 1.19371, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_nw_standing_guard', 0),
(@CGUID+430, 30740, 571, 0, 0, 1, 1, 0, 1, 5257.11, 3044.36, 412.148, 3.18076, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_nw_standing_guard', 0),
(@CGUID+431, 30740, 571, 0, 0, 1, 1, 0, 1, 5256.3, 3048.9, 412.148, 2.90196, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_nw_standing_guard', 0),
(@CGUID+432, 30740, 571, 0, 0, 1, 1, 0, 1, 5278.73, 3052.34, 438.5, 2.09693, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_nw_standing_guard', 0),
(@CGUID+433, 30740, 571, 0, 0, 1, 1, 0, 1, 5275.22, 3049.24, 438.5, 2.47393, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_nw_standing_guard', 0),
(@CGUID+434, 30740, 571, 0, 0, 1, 1, 0, 1, 5279.95, 3024.97, 438.5, 4.67698, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_nw_standing_guard', 0),
(@CGUID+435, 30740, 571, 0, 0, 1, 1, 0, 1, 5303.29, 3046.83, 438.5, 6.20851, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_nw_standing_guard', 0),
(@CGUID+436, 30740, 571, 0, 0, 1, 1, 0, 1, 5266.1, 3014.83, 408.661, 3.13911, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_nw_standing_guard', 0),
(@CGUID+437, 30740, 571, 0, 0, 1, 1, 0, 1, 5267.73, 3011.08, 408.805, 3.46897, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_nw_standing_guard', 0),
(@CGUID+438, 30740, 571, 0, 0, 1, 1, 0, 1, 5311.99, 3057.63, 408.807, 1.79216, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_nw_standing_guard', 0),
(@CGUID+439, 30740, 571, 0, 0, 1, 1, 0, 1, 5317.58, 3056.54, 409.063, 1.0264, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_nw_standing_guard', 0),

(@CGUID+440, 30739, 571, 0, 0, 1, 1, 0, 1, 5275.82, 3069.91, 412.148, 1.84166, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_nw_standing_guard', 0),
(@CGUID+441, 30739, 571, 0, 0, 1, 1, 0, 1, 5285.28, 3071.04, 412.148, 1.19371, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_nw_standing_guard', 0),
(@CGUID+442, 30739, 571, 0, 0, 1, 1, 0, 1, 5257.11, 3044.36, 412.148, 3.18076, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_nw_standing_guard', 0),
(@CGUID+443, 30739, 571, 0, 0, 1, 1, 0, 1, 5256.3, 3048.9, 412.148, 2.90196, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_nw_standing_guard', 0),
(@CGUID+444, 30739, 571, 0, 0, 1, 1, 0, 1, 5278.73, 3052.34, 438.5, 2.09693, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_nw_standing_guard', 0),
(@CGUID+445, 30739, 571, 0, 0, 1, 1, 0, 1, 5275.22, 3049.24, 438.5, 2.47393, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_nw_standing_guard', 0),
(@CGUID+446, 30739, 571, 0, 0, 1, 1, 0, 1, 5279.95, 3024.97, 438.5, 4.67698, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_nw_standing_guard', 0),
(@CGUID+447, 30739, 571, 0, 0, 1, 1, 0, 1, 5303.29, 3046.83, 438.5, 6.20851, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_nw_standing_guard', 0),
(@CGUID+448, 30739, 571, 0, 0, 1, 1, 0, 1, 5266.1, 3014.83, 408.661, 3.13911, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_nw_standing_guard', 0),
(@CGUID+449, 30739, 571, 0, 0, 1, 1, 0, 1, 5267.73, 3011.08, 408.805, 3.46897, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_nw_standing_guard', 0),
(@CGUID+450, 30739, 571, 0, 0, 1, 1, 0, 1, 5311.99, 3057.63, 408.807, 1.79216, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_nw_standing_guard', 0),
(@CGUID+451, 30739, 571, 0, 0, 1, 1, 0, 1, 5317.58, 3056.54, 409.063, 1.0264, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_nw_standing_guard', 0),

(@CGUID+452, 30740, 571, 0, 0, 1, 1, 0, 1, 5287.31, 3045.18, 438.5, 0.137304, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_nw_roaming_guard', 0),
(@CGUID+453, 30740, 571, 0, 0, 1, 1, 0, 1, 5291, 3056.95, 412.148, 0.639962, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_nw_roaming_guard', 0),
(@CGUID+454, 30740, 571, 0, 0, 1, 1, 0, 1, 5270.89, 3056.87, 412.148, 2.38355, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_nw_roaming_guard', 0),
(@CGUID+456, 30740, 571, 0, 0, 1, 1, 0, 1, 5271.26, 3038.46, 412.148, 3.88366, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_nw_roaming_guard', 0),

(@CGUID+457, 30739, 571, 0, 0, 1, 1, 0, 1, 5287.31, 3045.18, 438.5, 0.137304, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_nw_roaming_guard', 0),
(@CGUID+458, 30739, 571, 0, 0, 1, 1, 0, 1, 5291, 3056.95, 412.148, 0.639962, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_nw_roaming_guard', 0),
(@CGUID+459, 30739, 571, 0, 0, 1, 1, 0, 1, 5270.89, 3056.87, 412.148, 2.38355, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_nw_roaming_guard', 0),
(@CGUID+460, 30739, 571, 0, 0, 1, 1, 0, 1, 5271.26, 3038.46, 412.148, 3.88366, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_nw_roaming_guard', 0),

--  keep tower SW guards
(@CGUID+461, 30740, 571, 0, 0, 1, 1, 0, 1, 5154.55, 2850.13, 409.16, 2.99613, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_sw_standing_guard', 0),
(@CGUID+462, 30740, 571, 0, 0, 1, 1, 0, 1, 5195.77, 2947.06, 409.192, 1.606, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_sw_standing_guard', 0),
(@CGUID+463, 30740, 571, 0, 0, 1, 1, 0, 1, 5199.91, 2944.89, 409.19, 0.663525, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_sw_standing_guard', 0),
(@CGUID+464, 30740, 571, 0, 0, 1, 1, 0, 1, 5152.8, 2898.35, 409.197, 4.09177, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_sw_standing_guard', 0),
(@CGUID+465, 30740, 571, 0, 0, 1, 1, 0, 1, 5150.89, 2903.39, 409.192, 3.09824, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_sw_standing_guard', 0),
(@CGUID+466, 30740, 571, 0, 0, 1, 1, 0, 1, 5175.29, 2852.24, 409.191, 4.60622, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_sw_standing_guard', 0),
(@CGUID+467, 30740, 571, 0, 0, 1, 1, 0, 1, 5174.53, 2873.89, 409.197, 1.26435, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_sw_standing_guard', 0),
(@CGUID+468, 30740, 571, 0, 0, 1, 1, 0, 1, 5245.8, 2922.53, 409.191, 6.28304, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_sw_standing_guard', 0),
(@CGUID+469, 30740, 571, 0, 0, 1, 1, 0, 1, 5225.08, 2921.72, 409.192, 3.17679, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_sw_standing_guard', 0),
(@CGUID+470, 30740, 571, 0, 0, 1, 1, 0, 1, 5185.09, 2934.41, 439.847, 0.0548558, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_sw_standing_guard', 0),
(@CGUID+471, 30740, 571, 0, 0, 1, 1, 0, 1, 5162.58, 2912.77, 439.847, 4.76725, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_sw_standing_guard', 0),
(@CGUID+472, 30740, 571, 0, 0, 1, 1, 0, 1, 5176.83, 2951.8, 413.495, 0.730304, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_sw_standing_guard', 0),
(@CGUID+473, 30740, 571, 0, 0, 1, 1, 0, 1, 5180.17, 2947.78, 413.495, 0.604639, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_sw_standing_guard', 0),
(@CGUID+474, 30740, 571, 0, 0, 1, 1, 0, 1, 5145.83, 2948.01, 413.496, 2.67415, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_sw_standing_guard', 0),
(@CGUID+475, 30740, 571, 0, 0, 1, 1, 0, 1, 5149.89, 2952.17, 413.496, 2.0262, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_sw_standing_guard', 0),
(@CGUID+476, 30740, 571, 0, 0, 1, 1, 0, 1, 5146.22, 2922.3, 413.495, 3.69909, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_sw_standing_guard', 0),
(@CGUID+477, 30740, 571, 0, 0, 1, 1, 0, 1, 5149.67, 2916.7, 413.495, 3.74622, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_sw_standing_guard', 0),
(@CGUID+478, 30740, 571, 0, 0, 1, 1, 0, 1, 5197.32, 2914.2, 409.192, 5.35629, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_sw_standing_guard', 0),
(@CGUID+479, 30740, 571, 0, 0, 1, 1, 0, 1, 5182.54, 2900.89, 409.192, 5.45838, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_sw_standing_guard', 0),

(@CGUID+480, 30739, 571, 0, 0, 1, 1, 0, 1, 5154.55, 2850.13, 409.16, 2.99613, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_sw_standing_guard', 0),
(@CGUID+481, 30739, 571, 0, 0, 1, 1, 0, 1, 5195.77, 2947.06, 409.192, 1.606, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_sw_standing_guard', 0),
(@CGUID+482, 30739, 571, 0, 0, 1, 1, 0, 1, 5199.91, 2944.89, 409.19, 0.663525, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_sw_standing_guard', 0),
(@CGUID+483, 30739, 571, 0, 0, 1, 1, 0, 1, 5152.8, 2898.35, 409.197, 4.09177, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_sw_standing_guard', 0),
(@CGUID+484, 30739, 571, 0, 0, 1, 1, 0, 1, 5150.89, 2903.39, 409.192, 3.09824, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_sw_standing_guard', 0),
(@CGUID+485, 30739, 571, 0, 0, 1, 1, 0, 1, 5175.29, 2852.24, 409.191, 4.60622, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_sw_standing_guard', 0),
(@CGUID+486, 30739, 571, 0, 0, 1, 1, 0, 1, 5174.53, 2873.89, 409.197, 1.26435, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_sw_standing_guard', 0),
(@CGUID+487, 30739, 571, 0, 0, 1, 1, 0, 1, 5245.8, 2922.53, 409.191, 6.28304, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_sw_standing_guard', 0),
(@CGUID+488, 30739, 571, 0, 0, 1, 1, 0, 1, 5225.08, 2921.72, 409.192, 3.17679, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_sw_standing_guard', 0),
(@CGUID+489, 30739, 571, 0, 0, 1, 1, 0, 1, 5185.09, 2934.41, 439.847, 0.0548558, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_sw_standing_guard', 0),
(@CGUID+490, 30739, 571, 0, 0, 1, 1, 0, 1, 5162.58, 2912.77, 439.847, 4.76725, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_sw_standing_guard', 0),
(@CGUID+491, 30739, 571, 0, 0, 1, 1, 0, 1, 5176.83, 2951.8, 413.495, 0.730304, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_sw_standing_guard', 0),
(@CGUID+492, 30739, 571, 0, 0, 1, 1, 0, 1, 5180.17, 2947.78, 413.495, 0.604639, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_sw_standing_guard', 0),
(@CGUID+493, 30739, 571, 0, 0, 1, 1, 0, 1, 5145.83, 2948.01, 413.496, 2.67415, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_sw_standing_guard', 0),
(@CGUID+494, 30739, 571, 0, 0, 1, 1, 0, 1, 5149.89, 2952.17, 413.496, 2.0262, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_sw_standing_guard', 0),
(@CGUID+495, 30739, 571, 0, 0, 1, 1, 0, 1, 5146.22, 2922.3, 413.495, 3.69909, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_sw_standing_guard', 0),
(@CGUID+496, 30739, 571, 0, 0, 1, 1, 0, 1, 5149.67, 2916.7, 413.495, 3.74622, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_sw_standing_guard', 0),
(@CGUID+497, 30739, 571, 0, 0, 1, 1, 0, 1, 5197.32, 2914.2, 409.192, 5.35629, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_sw_standing_guard', 0),
(@CGUID+498, 30739, 571, 0, 0, 1, 1, 0, 1, 5182.54, 2900.89, 409.192, 5.45838, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_sw_standing_guard', 0),

(@CGUID+499, 30740, 571, 0, 0, 1, 1, 0, 1, 5261.11, 2857.32, 409.191, 4.95806, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_sw_roaming_guard', 0),
(@CGUID+500, 30740, 571, 0, 0, 1, 1, 0, 1, 5242.9, 2882.67, 409.192, 5.80786, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_sw_roaming_guard', 0),
(@CGUID+501, 30740, 571, 0, 0, 1, 1, 0, 1, 5213.54, 2895.66, 409.192, 0.146713, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_sw_roaming_guard', 0),
(@CGUID+502, 30740, 571, 0, 0, 1, 1, 0, 1, 5182.78, 2875.56, 409.192, 0.578682, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_sw_roaming_guard', 0),
(@CGUID+503, 30740, 571, 0, 0, 1, 1, 0, 1, 5179.43, 2852.55, 409.198, 3.46895, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_sw_roaming_guard', 0),
(@CGUID+504, 30740, 571, 0, 0, 1, 1, 0, 1, 5158.75, 2938.87, 439.846, 2.67571, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_sw_roaming_guard', 0),
(@CGUID+505, 30740, 571, 0, 0, 1, 1, 0, 1, 5172.62, 2925.42, 413.495, 5.47565, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_sw_roaming_guard', 0),
(@CGUID+506, 30740, 571, 0, 0, 1, 1, 0, 1, 5173.56, 2944.99, 413.495, 0.75934, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_sw_roaming_guard', 0),
(@CGUID+507, 30740, 571, 0, 0, 1, 1, 0, 1, 5152.66, 2945.74, 413.495, 2.29086, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_sw_roaming_guard', 0),
(@CGUID+508, 30740, 571, 0, 0, 1, 1, 0, 1, 5153.57, 2925.49, 413.495, 3.90878, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_sw_roaming_guard', 0),
(@CGUID+509, 30740, 571, 0, 0, 1, 1, 0, 1, 5186.37, 2910.25, 410.175, 5.46779, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_sw_roaming_guard', 0),

(@CGUID+510, 30739, 571, 0, 0, 1, 1, 0, 1, 5261.11, 2857.32, 409.191, 4.95806, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_sw_roaming_guard', 0),
(@CGUID+511, 30739, 571, 0, 0, 1, 1, 0, 1, 5242.9, 2882.67, 409.192, 5.80786, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_sw_roaming_guard', 0),
(@CGUID+512, 30739, 571, 0, 0, 1, 1, 0, 1, 5213.54, 2895.66, 409.192, 0.146713, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_sw_roaming_guard', 0),
(@CGUID+513, 30739, 571, 0, 0, 1, 1, 0, 1, 5182.78, 2875.56, 409.192, 0.578682, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_sw_roaming_guard', 0),
(@CGUID+514, 30739, 571, 0, 0, 1, 1, 0, 1, 5179.43, 2852.55, 409.198, 3.46895, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_sw_roaming_guard', 0),
(@CGUID+515, 30739, 571, 0, 0, 1, 1, 0, 1, 5158.75, 2938.87, 439.846, 2.67571, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_sw_roaming_guard', 0),
(@CGUID+516, 30739, 571, 0, 0, 1, 1, 0, 1, 5172.62, 2925.42, 413.495, 5.47565, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_sw_roaming_guard', 0),
(@CGUID+517, 30739, 571, 0, 0, 1, 1, 0, 1, 5173.56, 2944.99, 413.495, 0.75934, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_sw_roaming_guard', 0),
(@CGUID+518, 30739, 571, 0, 0, 1, 1, 0, 1, 5152.66, 2945.74, 413.495, 2.29086, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_sw_roaming_guard', 0),
(@CGUID+519, 30739, 571, 0, 0, 1, 1, 0, 1, 5153.57, 2925.49, 413.495, 3.90878, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_sw_roaming_guard', 0),
(@CGUID+520, 30739, 571, 0, 0, 1, 1, 0, 1, 5186.37, 2910.25, 410.175, 5.46779, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_sw_roaming_guard', 0),

--  keep tower SE guards
(@CGUID+521, 30740, 571, 0, 0, 1, 1, 0, 1, 5272.89, 2838.61, 409.192, 3.02913, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_se_standing_guard', 0),
(@CGUID+522, 30740, 571, 0, 0, 1, 1, 0, 1, 5248.29, 2759.13, 409.192, 6.28068, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_se_standing_guard', 0),
(@CGUID+523, 30740, 571, 0, 0, 1, 1, 0, 1, 5226.18, 2759.94, 409.19, 2.98985, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_se_standing_guard', 0),
(@CGUID+524, 30740, 571, 0, 0, 1, 1, 0, 1, 5164.16, 2769.13, 439.844, 1.41121, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_se_standing_guard', 0),
(@CGUID+525, 30740, 571, 0, 0, 1, 1, 0, 1, 5185.53, 2747.88, 439.844, 0.0760173, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_se_standing_guard', 0),
(@CGUID+526, 30740, 571, 0, 0, 1, 1, 0, 1, 5197.19, 2767.43, 409.19, 0.672916, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_se_standing_guard', 0),
(@CGUID+527, 30740, 571, 0, 0, 1, 1, 0, 1, 5184.27, 2781.66, 409.189, 0.688617, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_se_standing_guard', 0),
(@CGUID+528, 30740, 571, 0, 0, 1, 1, 0, 1, 5176.03, 2809.96, 409.19, 4.71379, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_se_standing_guard', 0),
(@CGUID+529, 30740, 571, 0, 0, 1, 1, 0, 1, 5175.29, 2831.98, 409.191, 1.37585, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_se_standing_guard', 0),
(@CGUID+530, 30740, 571, 0, 0, 1, 1, 0, 1, 5180.55, 2734.52, 413.492, 5.71123, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_se_standing_guard', 0),
(@CGUID+531, 30740, 571, 0, 0, 1, 1, 0, 1, 5177.12, 2731.46, 413.494, 5.47954, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_se_standing_guard', 0),
(@CGUID+532, 30740, 571, 0, 0, 1, 1, 0, 1, 5146.41, 2734.35, 413.493, 3.73988, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_se_standing_guard', 0),
(@CGUID+533, 30740, 571, 0, 0, 1, 1, 0, 1, 5150.83, 2729.16, 413.493, 4.00692, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_se_standing_guard', 0),
(@CGUID+534, 30740, 571, 0, 0, 1, 1, 0, 1, 5147.24, 2760.96, 413.493, 2.53823, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_se_standing_guard', 0),
(@CGUID+535, 30740, 571, 0, 0, 1, 1, 0, 1, 5151.32, 2766.82, 413.493, 1.92955, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_se_standing_guard', 0),
(@CGUID+536, 30740, 571, 0, 0, 1, 1, 0, 1, 5195.16, 2735.65, 409.189, 4.28182, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_se_standing_guard', 0),
(@CGUID+537, 30740, 571, 0, 0, 1, 1, 0, 1, 5199.4, 2736.21, 409.189, 5.44812, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_se_standing_guard', 0),
(@CGUID+538, 30740, 571, 0, 0, 1, 1, 0, 1, 5151.96, 2779.9, 409.304, 3.1901, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_se_standing_guard', 0),
(@CGUID+539, 30740, 571, 0, 0, 1, 1, 0, 1, 5153.44, 2784.61, 409.284, 2.31831, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_se_standing_guard', 0),
(@CGUID+540, 30740, 571, 0, 0, 1, 1, 0, 1, 5155.4, 2831.47, 409.124, 3.00553, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_se_standing_guard', 0),

(@CGUID+541, 30740, 571, 0, 0, 1, 1, 0, 1, 5165.69, 2720.24, 413.492, 6.12048, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_se_roaming_guard', 0),
(@CGUID+542, 30740, 571, 0, 0, 1, 1, 0, 1, 5149.15, 2762.42, 413.493, 3.49648, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_se_roaming_guard', 0),
(@CGUID+543, 30740, 571, 0, 0, 1, 1, 0, 1, 5157.62, 2742.18, 439.844, 1.17169, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_se_roaming_guard', 0),
(@CGUID+544, 30740, 571, 0, 0, 1, 1, 0, 1, 5185.43, 2832.45, 409.192, 3.0158, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_se_roaming_guard', 0),
(@CGUID+545, 30740, 571, 0, 0, 1, 1, 0, 1, 5256.58, 2824.97, 409.193, 1.41987, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_se_roaming_guard', 0),
(@CGUID+546, 30740, 571, 0, 0, 1, 1, 0, 1, 5264.74, 2785.98, 409.192, 1.39552, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_se_roaming_guard', 0),
(@CGUID+547, 30740, 571, 0, 0, 1, 1, 0, 1, 5226.08, 2763.18, 409.193, 0.0564179, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_se_roaming_guard', 0),
(@CGUID+548, 30740, 571, 0, 0, 1, 1, 0, 1, 5190.1, 2773.66, 409.189, 0.89286, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_se_roaming_guard', 0),

(@CGUID+549, 30739, 571, 0, 0, 1, 1, 0, 1, 5272.89, 2838.61, 409.192, 3.02913, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_se_standing_guard', 0),
(@CGUID+550, 30739, 571, 0, 0, 1, 1, 0, 1, 5248.29, 2759.13, 409.192, 6.28068, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_se_standing_guard', 0),
(@CGUID+551, 30739, 571, 0, 0, 1, 1, 0, 1, 5226.18, 2759.94, 409.19, 2.98985, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_se_standing_guard', 0),
(@CGUID+552, 30739, 571, 0, 0, 1, 1, 0, 1, 5164.16, 2769.13, 439.844, 1.41121, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_se_standing_guard', 0),
(@CGUID+553, 30739, 571, 0, 0, 1, 1, 0, 1, 5185.53, 2747.88, 439.844, 0.0760173, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_se_standing_guard', 0),
(@CGUID+554, 30739, 571, 0, 0, 1, 1, 0, 1, 5197.19, 2767.43, 409.19, 0.672916, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_se_standing_guard', 0),
(@CGUID+555, 30739, 571, 0, 0, 1, 1, 0, 1, 5184.27, 2781.66, 409.189, 0.688617, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_se_standing_guard', 0),
(@CGUID+556, 30739, 571, 0, 0, 1, 1, 0, 1, 5176.03, 2809.96, 409.19, 4.71379, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_se_standing_guard', 0),
(@CGUID+557, 30739, 571, 0, 0, 1, 1, 0, 1, 5175.29, 2831.98, 409.191, 1.37585, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_se_standing_guard', 0),
(@CGUID+558, 30739, 571, 0, 0, 1, 1, 0, 1, 5180.55, 2734.52, 413.492, 5.71123, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_se_standing_guard', 0),
(@CGUID+559, 30739, 571, 0, 0, 1, 1, 0, 1, 5177.12, 2731.46, 413.494, 5.47954, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_se_standing_guard', 0),
(@CGUID+560, 30739, 571, 0, 0, 1, 1, 0, 1, 5146.41, 2734.35, 413.493, 3.73988, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_se_standing_guard', 0),
(@CGUID+561, 30739, 571, 0, 0, 1, 1, 0, 1, 5150.83, 2729.16, 413.493, 4.00692, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_se_standing_guard', 0),
(@CGUID+562, 30739, 571, 0, 0, 1, 1, 0, 1, 5147.24, 2760.96, 413.493, 2.53823, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_se_standing_guard', 0),
(@CGUID+563, 30739, 571, 0, 0, 1, 1, 0, 1, 5151.32, 2766.82, 413.493, 1.92955, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_se_standing_guard', 0),
(@CGUID+564, 30739, 571, 0, 0, 1, 1, 0, 1, 5195.16, 2735.65, 409.189, 4.28182, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_se_standing_guard', 0),
(@CGUID+565, 30739, 571, 0, 0, 1, 1, 0, 1, 5199.4, 2736.21, 409.189, 5.44812, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_se_standing_guard', 0),
(@CGUID+566, 30739, 571, 0, 0, 1, 1, 0, 1, 5151.96, 2779.9, 409.304, 3.1901, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_se_standing_guard', 0),
(@CGUID+567, 30739, 571, 0, 0, 1, 1, 0, 1, 5153.44, 2784.61, 409.284, 2.31831, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_se_standing_guard', 0),
(@CGUID+568, 30739, 571, 0, 0, 1, 1, 0, 1, 5155.4, 2831.47, 409.124, 3.00553, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_se_standing_guard', 0),

(@CGUID+569, 30739, 571, 0, 0, 1, 1, 0, 1, 5165.69, 2720.24, 413.492, 6.12048, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_se_roaming_guard', 0),
(@CGUID+570, 30739, 571, 0, 0, 1, 1, 0, 1, 5149.15, 2762.42, 413.493, 3.49648, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_se_roaming_guard', 0),
(@CGUID+571, 30739, 571, 0, 0, 1, 1, 0, 1, 5157.62, 2742.18, 439.844, 1.17169, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_se_roaming_guard', 0),
(@CGUID+572, 30739, 571, 0, 0, 1, 1, 0, 1, 5185.43, 2832.45, 409.192, 3.0158, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_se_roaming_guard', 0),
(@CGUID+573, 30739, 571, 0, 0, 1, 1, 0, 1, 5256.58, 2824.97, 409.193, 1.41987, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_se_roaming_guard', 0),
(@CGUID+574, 30739, 571, 0, 0, 1, 1, 0, 1, 5264.74, 2785.98, 409.192, 1.39552, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_se_roaming_guard', 0),
(@CGUID+575, 30739, 571, 0, 0, 1, 1, 0, 1, 5226.08, 2763.18, 409.193, 0.0564179, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_se_roaming_guard', 0),
(@CGUID+576, 30739, 571, 0, 0, 1, 1, 0, 1, 5190.1, 2773.66, 409.189, 0.89286, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_se_roaming_guard', 0),

--  keep tower NE guards
(@CGUID+577, 30740, 571, 0, 0, 1, 1, 0, 1, 5279.8, 2653.35, 439.755, 1.67747, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_ne_standing_guard', 0),
(@CGUID+578, 30740, 571, 0, 0, 1, 1, 0, 1, 5300.43, 2630.43, 439.755, 0.000641346, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_ne_standing_guard', 0),
(@CGUID+579, 30740, 571, 0, 0, 1, 1, 0, 1, 5365.11, 2709.76, 409.165, 3.2954, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_ne_standing_guard', 0),
(@CGUID+580, 30740, 571, 0, 0, 1, 1, 0, 1, 5365.34, 2726.86, 409.125, 2.93805, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_ne_standing_guard', 0),
(@CGUID+581, 30740, 571, 0, 0, 1, 1, 0, 1, 5344.64, 2765.16, 409.189, 4.6031, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_ne_standing_guard', 0),
(@CGUID+582, 30740, 571, 0, 0, 1, 1, 0, 1, 5340.23, 2764.88, 409.192, 4.62273, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_ne_standing_guard', 0),
(@CGUID+583, 30740, 571, 0, 0, 1, 1, 0, 1, 5291.8, 2715.99, 409.19, 1.54788, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_ne_standing_guard', 0),
(@CGUID+584, 30740, 571, 0, 0, 1, 1, 0, 1, 5291.9, 2693.15, 409.189, 4.36353, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_ne_standing_guard', 0),
(@CGUID+585, 30740, 571, 0, 0, 1, 1, 0, 1, 5299.26, 2664.33, 409.164, 0.746772, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_ne_standing_guard', 0),
(@CGUID+586, 30740, 571, 0, 0, 1, 1, 0, 1, 5312.5, 2651.1, 409.099, 0.731064, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_ne_standing_guard', 0),
(@CGUID+587, 30740, 571, 0, 0, 1, 1, 0, 1, 5340.76, 2642.93, 409.099, 3.26005, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_ne_standing_guard', 0),
(@CGUID+588, 30740, 571, 0, 0, 1, 1, 0, 1, 5360.26, 2643.14, 409.099, 6.14638, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_ne_standing_guard', 0),
(@CGUID+589, 30740, 571, 0, 0, 1, 1, 0, 1, 5382.24, 2643.33, 409.099, 3.11475, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_ne_standing_guard', 0),
(@CGUID+590, 30740, 571, 0, 0, 1, 1, 0, 1, 5400.61, 2642.32, 410.611, 6.00109, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_ne_standing_guard', 0),
(@CGUID+591, 30740, 571, 0, 0, 1, 1, 0, 1, 5291.78, 2616.34, 413.404, 4.4083, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_ne_standing_guard', 0),
(@CGUID+592, 30740, 571, 0, 0, 1, 1, 0, 1, 5295.54, 2618.73, 413.403, 5.39004, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_ne_standing_guard', 0),
(@CGUID+593, 30740, 571, 0, 0, 1, 1, 0, 1, 5262.04, 2618.53, 413.403, 3.57186, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_ne_standing_guard', 0),
(@CGUID+594, 30740, 571, 0, 0, 1, 1, 0, 1, 5265.19, 2614.87, 413.403, 4.10986, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_ne_standing_guard', 0),
(@CGUID+595, 30740, 571, 0, 0, 1, 1, 0, 1, 5262.98, 2645.29, 413.404, 2.75113, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_ne_standing_guard', 0),
(@CGUID+596, 30740, 571, 0, 0, 1, 1, 0, 1, 5265.52, 2648.18, 413.404, 2.04427, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_ne_standing_guard', 0),
(@CGUID+597, 30740, 571, 0, 0, 1, 1, 0, 1, 5309.03, 2618.35, 409.097, 4.05096, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_ne_standing_guard', 0),
(@CGUID+598, 30740, 571, 0, 0, 1, 1, 0, 1, 5314.88, 2619.83, 409.064, 5.11516, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_ne_standing_guard', 0),
(@CGUID+599, 30740, 571, 0, 0, 1, 1, 0, 1, 5266.86, 2664.84, 409.099, 3.50511, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_ne_standing_guard', 0),
(@CGUID+600, 30740, 571, 0, 0, 1, 1, 0, 1, 5269.54, 2669.11, 409.099, 2.61761, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_ne_standing_guard', 0),

(@CGUID+601, 30740, 571, 0, 0, 1, 1, 0, 1, 5272.64, 2605.12, 413.404, 0.27552, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_ne_roaming_guard', 0),
(@CGUID+602, 30740, 571, 0, 0, 1, 1, 0, 1, 5253.57, 2631.79, 413.404, 0.035979, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_ne_roaming_guard', 0),
(@CGUID+603, 30740, 571, 0, 0, 1, 1, 0, 1, 5272.54, 2627.28, 439.755, 3.08333, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_ne_roaming_guard', 0),
(@CGUID+604, 30740, 571, 0, 0, 1, 1, 0, 1, 5361.84, 2753.64, 409.167, 5.88327, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_ne_roaming_guard', 0),
(@CGUID+605, 30740, 571, 0, 0, 1, 1, 0, 1, 5316.56, 2750.8, 409.193, 2.38431, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_ne_roaming_guard', 0),
(@CGUID+606, 30740, 571, 0, 0, 1, 1, 0, 1, 5299.26, 2711.12, 409.193, 3.92762, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_ne_roaming_guard', 0),
(@CGUID+607, 30740, 571, 0, 0, 1, 1, 0, 1, 5361.84, 2718.56, 409.166, 3.154, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_ne_roaming_guard', 0),
(@CGUID+608, 30740, 571, 0, 0, 1, 1, 0, 1, 5304.56, 2657.22, 409.099, 0.829224, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_ne_roaming_guard', 0),
(@CGUID+609, 30740, 571, 0, 0, 1, 1, 0, 1, 5350.65, 2647.5, 409.1, 1.32403, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_ne_roaming_guard', 0),

(@CGUID+610, 30739, 571, 0, 0, 1, 1, 0, 1, 5279.8, 2653.35, 439.755, 1.67747, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_ne_standing_guard', 0),
(@CGUID+611, 30739, 571, 0, 0, 1, 1, 0, 1, 5300.43, 2630.43, 439.755, 0.000641346, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_ne_standing_guard', 0),
(@CGUID+612, 30739, 571, 0, 0, 1, 1, 0, 1, 5365.11, 2709.76, 409.165, 3.2954, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_ne_standing_guard', 0),
(@CGUID+613, 30739, 571, 0, 0, 1, 1, 0, 1, 5365.34, 2726.86, 409.125, 2.93805, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_ne_standing_guard', 0),
(@CGUID+614, 30739, 571, 0, 0, 1, 1, 0, 1, 5344.64, 2765.16, 409.189, 4.6031, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_ne_standing_guard', 0),
(@CGUID+615, 30739, 571, 0, 0, 1, 1, 0, 1, 5340.23, 2764.88, 409.192, 4.62273, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_ne_standing_guard', 0),
(@CGUID+616, 30739, 571, 0, 0, 1, 1, 0, 1, 5291.8, 2715.99, 409.19, 1.54788, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_ne_standing_guard', 0),
(@CGUID+617, 30739, 571, 0, 0, 1, 1, 0, 1, 5291.9, 2693.15, 409.189, 4.36353, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_ne_standing_guard', 0),
(@CGUID+618, 30739, 571, 0, 0, 1, 1, 0, 1, 5299.26, 2664.33, 409.164, 0.746772, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_ne_standing_guard', 0),
(@CGUID+619, 30739, 571, 0, 0, 1, 1, 0, 1, 5312.5, 2651.1, 409.099, 0.731064, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_ne_standing_guard', 0),
(@CGUID+620, 30739, 571, 0, 0, 1, 1, 0, 1, 5340.76, 2642.93, 409.099, 3.26005, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_ne_standing_guard', 0),
(@CGUID+621, 30739, 571, 0, 0, 1, 1, 0, 1, 5360.26, 2643.14, 409.099, 6.14638, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_ne_standing_guard', 0),
(@CGUID+622, 30739, 571, 0, 0, 1, 1, 0, 1, 5382.24, 2643.33, 409.099, 3.11475, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_ne_standing_guard', 0),
(@CGUID+623, 30739, 571, 0, 0, 1, 1, 0, 1, 5400.61, 2642.32, 410.611, 6.00109, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_ne_standing_guard', 0),
(@CGUID+624, 30739, 571, 0, 0, 1, 1, 0, 1, 5291.78, 2616.34, 413.404, 4.4083, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_ne_standing_guard', 0),
(@CGUID+625, 30739, 571, 0, 0, 1, 1, 0, 1, 5295.54, 2618.73, 413.403, 5.39004, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_ne_standing_guard', 0),
(@CGUID+626, 30739, 571, 0, 0, 1, 1, 0, 1, 5262.04, 2618.53, 413.403, 3.57186, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_ne_standing_guard', 0),
(@CGUID+627, 30739, 571, 0, 0, 1, 1, 0, 1, 5265.19, 2614.87, 413.403, 4.10986, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_ne_standing_guard', 0),
(@CGUID+628, 30739, 571, 0, 0, 1, 1, 0, 1, 5262.98, 2645.29, 413.404, 2.75113, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_ne_standing_guard', 0),
(@CGUID+629, 30739, 571, 0, 0, 1, 1, 0, 1, 5265.52, 2648.18, 413.404, 2.04427, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_ne_standing_guard', 0),
(@CGUID+630, 30739, 571, 0, 0, 1, 1, 0, 1, 5309.03, 2618.35, 409.097, 4.05096, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_ne_standing_guard', 0),
(@CGUID+631, 30739, 571, 0, 0, 1, 1, 0, 1, 5314.88, 2619.83, 409.064, 5.11516, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_ne_standing_guard', 0),
(@CGUID+632, 30739, 571, 0, 0, 1, 1, 0, 1, 5266.86, 2664.84, 409.099, 3.50511, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_ne_standing_guard', 0),
(@CGUID+633, 30739, 571, 0, 0, 1, 1, 0, 1, 5269.54, 2669.11, 409.099, 2.61761, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_ne_standing_guard', 0),

(@CGUID+634, 30739, 571, 0, 0, 1, 1, 0, 1, 5272.64, 2605.12, 413.404, 0.27552, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_ne_roaming_guard', 0),
(@CGUID+635, 30739, 571, 0, 0, 1, 1, 0, 1, 5253.57, 2631.79, 413.404, 0.035979, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_ne_roaming_guard', 0),
(@CGUID+636, 30739, 571, 0, 0, 1, 1, 0, 1, 5272.54, 2627.28, 439.755, 3.08333, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_ne_roaming_guard', 0),
(@CGUID+637, 30739, 571, 0, 0, 1, 1, 0, 1, 5361.84, 2753.64, 409.167, 5.88327, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_ne_roaming_guard', 0),
(@CGUID+638, 30739, 571, 0, 0, 1, 1, 0, 1, 5316.56, 2750.8, 409.193, 2.38431, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_ne_roaming_guard', 0),
(@CGUID+639, 30739, 571, 0, 0, 1, 1, 0, 1, 5299.26, 2711.12, 409.193, 3.92762, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_ne_roaming_guard', 0),
(@CGUID+640, 30739, 571, 0, 0, 1, 1, 0, 1, 5361.84, 2718.56, 409.166, 3.154, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_ne_roaming_guard', 0),
(@CGUID+641, 30739, 571, 0, 0, 1, 1, 0, 1, 5304.56, 2657.22, 409.099, 0.829224, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_ne_roaming_guard', 0),
(@CGUID+642, 30739, 571, 0, 0, 1, 1, 0, 1, 5350.65, 2647.5, 409.1, 1.32403, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_ne_roaming_guard', 0),

--  keep vault
(@CGUID+643, 30740, 571, 0, 0, 1, 1, 0, 1, 5373.16, 2784.56, 409.354, 5.77728, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_vault_standing_guard', 0),
(@CGUID+644, 30740, 571, 0, 0, 1, 1, 0, 1, 5352.36, 2783.33, 409.178, 3.02445, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_vault_standing_guard', 0),
(@CGUID+645, 30740, 571, 0, 0, 1, 1, 0, 1, 5344.37, 2777.48, 409.178, 1.44188, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_vault_standing_guard', 0),
(@CGUID+646, 30740, 571, 0, 0, 1, 1, 0, 1, 5340.79, 2777.34, 409.187, 1.4458, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_vault_standing_guard', 0),
(@CGUID+647, 30740, 571, 0, 0, 1, 1, 0, 1, 5332.61, 2783.51, 409.193, 0.0320937, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_vault_standing_guard', 0),
(@CGUID+648, 30740, 571, 0, 0, 1, 1, 0, 1, 5311.14, 2783.39, 409.192, 3.09908, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_vault_standing_guard', 0),
(@CGUID+649, 30740, 571, 0, 0, 1, 1, 0, 1, 5291.35, 2809.3, 409.192, 4.66595, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_vault_standing_guard', 0),
(@CGUID+650, 30740, 571, 0, 0, 1, 1, 0, 1, 5291.62, 2830.94, 409.192, 1.60682, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_vault_standing_guard', 0),
(@CGUID+651, 30740, 571, 0, 0, 1, 1, 0, 1, 5285.08, 2838.98, 409.192, 6.27994, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_vault_standing_guard', 0),
(@CGUID+652, 30740, 571, 0, 0, 1, 1, 0, 1, 5285.48, 2842.98, 409.192, 6.27994, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_vault_standing_guard', 0),
(@CGUID+653, 30740, 571, 0, 0, 1, 1, 0, 1, 5291.55, 2851.37, 409.192, 4.92121, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_vault_standing_guard', 0),
(@CGUID+654, 30740, 571, 0, 0, 1, 1, 0, 1, 5290.89, 2872.67, 409.191, 1.49295, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_vault_standing_guard', 0),
(@CGUID+655, 30740, 571, 0, 0, 1, 1, 0, 1, 5374.96, 2896.78, 409.24, 6.16214, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_vault_standing_guard', 0),
(@CGUID+656, 30740, 571, 0, 0, 1, 1, 0, 1, 5353.44, 2896.85, 409.24, 3.16585, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_vault_standing_guard', 0),
(@CGUID+657, 30740, 571, 0, 0, 1, 1, 0, 1, 5311.18, 2897.29, 409.192, 3.08731, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_vault_standing_guard', 0),
(@CGUID+658, 30740, 571, 0, 0, 1, 1, 0, 1, 5332.93, 2896.48, 409.192, 6.0679, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_vault_standing_guard', 0),
(@CGUID+659, 30740, 571, 0, 0, 1, 1, 0, 1, 5347.14, 2902.28, 409.192, 4.90157, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_vault_standing_guard', 0),
(@CGUID+660, 30740, 571, 0, 0, 1, 1, 0, 1, 5340.25, 2902.55, 409.192, 4.61883, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_vault_standing_guard', 0),
(@CGUID+661, 30740, 571, 0, 0, 1, 1, 0, 1, 5369.03, 2856.05, 409.24, 3.13835, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_vault_standing_guard', 0),
(@CGUID+662, 30740, 571, 0, 0, 1, 1, 0, 1, 5369.26, 2827.09, 409.24, 3.16977, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_vault_standing_guard', 0),
(@CGUID+663, 30740, 571, 0, 0, 1, 1, 0, 1, 5386.11, 2853.83, 418.676, 3.01662, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_vault_standing_guard', 0),
(@CGUID+664, 30740, 571, 0, 0, 1, 1, 0, 1, 5386.51, 2828.08, 419.474, 3.06374, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_vault_standing_guard', 0),

(@CGUID+665, 30740, 571, 0, 0, 1, 1, 0, 1, 5353.45, 2891.14, 409.238, 3.05035, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_vault_roaming_guard', 0),
(@CGUID+666, 30740, 571, 0, 0, 1, 1, 0, 1, 5316.25, 2888.96, 409.191, 0.136526, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_vault_roaming_guard', 0),
(@CGUID+667, 30740, 571, 0, 0, 1, 1, 0, 1, 5289.84, 2862.15, 414.895, 0.395707, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_vault_roaming_guard', 0),
(@CGUID+668, 30740, 571, 0, 0, 1, 1, 0, 1, 5290, 2820.9, 414.965, 0.136526, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_vault_roaming_guard', 0),
(@CGUID+669, 30740, 571, 0, 0, 1, 1, 0, 1, 5350.92, 2783.79, 409.18, 2.71264, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_vault_roaming_guard', 0),
(@CGUID+670, 30740, 571, 0, 0, 1, 1, 0, 1, 5321.48, 2791.61, 409.195, 1.44815, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_vault_roaming_guard', 0),
(@CGUID+671, 30740, 571, 0, 0, 1, 1, 0, 1, 5321.09, 2826.74, 409.239, 4.54733, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_vault_roaming_guard', 0),
(@CGUID+672, 30740, 571, 0, 0, 1, 1, 0, 1, 5326.23, 2852.23, 409.285, 3.06764, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_vault_roaming_guard', 0),
(@CGUID+673, 30740, 571, 0, 0, 1, 1, 0, 1, 5367.56, 2849.17, 409.239, 3.07157, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_vault_roaming_guard', 0),
(@CGUID+674, 30740, 571, 0, 0, 1, 1, 0, 1, 5366.56, 2836.68, 409.239, 3.06764, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_vault_roaming_guard', 0),
(@CGUID+675, 30740, 571, 0, 0, 1, 1, 0, 1, 5385.61, 2835.27, 418.675, 3.14225, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_vault_roaming_guard', 0),
(@CGUID+676, 30740, 571, 0, 0, 1, 1, 0, 1, 5384.71, 2846.15, 418.251, 3.22472, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_vault_roaming_guard', 0),

(@CGUID+677, 30739, 571, 0, 0, 1, 1, 0, 1, 5373.16, 2784.56, 409.354, 5.77728, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_vault_standing_guard', 0),
(@CGUID+678, 30739, 571, 0, 0, 1, 1, 0, 1, 5352.36, 2783.33, 409.178, 3.02445, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_vault_standing_guard', 0),
(@CGUID+679, 30739, 571, 0, 0, 1, 1, 0, 1, 5344.37, 2777.48, 409.178, 1.44188, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_vault_standing_guard', 0),
(@CGUID+680, 30739, 571, 0, 0, 1, 1, 0, 1, 5340.79, 2777.34, 409.187, 1.4458, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_vault_standing_guard', 0),
(@CGUID+681, 30739, 571, 0, 0, 1, 1, 0, 1, 5332.61, 2783.51, 409.193, 0.0320937, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_vault_standing_guard', 0),
(@CGUID+682, 30739, 571, 0, 0, 1, 1, 0, 1, 5311.14, 2783.39, 409.192, 3.09908, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_vault_standing_guard', 0),
(@CGUID+683, 30739, 571, 0, 0, 1, 1, 0, 1, 5291.35, 2809.3, 409.192, 4.66595, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_vault_standing_guard', 0),
(@CGUID+684, 30739, 571, 0, 0, 1, 1, 0, 1, 5291.62, 2830.94, 409.192, 1.60682, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_vault_standing_guard', 0),
(@CGUID+685, 30739, 571, 0, 0, 1, 1, 0, 1, 5285.08, 2838.98, 409.192, 6.27994, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_vault_standing_guard', 0),
(@CGUID+686, 30739, 571, 0, 0, 1, 1, 0, 1, 5285.48, 2842.98, 409.192, 6.27994, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_vault_standing_guard', 0),
(@CGUID+687, 30739, 571, 0, 0, 1, 1, 0, 1, 5291.55, 2851.37, 409.192, 4.92121, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_vault_standing_guard', 0),
(@CGUID+688, 30739, 571, 0, 0, 1, 1, 0, 1, 5290.89, 2872.67, 409.191, 1.49295, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_vault_standing_guard', 0),
(@CGUID+689, 30739, 571, 0, 0, 1, 1, 0, 1, 5374.96, 2896.78, 409.24, 6.16214, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_vault_standing_guard', 0),
(@CGUID+690, 30739, 571, 0, 0, 1, 1, 0, 1, 5353.44, 2896.85, 409.24, 3.16585, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_vault_standing_guard', 0),
(@CGUID+691, 30739, 571, 0, 0, 1, 1, 0, 1, 5311.18, 2897.29, 409.192, 3.08731, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_vault_standing_guard', 0),
(@CGUID+692, 30739, 571, 0, 0, 1, 1, 0, 1, 5332.93, 2896.48, 409.192, 6.0679, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_vault_standing_guard', 0),
(@CGUID+693, 30739, 571, 0, 0, 1, 1, 0, 1, 5347.14, 2902.28, 409.192, 4.90157, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_vault_standing_guard', 0),
(@CGUID+694, 30739, 571, 0, 0, 1, 1, 0, 1, 5340.25, 2902.55, 409.192, 4.61883, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_vault_standing_guard', 0),
(@CGUID+695, 30739, 571, 0, 0, 1, 1, 0, 1, 5369.03, 2856.05, 409.24, 3.13835, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_vault_standing_guard', 0),
(@CGUID+696, 30739, 571, 0, 0, 1, 1, 0, 1, 5369.26, 2827.09, 409.24, 3.16977, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_vault_standing_guard', 0),
(@CGUID+697, 30739, 571, 0, 0, 1, 1, 0, 1, 5386.11, 2853.83, 418.676, 3.01662, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_vault_standing_guard', 0),
(@CGUID+698, 30739, 571, 0, 0, 1, 1, 0, 1, 5386.51, 2828.08, 419.474, 3.06374, 300, 0, 0, 11001, 0, 0, 0, 0, 0, 'wg_vault_standing_guard', 0),

(@CGUID+699, 30739, 571, 0, 0, 1, 1, 0, 1, 5353.45, 2891.14, 409.238, 3.05035, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_vault_roaming_guard', 0),
(@CGUID+700, 30739, 571, 0, 0, 1, 1, 0, 1, 5316.25, 2888.96, 409.191, 0.136526, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_vault_roaming_guard', 0),
(@CGUID+701, 30739, 571, 0, 0, 1, 1, 0, 1, 5289.84, 2862.15, 414.895, 0.395707, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_vault_roaming_guard', 0),
(@CGUID+702, 30739, 571, 0, 0, 1, 1, 0, 1, 5290, 2820.9, 414.965, 0.136526, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_vault_roaming_guard', 0),
(@CGUID+703, 30739, 571, 0, 0, 1, 1, 0, 1, 5350.92, 2783.79, 409.18, 2.71264, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_vault_roaming_guard', 0),
(@CGUID+704, 30739, 571, 0, 0, 1, 1, 0, 1, 5321.48, 2791.61, 409.195, 1.44815, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_vault_roaming_guard', 0),
(@CGUID+705, 30739, 571, 0, 0, 1, 1, 0, 1, 5321.09, 2826.74, 409.239, 4.54733, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_vault_roaming_guard', 0),
(@CGUID+706, 30739, 571, 0, 0, 1, 1, 0, 1, 5326.23, 2852.23, 409.285, 3.06764, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_vault_roaming_guard', 0),
(@CGUID+707, 30739, 571, 0, 0, 1, 1, 0, 1, 5367.56, 2849.17, 409.239, 3.07157, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_vault_roaming_guard', 0),
(@CGUID+708, 30739, 571, 0, 0, 1, 1, 0, 1, 5366.56, 2836.68, 409.239, 3.06764, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_vault_roaming_guard', 0),
(@CGUID+709, 30739, 571, 0, 0, 1, 1, 0, 1, 5385.61, 2835.27, 418.675, 3.14225, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_vault_roaming_guard', 0),
(@CGUID+710, 30739, 571, 0, 0, 1, 1, 0, 1, 5384.71, 2846.15, 418.251, 3.22472, 300, 30, 0, 11001, 0, 1, 0, 0, 0, 'wg_vault_roaming_guard', 0),

(@CGUID+711, 30400, 571, 0, 0, 1, 1, 0, 0, 5390.05, 2974.65, 415.141, 1.43343, 300, 0, 0, 6986, 0, 0, 0, 0, 0, 'wg_ke_workshop_mechanic', 0),
(@CGUID+712, 30400, 571, 0, 0, 1, 1, 0, 0, 5388.26, 2707.6, 414.969, 1.58265, 300, 0, 0, 6986, 0, 0, 0, 0, 0, 'wg_kw_workshop_mechanic', 0),
(@CGUID+713, 30499, 571, 0, 0, 1, 1, 0, 0, 5390.05, 2974.65, 415.141, 1.43343, 300, 0, 0, 6986, 0, 0, 0, 0, 0, 'wg_ke_workshop_mechanic', 0),
(@CGUID+714, 30499, 571, 0, 0, 1, 1, 0, 0, 5388.26, 2707.6, 414.969, 1.58265, 300, 0, 0, 6986, 0, 0, 0, 0, 0, 'wg_kw_workshop_mechanic', 0);

UPDATE `creature` SET `ScriptName` = '' WHERE `ScriptName` = 'npc_wg_give_promotion_credit';
UPDATE `spell_area` SET `autocast` = 0 WHERE `spell` = 56618;
UPDATE `spell_area` SET `autocast` = 0 WHERE `spell` = 56617;

DELETE FROM `gameobject_addon` WHERE `guid` =17789;
DELETE FROM `gameobject_addon` WHERE `guid` =74739;
DELETE FROM `gameobject_addon` WHERE `guid` =17787;
DELETE FROM `gameobject_addon` WHERE `guid` =17786;
DELETE FROM `gameobject_addon` WHERE `guid` =74737;
DELETE FROM `gameobject_addon` WHERE `guid` =74735;
DELETE FROM `gameobject_addon` WHERE `guid` =74733;
DELETE FROM `gameobject_addon` WHERE `guid` =74731;
DELETE FROM `gameobject_addon` WHERE `guid` =74729;
DELETE FROM `gameobject_addon` WHERE `guid` =75982;
DELETE FROM `gameobject_addon` WHERE `guid` =75981;
DELETE FROM `gameobject_addon` WHERE `guid` =71414;
DELETE FROM `gameobject_addon` WHERE `guid` =75980;
DELETE FROM `gameobject_addon` WHERE `guid` =75979;
DELETE FROM `gameobject_addon` WHERE `guid` =71413;
DELETE FROM `gameobject_addon` WHERE `guid` =71412;
DELETE FROM `gameobject_addon` WHERE `guid` =75978;
DELETE FROM `gameobject_addon` WHERE `guid` =75977;
DELETE FROM `gameobject_addon` WHERE `guid` =75974;
DELETE FROM `gameobject_addon` WHERE `guid` =75973;
DELETE FROM `gameobject_addon` WHERE `guid` =75972;
DELETE FROM `gameobject_addon` WHERE `guid` =75971;
DELETE FROM `gameobject_addon` WHERE `guid` =75970;
DELETE FROM `gameobject_addon` WHERE `guid` =75969;
DELETE FROM `gameobject_addon` WHERE `guid` =75968;
DELETE FROM `gameobject_addon` WHERE `guid` =71411;
DELETE FROM `gameobject_addon` WHERE `guid` =75967;
DELETE FROM `gameobject_addon` WHERE `guid` =71410;
DELETE FROM `gameobject_addon` WHERE `guid` =75966;
DELETE FROM `gameobject_addon` WHERE `guid` =75965;
DELETE FROM `gameobject_addon` WHERE `guid` =71409;
DELETE FROM `gameobject_addon` WHERE `guid` =71408;
DELETE FROM `gameobject_addon` WHERE `guid` =75964;
DELETE FROM `gameobject_addon` WHERE `guid` =71407;
DELETE FROM `gameobject_addon` WHERE `guid` =75963;
DELETE FROM `gameobject_addon` WHERE `guid` =71406;
DELETE FROM `gameobject_addon` WHERE `guid` =75962;
DELETE FROM `gameobject_addon` WHERE `guid` =75961;
DELETE FROM `gameobject_addon` WHERE `guid` =71403;
DELETE FROM `gameobject_addon` WHERE `guid` =75960;
DELETE FROM `gameobject_addon` WHERE `guid` =75959;
DELETE FROM `gameobject_addon` WHERE `guid` =75958;
DELETE FROM `gameobject_addon` WHERE `guid` =75957;
DELETE FROM `gameobject_addon` WHERE `guid` =75956;
DELETE FROM `gameobject_addon` WHERE `guid` =75955;
DELETE FROM `gameobject_addon` WHERE `guid` =75954;
DELETE FROM `gameobject_addon` WHERE `guid` =75953;
DELETE FROM `gameobject_addon` WHERE `guid` =75952;
DELETE FROM `gameobject_addon` WHERE `guid` =75951;
DELETE FROM `gameobject_addon` WHERE `guid` =75950;
DELETE FROM `gameobject_addon` WHERE `guid` =75949;
DELETE FROM `gameobject_addon` WHERE `guid` =75948;
DELETE FROM `gameobject_addon` WHERE `guid` =75947;
DELETE FROM `gameobject_addon` WHERE `guid` =75946;
DELETE FROM `gameobject_addon` WHERE `guid` =75945;
DELETE FROM `gameobject_addon` WHERE `guid` =75944;
DELETE FROM `gameobject_addon` WHERE `guid` =75943;
DELETE FROM `gameobject_addon` WHERE `guid` =75942;
DELETE FROM `gameobject_addon` WHERE `guid` =75941;
DELETE FROM `gameobject_addon` WHERE `guid` =75940;
DELETE FROM `gameobject_addon` WHERE `guid` =75939;
DELETE FROM `gameobject_addon` WHERE `guid` =74727;
DELETE FROM `gameobject_addon` WHERE `guid` =74725;
DELETE FROM `gameobject_addon` WHERE `guid` =74723;
DELETE FROM `gameobject_addon` WHERE `guid` =74721;
DELETE FROM `gameobject_addon` WHERE `guid` =74719;
DELETE FROM `gameobject_addon` WHERE `guid` =74717;
DELETE FROM `gameobject_addon` WHERE `guid` =74715;
DELETE FROM `gameobject_addon` WHERE `guid` =74713;
DELETE FROM `gameobject_addon` WHERE `guid` =74711;
DELETE FROM `gameobject_addon` WHERE `guid` =76014;
DELETE FROM `gameobject_addon` WHERE `guid` =74709;
DELETE FROM `gameobject_addon` WHERE `guid` =74707;
DELETE FROM `gameobject_addon` WHERE `guid` =74705;
DELETE FROM `gameobject_addon` WHERE `guid` =74703;
DELETE FROM `gameobject_addon` WHERE `guid` =74701;
DELETE FROM `gameobject_addon` WHERE `guid` =74700;
DELETE FROM `gameobject_addon` WHERE `guid` =74699;
DELETE FROM `gameobject_addon` WHERE `guid` =74697;
DELETE FROM `gameobject_addon` WHERE `guid` =74695;
DELETE FROM `gameobject_addon` WHERE `guid` =74693;
DELETE FROM `gameobject_addon` WHERE `guid` =74691;
DELETE FROM `gameobject_addon` WHERE `guid` =74689;
DELETE FROM `gameobject_addon` WHERE `guid` =74687;
DELETE FROM `gameobject_addon` WHERE `guid` =74685;
DELETE FROM `gameobject_addon` WHERE `guid` =76053;
DELETE FROM `gameobject_addon` WHERE `guid` =76054;
DELETE FROM `gameobject_addon` WHERE `guid` =17790;
DELETE FROM `gameobject_addon` WHERE `guid` =17791;
DELETE FROM `gameobject_addon` WHERE `guid` =71385;
DELETE FROM `gameobject_addon` WHERE `guid` =71386;
DELETE FROM `gameobject_addon` WHERE `guid` =71387;
DELETE FROM `gameobject_addon` WHERE `guid` =71388;
DELETE FROM `gameobject_addon` WHERE `guid` =71415;
DELETE FROM `gameobject_addon` WHERE `guid` =71416;
DELETE FROM `gameobject_addon` WHERE `guid` =71417;
DELETE FROM `gameobject_addon` WHERE `guid` =71418;
DELETE FROM `gameobject_addon` WHERE `guid` =71419;
DELETE FROM `gameobject_addon` WHERE `guid` =71420;
DELETE FROM `gameobject_addon` WHERE `guid` =71421;
DELETE FROM `gameobject_addon` WHERE `guid` =71422;
DELETE FROM `gameobject_addon` WHERE `guid` =71423;
DELETE FROM `gameobject_addon` WHERE `guid` =71424;
DELETE FROM `gameobject_addon` WHERE `guid` =71425;
DELETE FROM `gameobject_addon` WHERE `guid` =71434;
DELETE FROM `gameobject_addon` WHERE `guid` =71435;
DELETE FROM `gameobject_addon` WHERE `guid` =71436;
DELETE FROM `gameobject_addon` WHERE `guid` =71437;
DELETE FROM `gameobject_addon` WHERE `guid` =71438;
DELETE FROM `gameobject_addon` WHERE `guid` =71439;
DELETE FROM `gameobject_addon` WHERE `guid` =71440;
DELETE FROM `gameobject_addon` WHERE `guid` =71441;
DELETE FROM `gameobject_addon` WHERE `guid` =71442;
DELETE FROM `gameobject_addon` WHERE `guid` =71443;
DELETE FROM `gameobject_addon` WHERE `guid` =71444;
DELETE FROM `gameobject_addon` WHERE `guid` =74741;
DELETE FROM `gameobject_addon` WHERE `guid` =74743;
DELETE FROM `gameobject_addon` WHERE `guid` =74745;
DELETE FROM `gameobject_addon` WHERE `guid` =74747;
DELETE FROM `gameobject_addon` WHERE `guid` =74749;
DELETE FROM `gameobject_addon` WHERE `guid` =74751;
DELETE FROM `gameobject_addon` WHERE `guid` =74753;
DELETE FROM `gameobject_addon` WHERE `guid` =74755;
DELETE FROM `gameobject_addon` WHERE `guid` =74757;
DELETE FROM `gameobject_addon` WHERE `guid` =74759;
DELETE FROM `gameobject_addon` WHERE `guid` =74761;
DELETE FROM `gameobject_addon` WHERE `guid` =74763;
DELETE FROM `gameobject_addon` WHERE `guid` =74765;
DELETE FROM `gameobject_addon` WHERE `guid` =74767;
DELETE FROM `gameobject_addon` WHERE `guid` =74769;
DELETE FROM `gameobject_addon` WHERE `guid` =74771;
DELETE FROM `gameobject_addon` WHERE `guid` =75166;
DELETE FROM `gameobject_addon` WHERE `guid` =75167;
DELETE FROM `gameobject_addon` WHERE `guid` =75168;
DELETE FROM `gameobject_addon` WHERE `guid` =75169;
DELETE FROM `gameobject_addon` WHERE `guid` =75170;
DELETE FROM `gameobject_addon` WHERE `guid` =75171;
DELETE FROM `gameobject_addon` WHERE `guid` =75172;
DELETE FROM `gameobject_addon` WHERE `guid` =75173;
DELETE FROM `gameobject_addon` WHERE `guid` =75174;
DELETE FROM `gameobject_addon` WHERE `guid` =75175;
DELETE FROM `gameobject_addon` WHERE `guid` =75176;
DELETE FROM `gameobject_addon` WHERE `guid` =75177;
DELETE FROM `gameobject_addon` WHERE `guid` =75178;
DELETE FROM `gameobject_addon` WHERE `guid` =75179;
DELETE FROM `gameobject_addon` WHERE `guid` =75180;
DELETE FROM `gameobject_addon` WHERE `guid` =75181;
DELETE FROM `gameobject_addon` WHERE `guid` =75182;
DELETE FROM `gameobject_addon` WHERE `guid` =75183;
DELETE FROM `gameobject_addon` WHERE `guid` =75184;
DELETE FROM `gameobject_addon` WHERE `guid` =75185;
DELETE FROM `gameobject_addon` WHERE `guid` =75186;
DELETE FROM `gameobject_addon` WHERE `guid` =75187;
DELETE FROM `gameobject_addon` WHERE `guid` =75188;
DELETE FROM `gameobject_addon` WHERE `guid` =75189;
DELETE FROM `gameobject_addon` WHERE `guid` =75190;
DELETE FROM `gameobject_addon` WHERE `guid` =75191;
DELETE FROM `gameobject_addon` WHERE `guid` =75192;
DELETE FROM `gameobject_addon` WHERE `guid` =75193;
DELETE FROM `gameobject_addon` WHERE `guid` =75194;

UPDATE `creature_template` SET `ScriptName`='' WHERE (`entry`='30400');
UPDATE `creature_template` SET `ScriptName`='' WHERE (`entry`='30499');