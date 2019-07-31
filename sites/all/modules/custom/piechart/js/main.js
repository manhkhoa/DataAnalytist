jQuery(document).ready(function($) {
	$('select.select-chart').change(function(){
		if($(this).val() == 'all'){
			window.location.href = "/piechart-all-pt";
		}else{
			window.location.href = "/piechart-male-pt";
		}
	});		
});