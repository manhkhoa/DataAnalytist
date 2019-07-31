<?php
function get_drug_info($form,&$form_state){
	$form = array();
	$view_search = '';
	$drug_name = str_replace(' ','+',arg(1));

	// connect to mongodb
	$m = new MongoClient();
	// select a database
	$db = $m->adverse_drug_reactions;
	$drugs_info = $db->drugs_info;

	// $result_search_drugs = $drugs_info->find(array('drug_name' => $drug_name)); // Run find method
	// $count_result_search_drugs = $result_search_drugs->count();

	$string = file_get_contents('http://dailymed.nlm.nih.gov/dailymed/services/v2/spls.json?drug_name='.$drug_name);
	
	$json_drug = json_decode($string, true);
	$data = $json_drug['data'];

	foreach ($data as $key => $value) {
		$set_id = $value['setid'];
		$title = $value['title'];

		$result_search_drugs = $drugs_info->find(array('setId' => $set_id)); // Run find method
		foreach ($result_search_drugs as $document) {
			$rootId = $document['rootId'];
			$displayName = $document['displayName'];
			$version = $document['version'];
			$effectiveTime = $document['effectiveTime'];

			$view_search .= '
				<div class="content_search_drug">					
					<div class="drug_content">
						<div class="title">
							<a href="http://dailymed.nlm.nih.gov/dailymed/drugInfo.cfm?setid='.$set_id.'" target="_blank">'.$title.'</a>							
						</div>
						<div class="packaging">
							<div><label>Root ID:</label> '.$rootId.'</div>
							<div><label>Display Name:</label> '.$displayName.'</div>
							<div><label>Effective Time:</label> '.$effectiveTime.'</div>
							<div><label>Version:</label> '.$version.'</div>
						</div>
						<div class="down-load"> <span class="down-load-spl"><a href="http://dailymed.nlm.nih.gov/dailymed/getFile.cfm?setid='.$set_id.'&type=zip">Download</a></span>
						</div>
					</div>
				</div><div class="clearfix"></div><hr/>
			';	
		}
	}


	// Get drug Info via API
	if($view_search == ''){
		foreach ($data as $key => $value) {				
			if($key <= 10){
				$setid = $value['setid'];
				$title = $value['title'];

				$img = get_image($setid);
				$pkg = get_packaging($setid);

				$img_link = $img['data']['media'][0]['url'];
				$version = $img['data']['spl_version'];

				// Get product ndc
				$pkg_ndc = '';
				foreach ($pkg['data']['products'] as $p_value) {
					foreach ($p_value['packaging'] as $ndc) {
						if($pkg_ndc == ''){
							$pkg_ndc .= $ndc['ndc'];
						} else {
							$pkg_ndc .= ', '.$ndc['ndc'];
						}
					}
				}



				$view_search .= '
					<div class="content_search_drug">
						<div class="drug_image">
							<img src="'.$img_link.'" width="300">
						</div>
					<div class="drug_content">
						<div class="title">
							<a href="http://dailymed.nlm.nih.gov/dailymed/drugInfo.cfm?setid='.$setid.'">'.$title.'</a>
						</div>
						<div class="packaging">
							<div><label>NDC Code(s):</label> '.$pkg_ndc.'</div>					
							<div><label>Version:</label> '.$version.'</div>
						</div>
						
						<div class="down-load"> <span class="down-load-spl"><a href="http://dailymed.nlm.nih.gov/dailymed/getFile.cfm?setid='.$set_id.'&type=zip">Download</a></span>
						</div>
					</div>
					</div><div class="clearfix"></div><hr/>
				';	
			}

		}
	} 

	drupal_add_css(drupal_get_path('module', 'circle_chart').'/css/druginfo.css');

	if($view_search == ''){
		$view_search = 'Not Found';
	}

	$form['drug_results'] = array(
		'#markup' => $view_search,
	);

	return $form;
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