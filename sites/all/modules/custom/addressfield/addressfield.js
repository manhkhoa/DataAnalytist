jQuery(document).ready(function(){
	jQuery("body").delegate(".postal-code", "blur",function(event){ 
		var length = jQuery(".postal-code").val().length;
		var country = jQuery('.country option:selected').text();
		if(country == "United States"){
			if(length > 5){
				jQuery(".postal-code").removeClass('validate[custom[validate_zipcode_countryUS]]');
				jQuery(".postal-code").addClass('validate[custom[zipcodeUS]]');
			}else{
				jQuery(".postal-code").removeClass('validate[custom[zipcodeUS]]');
				jQuery(".postal-code").addClass('validate[custom[validate_zipcode_countryUS]]');
			}	
		}					
	});

	jQuery("body").delegate("#edit-field-company-address .postal-code", "blur",function(event){ 
		var length = jQuery("#edit-field-company-address .postal-code").val().length;
		var country = jQuery('#edit-field-company-address .country option:selected').text();
		if(country == "United States"){
			if(length > 5){
				jQuery("#edit-field-company-address .postal-code").removeClass('validate[custom[validate_zipcode_countryUS]]');
				jQuery("#edit-field-company-address .postal-code").addClass('validate[custom[zipcodeUS]]');
			}else{
				jQuery("#edit-field-company-address .postal-code").removeClass('validate[custom[zipcodeUS]]');
				jQuery("#edit-field-company-address .postal-code").addClass('validate[custom[validate_zipcode_countryUS]]');
			}	
		}					
	});


	jQuery("body").delegate("#edit-field-contact-address .postal-code", "blur",function(event){ 
		var length = jQuery("#edit-field-contact-address .postal-code").val().length;
		var country = jQuery('#edit-field-contact-address .country option:selected').text();
		if(country == "United States"){
			if(length > 5){
				jQuery("#edit-field-contact-address .postal-code").removeClass('validate[custom[validate_zipcode_countryUS]]');
				jQuery("#edit-field-contact-address .postal-code").addClass('validate[custom[zipcodeUS]]');
			}else{
				jQuery("#edit-field-contact-address .postal-code").removeClass('validate[custom[zipcodeUS]]');
				jQuery("#edit-field-contact-address .postal-code").addClass('validate[custom[validate_zipcode_countryUS]]');
			}	
		}					
	});

	
});