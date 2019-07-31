(function ($) {

Drupal.behaviors.password_reset = {
  attach: function() {
    var f = $('.password-reset-question-set');
    $('#edit-password-reset-first-question', f).attr('disabled', 'disabled');
    $('#edit-password-reset-second-question', f).attr('disabled', 'disabled');
    $('#edit-password-reset-third-question', f).attr('disabled', 'disabled');
    var a = $('.form-item-password-reset-first-answer', f)
      .hide()
      .after('<div class="password-reset-change">' + Drupal.t('Your answer for the chosen question has <strong>already</strong> been saved. <a href="#">Click here</a> if you would like to change the question or your answer.') + '</div>')
      .next('.password-reset-change')
      .children('a')
      .click(function(e) {
        $('#edit-password-reset-first-question', f).removeAttr('disabled');
        $('.form-item-password-reset-first-answer', f).show('slow');
        $(this).parent().hide();
        e.preventDefault();
      });
      
    var b = $('.form-item-password-reset-second-answer', f)
      .hide()
      .after('<div class="password-reset-change">' + Drupal.t('Your answer for the chosen question has <strong>already</strong> been saved. <a href="#">Click here</a> if you would like to change the question or your answer.') + '</div>')
      .next('.password-reset-change')
      .children('a')
      .click(function(e) {
        $('#edit-password-reset-second-question', f).removeAttr('disabled');
        $('.form-item-password-reset-second-answer', f).show('slow');
        $(this).parent().hide();
        e.preventDefault();
      });
      
    var c = $('.form-item-password-reset-third-answer', f)
      .hide()
      .after('<div class="password-reset-change">' + Drupal.t('Your answer for the chosen question has <strong>already</strong> been saved. <a href="#">Click here</a> if you would like to change the question or your answer.') + '</div>')
      .next('.password-reset-change')
      .children('a')
      .click(function(e) {
        $('#edit-password-reset-third-question', f).removeAttr('disabled');
        $('.form-item-password-reset-third-answer', f).show('slow');
        $(this).parent().hide();
        e.preventDefault();
      });
    
    // If there's an answer validation error, then unhide the answer field.
    if (Drupal.settings.password_reset) {
      $(a).click();
      $(b).click();
      $(c).click();
    }

    $('#edit-password-confirm-pass1').addClass('validate[required, funcCall[check_pass_digit], funcCall[check_length_pass], funcCall[check_pass_uppercase], funcCall[check_pass_lowercase]]'); 
    $('#edit-password-confirm-pass2').addClass('validate[required, funcCall[check_reset_password]]');


    // Select method reset password
    $('#wrap-security-questions').hide();
   
    $('#send-email').click(function(){
      var uid = $('#hidden-uid').val();      
      location.href = Drupal.settings.basePath+'send-reset-link?uid='+uid;
      $('.wrapper-select-option').hide();
    });

    $('#answer-question').click(function(){
      $('.wrapper-select-option').remove();
      $('#wrap-security-questions').show();
    })
    
  }
};

  
}(jQuery));
