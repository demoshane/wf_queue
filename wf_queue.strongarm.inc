<?php
/**
 * @file
 * wf_queue.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function wf_queue_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'webform_node_types';
  $strongarm->value = array(
    0 => 'webform',
    1 => 'event',
  );
  $export['webform_node_types'] = $strongarm;

  return $export;
}
