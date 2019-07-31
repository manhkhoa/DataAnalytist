<?php
die('Dubugging');
// connect to mongodb
$m = new MongoClient();
// select a database
$db = $m->adverse_drug_reactions;
$enf_report = $db->enf_report;

for($i = 0; $i <= 52; $i++){
	$path = 'json/json/enforcement ('.$i.').json';
	$file_content = file_get_contents($path);
	$data = json_decode($file_content, true);
	$data_arr = $data['results'];

	if(file_exists($path)){
		foreach ($data_arr as $key => $value) {			

			$record = array(
				"product_type" => $value['product_type'],
				"event_id" => $value['event_id'],
				"status" => $value['status'],
				"recalling_firm" => $value['recalling_firm'],		
				"city" => $value['city'],		
				"state" => $value['state'],		
				"country" => $value['country'],			
				"voluntary_mandated" => $value['voluntary_mandated'],			
				"initial_firm_notification" => $value['initial_firm_notification'],		
				"distribution_pattern" => $value['distribution_pattern'],		
				"recall_number" => '',		
				"classification" => $value['classification'],		
				"product_description" => $value['product_description'],	
				"code_info" => $value['code_info'],		
				"code_info2" => '',			
				"product_quantity" => $value['product_quantity'],			
				"reason_for_recall" => $value['reason_for_recall'],			
				"recall_initiation_date" => substr($value['recall_initiation_date'], 0, 4),		
				"report_date" => $value['report_date'],		
			);		

			try {
				$enf_report->insert($record); // insert data in to reaction collection
				ob_flush();
			} catch (Exception $e){
				print_r($value);
			}
		}

		print('Imported '.$path.' successful!<br>');
		unlink($path);
	}
}

?>