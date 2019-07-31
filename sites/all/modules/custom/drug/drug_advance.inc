<?php

/**
 * Function Build Form Create Reports
 */

function drug_advance_search_form($form,&$form_state){
	$form = array();

	// Connect to Mongodb
	$m = new MongoClient();
	// Select a database
	$db = $m->adverse_drug_reactions;
	$reaction = $db->reactions;
	$demographics = $db->demographics;

	if(isset($form_state['primaryid']) && !empty($form_state['primaryid'])){

		$primaryid_arr_tmp = array(); // Store primaryid in string
		foreach ($form_state['primaryid'] as $key => $value) {
			$primaryid_arr_tmp[] = $value;
		}

		// All adverse event reports
		$where=array('pt'=>"Drug ineffective", 'primaryid' => array('$in' => $primaryid_arr_tmp));
		$where1=array('pt'=>"Nausea", 'primaryid' => array('$in' => $primaryid_arr_tmp));
		$where2=array('pt'=>"Death", 'primaryid' => array('$in' => $primaryid_arr_tmp));
		$where3=array('pt'=>"Fatigue", 'primaryid' => array('$in' => $primaryid_arr_tmp));
		$where4=array('pt'=>"Headache", 'primaryid' => array('$in' => $primaryid_arr_tmp));
		$where5=array('pt'=>"Dyspnoea", 'primaryid' => array('$in' => $primaryid_arr_tmp));
		$where6=array('pt'=>"Pain", 'primaryid' => array('$in' => $primaryid_arr_tmp));
		$where7=array('pt'=>"Vomiting", 'primaryid' => array('$in' => $primaryid_arr_tmp));
		$where8=array('pt'=>"Diarrhoea", 'primaryid' => array('$in' => $primaryid_arr_tmp));
		$where9=array('pt'=>"Dizziness", 'primaryid' => array('$in' => $primaryid_arr_tmp));


	} else {	

		// Condition
		$where=array('pt'=>"Drug ineffective");
		$where1=array('pt'=>"Nausea");
		$where2=array('pt'=>"Death");
		$where3=array('pt'=>"Fatigue");
		$where4=array('pt'=>"Headache");
		$where5=array('pt'=>"Dyspnoea");
		$where6=array('pt'=>"Pain");
		$where7=array('pt'=>"Vomiting");
		$where8=array('pt'=>"Diarrhoea");
		$where9=array('pt'=>"Dizziness");

	}

	$c_Drug_ine = $reaction->find($where)->count();
	$c_Nausea = $reaction->find($where1)->count();
	$c_Death = $reaction->find($where2)->count();
	$c_Headache = $reaction->find($where4)->count();
	$c_Dyspnoea = $reaction->find($where5)->count();
	$c_Dizziness = $reaction->find($where9)->count();
	$c_Pain = $reaction->find($where6)->count();
	$c_Vomiting = $reaction->find($where7)->count();
	$c_Diarrhoea = $reaction->find($where8)->count();
	$c_Fatigue = $reaction->find($where3)->count();

	$chart_mrk = '<input type="hidden" value="'.$c_Drug_ine.'" id="view_se_1">
	   <input type="hidden" value="'.$c_Nausea.'" id="view_se_2">
	   <input type="hidden" value="'.$c_Death.'" id="view_se_3">
	   <input type="hidden" value="'.$c_Fatigue.'" id="view_se_4">
       <input type="hidden" value="'.$c_Headache.'" id="view_se_5">
       <input type="hidden" value="'.$c_Dyspnoea.'" id="view_se_6">
       <input type="hidden" value="'.$c_Pain.'" id="view_se_7">
       <input type="hidden" value="'.$c_Vomiting.'" id="view_se_8">
       <input type="hidden" value="'.$c_Diarrhoea.'" id="view_se_9">
       <input type="hidden" value="'.$c_Dizziness.'" id="view_se_10">';

	// add js and css
	drupal_add_js(drupal_get_path('module', 'drug').'/js/d3.min.js',array('weight' => 0));
	drupal_add_js(drupal_get_path('module', 'drug').'/js/d3pie.min.js',array('weight' => 1));
	drupal_add_js(drupal_get_path('module', 'drug').'/js/jquery-1.7.2.js',array('weight' => 2));
	drupal_add_js(drupal_get_path('module', 'drug').'/js/main.js',array('weight' => 3));
	drupal_add_css(drupal_get_path('module', 'drug').'/css/main.css');

	$form['type_search'] = array(
		'#type' => 'radios',
			'#options' => array(
				'0' => t('Drug Infomation'),
				'1' => t('Adverse Reactions'),
			),
			'#default_value' => '1',
			'#attributes' => array(
				'class' => array(''),
			),
			'#prefix' => '<div id="adv-search-content" class="row-fluid"><div class="parent-row">',
			'#suffix' => '</div><div class="clearfix"></div>',
	);

	$form['reaction'] = array(
		'#title' => t('Reaction:'),
		'#type' => 'textfield',
		'#attributes' => array(
			'class' => array(''),
		),
		'#prefix' => '<div id="content-search"><div class="parent-row">',
	);

	$form['drug_name'] = array(
		'#title' => t('Drug Name:'),
		'#type' => 'textfield',
		'#attributes' => array(
			'class' => array(''),
		),
		'#suffix' => '</div>',
	);

	// $outcome = array(
	// 		'All' => 'All',
	// 		'DE' => t('Death'),
	// 		'LT' => t('Life-Threatening'),
	// 		'HO' => t('Hospitalization - Initial or Prolonged'),
	// 		'DS' => t('Disability'),
	// 		'CA' => t('Congenital Anomaly'),
	// 		'RI' => t('Required Intervention to Prevent Permanent Impairment/Damage'),
	// 		'OT' => t('Other Serious '),
	// 	);

	// $form['patient_out'] = array(
	// 	'#title' => t('Patient Outcome:'),
	// 	'#type' => 'select',
	// 	'#options' => $outcome,
	// 	'#attributes' => array(
	// 		'class' => array(''),
	// 	),
	// 	'#prefix' => '<div class="parent-row">',
	// );

	$form['dose_form'] = array(
		'#title' => t('Dosage Form:'),
		'#type' => 'textfield',
		'#prefix' => '<div class="parent-row">',
		'#suffix' => '</div>',
	);
	

	// $form['first_date'] = array(
	// 	'#type' => 'date_popup',
	// 	'#title' => t("From:"),
	// 	'#date_label_position' => 'within',
	// 	'#date_format' => 'm/d/Y',
	// 	'#date_year_range' => '-10:+0', 
	// 	'#size' => 50,
	// 	'#prefix' => '<div class="parent-row"><div class="from-date-wrap date-wrap">',
	// 	'#suffix' => '</div>',
	// );

	// $form['second_date'] = array(
	// 	'#type' => 'date_popup',
	// 	'#title' => t('To:'),
	// 	'#date_label_position' => 'within',
	// 	'#date_format' => 'm/d/Y',
	// 	'#size' => 50,
	// 	'#date_year_range' => '-10:+0',
	// 	'#suffix' => '</div></div>',
	// 	'#prefix' => '<div class="to-date-wrap date-wrap">',
	// );

	$form['end_title'] = array(
		'#markup' => '
			<span class="title">(Other ones will be added more)</span>
		',
		'#prefix' => '<div id="end-title-adv">',
		'#suffix' => '</div></div><div class="clearfix"></div>',
	);

	$form['action-adv'] = array(
		'#type' => 'submit',
		'#value' => t('Search'),
		'#attributes' => array(
			'class' => array(),
		),
		'#prefix' => '<div id="button-adv" class="row-fluid">',
		'#suffix' => '</div><div class="clearfix"></div>',
	);

	$form['chart_hidden'] = array(
		'#markup' => '<div class="chart-hidden-values">'.$chart_mrk.'</div>',
	);

	$form['chart'] = array(
		'#markup' => '
	<div id="table-chart" style="float: left;width: 100%;border: 1px solid #bbb;">
		<div id="radio-view-chart" style="float:left;width:28%;margin-top:35px;margin-left:11px;">
			<label>Statistic</label>
			<div class="wrap-radio-button">
			<input type="radio" name="reactions" value="" style="position:relative;top:2px;margin-top:6px;" checked>
			<span>All adverse event reports</span>
			</div>

			<div class="wrap-radio-button">
			<input type="radio" name="reactions" value="" style="position:relative;top:2px;margin-top:6px;">
			<span>Nonsteroidal anti-inflammatory drug class</span>
			</div>

			<div class="wrap-radio-button">
			<input type="radio" name="reactions" value="" style="position:relative;top:2px;margin-top:6px;">
			<span>Females, age 5 to 17</span>
			</div>

			<div class="wrap-radio-button">
			<input type="radio" name="reactions" value="" style="position:relative;top:2px;margin-top:6px;">
			<span>Females, age 55 to 90</span>
			</div>

			<div class="wrap-radio-button">
			<input type="radio" name="reactions" value="" style="position:relative;top:2px;margin-top:6px;">
			<span>Males</span>
			</div>

			<div class="wrap-radio-button">
			<input type="radio" name="reactions" value="" style="position:relative;top:2px;margin-top:6px;">
			<span>Males, age 5 to 17</span>
			</div>

			<div class="wrap-radio-button">
			<input type="radio" name="reactions" value="" style="position:relative;top:2px;margin-top:6px;">
			<span>Males, age 55 to 90</span>
			</div>

		</div>
		<div id="pieChart" style="float: left;"></div>
	</div>
	<script>
	var pie = new d3pie("pieChart", {
	"header": {
		"title": {
			"text": "All adverse event reports",
			"fontSize": 22,
			"font": "verdana"
		},
		"subtitle": {
			"color": "#999999",
			"fontSize": 10,
			"font": "verdana"
		},
		"titleSubtitlePadding": 12
	},
	"footer": {
		"color": "#999999",
		"fontSize": 11,
		"font": "open sans",
		"location": "bottom-center"
	},
	"size": {
		"canvasHeight": 400,
		"canvasWidth": 490,
		"pieInnerRadius": "20%",
		"pieOuterRadius": "97%"
	},
	"data": {
		"content": [
			{
				"label": "Drug Ineffective",
				"value": + $("#view_se_1").val(),
				"color": "#2484c1"
			},
			{
				"label": "Nausea",
				"value": + $("#view_se_2").val(),
				"color": "#0c6197"
			},
			{
				"label": "Death",
				"value": + $("#view_se_3").val(),
				"color": "#4daa4b"
			},
			{
				"label": "Fatigue",
				"value": + $("#view_se_4").val(),
				"color": "#90c469"
			},
			{
				"label": "Headache",
				"value": + $("#view_se_5").val(),
				"color": "#daca61"
			},
			{
				"label": "Dyspnoea",
				"value": + $("#view_se_6").val(),
				"color": "#e4a14b"
			},
			{
				"label": "Dizziness",
				"value": + $("#view_se_10").val(),
				"color": "#e98125"
			},
			{
				"label": "Pain",
				"value": + $("#view_se_7").val(),
				"color": "#cb2121"
			},
			{
				"label": "Vomiting",
				"value": + $("#view_se_8").val(),
				"color": "#830909"
			},
			{
				"label": "Diarrhoea",
				"value": + $("#view_se_9").val(),
				"color": "#923e99"
			}
		]
	},
	"labels": {
		"outer": {
			"pieDistance": 32
		},
		"inner": {
			"format": "value"
		},
		"mainLabel": {
			"font": "verdana"
		},
		"percentage": {
			"color": "#e1e1e1",
			"font": "verdana",
			"decimalPlaces": 0
		},
		"value": {
			"color": "#e1e1e1",
			"font": "verdana"
		},
		"lines": {
			"enabled": true,
			"color": "#cccccc"
		}
	},
	"effects": {
		"pullOutSegmentOnClick": {
			"effect": "linear",
			"speed": 400,
			"size": 8
		}
	}
    });
    </script>
		',
	);

	if(isset($form_state['results'])){
		if($form_state['results'] == 'Not Found'){
			$form['result_advance'] = array(
				'#markup' => '
					<h2>Results:</h2>
				'.$form_state['results'],
				'#prefix' => '<div id="form-result-background" class="row-fluid">',
				'#suffix' => '</div>',
			);
		}else{
			$form['result_advance'] = array(
				'#markup' => '
					<h2>Results</h2>
					<div id="form-result-simple" class="row-fluid">
				'.$form_state['results'].'</div>',
				'#prefix' => '<div id="form-result-background" class="row-fluid">',
				'#suffix' => '</div>',
			);
		}
	}else{
		$form['result_advance'] = array(
			'#markup' => '',
			'#prefix' => '<div id="form-result-background" class="row-fluid">',
			'#suffix' => '</div>',
		);
	}



	return $form;
}


