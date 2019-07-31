jQuery(document).ready(function ($) {
 /*Side Chat*/
  // jQuery('.toggle-menu').jPushMenu();
  /*Chat*/
    
    jQuery('.side-chat .content .contacts li a').click(function(e){
      var user = jQuery('<span>' + jQuery(this).html() + '</span>');
      user.find('i').remove();
 
      jQuery('#chat-box').fadeIn();

      jQuery('#chat-box .header span').html(user.html());
      jQuery("#chat-box .nano").nanoScroller();
      jQuery("#chat-box .nano").nanoScroller({ scroll: 'top' });

      e.preventDefault();
    });
    
    jQuery('#chat-box .header .close').click(function(r){
      var h = jQuery(this).parents(".header");
      var p = h.parent();
      
      p.fadeOut();
      r.preventDefault();
    });
    
    function addText(input){
      var message = input.val();
      var chat = input.parents('#chat-box').find('.content .conversation');
      
      if(message != ''){
       input.val('');
       chat.append('<li class="text-right"><p>' + message + '</p></li>');
       jQuery("#chat-box .nano .content").animate({ scrollTop: jQuery("#chat-box .nano .content .conversation").height() }, 1000);
      }
    }
    
    
    jQuery('.chat-input .input-group button').click(function(){
      addText( jQuery(this).parents('.input-group').find('input'));
    });
    
    jQuery('.chat-input .input-group input').keypress(function(e){
      if(e.which == 13) {
         addText(jQuery(this));
      }
    });
    
    jQuery(document).click(function(){
      jQuery('#chat-box').fadeOut();
    
    });

});