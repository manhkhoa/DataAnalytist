<?php

function get_hiren_chart($form, &$form_state){

	$form['#attached']['css'] = array(
	  drupal_get_path('module', 'hirenchart') . '/app/css/app.css',
	  drupal_get_path('module', 'hirenchart').'app/css/hiren-chart1.css',
	  drupal_get_path('module', 'hirenchart').'app/css/hiren-chart2.css'
	);

	$form['#attached']['js'] = array(
	  drupal_get_path('module', 'hirenchart') . '/bower_components/d3/d3.min.js',
	  drupal_get_path('module', 'hirenchart').'/bower_components/angular/angular.js',
	  drupal_get_path('module', 'hirenchart').'/bower_components/angular-route/angular-route.js',
	  drupal_get_path('module', 'hirenchart').'/bower_components/underscore/underscore.js',
	  drupal_get_path('module', 'hirenchart').'/app/js/app.js',
	  drupal_get_path('module', 'hirenchart').'/app/js/routes.js',
	  drupal_get_path('module', 'hirenchart').'/app/js/services.js',
	  drupal_get_path('module', 'hirenchart').'/app/js/controllers.js',
	  drupal_get_path('module', 'hirenchart').'/app/js/filters.js',
	  drupal_get_path('module', 'hirenchart').'/app/js/directives.js',
	  drupal_get_path('module', 'hirenchart').'/app/js/directives/breadcrumb.js',
	  drupal_get_path('module', 'hirenchart').'/app/js/directives/sunburst-perspective.js',
	  drupal_get_path('module', 'hirenchart').'/app/js/directives/sunburst.js',
	  drupal_get_path('module', 'hirenchart').'/bower_components/main.js',
	);

	$form['hiren_chart'] = array(
		'#markup' => '
		<div id="table-chart" style="float: left;width: 103.2%;border: 1px solid #bbb;">
			<div style="width:100%;float:left;">
				<div ng-app="hierarchie"><div ng-view></div></div>
			</div>
		</div>
		',
	);

	return $form;
}
