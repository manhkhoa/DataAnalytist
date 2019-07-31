(function( $ ) {
	$(function() {		

		$('#get-circle-chart-com circle').click(function(){
			var company_name = $('#nytg-tooltipContainer .nytg-name').text();			
			window.open(window.location.origin+"/drugs-chart/"+company_name, '_blank');
		});

		
		$('#block-circle-chart-adverse-events-chart circle').click(function(){
			var company_name = $('#nytg-tooltipContainer .nytg-name').text();			
			window.open(window.location.origin+"/drugs-chart/"+company_name, '_blank');
		});



		$('#get-drug-chart circle').click(function(){
			var drug_name = $('#nytg-tooltipContainer .nytg-name').text();
			window.open(window.location.origin+"/drugs-info/"+drug_name, '_blank');
		});


	});

})(jQuery);


