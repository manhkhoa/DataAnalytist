<?php

function get_circle_chart($form,&$form_state){
	global $base_url;	
	
	// Call function get data
	// If file is not exists, we will generate new data file
	// if(!file_exists($base_url.'/importdb/data/drugs/data.js')){		
	// 	circle_getdata_drugs();		
	// } 
	

	$form['#attached']['js'] = array(
	  $base_url.'/importdb/data/drugs/data.js',	
	  drupal_get_path('module', 'circle_chart') . '/js/drugs/libs1.js',	  
	  drupal_get_path('module', 'circle_chart') . '/js/tooltip.js',	
	  drupal_get_path('module', 'circle_chart') . '/js/drugs/custom1.js',

	);

	$form['#attached']['css'] = array(
	  drupal_get_path('module', 'circle_chart') . '/css/drugs/base1.css',
	  drupal_get_path('module', 'circle_chart') . '/css/drugs/main1.css',
	);

	$form['circle-chart'] = array(
		'#markup' => '
		<div class="circle-chart1">					

			<div id="FreeFormMain">

			  <div class="nytg1">

			    <div id="nytg1-chartFrame">
			      <div id="nytg1-chart">

			        <div class="nytg1-navBar"> <!-- Start tab -->
			          <div id="nytg1-search" style="display:none;"></div>
			            <ul class="nytg1-navigation clearfix">
			              <li id="nytg1-nav-all">All drug names</li>
			            </ul>
			        </div> <!-- End tab -->

			        <div id="nytg1-tooltip">
			          <div id="nytg1-tooltipContainer">
			            <div class="nytg1-department"></div>
			            <div class="nytg1-name"></div>
			          <div class="nytg1-discretion"></div>
			            <div class="nytg1-valuesContainer">
			              <span class="nytg1-value"></span>
			              <span class="nytg1-change"></span>
			            </div>
			            <div class="nytg1-chart"></div>
			            <div class="nytg1-tail"></div>
			          </div>
			        </div>

			        <div id="nytg1-chartCanvas"></div> <!-- Very Important -->

			      </div>
			    </div>
			  </div>
			<!--END Stencil generated content. -->    

			</div><!--close main free form -->
		</div>'
		);

	return $form;
}



function get_drug_chart($form,&$form_state){
	global $base_url;	
	$company_name = arg(1);

	drupal_set_title('Drug chart: '.$company_name);

	// Call function get data
	// If file is not exists, we will generate new data file
	// if(!file_exists($base_url.'/importdb/data/companies/drug_items/'.$company_name.'.js')){		
	// 	circle_getdata_drug_item($company_name);		
	// } 
	

	$form['#attached']['js'] = array(
	  $base_url.'/importdb/data/companies/drug_items/'.$company_name.'.js',	
	  drupal_get_path('module', 'circle_chart') . '/js/libs.js',	  
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
				            <div class="nytg-department"></div>
				            <div class="nytg-name"></div>
				          <div class="nytg-discretion"></div>
				            <div class="nytg-valuesContainer">
				              <span class="nytg-value"></span>
				              <span class="nytg-change"></span>
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