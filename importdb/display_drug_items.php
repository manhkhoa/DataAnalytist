<?php

// connect to mongodb
$m = new MongoClient();
// select a database
$db = $m->adverse_drug_reactions;
$drug_info = $db->drug_info;

$result_search_drugs = $drug_info->find(); // Run find method


foreach ($result_search_drugs as $key => $value) {
	$view_search = '';

	foreach ($value['drug_info'] as $val) {
		$setid = $val['setid'];
		$title = $val['title'];
		$img = $val['img'];
		$pkg = $val['pkg'];

		$view_search .= '
			<div class="content_search_drug">
				<div class="drug_image">
					<img src="'.$img.'" width="300">
				</div>
			<div class="drug_content">
				<div class="title">
					<a href="http://dailymed.nlm.nih.gov/dailymed/drugInfo.cfm?setid='.$setid.'">'.$title.'</a>
				</div>
				<div class="packaging">
					<label>NDC Code(s):'.$pkg.'
					</label>
				</div>
			</div>
			</div><div class="clearfix"></div><hr/>
		';	

	}

	// print($view_search);

}