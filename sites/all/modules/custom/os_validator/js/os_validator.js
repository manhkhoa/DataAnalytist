
jQuery(document).ready(function(){
	// Prevent double click submit
	// jQuery('form').preventDoubleSubmission();

	/* Set max length for all element of form */
	jQuery("#application-node-form input[type='text']").each(function(){
		var check_maxlength = jQuery(this).attr('maxlength');
		if(check_maxlength == 128){
			jQuery("#application-node-form input[type='text']").attr("maxlength", 40);
		}
	});

	jQuery("#application-node-form input[type='text']").attr("maxlength", 40);

	jQuery("#user-profile-form input[type='text']").each(function(){
		var check_maxlength = jQuery(this).attr('maxlength');
		if(check_maxlength == 128){
			jQuery("#user-profile-form input[type='text']").attr("maxlength", 40);
		}
	});

	// jQuery('#edit-field-terms-and-conditions-und-0-value').attr('readonly', 'readonly');


	jQuery('#edit-mail').addClass('validate[required, custom[email],ajax[ajax_check_user_profile]]');
	jQuery("#edit-current-pass").addClass('validate[required]');

	// hide Cancel user
	jQuery('#user-profile-form #edit-cancel').hide();
	jQuery('.node-application-form .form-actions.form-wrapper #edit-delete').hide();

	// Check require pass
	var check_exist_current_pass = jQuery('#edit-current-pass').size();
	var check_admin_page = jQuery('body.page.admin-menu').size();
	if(check_admin_page == 0 && check_exist_current_pass == 0){
		jQuery('#edit-pass-pass1').addClass('validate[required, funcCall[check_pass_digit], funcCall[check_length_pass], funcCall[check_pass_uppercase], funcCall[check_pass_lowercase]]');
	  	jQuery('#edit-pass-pass2').addClass('validate[required, funcCall[check_confirm_profile_password]]');
	} else if(check_exist_current_pass > 0){
		jQuery('#edit-pass-pass1').blur(function(){
			if(jQuery('#edit-pass-pass1').val() != '' || jQuery('#edit-pass-pass2').val() != ''){
				jQuery('#edit-pass-pass1').addClass('validate[required, funcCall[check_pass_digit], funcCall[check_length_pass], funcCall[check_pass_uppercase], funcCall[check_pass_lowercase]]');
		  		jQuery('#edit-pass-pass2').addClass('validate[required, funcCall[check_confirm_profile_password]]');
		  	} else {
		  		jQuery('#edit-pass-pass1').removeClass('validate[required, funcCall[check_pass_digit], funcCall[check_length_pass], funcCall[check_pass_uppercase], funcCall[check_pass_lowercase]]');
		  		jQuery('#edit-pass-pass2').removeClass('validate[required, funcCall[check_confirm_profile_password]]');
		  	}
		});

		jQuery('#edit-pass-pass2').blur(function(){
			if(jQuery('#edit-pass-pass2').val() != '' || jQuery('#edit-pass-pass1').val() != ''){
				jQuery('#edit-pass-pass1').addClass('validate[required, funcCall[check_pass_digit], funcCall[check_length_pass], funcCall[check_pass_uppercase], funcCall[check_pass_lowercase]]');
		  		jQuery('#edit-pass-pass2').addClass('validate[required, funcCall[check_confirm_profile_password]]');
		  	} else {
		  		jQuery('#edit-pass-pass1').removeClass('validate[required, funcCall[check_pass_digit], funcCall[check_length_pass], funcCall[check_pass_uppercase], funcCall[check_pass_lowercase]]');
		  		jQuery('#edit-pass-pass2').removeClass('validate[required, funcCall[check_confirm_profile_password]]');
		  	}
		});
	}

	jQuery(".state").addClass('validate[required]');
	jQuery(".locality").addClass('validate[required]');
	jQuery(".thoroughfare").addClass('validate[required]');
	jQuery(".postal-code").addClass('validate[required]');
	jQuery(".postal-code").addClass('validate[required]');

	// Validate zipcode when create contact and establishment
	jQuery(".postal-code").blur(function(){

		var country = jQuery('.country option:selected').text();

		if(country == "United States"){
			var length = jQuery(".postal-code").val().length;
			jQuery(".postal-code").removeClass('validate[custom[validate_zipcode_countryUS]]');
			jQuery(".postal-code").removeClass('validate[custom[zipcodeUS]]');
			if(length > 5){
				jQuery(".postal-code").addClass('validate[custom[zipcodeUS]]');
			}else{
				jQuery(".postal-code").addClass('validate[custom[validate_zipcode_countryUS]]');
			}
		}

	});

	
	// Validate zipcode in Contact address when register
	jQuery("#edit-field-contact-address-und-0-postal-code").blur(function(){

		var country = jQuery('#edit-field-company-address-und-0-country option:selected').text();

		if(country == "United States"){
			var length = jQuery("#edit-field-contact-address-und-0-postal-code").val().length;
			jQuery("#edit-field-contact-address-und-0-postal-code").removeClass('validate[custom[validate_zipcode_countryUS]]');
			jQuery("#edit-field-contact-address-und-0-postal-code").removeClass('validate[custom[zipcodeUS]]');
			if(length > 5){
				jQuery("#edit-field-contact-address-und-0-postal-code").addClass('validate[custom[zipcodeUS]]');
			}else{
				jQuery("#edit-field-contact-address-und-0-postal-code").addClass('validate[custom[validate_zipcode_countryUS]]');
			}
		}

	});

	

	jQuery("#application-node-form").validationEngine();
	jQuery("#user-profile-form").validationEngine();
	jQuery("#password-reset-form").validationEngine();
	

});

	function checkYear(field, rules, i, options){
		var currentYear = (new Date).getFullYear();
		var data = field.val().split('/');
		if(data[2] != currentYear ) {
				return 'Year must be '+currentYear;
		}
	}

	
	// Password must be 8 character
	function check_length_pass(field, rules, i, options){
		if (field.val().length < 8) {
			return options.allrules.pass_length.alertText;
		}
	}

	// Password must be contain 1 digit
	function check_pass_digit(field, rules, i, options){
		var val = field.val();
		var matches = val.match(/\d+/g);
		if (matches == null) {
		    return options.allrules.number_in_pass.alertText;
		}
	}

	// Password must be contain 1 uppercase
	function check_pass_uppercase(field, rules, i, options){
		var val = field.val();
		var num_upper = val.replace(/[^A-Z]/g, "").length;
		if (num_upper == 0) {
			return options.allrules.uppercase_in_pass.alertText;
		}
	}

	// Password must be contain 1 lowercase
	function check_pass_lowercase(field, rules, i, options){
		var val = field.val();
		var num_upper = val.replace(/[^a-z]/g, "").length;
		if (num_upper == 0) {
			return options.allrules.lowercase_in_pass.alertText;
		}
	}

	// validate center submission
	function check_value_center_submission(field, rules, i, options){
			if (field.val() = '' ) {
				return options.allrules.validate_center_submission.alertText;
			}
	}

	function check_value_contact(field, rules, i, options){
			if (field.val().length != '9' ) {
				return options.allrules.validate_value_contact_facility.alertText;
			}
	}

	// Check lenght user id
	function check_lenght_user_id(field, rules, i, options){
			if (!((field.val().length < '20'))) {
				return options.allrules.validate_length_user_id.alertText;
			}
	}

	// Activate sub user
	function check_confirm_password(field, rules, i, options){
		var password = jQuery("#edit-field-confirm-password-und-0-pass1").val();
		var confirm_password = jQuery("#edit-field-confirm-password-und-0-pass2").val();
		if (confirm_password != password) {
			return options.allrules.validate_password.alertText;
		}
	}

	// update pass in user profile
	function check_confirm_profile_password(field, rules, i, options){
		var password = jQuery("#edit-pass-pass1").val();
		var confirm_password = jQuery("#edit-pass-pass2").val();

		if (confirm_password != password) {
			return options.allrules.validate_password.alertText;
		}
	}

	function check_reset_password(field, rules, i, options){
		var password = jQuery("#edit-password-confirm-pass1").val();
		var confirm_password = jQuery("#edit-password-confirm-pass2").val();
		if (confirm_password != password) {
			return options.allrules.validate_password.alertText;
		}
	}

	// Validate phone length
	function check_length_phone(field, rules, i, options){
		var area_code = jQuery("#edit-field-code-phone-area-und-0-value").val().length;
		var telephone = jQuery("#edit-field-code-phone-und-0-value").val().length;
		var phone = telephone + area_code;
		if(telephone < '11'){
			if (phone > '10' ) {
				return options.allrules.validate_length_phone.alertText;
			}
		}
	}

	// jQuery plugin to prevent double submission of forms
	jQuery.fn.preventDoubleSubmission = function() {

		jQuery('.form-submit').click(function(){
			var processStatus = '<span class="label label-primary spinner" style="margin-right: 5px; padding:8px;"><i class="icon-spin icon-refresh"></i> Processing ...</span>';
			var processing = false;

			var clicked_button = this;
			jQuery('form:not(#imce-upload-form)').submit(function(event) {
				if((jQuery('form .formError').size() == 0) && (processing == false)){
					processing = true;
					if(jQuery(clicked_button).parent().find('.spinner').size() == 0){
						jQuery(processStatus).insertBefore(clicked_button);
					}
					jQuery(clicked_button).css("display","none");

				}
			});
		})


	};



