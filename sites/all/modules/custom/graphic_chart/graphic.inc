<?php

function get_graphic_chart($form,&$form_state){
	global $base_url;	


	$form['#attached']['js'] = array(
	  drupal_get_path('module', 'graphic_chart') . '/js/tooltip.js',
	  drupal_get_path('module', 'graphic_chart') . '/js/d3.v2.min.js',	  
	  drupal_get_path('module', 'graphic_chart') . '/js/data.js',	  
	  // drupal_get_path('module', 'graphic_chart') . '/js/main.js',
	);

	$form['#attached']['css'] = array(
	  drupal_get_path('module', 'graphic_chart') . '/css/styles.css',
	  drupal_get_path('module', 'graphic_chart') . '/css/base.css',
	  drupal_get_path('module', 'graphic_chart') . '/css/main.css',	  
	  drupal_get_path('module', 'graphic_chart') . '/css/libs/sectionfront.css',
	  drupal_get_path('module', 'graphic_chart') . '/css/libs/common.css',
	  drupal_get_path('module', 'graphic_chart') . '/css/libs/common_module.css',
	  drupal_get_path('module', 'graphic_chart') . '/css/libs/common_global.css',
	  drupal_get_path('module', 'graphic_chart') . '/css/libs/forms.css',
	  drupal_get_path('module', 'graphic_chart') . '/css/libs/dialogbox.css',
	);

	$form['graphic-chart'] = array(
		'#markup' => '
		<div class="graphic-chart">		
			<div class="ledeStory">
	            <div class="module insetHFullWidth">
	                <div class="storyHeader">
	                    <h1>Drought Extends, Crops Wither</h1>
	                </div><!--close .storyHeader -->
	            </div><!--end .module insetHFullWidth -->

	            <div id="interactiveFreeFormMain">
	                <div class="g-wrapper">
	                    <div class="g-chart">

	                        <!-- Start Corn -->    
	                        <div id="corn" class="g-crop">
	                        <div class="g-header" style="left:0;">Crop</div>
	                        <div class="g-header" style="left:120px;">Crop Conditions</div>
	                        <div class="g-header" style="left:320px;">Price Received and Yield</div>
	                        <div class="g-header" style="left:640px;">Crop Size and Location</div>
	                        <div class="g-condition">
	                        <table class="g-scoreboard">
	                        <tr>
	                        <td style="width:120px;"><div class="g-big">Corn</div></td>
	                        <td style="width:40px;"><div class="g-big g-value g-poor">25%</div></td>
	                        <td style="width:40px;"><div class="g-unit">poor</div></td>
	                        <td style="width:40px;"><div class="g-big g-value g-very g-poor">26%</div></td>
	                        <td style="width:60px;"><div class="g-unit">very poor</div></td>
	                        <td style="width:60px;"><div class="g-value g-price">$7.36</div></td>
	                        <td style="width:40px;"><div class="g-grey g-unit">/bu.</div></td>
	                        <td style="width:40px;"><div class="g-value g-yield">123</div></td>
	                        <td style="width:110px;"><div class="g-grey g-unit">bu./acre</div></td>
	                        </tr>
	                        <tr>
	                        <td><div class="g-grey">Annual change</div></td>
	                        <td><div class="g-value g-poorchange">+15%</div></td>
	                        <td colspan="2"><div class="g-value g-verypoorchange">+21%</div></td>
	                        <td colspan="2"><div class="g-value g-pricechange">+$0.41</div></td>
	                        <td colspan="2"><div class="g-value g-yieldchange">-24</div></td>
	                        <td></td>
	                        </tr>
	                        </table>
	                        <div class="g-note" style="left:100px;">
	                        <div class="g-arrow g-left" style="left:-40px;height:28px;"></div>
	                        Corn needs water at the critical pollination stage &mdash; otherwise, the kernels cannot form. In the 1988 drought, more than half of the corn crop was affected.
	                        </div>
	                        <div class="g-note" style="left:356px;">
	                        <div class="g-arrow g-right" style="right:-33px;height:30px;"></div>
	                        Last week, more than half of the corn in the fields was deemed poor or worse, so much of it will be turned into silage or not harvested.
	                        </div>
	                        </div><div class="g-map">
	                        <table class="g-scoreboard">
	                        <tr>
	                        <td><div>
	                        <span class="g-big"></span>
	                        <span class="g-value">96 million</span>
	                        <span class="g-grey">acres planted, 2012</span>
	                        </div></td>
	                        </tr>
	                        </table>
	                        <div class="g-label">
	                        <span class="g-swatch g-moderate" title="Moderate drought"></span>
	                        <span class="g-swatch g-severe" title="Severe drought"></span>
	                        <span class="g-swatch g-extreme" title="Extreme drought"></span>
	                        Drought during <span class="g-date">July 2012</span>
	                        <span style="float:right;">&bull; <span class="g-grey">10,000 acres</span></span>
	                        </div>
	                        </div>
	                        </div> <!-- End Corn -->

	                        <!-- Start Soybeans -->
	                        <div id="soybeans" class="g-crop">
	                        <div class="g-condition">
	                        <table class="g-scoreboard">
	                        <tr>
	                        <td style="width:120px;"><div class="g-big">Soybeans</div></td>
	                        <td style="width:40px;"><div class="g-big g-value g-poor">21%</div></td>
	                        <td style="width:40px;"><div class="g-unit">poor</div></td>
	                        <td style="width:40px;"><div class="g-big g-value g-very g-poor">16%</div></td>
	                        <td style="width:60px;"><div class="g-unit">very poor</div></td>
	                        <td style="width:60px;"><div class="g-value g-price">$15.60</div></td>
	                        <td style="width:40px;"><div class="g-grey g-unit">/bu.</div></td>
	                        <td style="width:40px;"><div class="g-value g-yield">36.1</div></td>
	                        <td style="width:110px;"><div class="g-grey g-unit">bu./acre</div></td>
	                        </tr>
	                        <tr>
	                        <td><div class="g-grey">Annual change</div></td>
	                        <td><div class="g-value g-poorchange">+12%</div></td>
	                        <td colspan="2"><div class="g-value g-verypoorchange">+12%</div></td>
	                        <td colspan="2"><div class="g-value g-pricechange">+$2.05</div></td>
	                        <td colspan="2"><div class="g-value g-yieldchange">-5.4</div></td>
	                        <td></td>
	                        </tr>
	                        </table>
	                        <div class="g-note" style="left:100px;">
	                        <div class="g-arrow g-left" style="left:-40px;height:66px;"></div>
	                        Soybeans reach their most critical growth stage later in the season than corn, and need less water. The timing of the 1988 drought saved much of the crop.
	                        </div>
	                        <div class="g-note" style="left:356px;">
	                        <div class="g-arrow g-right" style="top:18px;right:-33px;height:68px;"></div>
	                        The recent prolonged dry weather has made each week look more dire for soybeans.
	                        </div>
	                        </div><div class="g-map">
	                        <table class="g-scoreboard">
	                        <tr><td><div>
	                        <span class="g-big"></span>
	                        <span class="g-value">76 million</span>
	                        <span class="g-grey">acres planted, 2012</span>
	                        </div></td></tr>
	                        </table>
	                        <div class="g-label">
	                        <span class="g-date">July 2012</span>
	                        <span style="float:right;">&bull; <span class="g-grey">10,000 acres</span></span>
	                        </div>
	                        </div>
	                        </div> <!-- End Soybeans -->

	                        <!-- Start Wheat Spring -->
	                        <div id="wheat-spring" class="g-crop">
	                        <div class="g-condition">
	                        <table class="g-scoreboard">
	                        <tr>
	                        <td style="width:120px;"><div class="g-big">Wheat</div></td>
	                        <td style="width:40px;"><div class="g-big g-value g-poor">9%</div></td>
	                        <td style="width:40px;"><div class="g-unit">poor</div></td>
	                        <td style="width:40px;"><div class="g-big g-value g-very g-poor">2%</div></td>
	                        <td style="width:60px;"><div class="g-unit">very poor</div></td>
	                        <td style="width:60px;"><div class="g-value g-price">$8.68</div></td>
	                        <td style="width:40px;"><div class="g-grey g-unit">/bu.</div></td>
	                        <td style="width:40px;"><div class="g-value g-yield">42.8</div></td>
	                        <td style="width:110px;"><div class="g-grey g-unit">bu./acre</div></td>
	                        </tr>
	                        <tr>
	                        <td><div class="g-grey">Annual change</div></td>
	                        <td><div class="g-value g-poorchange">+2%</div></td>
	                        <td colspan="2"><div class="g-value g-verypoorchange">+1%</div></td>
	                        <td colspan="2"><div class="g-value g-pricechange">+$0.31</div></td>
	                        <td colspan="2"><div class="g-value g-yieldchange">+5.1</div></td>
	                        <td></td>
	                        </tr>
	                        </table>
	                        <div class="g-note" style="left:100px;">
	                        <div class="g-arrow g-left" style="left:-26px;height:0;width:18px;top:10px;"></div>
	                        Almost every acre of spring wheat was affected in 1988.
	                        </div>
	                        <div class="g-note" style="left:356px;">
	                        <div class="g-arrow g-right" style="top:18px;right:-33px;height:140px;"></div>
	                        Because a mild winter allowed for earlier planting and harvest, spring wheat, which is used for bread and other high-gluten flours, has been relatively untouched by the drought.
	                        </div>
	                        </div><div class="g-map">
	                        <table class="g-scoreboard">
	                        <tr><td><div>
	                        <span class="g-big"></span>
	                        <span class="g-value">12 million</span>
	                        <span class="g-grey">acres planted, 2012</span>
	                        </div></td></tr>
	                        </table>
	                        <div class="g-label">
	                        <span class="g-date">July 2012</span>
	                        <span style="float:right;">&bull; <span class="g-grey">10,000 acres (includes spring and winter)</span></span>
	                        </div>
	                        </div>
	                        </div> <!-- End Wheat Spring -->

	                        <!-- Start Cotton -->
	                        <div id="cotton" class="g-crop">
	                        <div class="g-condition">
	                        <table class="g-scoreboard">
	                        <tr>
	                        <td style="width:120px;"><div class="g-big">Cotton</div></td>
	                        <td style="width:40px;"><div class="g-big g-value g-poor">19%</div></td>
	                        <td style="width:40px;"><div class="g-unit">poor</div></td>
	                        <td style="width:40px;"><div class="g-big g-value g-very g-poor">10%</div></td>
	                        <td style="width:60px;"><div class="g-unit">very poor</div></td>
	                        <td style="width:60px;"><div class="g-value g-price">$1.00</div></td>
	                        <td style="width:40px;"><div class="g-grey g-unit">/lb.</div></td>
	                        <td style="width:40px;"><div class="g-value g-yield">784</div></td>
	                        <td style="width:110px;"><div class="g-grey g-unit">lb./acre</div></td>
	                        </tr>
	                        <tr>
	                        <td><div class="g-grey">Annual change</div></td>
	                        <td><div class="g-value g-poorchange">-0%</div></td>
	                        <td colspan="2"><div class="g-value g-verypoorchange">-11%</div></td>
	                        <td colspan="2"><div class="g-value g-pricechange">+$0.00</div></td>
	                        <td colspan="2"><div class="g-value g-yieldchange">-6.0</div></td>
	                        <td></td>
	                        </tr>
	                        </table>
	                        <div class="g-note">
	                        <div class="g-arrow g-left" style="left:60px;top:55px;height:80px;width:0;"></div>
	                        Cotton, which can withstand hotter and drier conditions than other crops,  was largely spared by the 1988 drought. 
	                        </div>
	                        <div class="g-note" style="left:356px;">
	                        <div class="g-arrow g-right" style="right:-33px;height:90px;"></div>
	                        Hurricanes and heavy rains have adversely affected cotton in recent years, but the crop is doing fairly well this year.
	                        </div>
	                        </div><div class="g-map">
	                        <table class="g-scoreboard">
	                        <tr><td><div>
	                        <span class="g-big"></span>
	                        <span class="g-value">13 million</span>
	                        <span class="g-grey">acres planted, 2012</span>
	                        </div></td></tr>
	                        </table>
	                        <div class="g-label">
	                        <span class="g-date">July 2012</span>
	                        <span style="float:right;">&bull; <span class="g-grey">5,000 acres</span></span>
	                        </div>
	                        </div>
	                        </div> <!-- End Cotton -->

	                        <!-- Start Sorghum -->
	                        <div id="sorghum" class="g-crop">
	                        <div class="g-condition">
	                        <table class="g-scoreboard">
	                        <tr>
	                        <td style="width:120px;"><div class="g-big">Sorghum</div></td>
	                        <td style="width:40px;"><div class="g-big g-value g-poor">28%</div></td>
	                        <td style="width:40px;"><div class="g-unit">poor</div></td>
	                        <td style="width:40px;"><div class="g-big g-value g-very g-poor">23%</div></td>
	                        <td style="width:60px;"><div class="g-unit">very poor</div></td>
	                        <td style="width:60px;"><div class="g-value g-price">$12.00</div></td>
	                        <td style="width:40px;"><div class="g-grey g-unit">/bu.</div></td>
	                        <td style="width:40px;"><div class="g-value g-yield">48.6</div></td>
	                        <td style="width:110px;"><div class="g-grey g-unit">bu./acre</div></td>
	                        </tr>
	                        <tr>
	                        <td><div class="g-grey">Annual change</div></td>
	                        <td><div class="g-value g-poorchange">+5%</div></td>
	                        <td colspan="2"><div class="g-value g-verypoorchange">+5%</div></td>
	                        <td colspan="2"><div class="g-value g-pricechange">+$1.18</div></td>
	                        <td colspan="2"><div class="g-value g-yieldchange">-6.0</div></td>
	                        <td></td>
	                        </tr>
	                        </table>
	                        <div class="g-note">
	                        <div class="g-arrow g-left" style="left:60px;top:70px;height:46px;width:0;"></div>
	                        Sorghum, which is primarity used for livestock feed, can become dormant in dry conditions but resume growth after a drought is over. Sorghum recovered well in 1988. 
	                        </div>
	                        <div class="g-note" style="left:356px;">
	                        <div class="g-arrow g-right" style="right:-33px;width:26px;height:36px;"></div>
	                        The intensity of the recent drought has threatened sorghum even in dormancy, harming its quality in recent weeks.
	                        </div>
	                        </div><div class="g-map">
	                        <table class="g-scoreboard">
	                        <tr><td><div>
	                        <span class="g-big"></span>
	                        <span class="g-value">6 million</span>
	                        <span class="g-grey">acres planted, 2012</span>
	                        </div></td></tr>
	                        </table>
	                        <div class="g-label">
	                        <span class="g-date">July 2012</span>
	                        <span style="float:right;">&bull; <span class="g-grey">2,000 acres</span></span>
	                        </div>
	                        </div>
	                        </div> <!-- End Sorghum -->

	                        <!-- Start Pastureland -->
	                        <div id="pastureland" class="g-crop">
	                        <div class="g-condition">
	                        <table class="g-scoreboard">
	                        <tr>
	                        <td style="width:120px;"><div class="g-big">Pasture</div></td>
	                        <td style="width:40px;"><div class="g-big g-value g-poor">27%</div></td>
	                        <td style="width:40px;"><div class="g-unit">poor</div></td>
	                        <td style="width:40px;"><div class="g-big g-value g-very g-poor">32%</div></td>
	                        <td style="width:60px;"><div class="g-unit">very poor</div></td>
	                        <td style="width:250px;"></td>
	                        </tr>
	                        <tr>
	                        <td><div class="g-grey">Annual change</div></td>
	                        <td><div class="g-value g-poorchange">+9%</div></td>
	                        <td colspan="2"><div class="g-value g-verypoorchange">+11%</div></td>
	                        <td colspan="5"></td>
	                        </tr>
	                        </table>
	                        <div class="g-note" style="left:0;width:520px;">
	                        <div class="g-arrow g-right" style="top:18px;right:-29px;width:40px;height:12px;"></div>
	                        Nearly 60 percent of all pastureland has been rated as poor or worse, so pastured cattle don&rsquo;t have enough food. Farmers are selling cattle instead of breeding them. Analysts predict the price will climb next year with a dearth of young cattle.
	                        </div>
	                        </div><div class="g-map">
	                        <table class="g-scoreboard">
	                        <tr><td><div>
	                        <span class="g-big"></span>
	                        <span class="g-value">473 million</span>
	                        <span class="g-grey">acres pastured, 2007</span>
	                        </div></td></tr>
	                        </table>
	                        <div class="g-label">
	                        <span class="g-date">July 2012</span>
	                        <span style="float:right;">&bull; <span class="g-grey">50,000 acres</span></span>
	                        </div>
	                        </div> 
	                        </div> <!-- End Pastureland -->

	                    </div> <!-- End G-Chart -->
	                   
	                   <script src="'.drupal_get_path('module', 'graphic_chart').'/js/main.js" type="text/javascript" ></script>	                    
	                    

	                </div><!--END Stencil generated content. -->    
	            </div><!--close main free form -->
	        </div><!--close .ledeStory -->
		</div>'
		);

	return $form;
}