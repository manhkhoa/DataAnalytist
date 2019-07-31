jQuery(document).ready(function ($) {
  
	var path = window.location.pathname;

	if(path.split("/")[1] == "recalls-chart"){
		$('#layout-container ul.navigation li a').removeClass('active');
		$('#layout-container ul.navigation li a.recall-chart').addClass('active');

	} else if(path.split("/")[1] == "adverse-events-chart") {
		$('#layout-container ul.navigation li a').removeClass('active');
		$('#layout-container ul.navigation li a.circle-company').addClass('active');
	} else if(path.split("/")[1] == "drugs-chart") {
		$('#layout-container ul.navigation li a').removeClass('active');
		$('#layout-container ul.navigation li a.circle-drugs').addClass('active');
		
	} else if(path.split("/")[1] == "pending-registration") {
		$('#layout-container ul.navigation li a').removeClass('active');
		$('#layout-container ul.navigation li a.pending-registration').addClass('active');
		
	} else if(path.split("/")[1] == "register") {
		$('#layout-container ul.navigation li a').removeClass('active');
		$('#layout-container ul.navigation li a.register').addClass('active');
		
	} else if(path.split("/")[1] == "login") {
		$('#layout-container ul.navigation li a').removeClass('active');
		$('#layout-container ul.navigation li a.login').addClass('active');
		
	} else {
		$('#layout-container ul.navigation li a').removeClass('active');
		$('#layout-container ul.navigation li a.dasboard').addClass('active');
		
	}


	$('table').addClass('display table table-bordered table-striped dataTable');
	$('input[type="submit"]').addClass('btn-danger btn');


	var device_width = (window.innerWidth > 0) ? window.innerWidth : screen.width;
	if(device_width < 500){
		$('.profile-info .img-circle').hide();
		$('#block-circle-chart-adverse-events-chart .col-md-12').addClass('tmp-class');
		$('#block-circle-chart-drug-chart .col-md-12').addClass('tmp-class');

		$('#block-circle-chart-adverse-events-chart .col-md-12').addClass('col-md-6');
		$('#block-circle-chart-drug-chart .col-md-12').addClass('col-md-6');

		$('#block-circle-chart-adverse-events-chart .tmp-class').removeClass('col-md-12');
		$('#block-circle-chart-drug-chart .tmp-class').removeClass('col-md-12');
	}
			
});