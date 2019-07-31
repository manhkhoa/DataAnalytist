<?php
// connect to mongodb
$m = new MongoClient();
// select a database
$db = $m->adverse_drug_reactions;
$drug = $db->drugs;
$demo = $db->demographics;
$react = $db->reactions;

// Get Total new AE’s for the week
$today = date("Ymd"); 

print($today);