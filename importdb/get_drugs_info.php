<?php

// connect to mongodb
$m = new MongoClient();
// select a database
$db = $m->adverse_drug_reactions;
$counting_drugs = $db->count_drugs;
$drug_info = $db->drug_info;

$result_search_drugs = $counting_drugs->find(); // Run find method


foreach ($result_search_drugs as $key => $value) {	
	$drug_name = $value['_id'];
	$drug_name = str_replace(' ','+', $drug_name);

	$string = file_get_contents("http://dailymed.nlm.nih.gov/dailymed/services/v2/spls.json?drug_name=".$drug_name);
	$json_spls = json_decode($string, true);

	// $drug_name_tmp = str_replace('/', '-', $drug_name);
	// if($drug_name == ''){
	// 	$drug_name_tmp = 'Unknown';
	// } else {
	// 	$drug_name_tmp = $drug_name;
	// }

	// $path = 'data/drugs/drug_items/'.$drug_name_tmp.'.json';

	// $string = '['; // Start of string
	if($json_spls["metadata"]["total_elements"] != 0){

		// Store data in an array
		$drug_info_arr = array();

		foreach ($json_spls['data'] as $data_spls) {
			$setid = $data_spls['setid'];
			$title = $data_spls['title'];
			$image = get_image($setid);
			$packaging = get_packaging($setid);
			$total_packaging = '';

			if(isset($packaging['data']['products'])){
				foreach ($packaging['data']['products'] as $parent) {
					foreach ($parent['packaging'] as $child) {
						$total_packaging.= $child['ndc'].',';
					}
				}
			}

			// if(!file_exists('data/drugs/drug_items/'.$drug_name_tmp)) {
			// 	mkdir('data/drugs/drug_items/'.$drug_name_tmp);
			// }

			// copy($image["data"]["media"][0]["url"], 'data/drugs/drug_items/'.$drug_name_tmp.'/'.$image["data"]["media"][0]["name"]);

			// $string .= '{"setid": '.$setid.', "title": '.$title.', "img": '.$image["data"]["media"][0]["name"].', "pkg": '.substr($total_packaging,0,-1).'},';

			$drug_info_arr[] = array(
				"setid" => $setid,
				"title" => $title,
				"img" => $image["data"]["media"][0]["url"],
				"pkg" => substr($total_packaging,0,-1)
			);

		}

		$drug_arr = array(
			"drug_name" => $drug_name,
			"drug_info" => $drug_info_arr				
		);		

		try {				
			$drug_info->insert($drug_arr); // insert data into drug collections
			unset($value);
			unset($drug_arr);
			
			ob_flush(); // clear cache
		} catch (Exception $e){
			print_r($value); // print out error data
		}
	}


	// $string .= ']'; // End of string

	// file_put_contents($path, $string); // Write to json file
	// unset($json_spls);	
	// ob_flush(); // clear cache

	

}


function get_image($setid){
	$string_img = file_get_contents("http://dailymed.nlm.nih.gov/dailymed/services/v2/spls/".$setid."/media.json");
	$json_image = json_decode($string_img, true);
	return $json_image;
}

function get_packaging($setid){
	$string_packaging = file_get_contents("http://dailymed.nlm.nih.gov/dailymed/services/v2/spls/".$setid."/packaging.json");
	$json_packaging = json_decode($string_packaging, true);
	return $json_packaging;
}