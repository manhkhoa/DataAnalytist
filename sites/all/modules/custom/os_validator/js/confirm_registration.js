jQuery(document).ready(function(){
	jQuery('#edit-submit').click(function(){
		var click = 0;			

		var status = jQuery("#edit-field-application-status .form-select").val();		
		var remarks = jQuery("#edit-field-remark .form-textarea").val();
		
		if(status == "approved") {
			if(click == 0){
				var r=confirm(Drupal.t("Would you like to approve this registration request?"));
			} else{
				alert("Your registration request has been approved!");
				return false;
			}
			if(r == false){
					click = 0;
			}else{
				click = click + 1;
				return true;
			}
			
		} else if(status == "denied") {
			var r=confirm(Drupal.t("Would you like to reject this registration request?"));
			jQuery("#edit-field-remark .form-textarea").focus();
			
		}
		
		return r;
	});
});