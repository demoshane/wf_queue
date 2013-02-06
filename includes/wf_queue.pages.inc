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
  //$headMarkup = "<tr><th>User name</th>";
  $test_headers['username'] = 'User name';

  // Get component names
  $componentNames = db_select('webform_component', 'comp')
                  ->fields('comp', array('name'))
                  ->condition('nid', $nid, '=')
                  ->execute()
                  ->fetchAll();

  // Build components as header
  foreach($componentNames as $header) {
    //$headMarkup .= '<th>'.$header->name.'</th>';
    $test_headers[] = $header->name;
  }
  $headers = array_merge($test_headers, array(
    'edit' => 'Edit',
    'delete' => 'Delete',
    'view' => 'View'
  ));

  //$markup = "";

  // Loop through submissions
  foreach ($submissions as $submission) {
    // Row markup
    //$markup .= "<tr>";
    // Get submission id
    $sid = $submission->sid;
    // Get uid for the submission
    $uid = $submission->uid;
    $user = user_load($uid);
    // Get components
    $result = $submission->data;
    // First row shall be the user
    // $markup .= '<td>' . l($user->name, 'user/' . $uid) . '</td>';

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
        // $markup .= "<td>" . ucfirst($component[0]) . "</td>";
      }
      else {
        $comp[] = ucfirst($component['value'][0]);
        // $markup .= "<td>" . ucfirst($component['value'][0]) . "</td>";
      }
    }
    $links = array(
      'edit' => l(t('Edit'), 'node/' . $nid . '/submission/' . $sid . '/edit?destination=node/' . $nid . '/manage-event'),
      'delete' => l(t('Delete'), 'node/' . $nid . '/submission/' . $sid . '/delete?destination=node/' . $nid . '/manage-event'),
      'view' => l(t('View'), 'node/' . $nid . '/submission/' . $sid),
    );
    $fields = array_merge($comp, $links);
    $test_subs['fields'] = array_merge($test_subs['fields'], $fields);
    $subs[] = $test_subs;
  }

  // Load queue
  $queue = db_query("SELECT sid FROM {webform_submitted_data} WHERE nid = :nid AND data = :data", array(":nid" => $nid, ":data" => "queue"))->fetchAll();

  // Get first one in the queue
  if (!empty($queue)) {
    $firstQueued = min($queue)->sid;
  }

  // Create link for easy access.
  if (!empty($firstQueued)) {
    $queuelink = l(t('View first submission in the queue'), 'node/' . $nid . '/submission/' . $firstQueued . '/edit?destination=node/' . $nid . '/manage-event');
  }

  // Users that have cancelled their participation
  // Check users that have also cancelled status submission(s).
  $userCancel = db_query("SELECT sid FROM {webform_submitted_data} WHERE data = :cancel AND nid = :nid", array(":cancel" => "cancel", ":nid" => $nid))->fetchAll();

  // Loop cancellations
  //$cancelMarkup = "";
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
      //$cancelMarkupTransfer = "";
      $userCancel = user_load($uid);
      // Build markup for each user
      //$cancelMarkupTransfer = '<div class="cancellation"><b>User: </b>' . $userCancel->name . ',<br/>has canceled and has the following other submissions:<br/>';
      $cancels[$userCancel->name] = _wf_queue_cancel_submissions($nid, $uid);
      //$cancelMarkup .= _wf_queue_cancel_submissions($nid, $uid, $cancelMarkupTransfer);
    }
  }
  //$cancelMarkup = "<h3>Canceled users:</h3><p>When managing cancellations, delete cancellation last.</p>" . $cancelMarkup;

  // Finalize the markup for the page
  /*
    $headMarkup .= "<th>Edit</th><th>Delete</th><th>View</th></tr>";
    $finalMarkup = '<table>' . $headMarkup . $markup . "</table>" . $queueMarkup . $cancelMarkup;
  */

  // Finish it!
  $form = array(
    '#suffix' => theme('wf_queue', array('headers' => $headers, 'submissions' => $subs, 'queue' => $queuelink, 'cancel' => $cancels)),
  );

  // Return built form
  return $form;
}

// This function gets submissions for user that has cancellations

//function _wf_queue_cancel_submissions($nid, $uid, $cancelMarkupTransfer) {
function _wf_queue_cancel_submissions($nid, $uid) {
  //$cancelMarkup = $cancelMarkupTransfer;
  // Get other submissions for canceled user
  //$otherSubmissions = db_query("SELECT sid FROM {webform_submissions} WHERE uid = :uid AND nid = :nid", array(":uid" => $uid, ":nid" => $nid))->fetchAll();
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

    //$cancelMarkup .= '<div style="width:200px; display:block; height: auto; padding: 10px; background-color: #eee; margin-left:20px; margin-top:10px; position:relative; left: -20px;">' . $username . ': <a href="/node/'.$nid.'/submission/'.$submissionData->sid.'">View</a> | <a href="/node/'.$nid.'/submission/'.$submissionData->sid. '/delete?destination=node/'.$nid.'/manage-event">Delete</a><br/></div>';
    $i++;
  }
  // $cancelMarkup .= "</div>";

  // $cancelMarkupTransfer = $cancelMarkup;
  // Return markup
  //return $cancelMarkupTransfer;
  return $return;
}