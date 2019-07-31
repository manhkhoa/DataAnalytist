<?php

function get_circle_chart_com($form,&$form_state){
	global $base_url;	

	// Call function get data
	// If file is not exists, we will generate new data file
	// if(!file_exists(getcwd().'/sites/all/modules/custom/circle_chart/js/companies/data.js')){		
	// 	circle_getdata_companies();		
	// } 
	

	$form['#attached']['js'] = array(
	  $base_url.'/importdb/data/companies/data.js',	
	  drupal_get_path('module', 'circle_chart') . '/js/companies/libs.js',	  
	  drupal_get_path('module', 'circle_chart') . '/js/tooltip.js',	   
	  drupal_get_path('module', 'circle_chart') . '/js/custom.js',	
	);

	$form['#attached']['css'] = array(
	  drupal_get_path('module', 'circle_chart') . '/css/base.css',
	  drupal_get_path('module', 'circle_chart') . '/css/main.css',

	);

	$form['circle-chart'] = array(
		'#markup' => '
		<div class="circle-chart">					

			<div id="interactiveFreeFormMain">

			  <div class="nytg">

			    <div id="nytg-chartFrame">
			      <div id="nytg-chart">

			        <div class="nytg-navBar"> <!-- Start tab -->
			          <div id="nytg-search" style="display:none;"></div>
			            <ul class="nytg-navigation clearfix">
			              <li id="nytg-nav-all">All drug names</li>
			            </ul>
			        </div> <!-- End tab -->

			        <div id="nytg-tooltip">
			          <div id="nytg-tooltipContainer">			            
			            <div class="nytg-name"></div>
			          <div class="nytg-discretion"></div>
			            <div class="nytg-valuesContainer">
			              <span class="nytg-value"></span>
			              <span class="nytg-change"></span>
			              <div class="nytg-department"></div>
			            </div>
			            <div class="nytg-chart"></div>
			            <div class="nytg-tail"></div>
			          </div>
			        </div>

			        <div id="nytg-chartCanvas"></div> <!-- Very Important -->

			      </div>
			    </div>
			  </div>
			<!--END Stencil generated content. -->    

			</div><!--close main free form -->
		</div>'
		);

	return $form;
}