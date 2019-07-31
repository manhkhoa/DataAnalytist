<?php
function getDB(){
	// Connect to Mongodb
	$m = new MongoClient();
	// Select a database
	$db = $m->adverse_drug_reactions;
	return $db;
}
?>