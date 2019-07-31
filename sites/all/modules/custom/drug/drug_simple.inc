<?php

/**
 * Function Build Form Create Reports
 */

function drug_simple_search_form($form,&$form_state){
	$form = array();

	//add js and css
	drupal_add_js(drupal_get_path('module', 'drug').'/js/main.js',array('weight' => 1));
	drupal_add_js(drupal_get_path('module', 'drug').'/js/jquery-1.7.2.js',array('weight' => 0));
	drupal_add_css(drupal_get_path('module', 'drug').'/css/main.css');

	$form['type_search'] = array(
		'#type' => 'radios',
			'#options' => array(
				'0' => t('Drug Infomation'),
				'1' => t('Adverse Reactions'),
			),
			'#default_value' => '0',
			'#attributes' => array(
				'class' => array(''),
			),
			'#prefix' => '<div id="simple-search-content" class="row-fluid"><div class="parent-row">',
			'#suffix' => '</div><div class="clearfix"></div>',
	);

	$form['drug_name'] = array(
		'#title' => t('Drug Name:'),
		'#type' => 'textfield',
		'#attributes' => array(
			'class' => array(''),
		),
		'#prefix' => '<div id="content-search"><div class="parent-row">',
	);

	$form['ndc_code'] = array(
		'#title' => t('NDC Code:'),
		'#type' => 'textfield',
		'#attributes' => array(
			'class' => array(''),
		),
		'#suffix' => '</div><div class="clearfix"></div>',
	);

	$form['ingredients'] = array(
		'#title' => t('Ingredients:'),
		'#type' => 'textfield',
		'#attributes' => array(
			'class' => array(''),
		),
		'#prefix' => '<div class="parent-row">',
	);

	$form['drug_class'] = array(
		'#title' => t('Drug Class:'),
		'#type' => 'textfield',
		'#attributes' => array(
			'class' => array(''),
		),
		'#suffix' => '</div></div><div class="clearfix"></div>',
	);

	$form['action-simple'] = array(
		'#type' => 'submit',
		'#value' => t('Search'),
		'#attributes' => array(
			'class' => array(),
		),
		'#prefix' => '<div id="button-simple" class="parent-row">',
		'#suffix' => '</div></div>',
		'#submit' => array('drug_simple_search_form_submit'),
	);

	if(isset($form_state['results'])){
		if($form_state['results'] == 'Not Found'){
			$form['result_simple'] = array(
				'#markup' => '
					<span class="title">Results:</span>
				'.$form_state['results'],
				'#prefix' => '<div id="form-result-background" class="row-fluid">',
				'#suffix' => '</div>',
			);
		}else{
			$form['result_simple'] = array(
				'#markup' => '
					<span class="title">Results:</span>
					<div id="form-result-simple" class="row-fluid">
				'.$form_state['results'].'</div>',
				'#prefix' => '<div id="form-result-background" class="row-fluid">',
				'#suffix' => '</div>',
			);
		}
	}else{
		$form['result_simple'] = array(
			'#markup' => '
				<span class="title">Results:</span>
			',
			'#prefix' => '<div id="form-result-background" class="row-fluid">',
			'#suffix' => '</div>',
		);
	}

	return $form;
}

function drug_simple_search_form_submit($form, &$form_state){
	$view_search = '';
	if($_POST['drug_name'] != ''){
		$drug_name = str_replace(' ','+',$_POST['drug_name']);
		$string = file_get_contents("http://dailymed.nlm.nih.gov/dailymed/services/v2/spls.json?drug_name=".$drug_name."&pagesize=5&page=1");
		$json_spls = json_decode($string, true);
		if($json_spls["metadata"]["total_elements"] == 0){
			$view_search .= 'Not Found';
		}else{
			$view_search .= '
				<div id="name_title">
					SEARCH RESULTS FOR: '.$_POST['drug_name'].' ('.$json_spls["metadata"]["total_elements"].' results)
				</div> 
			';
			foreach ($json_spls['data'] as $data_spls) {
				$setid = $data_spls['setid'];
				$title = $data_spls['title'];
				$image = get_image($setid);
				$packaging = get_packaging($setid);
				$total_packaging = '';
				foreach ($packaging['data']['products'] as $parent) {
					foreach ($parent['packaging'] as $child) {
						$total_packaging.= $child['ndc'].',';
					}
				}

				$view_search .= '
					<div class="content_search_drug">
					<div class="drug_image">
						<img src="'.$image["data"]["media"][0]["url"].'">
					</div>
					<div class="drug_content">
						<div class="title">
							<a href="http://dailymed.nlm.nih.gov/dailymed/drugInfo.cfm?setid='.$setid.'">'.$title.'</a>
						</div>
						<div class="packaging">
							<label>NDC Code(s):'.substr($total_packaging,0,-1).'</label>
						</div>
					</div>
					</div><div class="clearfix"></div><hr/>
				';	
			}
		}		
	}else{
		$view_search .= 'Not Found';
	}

	$form_state['results'] = $view_search;
  	$form_state['rebuild'] = TRUE;
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



