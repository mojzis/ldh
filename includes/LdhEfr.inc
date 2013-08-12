<?php
/**
 * @file
 * Lazy developers helper -LdhEfr Class. Reduces typing when using the EFQ.
 */
 /**
 * $akce = 19;
 * $r = ldh_efq('ucast','ucast')->fieldCondition('field_uc_akce', 'target_id', $akce)
 *   ->execute();
 * dpm($r);
 * $l = new LdhEfr('ucast','ucast');
 * $l->fieldCo('field_uc_akce',$akce,'=','target_id');
 * dpm($l->getResult());
 * dpm($l->getAllIDs());
 * dpm($l->getOneID());
 *
 * @todo make sure execute() is only ran once - record it somewhere
 * @todo think about a "no results behaviour" - now its only false
 */
class LdhEfr{
  var $efq;
  var $result;
  public $type; // should be protected ?
  public $bundle;
  protected $noBundleTypes = array('user');

  function __construct($bundle,$type = null) {
    $this->efq = new EntityFieldQuery();
    // if type null, try to find it, otherwise throw an exceptional exception
    if (empty($type)) {
      $type = 'node';
    }
    $this->type = $type;
    $this->bundle = $bundle;
    $this->efq->entityCondition('entity_type', $this->type);
    if(! in_array($this->type, $this->noBundleTypes) && $this->bundle != 'no_bundle_cond') {
      $this->efq->entityCondition('bundle', $this->bundle);
    }
  }

  public function addTag($tag) {
    return $this->efq->addTag($tag);
  }

  public function fieldCo($fieldname, $val, $op = null, $colname = null) {
    // find the column name for us 'column name to be determined from metadata'
    if(empty($op))
      $op = "=";
    if (empty($colname)) {
      $colname = ldh_colname_field($fieldname);
    }
    $this->efq->fieldCondition($fieldname, $colname , $val, $op);
    return $this;
  }

  public function propCoA($filter) {
    $op = (isset($filter['op'])) ? $filter['op'] : NULL ;
    $this->efq->propertyCondition($filter['column'], $filter['value'], $op );
  }
  public function propCo($column, $value, $operator = NULL) {
    $this->efq->propertyCondition($column, $value, $operator );
  }

  public function getResult() {
    $this->result = $this->efq->execute();
    if ( $this->result && isset($this->result[$this->type]) && $this->result[$this->type]) {
      return $this->result[$this->type];
    } else {
      return false;
    }
  }

  public function dpm($message = null) {
    // TODO: add some generic text in case message is null
    dpm($this->getResult(), $message);
  }

  public function debug() {
    dpm($this->efq);
    return $this;
  }

  public function getAllIDs() {
    $result = $this->getResult();
    if ($result) {
      return array_keys($result);
    } else {
      return false;
    }
  }

  public function getEntities() {
    $ids = $this->getAllIDs();
    if ($ids) {
      return entity_load($this->type, $ids);
    } else {
      return false;
    }
  }

  public function getWrappers() {
    $ents = $this->getEntities();
    if ($ents) {
      foreach($ents as $ent) {
        $out[] = entity_metadata_wrapper($this->type, $ent);
      }
      return $out;
    } else {
      return false;
    }
  }


  public function getOneID() {
    $ids = $this->getAllIDs();
    if ($ids) {
      return end($ids);
    } else {
      return false;
    }

  }

  public function getOneWr() {
    $id = $this->getOneID();
    if ($id) {
      return ldh_ew($id, $this->type);
    } else {
      return false;
    }
  }

  public function getCount() {
    $this->efq->count();
    return $this->efq->execute();
  }

  public function limitCount($count) {
    $this->efq->range(NULL,$count);
  }
}

