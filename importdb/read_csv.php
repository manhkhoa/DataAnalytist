<?php

# include parseCSV class.
require_once('parsecsv/parsecsv.lib.php');
die('Dubugging');

// connect to mongodb
$m = new MongoClient();
// select a database
$db = $m->adverse_drug_reactions;
$enf_report = $db->enf_report;

for($i = 0; $i <= 127; $i++){
	$path = 'csv/csv/Enforcement_Report ('.$i.').csv';
	if(file_exists($path)){
		
		// # create new parseCSV object.
		$csv = new parseCSV();
		$csv->auto($path);
		$rows = $csv->data;

		foreach ($rows as $row) {
			$data_arr = array(
				"product_type" => $row["Product Type"],
				"event_id" => $row['Event ID'],
				"status" => $row['Status'],	
				"recalling_firm" => $row['Recalling Firm'],			
				"city" => $row['City'],			
				"state" => $row['State'],			
				"country" => $row['Country'],			
				"voluntary_mandated" => $row['Voluntary/Mandated'],			
				"initial_firm_notification" => $row['Initial Firm Notification of Consignee or Public'],			
				"distribution_pattern" => $row['Distribution Pattern'],			
				"recall_number" => $row['Recall Number'],			
				"classification" => $row['Classification'],			
				"product_description" => $row['Product Description'],			
				"code_info" => $row['Code Info'],			
				"code_info2" => $row['Code Info (Continued)'],			
				"product_quantity" => $row[' Product Quantity'],			
				"reason_for_recall" => $row['Reason for Recall'],			
				"recall_initiation_date" => substr($row['Recall Initiation Date'], -4),			
				"report_date" => $row['Report Date'],		
			);		

			try {
				$enf_report->insert($data_arr); // insert data in to reaction collection
				ob_flush();
			} catch (Exception $e){
				print_r($row);
			}
		}

		print('Imported '.$path.' successful!');
		unlink($path);
	}
}

	
?>