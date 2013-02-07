<?php
/**
 * @file
 *   Event management page.
 *
 * @ingroup wf_queue
 */

/**
 * Implements hook_form();
 */
function wf_queue_form($form, $form_state, $node) {
  $headers = array();
  $subs = array();

  // Load the Webform module functions for our use.
  module_load_include('inc', 'webform', 'includes/webform.report');
  module_load_include('inc', 'webform', 'includes/webform.submissions');

  // Set nid
  $nid = $node->nid;
  // Load submissions
  $submissions = webform_get_submissions($nid);
  // Initiate header markup
  $test_headers['username'] = 'User name';

  // Get component names
  $componentNames = db_select('webform_component', 'comp')
                  ->fields('comp', array('name'))
                  ->condition('nid', $nid, '=')
                  ->execute()
                  ->fetchAll();

  // Build components as header
  foreach($componentNames as $header) {
    $test_headers[] = $header->name;
  }
  $headers = array_merge($test_headers, array(
    'edit' => 'Edit',
    'delete' => 'Delete',
    'view' => 'View'
  ));

  // Loop through submissions
  foreach ($submissions as $submission) {
    // Get submission id
    $sid = $submission->sid;
    // Get uid for the submission
    $uid = $submission->uid;
    $user = user_load($uid);
    // Get components
    $result = $submission->data;

    $test_subs = array(
      'uid' => $uid,
      'nid' => $nid,
      'sid' => $submission->sid,
      'fields' => array(
        'username' => $user->name
      )
    );

    $comp = array();
    // Loop through components
    foreach ($result as $component) {
      if (isset($component[0])){
        $comp[] = ucfirst($component[0]);
      }
      else {
        $comp[] = ucfirst($component['value'][0]);
      }
    }
    $links = array(
      'edit' => l(t('Edit'), 'node/' . $nid . '/submission/' . $sid . '/edit', array('query' => drupal_get_destination())),
      'delete' => l(t('Delete'), 'node/' . $nid . '/submission/' . $sid . '/delete', array('query' => drupal_get_destination())),
      'view' => l(t('View'), 'node/' . $nid . '/submission/' . $sid),
    );
    $fields = array_merge($comp, $links);
    $test_subs['fields'] = array_merge($test_subs['fields'], $fields);
    $subs[] = $test_subs;
  }

  // Load queue
  $queue = db_select('webform_submitted_data', 'subs')
                ->fields('subs', array('sid'))
                ->condition('data', 'queue', '=')
                ->condition('nid', $nid, '=')
                ->execute()
                ->fetchAll();

  // Get first one in the queue
  if (!empty($queue)) {
    $firstQueued = min($queue)->sid;
  }

  // Create link for easy access.
  $queuelink = "";
  if (!empty($firstQueued)) {
    $queuelink = l(t('View first submission in the queue'), 'node/' . $nid . '/submission/' . $firstQueued . '/edit',  array('query' => drupal_get_destination()));
  }

  // Users that have cancelled their participation
  // Check users that have also cancelled status submission(s).
  $userCancel = db_select('webform_submitted_data', 'subs')
                    ->fields('subs', array('sid'))
                    ->condition('data', 'cancel', '=')
                    ->condition('nid', $nid, '=')
                    ->execute()
                    ->fetchAll();

  // Loop cancellations
  $cancels = array();
  foreach ($submissions as $submission) {
    $status = $submission->data[99];
    $uid = $submission->uid;
    if (isset($status[0])){
      $state = $status[0];
    }
    else {
      $state = $status['value'][0];
    }
    if ($state == "cancel") {
      $userCancel = user_load($uid);
      $cancels[$userCancel->name]['submissions'] = _wf_queue_cancel_submissions($nid, $uid);
      $cancels[$userCancel->name]['uid'] = $uid;
    }
  }

  // Finish it!
  $form = array(
    '#suffix' => theme('wf_queue', array('headers' => $headers, 'submissions' => $subs, 'queue' => $queuelink, 'cancel' => $cancels)),
  );

  // Return built form
  return $form;
}

// This custom function gets submissions for user that has cancellations
function _wf_queue_cancel_submissions($nid, $uid) {
  // Get other submissions for canceled user
  $return = array();
  $otherSubmissions = db_select('webform_submissions', 'subs')
                    ->fields('subs', array('sid'))
                    ->condition('uid', $uid, '=')
                    ->condition('nid', $nid, '=')
                    ->execute()
                    ->fetchAll();

  // Loop them
  $i = 0;
  foreach ($otherSubmissions as $submissionData) {
    // Load submission data
    $data = webform_get_submission($nid, $submissionData->sid);
    // Build markup
    if (isset($data->data[99][0])) {
      $return[$i]['action'] = $data->data[99][0];
    }
    else {
      $return[$i]['action'] = $data->data[99]['value'][0];
    }
    $return[$i]['nid'] = $nid;
    $return[$i]['sid'] = $submissionData->sid;
    $i++;
  }
  return $return;
}