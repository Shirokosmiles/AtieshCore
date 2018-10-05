-- SPELL L5 Arcane Charge (41360)
DELETE FROM spell_script_names WHERE spell_id=41360;
INSERT INTO spell_script_names VALUES(41360, 'spell_gen_100pct_count_pct_from_max_hp');

-- SPELL Disgruntled (40851)
DELETE FROM conditions WHERE SourceTypeOrReferenceId=13 AND SourceEntry=40851;
INSERT INTO conditions VALUES(13, 7, 40851, 0, 0, 31, 0, 3, 22963, 0, 0, 0, 0, '', 'Target Bonechewer Worker');
DELETE FROM spell_script_names WHERE spell_id=40851;
INSERT INTO spell_script_names VALUES(40851, 'spell_gen_select_target_count_7_1');

-- SPELL Rapid Shot (41172)
DELETE FROM spell_script_names WHERE spell_id=41172;
INSERT INTO spell_script_names VALUES(41172, 'spell_gen_select_target_count_24_1');