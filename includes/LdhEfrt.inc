<?php
/**
 * @file
 * Lazy developers helper -LdhEfrt Class. Reduces typing when using the EFQ. Helper for rare cases when there is no bundle.
 */

class LdhEfrt extends LdhEfr {
  function __construct($type){
    $this->efq = new EntityFieldQuery();
    $this->type = $type;
    $this->efq->entityCondition('entity_type', $this->type);
  }
}
