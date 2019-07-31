<?php

function get_pie_chart_male_pt($form,&$form_state){
	$form = array();

	$url = drupal_get_path('module','chart').'/connect-mongodb.php';
	include_once($url);
	$db = getDB();

	drupal_add_js(drupal_get_path('module', 'piechart').'/js/d3.min.js',array('weight' => 0));
	drupal_add_js(drupal_get_path('module', 'piechart').'/js/d3pie.min.js',array('weight' => 1));
	drupal_add_js(drupal_get_path('module', 'piechart').'/js/jquery-1.7.2.js',array('weight' => 2));
	drupal_add_js(drupal_get_path('module', 'piechart').'/js/main.js',array('weight' => 3));
	drupal_add_css(drupal_get_path('module', 'piechart').'/css/main.css');

		$males = $db->recdemo;
		$search_mp = array('value.gender'=>"M","value.pt"=>"Drug ineffective");
		$search_mp1 = array('value.gender'=>"M","value.pt"=>"Nausea");
		$search_mp2 = array('value.gender'=>"M","value.pt"=>"Death");
		$search_mp3 = array('value.gender'=>"M","value.pt"=>"Fatigue");
		$search_mp4 = array('value.gender'=>"M","value.pt"=>"Headache");
		$search_mp5 = array('value.gender'=>"M","value.pt"=>"Dyspnoea");
		$search_mp6 = array('value.gender'=>"M","value.pt"=>"Pain");
		$search_mp7 = array('value.gender'=>"M","value.pt"=>"Vomiting");
		$search_mp8 = array('value.gender'=>"M","value.pt"=>"Diarrhoea");
		$search_mp9 = array('value.gender'=>"M","value.pt"=>"Dizziness");

		$c = 0;
		$c1 = 0;
		$c2 = 0;
		$c3 = 0;
		$c4 = 0;
		$c5 = 0;
		$c6 = 0;
		$c7 = 0;
		$c8 = 0;
		$c9 = 0;
		$c10 = 0;

		$c1 = $males->find($search_mp)->count();
		$c2 = $males->find($search_mp1)->count();
		$c3 = $males->find($search_mp2)->count();
		$c4 = $males->find($search_mp3)->count();
		$c5 = $males->find($search_mp4)->count();
		$c6 = $males->find($search_mp5)->count();
		$c7 = $males->find($search_mp6)->count();
		$c8 = $males->find($search_mp7)->count();
		$c9 = $males->find($search_mp8)->count();
		$c = $males->find($search_mp9)->count();

		print('<input type="hidden" value="'.$c1.'" id="view_se_1">
		   <input type="hidden" value="'.$c2.'" id="view_se_2">
		   <input type="hidden" value="'.$c3.'" id="view_se_3">
		   <input type="hidden" value="'.$c4.'" id="view_se_4">
	       <input type="hidden" value="'.$c5.'" id="view_se_5">
	       <input type="hidden" value="'.$c6.'" id="view_se_6">
	       <input type="hidden" value="'.$c7.'" id="view_se_7">
	       <input type="hidden" value="'.$c8.'" id="view_se_8">
	       <input type="hidden" value="'.$c9.'" id="view_se_9">
	       <input type="hidden" value="'.$c.'" id="view_se_10">');
		
		$form['chart'] = array(
			'#markup' => '
			<div id="table-chart" style="float: left;width: 103.2%;border: 1px solid #bbb;">
				<div id="radio-view-chart" style="float:left;width:28%;margin-top:35px;margin-left:11px;">
					<div>
						<select style="width:100%;" class="select-chart">
							<option value="all">All adverse event reports</option>
							<option value="males" selected>Males</option>
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