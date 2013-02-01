<?php
/**
 * @file
 * wf_queue.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function wf_queue_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'display_events';
  $view->description = 'This view displays events on your site';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Display events';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Events';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['distinct'] = TRUE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'title' => 'title',
    'body' => 'body',
    'field_end_date' => 'field_end_date',
    'webform_submission_count_node' => 'webform_submission_count_node',
    'field_participants' => 'field_participants',
  );
  $handler->display->display_options['style_options']['default'] = 'field_end_date';
  $handler->display->display_options['style_options']['info'] = array(
    'title' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'body' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_end_date' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'webform_submission_count_node' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_participants' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['style_options']['sticky'] = TRUE;
  /* Relationship: Content: Webform submission */
  $handler->display->display_options['relationships']['webform_submission']['id'] = 'webform_submission';
  $handler->display->display_options['relationships']['webform_submission']['table'] = 'node';
  $handler->display->display_options['relationships']['webform_submission']['field'] = 'webform_submission';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = 'Event name';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: Description */
  $handler->display->display_options['fields']['field_description']['id'] = 'field_description';
  $handler->display->display_options['fields']['field_description']['table'] = 'field_data_field_description';
  $handler->display->display_options['fields']['field_description']['field'] = 'field_description';
  $handler->display->display_options['fields']['field_description']['label'] = 'Short description';
  $handler->display->display_options['fields']['field_description']['element_type'] = '0';
  $handler->display->display_options['fields']['field_description']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['field_description']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_description']['type'] = 'text_plain';
  $handler->display->display_options['fields']['field_description']['field_api_classes'] = TRUE;
  /* Field: Content: Due date */
  $handler->display->display_options['fields']['field_end_date']['id'] = 'field_end_date';
  $handler->display->display_options['fields']['field_end_date']['table'] = 'field_data_field_end_date';
  $handler->display->display_options['fields']['field_end_date']['field'] = 'field_end_date';
  $handler->display->display_options['fields']['field_end_date']['label'] = 'Signup ends';
  $handler->display->display_options['fields']['field_end_date']['element_type'] = '0';
  $handler->display->display_options['fields']['field_end_date']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['field_end_date']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_end_date']['settings'] = array(
    'format_type' => 'short',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  $handler->display->display_options['fields']['field_end_date']['field_api_classes'] = TRUE;
  /* Field: Webform: Webform submission count */
  $handler->display->display_options['fields']['webform_submission_count_node']['id'] = 'webform_submission_count_node';
  $handler->display->display_options['fields']['webform_submission_count_node']['table'] = 'node';
  $handler->display->display_options['fields']['webform_submission_count_node']['field'] = 'webform_submission_count_node';
  $handler->display->display_options['fields']['webform_submission_count_node']['relationship'] = 'webform_submission';
  $handler->display->display_options['fields']['webform_submission_count_node']['label'] = 'Participants';
  $handler->display->display_options['fields']['webform_submission_count_node']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['webform_submission_count_node']['alter']['text'] = '[webform_submission_count_node]';
  /* Field: Content: Participants */
  $handler->display->display_options['fields']['field_participants']['id'] = 'field_participants';
  $handler->display->display_options['fields']['field_participants']['table'] = 'field_data_field_participants';
  $handler->display->display_options['fields']['field_participants']['field'] = 'field_participants';
  $handler->display->display_options['fields']['field_participants']['label'] = 'Max. participants';
  $handler->display->display_options['fields']['field_participants']['element_type'] = '0';
  $handler->display->display_options['fields']['field_participants']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['field_participants']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_participants']['type'] = 'number_unformatted';
  $handler->display->display_options['fields']['field_participants']['settings'] = array(
    'thousand_separator' => '',
    'prefix_suffix' => 0,
  );
  $handler->display->display_options['fields']['field_participants']['field_api_classes'] = TRUE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'event' => 'event',
  );
  /* Filter criterion: Content: Due date (field_end_date) */
  $handler->display->display_options['filters']['field_end_date_value']['id'] = 'field_end_date_value';
  $handler->display->display_options['filters']['field_end_date_value']['table'] = 'field_data_field_end_date';
  $handler->display->display_options['filters']['field_end_date_value']['field'] = 'field_end_date_value';
  $handler->display->display_options['filters']['field_end_date_value']['operator'] = '>=';
  $handler->display->display_options['filters']['field_end_date_value']['expose']['operator_id'] = 'field_end_date_value_op';
  $handler->display->display_options['filters']['field_end_date_value']['expose']['label'] = 'Due date (field_end_date)';
  $handler->display->display_options['filters']['field_end_date_value']['expose']['operator'] = 'field_end_date_value_op';
  $handler->display->display_options['filters']['field_end_date_value']['expose']['identifier'] = 'field_end_date_value';
  $handler->display->display_options['filters']['field_end_date_value']['default_date'] = 'now -2 day';
  $handler->display->display_options['filters']['field_end_date_value']['year_range'] = '-0:+3';

  /* Display: Event listing */
  $handler = $view->new_display('page', 'Event listing', 'events_listing_page');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['path'] = 'events';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Events';
  $handler->display->display_options['menu']['name'] = 'main-menu';
  $translatables['display_events'] = array(
    t('Master'),
    t('Events'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('« first'),
    t('‹ previous'),
    t('next ›'),
    t('last »'),
    t('Webform Submission'),
    t('Event name'),
    t('Short description'),
    t('Signup ends'),
    t('Participants'),
    t('[webform_submission_count_node]'),
    t('Max. participants'),
    t('Due date (field_end_date)'),
    t('Event listing'),
  );
  $export['display_events'] = $view;

  return $export;
}
