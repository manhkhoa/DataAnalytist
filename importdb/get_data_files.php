<?php

// connect to mongodb
$m = new MongoClient();
// select a database
$db = $m->adverse_drug_reactions;
$drug = $db->drugs;
$demo = $db->demographics;
$react = $db->reactions;




// Get data for Recalls timeline chart
$report_date = $db->enf_report;  
$report_count = $db->count_enf_rpt; // Need run map-reduce to create this collection
$path = 'data/recalls/journals_db.json';	// link to data file

if(file_exists($path)){
	unlink($path); // Delete old file
}

$results = $report_count->find(); 

$product_type_arr = array();
foreach ($results as $key => $value) {
	$product_type_arr[] = $value['_id']; 
}

// Get data with date
$data = array();
foreach ($product_type_arr as $key => $val) {
	// Search all reactions without null date
	$find_query = array(
        '$and' => array(
            array(
                'product_type' => $val,
                ),
            array(
                'recall_initiation_date' => array('$ne' => ''),
                ), 
            )
        );

	$result_search = $report_date->find($find_query); // Run find method
	foreach ($result_search as $r_key => $r_value) {
		$data[$val][] = (string)$r_value['recall_initiation_date']; // Store date in $data
	}
}	


// Re-structured data array
/* Example: [Drug ineffective] => Array
    (
        [date] => Array
            (
                [2014] => 2
                [2013] => 2
                [2006] => 1
            )

        [count] => 5
    )
*/

$new_data = array(); 
foreach ($data as $d_key => $d_val) {
	$count = count($d_val);
	$new_tmp_arr = array_count_values($d_val);

	$new_data[$d_key] = array('date' => $new_tmp_arr, 'count' => $count);
}



// Store json data in a string before push to file
/* [{"articles": [[1997, 1], [2006, 50], [2013, 26]], "total": 457, "name": "Society"}, 

{"articles": [[1999, 1], [2000, 1], [2012, 2]], "total": 44, "name": "Archives"}] */

$string = '['; // Start of string
$last_data_key = key( array_slice( $new_data, -1, 1, TRUE ) ); // Get last key

foreach ($new_data as $data_key => $data_val) {
	$string .= '{"articles": [';

	// Get last key of date
	$last_date_key = key( array_slice( $data_val['date'], -1, 1, TRUE ) );
	foreach ($data_val['date'] as $k => $val) {
		if($last_date_key == $k){
			$string .= '['.$k.', '.$val.']';
		} else {
			$string .= '['.$k.', '.$val.'],';
		}
	}

	if($last_data_key == $data_key){
		$string .= '],	"total": '.$data_val['count'].', "name": "'.$data_key.'"}';
	} else {
		$string .= '],	"total": '.$data_val['count'].', "name": "'.$data_key.'"},';			
	}
}

$string .= ']'; // End of string

file_put_contents($path, $string); // Write to json file
if(file_exists($path)){
	print('Recalls chart\'s data has created.<br>');
}





// Get data for Companies bubble chart
$counting_companies = $db->count_companies;
$com = $db->com;
/* Need run map-reduce to creat 2 above collections */

$path = 'data/companies/data.js';	// link to data file
if(file_exists($path)){
	unlink($path); // delete old file
}

// Sort companies
$sort_com_query = array(
    array(
        '$sort' => array(
            "value" => -1,
        ),
    ),
);

$results = $counting_companies->aggregate($sort_com_query);

$list_drugs_com = 'var nytg = nytg || {};nytg.budget_array_data = [';	

// Get total
$total = 0;
foreach ($results['result'] as $key => $value) {
	$total = $total + $value['value'];
}

foreach ($results['result'] as $key => $value) {
	$name_com = '';
	$change = $value['value']/$total;

	if($value['_id'] == ''){
		$name_com = 'Unknown';
	}else{
		$name_com = $value['_id'];
	}

	$x = rand(0,999);
	$y = rand(0,999);

	if($name_com != 'Unknown'){
		$find_num_drugs_query_str = array('value.company' => $name_com);
	} else {
		$find_num_drugs_query_str = array('value.company' => '');
	}

	$results_count_drugs = $com->find($find_num_drugs_query_str);

	$num_drugs = 0;
	foreach ($results_count_drugs as $drug_value) {
	
		if(is_array($drug_value['value']['drugs'])){
			foreach ($drug_value['value']['drugs'] as $val) {
				if(is_array($val)){
					foreach ($val as $v) {
						if(is_array($v)){
							foreach ($v as $v_drug) {
								$num_drugs += 1;
							}
						} else {
							$num_drugs += 1;
						}						
					}
				} else {
					$num_drugs += 1;
				}
				
			}
		} else {
			$num_drugs += 1;
		}
	}

	$num_drugs = makecomma($num_drugs);

	$list_drugs_com .= '{
		"name":"'.$name_com.'",
		"positions":{"department":{"x":'.$x.',"y":'.$y.'}},
	  	"id":'.$key.',
	  	"budget_2012":1,
	  	"change":'.$change.',
	  	"budget_2013":'.$value['value'].',
	  	"department": "'.$num_drugs.'"
	},';
}

