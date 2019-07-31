(function( $ ) {
	$(function() {

		$('.circle-chart1 circle').click(function(){
			var drug_name = $('#nytg1-tooltipContainer .nytg1-name').text();
			window.open("/drugs-info/"+drug_name, '_blank');
		});

		$('.block-circle-chart circle').click(function(){
			var drug_name = $('#nytg1-tooltipContainer .nytg1-name').text();
			window.open("/drugs-info/"+drug_name, '_blank');
		});
		
	});

})(jQuery);