<?php

// connect to mongodb
$m = new MongoClient();

$db = $connection->adverse_drug_reactions;

$list = $db->listCollections();
foreach ($list as $collection) {
    echo "$collection </br>";       
}




die;

?>