/**
 * Search form
 */
function drug_advance_search_form_submit($form, &$form_state){
	$drugname = $_POST['drug_name'];
	$reaction_text = $_POST['reaction'];
	$dosage_form = $_POST['dose_form'];
	
	$primaryid_arr = array(); // Store primaryid

	// Connect to Mongodb
   	$m = new MongoClient();

	// Select a database
	$db = $m->adverse_drug_reactions;

	// Search		
	$searchQuery = array(
            '$and' => array(
                array(
                    'value.drugs.drugname' => new MongoRegex("/^$drugname/i"),
                    ),
                array(
                    'value.drugs.dosage_form' => new MongoRegex("/^$dosage_form/i"),
                    ),               
            	array(
                    'value.reactions.pt' => new MongoRegex("/^$reaction_text/i"),
                    ),
                )
            );

	$reduce_search = $db->joined->find($searchQuery)->limit(100);	

	// Get data from $results to display
	$header = array('PrimaryID', 'Drugs (DrugName(DosageForm))', 'Patient Gender', 'Manufacturer', 'Reactions');

	foreach ($reduce_search as $key => $value) {
		
		// Get id 
		$id = $value['_id'];
		$primaryid_arr[] = $id;

		// Get drugs name
		$drug_name_list = '';
		foreach ($value['value']['drugs'] as $drug_value) {			

			if($drug_value['dosage_form'] != ''){
				$drug_item =  $drug_value['drugname'].'<span class="dosage-form">('.ucfirst(strtolower($drug_value['dosage_form'])).')</span>';
			} else {
				$drug_item =  $drug_value['drugname'];
			}

			if($drug_name_list == ''){
				$drug_name_list = $drug_item;
			} else {
				$drug_name_list = $drug_name_list.', '.$drug_item;
			}
		}
		
		$gender = $value['value']['gender'];
		if($gender == "M"){
			$gender = "Male";
		} else {
			$gender = "Female";
		}

		$manu = $value['value']['manufacturer'];	


		$reactions_list = '';
		foreach ($value['value']['reactions'] as $react_value) {
			$react_item =  $react_value['pt'];
			
			if($reactions_list == ''){
				$reactions_list = $react_item;
			} else {
				$reactions_list = $reactions_list.', '.$react_item;
			}
		}

		$drug_name_list = str_ireplace($drugname, "<strong>".$drugname."</strong>", $drug_name_list);
		$drug_name_list = str_ireplace($dosage_form, "<strong>".$dosage_form."</strong>", $drug_name_list);		
		$reactions_list = str_ireplace($reaction_text, "<strong>".$reaction_text."</strong>", $reactions_list);

		$rows[] = array($id, $drug_name_list, $gender, $manu, $reactions_list);
	}

	if($reduce_search->count() == 0){
		$rows[] = 'Not Found';
	}
	
    $output = theme('table', array('header' => $header,
                  	         'rows' => $rows ));

	
	$form_state['results'] = $output;
	$form_state['primaryid'] = $primaryid_arr;
  	$form_state['rebuild'] = TRUE;
}

