<?php


/*
 * all people that dont have a category (field person_people) get it set
 */
// provide just the bundle name
$l = new LdhEfr('person');
// no extra conditions
$ids = $l->getAllIDs();

foreach($ids as $id) {
  // get an entity_metadata_wrapper
  $w = ldh_nw($id);
  if (! $w->field_person_people->value()) {
   // the field allows multiple vals so youo have to provide an array here
   $w->field_person_people->set(array(202));
   $w->save();
  }
}

