<?php

# include parseCSV class.
require_once('parsecsv/parsecsv.lib.php');

$path = 'DRUG12Q4-000.csv';
$file_name = 'DRUG12Q4-000.csv';
$file_name_tmp = strtoupper(substr($file_name, 0, 4));
$time_tmp = strtoupper(substr($file_name, 4, 4));

// connect to mongodb
$m = new MongoClient();
// select a database
$db = $m->adverse_drug_reactions;
$drug = $db->drugs;
$demo = $db->demographics;
$react = $db->reactions;

// # create new parseCSV object.
$csv = new parseCSV();
$csv->auto($path);
$rows = $csv->data;

if($file_name_tmp == 'DRUG'){ // Drug
	foreach ($rows as $row) {

		$drug_arr = array(
			"primaryid" => $row["primaryid"],
			"quarter" => $time_tmp,
			"caseid" => $row['caseid'],
			"drug_seq" => $row['drug_seq'],
			"role_cod" => $row['role_cod'],
			"drugname" => $row['drugname'],
			"val_vbm" => $row['val_vbm'],
			"route" => $row['route'],
			"dose_vbm" => $row['dose_vbm'],
			"cum_dose_chr" => $row['cum_dose_chr'],
			"cum_dose_unit" => $row['cum_dose_unit'],
			"dechal" => $row['dechal'],
			"rechal" => $row['rechal'],
			"lot_num" => $row['lot_nbr'],
			"exp_dt" => $row['exp_dt'],
			"nda_num" => $row['nda_num'],
			"dose_amt" => $row['dose_amt'],
			"dose_unit" => $row['dose_unit'],
			"dose_form" => $row['dose_form'],
			"dose_freq" => $row['dose_freq'],				
		);		

		try {				
			$drug->insert($drug_arr); // insert data into drug collections
			unset($row);
			unset($drug_arr);
			
			ob_flush(); // clear cache
		} catch (Exception $e){
			print_r($row); // print out error data
		}
	}

	print('Imported '.$file_name.' successful!');
	// unlink($path);
} else if($file_name_tmp == 'DEMO'){ // Demographics
	foreach ($rows as $row) {
		$demo_arr = array(
			"primaryid" => $row["primaryid"],
			"quarter" => $time_tmp,
			"caseid" => $row['caseid'],
			"caseversion" => $row['caseversion'],
			"i_f_code" => $row['i_f_code'],
			"event_dt" => $row['event_dt'],
			"mfr_dt" => $row['mfr_dt'],
			"init_fda_dt" => $row['init_fda_dt'],
			"fda_dt" => $row['fda_dt'],
			"rept_cod" => $row['rept_cod'],
			"mfr_num" => $row['mfr_num'],
			"mfr_sndr" => $row['mfr_sndr'],
			"age" => $row['age'],
			"age_cod" => $row['age_cod'],
			"gndr_cod" => $row['gndr_cod'],
			"e_sub" => $row['e_sub'],
			"wt" => $row['wt'],
			"wt_cod" => $row['wt_cod'],
			"rept_dt" => $row['rept_dt'],
			"to_mfr" => $row['to_mfr'],	
			"occp_cod" => $row['occp_cod'],				
			"reporter_country" => $row['reporter_country'],				
			"occr_country" => $row['occr_country'],
		);		

		try {
			$demo->insert($demo_arr); // insert data into demographics collection
			ob_flush();
		} catch (Exception $e){
			print_r($row);
		}
	}

	print('Imported '.$file_name.' successful!');
	unlink($path);
} else if($file_name_tmp == 'REAC'){ // Reactions
	foreach ($rows as $row) {
		$react_arr = array(
			"primaryid" => $row["primaryid"],
			"quarter" => $time_tmp,
			"caseid" => $row['caseid'],
			"pt" => $row['pt'],			
		);		

		try {
			$react->insert($react_arr); // insert data in to reaction collection
			ob_flush();
		} catch (Exception $e){
			print_r($row);
		}
	}

	print('Imported '.$file_name.' successful!');
	unlink($path);
} else { // Dont insert data
	print('Selected file has wrong name format. Please rename and try again.');
} //

	
?>