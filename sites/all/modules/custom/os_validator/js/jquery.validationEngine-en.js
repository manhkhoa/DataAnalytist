(function($){
		$.fn.validationEngineLanguage = function(){
		};
		$.validationEngineLanguage = {
			newLang: function(){
				$.validationEngineLanguage.allRules = {
					"required": { // Add your regex rules here, you can take telephone as an example
						"regex": "none",
						"alertText": "* This field is required",
						"alertTextCheckboxMultiple": "* Please select an option",
						"alertTextCheckboxe": "* This checkbox is required",
						"alertTextDateRange": "* Both date range fields are required"
					},

					

					"ajax_unique_uid": {
						"url": "../../unique_uid", // Remove /.. when upload code
						"extraDataDynamic": ['#node_current','#form-type'],
						"alertText": "* The user id is not available.",
						"alertTextLoad": "* Validating, please wait"
					},

					"ajax_unique_uid_edit": {
						"url": "../../unique_uid_edit",
						"extraDataDynamic": ['#node_current','#form-type'],
						"alertText": "* The user id is not available.",
						"alertTextLoad": "* Validating, please wait"
					},

					"ajax_unique_email": {
						"url": "../../unique_email",
						"extraDataDynamic": ['#node_current','#form-type'],
						"alertText": "* The email is not available.",
						"alertTextLoad": "* Validating, please wait"
					},

					"ajax_check_unique_email": {
						"url": "../../check_email_unique",
						"alertText": "* This email exists in our database. You might have already registered with us. Please login with your credentials or contact customer support.",
						"alertTextLoad": "* Validating, please wait"
					},

					"ajax_check_unique_email_edit": {
						"url": "../../check_email_unique_edit",
						"alertText": "* This email exists in our database. You might have already registered with us. Please login with your credentials or contact customer support.",
						"alertTextLoad": "* Validating, please wait"
					},

					"ajax_check_user_profile": {
						"url": "../../check_email_user_profile",
						"alertText": "* This email exists in our database. You might have already registered with us. Please login with your credentials or contact customer support.",
						"alertTextLoad": "* Validating, please wait"
					},

					
					"ajax_check_unique_email_users": {
						"url": "check_email_unique_users",
						"alertText": "* This email exists in our database. You might have already registered with us. Please login with your credentials or contact customer support.",
						"alertTextLoad": "* Validating, please wait"
					},

					"requiredInFunction": {
						"func": function(field, rules, i, options){
							return (field.val() == "test") ? true : false;
						},
						"alertText": "* Field must equal test"
					},
					"dateRange": {
						"regex": "none",
						"alertText": "* Invalid Value",
						"alertText2": "Date Range"
					},

					"requireSub": {
						"regex": "none",
						"alertText": "* You must chose packages to complete the registration.",
					},

					"dateTimeRange": {
						"regex": "none",
						"alertText": "* Invalid Value",
						"alertText2": "Date Time Range"
					},
					"minSize": {
						"regex": "none",
						"alertText": "* Minimum ",
						"alertText2": " characters allowed"
					},
					"maxSize": {
						"regex": "none",
						"alertText": "* Maximum ",
						"alertText2": " characters allowed"
					},
					"groupRequired": {
						"regex": "none",
						"alertText": "* You must fill one of the following fields"
					},
					"min": {
						"regex": "none",
						"alertText": "* Minimum value is "
					},
					"max": {
						"regex": "none",
						"alertText": "* Maximum value is "
					},
					"past": {
						"regex": "none",
						"alertText": "* Date prior to "
					},
					"future": {
						"regex": "none",
						"alertText": "* Date past "
					},
					"maxCheckbox": {
						"regex": "none",
						"alertText": "* Maximum ",
						"alertText2": " options allowed"
					},
					"minCheckbox": {
						"regex": "none",
						"alertText": "* Please select ",
						"alertText2": " options"
					},
					"equals": {
						"regex": "none",
						"alertText": "* Fields do not match"
					},
					"creditCard": {
						"regex": "none",
						"alertText": "* Invalid credit card number"
					},
					"phone": {
						// credit: jquery.h5validate.js / orefalo
						"regex": /^([\+][0-9]{1,3}[\ \.\-])?([\(]{1}[0-9]{2,6}[\)])?([0-9\ \.\-\/]{3,20})((x|ext|extension)[\ ]?[0-9]{1,4})?$/,
						"alertText": "* Invalid phone number"
					},
					"email": {
						// HTML5 compatible email regex ( http://www.whatwg.org/specs/web-apps/current-work/multipage/states-of-the-type-attribute.html#    e-mail-state-%28type=email%29 )
						"regex": /^[A-Za-z0-9](([_\.\-]?[a-zA-Z0-9]+)*)@([A-Za-z0-9]+)(([\.\-]?[a-zA-Z0-9]+)*)\.([A-Za-z]{2,})$/,
						"alertText": "* Invalid email address"
					},
					"integer": {
						"regex": /^[\-\+]?\d+$/,
						"alertText": "* Not a valid integer"
					},
					"number": {
						// Number, including positive, negative, and floating decimal. credit: orefalo
						"regex": /^[\-\+]?((([0-9]{1,3})([,][0-9]{3})*)|([0-9]+))?([\.]([0-9]+))?$/,
						"alertText": "* Invalid floating decimal number"
					},

					"validate_promotime": {
						// Number, including positive, negative, and floating decimal. credit: orefalo
						"regex": /^([1-9]|1[0-9]|2[0-4])$/,
						"alertText": "* Duration of Promotion must be 1-24 weeks."
					},

					"date": {
						//	Check if date is valid by leap year
				"func": function (field) {
						var pattern = new RegExp(/^(\d{4})[\/\-\.](0?[1-9]|1[012])[\/\-\.](0?[1-9]|[12][0-9]|3[01])$/);
						var match = pattern.exec(field.val());
						if (match == null)
						   return false;

						var year = match[1];
						var month = match[2]*1;
						var day = match[3]*1;
						var date = new Date(year, month - 1, day); // because months starts from 0.

						return (date.getFullYear() == year && date.getMonth() == (month - 1) && date.getDate() == day);
					},
					"alertText": "* Invalid date, must be in YYYY-MM-DD format"
					},
					"ipv4": {
						"regex": /^((([01]?[0-9]{1,2})|(2[0-4][0-9])|(25[0-5]))[.]){3}(([0-1]?[0-9]{1,2})|(2[0-4][0-9])|(25[0-5]))$/,
						"alertText": "* Invalid IP address"
					},
					"url": {
						"regex": /^(https?|ftp):\/\/(((([a-z]|\d|-|\.|_|~|[\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF])|(%[\da-f]{2})|[!\$&'\(\)\*\+,;=]|:)*@)?(((\d|[1-9]\d|1\d\d|2[0-4]\d|25[0-5])\.(\d|[1-9]\d|1\d\d|2[0-4]\d|25[0-5])\.(\d|[1-9]\d|1\d\d|2[0-4]\d|25[0-5])\.(\d|[1-9]\d|1\d\d|2[0-4]\d|25[0-5]))|((([a-z]|\d|[\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF])|(([a-z]|\d|[\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF])([a-z]|\d|-|\.|_|~|[\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF])*([a-z]|\d|[\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF])))\.)+(([a-z]|[\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF])|(([a-z]|[\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF])([a-z]|\d|-|\.|_|~|[\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF])*([a-z]|[\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF])))\.?)(:\d*)?)(\/((([a-z]|\d|-|\.|_|~|[\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF])|(%[\da-f]{2})|[!\$&'\(\)\*\+,;=]|:|@)+(\/(([a-z]|\d|-|\.|_|~|[\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF])|(%[\da-f]{2})|[!\$&'\(\)\*\+,;=]|:|@)*)*)?)?(\?((([a-z]|\d|-|\.|_|~|[\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF])|(%[\da-f]{2})|[!\$&'\(\)\*\+,;=]|:|@)|[\uE000-\uF8FF]|\/|\?)*)?(\#((([a-z]|\d|-|\.|_|~|[\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF])|(%[\da-f]{2})|[!\$&'\(\)\*\+,;=]|:|@)|\/|\?)*)?$/i,
						"alertText": "* Invalid URL"
					},
					"onlyNumberSp": {
						"regex": /^[0-9\ ]+$/,
						"alertText": "* Numbers only"
					},
					"zipcodeUS":{
						"regex": /[0-9]{5}-[0-9]{4}$/,
						"alertText": "* USA Zipcode Format : xxxxx or xxxxx-xxxx (x is a number)"
					},
					"onlyGUID":{
						"regex": /^[0-9a-fA-F]{8}-[0-9a-fA-F]{4}-[0-9a-fA-F]{4}-[0-9a-fA-F]{4}-[0-9a-fA-F]{12}$/,
						"alertText": "* Invalid GUID. E.g: 2c18c22d-5b4c-0ee3-e6cf-9143624a4857"
					},
					"customDate":{
						"regex": /(Jan|Feb|Mar|Apr|May|Jun|Jul|Aug|Sep|Oct|Nov|Dec)[\ \'](0?0[1-9]|[1-2][0-9]|3[01]),[\ \'](19[0-9]{2}|[2][0-9]{3}|[0-9]{2})$/,
						"alertText": "* Invalid date format"
					},
					"onlyLetterSp": {
						"regex": /^[a-zA-Z\ \']+$/,
						"alertText": "* Letters only"
					},
					"onlyRealNumbers": {
						"regex": /^(?=.*[1-9])\d*(?:\.\d{1,2})?$/,
						"alertText": "* Invalid value"
					},

					"price": {
						"regex": /^([0-9]+(?:[\.][0-9]*)?|\.[0-9]+)$/,
						"alertText": "* Invalid value"
					},


					"onlyLetterNumber": {
						"regex": /^[0-9a-zA-Z]+$/,
						"alertText": "* No special characters allowed"
					},
					"onlyCharacter": {
						"regex": /^[0-9a-zA-Z\ \']+$/,
						"alertText": "* No special characters allowed"
					},
					// --- CUSTOM RULES -- Those are specific to the demos, they can be removed or changed to your likings
					"ajaxUserCall": {
						"url": "ajaxValidateFieldUser",
						// you may want to pass extra data on the ajax call
						"extraData": "name=eric",
						"alertText": "* This user is already taken",
						"alertTextLoad": "* Validating, please wait"
					},
					"ajaxUserCallPhp": {
						"url": "phpajax/ajaxValidateFieldUser.php",
						// you may want to pass extra data on the ajax call
						"extraData": "name=eric",
						// if you provide an "alertTextOk", it will show as a green prompt when the field validates
						"alertTextOk": "* This username is available",
						"alertText": "* This user is already taken",
						"alertTextLoad": "* Validating, please wait"
					},
					"ajaxNameCall": {
						// remote json service location
						"url": "ajaxValidateFieldName",
						// error
						"alertText": "* This name is already taken",
						// if you provide an "alertTextOk", it will show as a green prompt when the field validates
						"alertTextOk": "* This name is available",
						// speaks by itself
						"alertTextLoad": "* Validating, please wait"
					},

					"validate_length_duns": {
						"alertText": "* DUNS should be a numeric 9 digit value"
					},

					"validate_length_phone": {
						"alertText": "* The maximum number of digits for the telephone number are 10. This includes area code."
					},

					"validate_product_ndc": {
						"alertText": "* Product NDC Code format: 12345-123, 12345-1234 or 1234-1234."
					},

					"validate_phone_ext": {
						"regex": /^[0-9][0-9]{2}[0-9]$/,
						"alertText": "* Phone Extension must be 4 digit number"
					},

					"validate_zipcode_countryUS": {
						"regex": /^[0-9][0-9]{3}[0-9]$/,
						"alertText": "* US Zipcode Format : xxxxx or xxxxx-xxxx (x is a number)"
					},

					"validate_length_fei": {
						"alertText": "* FEI# must be 7 or 10 digit number"
					},

					"validate_length_labeler_code":{
						"alertText": "* Labeler Code must be 4-5 digits in length. Please check your input!"
					},

					"pass_length":{
						"alertText": "* Password must be at least 8 characters in length."
					},

					"number_in_pass":{
						"alertText": "* Password must contain at least one digit."
					},

					"uppercase_in_pass":{
						"alertText": "* Password must contain at least one uppercase character."
					},

					"lowercase_in_pass":{
						"alertText": "* Password must contain at least one lowercase character."
					},

					"validate_password":{
						"alertText": "* Password and Confirm Password must be match. Please check your input!"
					},
					"validate_length_user_id":{
						"alertText": "* User ID must be less than 20 characters in length. Please check your input!"
					},
					//tls warning:homegrown not fielded
					"dateFormat":{
						"regex": /^\d{4}[\/\-](0?[1-9]|1[012])[\/\-](0?[1-9]|[12][0-9]|3[01])$|^(?:(?:(?:0?[13578]|1[02])(\/|-)31)|(?:(?:0?[1,3-9]|1[0-2])(\/|-)(?:29|30)))(\/|-)(?:[1-9]\d\d\d|\d[1-9]\d\d|\d\d[1-9]\d|\d\d\d[1-9])$|^(?:(?:0?[1-9]|1[0-2])(\/|-)(?:0?[1-9]|1\d|2[0-8]))(\/|-)(?:[1-9]\d\d\d|\d[1-9]\d\d|\d\d[1-9]\d|\d\d\d[1-9])$|^(0?2(\/|-)29)(\/|-)(?:(?:0[48]00|[13579][26]00|[2468][048]00)|(?:\d\d)?(?:0[48]|[2468][048]|[13579][26]))$/,
						"alertText": "* Invalid Date"
					},
					//tls warning:homegrown not fielded
					"dateTimeFormat": {
						"regex": /^\d{4}[\/\-](0?[1-9]|1[012])[\/\-](0?[1-9]|[12][0-9]|3[01])\s+(1[012]|0?[1-9]){1}:(0?[1-5]|[0-6][0-9]){1}:(0?[0-6]|[0-6][0-9]){1}\s+(am|pm|AM|PM){1}$|^(?:(?:(?:0?[13578]|1[02])(\/|-)31)|(?:(?:0?[1,3-9]|1[0-2])(\/|-)(?:29|30)))(\/|-)(?:[1-9]\d\d\d|\d[1-9]\d\d|\d\d[1-9]\d|\d\d\d[1-9])$|^((1[012]|0?[1-9]){1}\/(0?[1-9]|[12][0-9]|3[01]){1}\/\d{2,4}\s+(1[012]|0?[1-9]){1}:(0?[1-5]|[0-6][0-9]){1}:(0?[0-6]|[0-6][0-9]){1}\s+(am|pm|AM|PM){1})$/,
						"alertText": "* Invalid Date or Date Format",
						"alertText2": "Expected Format: ",
						"alertText3": "mm/dd/yyyy hh:mm:ss AM|PM or ",
						"alertText4": "yyyy-mm-dd hh:mm:ss AM|PM"

					},
					//phone for form medwatch
					"phoneformatmedwatch": {
						"regex": /^\(?([0-9]{3})\)?[-]?([0-9]{3})[-]?([0-9]{4})$/,
						// "alertText": "* Invalid Date or Date Format",
						"alertText": "Expected Format: xxx-xxx-xxxx",
					},
					//Validate fields Date for form medwatchs
					"Date3500": {
						"alertText": "Expected Format: mm/dd/yyyy",
					},
					"date_of_birth_3500a": {
						"alertText": "*  Invalid Year number !",
					},
					"age_select_year_3500": {
						"alertText": "* Invalid Year number 3->120",
					},
					"age_select_months_3500": {
						"alertText": "* Invalid Months number 1 -> 24",
					},
					"age_select_day_3500": {
						"alertText": "* Invalid Day number 1 -> 31",
					},
					"age_select_3500": {
						"alertText": "* Invalid select Age at Time of Event",
					},
					"age_select_3500_device_name": {
						"alertText": "*  Please do not use broad generic terms such as (catheter, valve, screw, etc..)",
					},
					"age_select_3500_procode": {
						"alertText": "*  Invalid a code that consists of three alpha characters",
					},












				};

			}
		};

		$.validationEngineLanguage.newLang();
})(jQuery);
