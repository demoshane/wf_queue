<?php
/**
 * @file
 * wf_queue.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function wf_queue_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function wf_queue_views_api() {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function wf_queue_node_info() {
  $items = array(
    'event' => array(
      'name' => t('Event'),
      'base' => 'node_content',
      'description' => t('Event with webform signups'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