$list_drugs_com .= '];nytg.category_list = [];nytg.category_data = [];';

file_put_contents($path, $list_drugs_com); // Write to json file
if(file_exists($path)){
	print('Companies chart\'s data has created.<br>');
}





// Get data for Drugs bubble chart
$counting_drugs = $db->count_drugs; // Need run map-reduce to creat this collection

$path = 'data/drugs/data.js';	// update data
if(file_exists($path)){
	unlink($path); // delete old file
}


// Get 500 popular drugs
$sort_drugs_query = array(
    array(
        '$sort' => array(
            "value" => -1,
        ),
    ),
    array(
    	'$limit' => 500 // only get first 500 drugs
    )
);

$results = $counting_drugs->aggregate($sort_drugs_query); // Run aggregate

// fetch data into js file

$data = 'var nytg1 = nytg1 || {};';

// Get category list
$list_manufacturers = 'nytg1.category_list = [];';

// Get category data
$list_category_data = 'nytg1.category_data = [];';

// Update coordinates
$list_drugs = 'nytg1.budget_array_data = [';	

$total_events = $demo->find()->count();

$id = 1;
$total_domain = 0;
foreach ($results['result'] as $key => $value) {		
	$name = $value['_id'];
	$count = $value['value'];
	$total_domain += $count;

	$x = rand(0,999);
	$y = rand(0,999);

	$change = $count/$total_events;

	$list_drugs .= '{
		"name":"'.$name.'",
	  	"positions":{"department":{"x":'.$x.',"y":'.$y.'}},
	  	"id":'.$id.',
	  	"budget_2013":'.$count.',
	  	"budget_2012": 1 ,
	  	"change": '.$change.',
	},';
	
	$id += 1;		
}

$scale_domain = $total_domain/5;
$list_drugs .= ']; var scale_domain = '.$scale_domain.'; ';

// Set data
$data .= $list_drugs.$list_manufacturers.$list_category_data;


file_put_contents($path, $data); // Write to json file
if(file_exists($path)){
	print('Drugs chart\'s data has created.<br>');
}





// Get data for all drug items - take time
$com = $db->com;
$com_drugs = $db->com_drugs;	

$search_com = $counting_companies->find(); // Run find method
foreach ($search_com as $com_val) {
	$company_name = $com_val['_id'];
	if($company_name != ''){
		$company_name_tmp = str_replace('/', '-', $company_name);
		$path = 'data/companies/drug_items/'.$company_name_tmp.'.js';	// link to data file
	} else {
		$path = 'data/companies/drug_items/Unknown.js';	// link to data file
	}

	if(file_exists($path)){
		unlink($path); // Delete old file
	}

	$find_query_drugs = array('_id' => $company_name);
	$result_search_drugs = $com_drugs->find($find_query_drugs); // Run find method

	$find_query = array('value.company' => $company_name);
	$result_search_com = $com->find($find_query); // Run find method
	$total = $result_search_com->count();

	$drugs_arr = array();

	$total_domain = 0;
	foreach ($result_search_drugs as $key => $value) {
		
		if(is_array($value['value']['drugs'])){
			foreach ($value['value']['drugs'] as $val) {
				if(is_array($val)){
					foreach ($val as $v) {
						if(is_array($v)){
							foreach ($v as $v_drug) {
								$drugs_arr[] = (string)$v_drug;
								$total_domain += 1;
							}
						} else {
							$drugs_arr[] = (string)$v;
							$total_domain += 1;
						}						
					}
				} else {
					$drugs_arr[] = (string)$val;
					$total_domain += 1;
				}
				
			}
		} else {
			$drugs_arr[] = (string)$value['value']['drugs'];
			$total_domain += 1;
		}
	}

	$new_drug_arr = array_count_values($drugs_arr);
	arsort($new_drug_arr);

	$new_drug_arr = array_slice($new_drug_arr, 0, 500);

	// fetch data into js file
	$scale_domain = $total_domain/5;
	$data = 'var scale_domain = '.$scale_domain.'; var nytg = nytg || {};';
	
	// Get category list
	$list_manufacturers = 'nytg.category_list = [];';

	// Get category data
	$list_category_data = 'nytg.category_data = [];';

	// Update coordinates
	$list_drugs = 'nytg.budget_array_data = [';		

	$id = 1;
	foreach ($new_drug_arr as $key => $value) {		
		$change = $value/$total;

		$x = rand(0,999);
		$y = rand(0,999);

		$list_drugs .= '{
			"name":"'.$key.'",
		  	"positions":{"department":{"x":'.$x.',"y":'.$y.'}},
		  	"id":'.$id.',
		  	"budget_2012":1,
		  	"change":'.$change.',
		  	"budget_2013":'.$value.',
		},';
		
		$id += 1;
		
	}

	$list_drugs .= '];';

	// Set data
	$data .= $list_drugs.$list_manufacturers.$list_category_data;

	file_put_contents($path, $data); // Write to json file
}














// Return number formar with comma
function makecomma($input)
{
    if(strlen($input)<=3)
    { return $input; }
    $length=substr($input,0,strlen($input)-3);
    $formatted_input = makecomma($length).",".substr($input,-3);
    return $formatted_input;
}