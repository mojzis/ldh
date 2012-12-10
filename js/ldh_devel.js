Drupal.behaviors.ldh = {
  attach: function (context, settings) {
    jQuery('.ldh-functions span', context).click( function(event) { FcInsert(event); });
  }
};

function FcInsert(event){
  event.preventDefault();
  clickedEl = jQuery(event.target);
  var code = jQuery('#edit-code');
  code.val(code.val() + clickedEl.html());
  //alert();
  //clickedEl.next().toggle();
}
