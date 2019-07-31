<?php

function get_pie_chart_all_pt($form,&$form_state){
	$form = array();
	
	$url = drupal_get_path('module','chart').'/connect-mongodb.php';
	include_once($url);
	$db = getDB();
	$reaction = $db->reactions;

	//Condition
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

	//Result
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

	print('<input type="hidden" value="'.$c_Drug_ine.'" id="view_se_1">
	   <input type="hidden" value="'.$c_Nausea.'" id="view_se_2">
	   <input type="hidden" value="'.$c_Death.'" id="view_se_3">
	   <input type="hidden" value="'.$c_Fatigue.'" id="view_se_4">
       <input type="hidden" value="'.$c_Headache.'" id="view_se_5">
       <input type="hidden" value="'.$c_Dyspnoea.'" id="view_se_6">
       <input type="hidden" value="'.$c_Pain.'" id="view_se_7">
       <input type="hidden" value="'.$c_Vomiting.'" id="view_se_8">
       <input type="hidden" value="'.$c_Diarrhoea.'" id="view_se_9">
       <input type="hidden" value="'.$c_Dizziness.'" id="view_se_10">');

	//add js and css

	drupal_add_js(drupal_get_path('module', 'piechart').'/js/d3.min.js',array('weight' => 0));
	drupal_add_js(drupal_get_path('module', 'piechart').'/js/d3pie.min.js',array('weight' => 1));
	drupal_add_js(drupal_get_path('module', 'piechart').'/js/jquery-1.7.2.js',array('weight' => 2));
	drupal_add_js(drupal_get_path('module', 'piechart').'/js/main.js',array('weight' => 3));
	drupal_add_css(drupal_get_path('module', 'piechart').'/css/main.css');

	$form['chart'] = array(
		'#markup' => '
		<div id="table-chart" style="float: left;width: 103.2%;border: 1px solid #bbb;">
			<div id="radio-view-chart" style="float:left;width:28%;margin-top:35px;margin-left:11px;">
				<div>
					<select style="width:100%;" class="select-chart">
						<option value="all" selected>All adverse event reports</option>
						<option value="males">Males</option>
					</select>
				</div>
			</div>
			<div id="pieChart" style="float: left;"></div>
		</div>
		<script>
		var pie = new d3pie("pieChart", {
		"header": {
			"title": {
				"text": "All adverse event reports",
				"fontSize": 24,
				"font": "open sans"
			},
			"subtitle": {
				"color": "#999999",
				"fontSize": 12,
				"font": "open sans"
			},
			"titleSubtitlePadding": 9
		},
		"footer": {
			"color": "#999999",
			"fontSize": 10,
			"font": "open sans",
			"location": "bottom-left"
		},
		"size": {
			"canvasWidth": 590
		},
		"data": {
			"sortOrder": "value-desc",
			"content": [
				{
					"label": "Drug Ineffective"+" ("+$("#view_se_1").val()+")",
					"value": + $("#view_se_1").val(),
					"color": "#2484c1"
				},
				{
					"label": "Nausea"+" ("+$("#view_se_2").val()+")",
					"value": + $("#view_se_2").val(),
					"color": "#0c6197"
				},
				{
					"label": "Death"+" ("+$("#view_se_3").val()+")",
					"value": + $("#view_se_3").val(),
					"color": "#4daa4b"
				},
				{
					"label": "Fatigue"+" ("+$("#view_se_4").val()+")",
					"value": + $("#view_se_4").val(),
					"color": "#90c469"
				},
				{
					"label": "Headache"+" ("+$("#view_se_5").val()+")",
					"value": + $("#view_se_5").val(),
					"color": "#daca61"
				},
				{
					"label": "Dyspnoea"+" ("+$("#view_se_6").val()+")",
					"value": + $("#view_se_6").val(),
					"color": "#e4a14b"
				},
				{
					"label": "Dizziness"+" ("+$("#view_se_10").val()+")",
					"value": + $("#view_se_10").val(),
					"color": "#e98125"
				},
				{
					"label": "Pain"+" ("+$("#view_se_7").val()+")",
					"value": + $("#view_se_7").val(),
					"color": "#cb2121"
				},
				{
					"label": "Vomiting"+" ("+$("#view_se_8").val()+")",
					"value": + $("#view_se_8").val(),
					"color": "#830909"
				},
				{
					"label": "Diarrhoea"+" ("+$("#view_se_9").val()+")",
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
				"hideWhenLessThanPercentage": 3
			},
			"mainLabel": {
				"fontSize": 11
			},
			"percentage": {
				"color": "#ffffff",
				"decimalPlaces": 0
			},
			"value": {
				"color": "#adadad",
				"fontSize": 11
			},
			"lines": {
				"enabled": true
			}
		},
		"effects": {
			"pullOutSegmentOnClick": {
				"effect": "linear",
				"speed": 400,
				"size": 8
			}
		},
		"misc": {
			"gradient": {
				"enabled": true,
				"percentage": 100
			}
		}
	    });
	    </script>
		',
	);

	return $form;
}

