<?php
/**
 * @file
 */

/**
 * page callback for /fields_json
 */
function ldh_fields_json(){
  $flds = field_info_instances();
  //$fldsjs = drupal_json_encode($flds);
  drupal_json_output($flds);
  //exit;
}
