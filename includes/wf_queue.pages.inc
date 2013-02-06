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
// DELETE THESE
/**
 * Fetch a specified submission for a webform node.
 */
// function webform_get_submission($nid, $sid, $reset = FALSE) {

// END DELETE

function wf_queue_form($form, $form_state, $node) {
  // Load the Webform module functions for our use.
  module_load_include('inc', 'webform', 'includes/webform.report');
  module_load_include('inc', 'webform', 'includes/webform.submissions');

  // Set nid
  $nid = $node->nid;
  // Load submissions
  $submissions = webform_get_submissions($nid);
  // Initiate header markup
  $headMarkup = "<tr><th>User name</th>";
  // Get component names
  $componentNames = db_query("SELECT name FROM {webform_component} WHERE nid = :nid", array(":nid" => $nid))->fetchAll();

  // Build components as header
  foreach($componentNames as $header) {
    $headMarkup .= '<th>'.$header->name.'</th>';
  }
  $markup = "";

  // Loop through submissions
  foreach ($submissions as $submission) {
    // Row markup
    $markup .= "<tr>";
    // Get submission id
    $sid = $submission->sid;
    // Get uid for the submission
    $uid = $submission->uid;
    $user = user_load($uid);
    // Get components
    $result = $submission->data;
    // First row shall be the user
    $markup .= '<td><a href="/user/'.$uid.'">'.$user->name.'</a></td>';

    // Loop through components
    foreach ($result as $component) {
      $markup .= "<td>" . $component[0] . "</td>";
    }

    // Tools
    $markup .= '
    <td><a href="/node/'.$nid.'/submission/'.$sid.'/edit?destination=node/'.$nid.'/manage-event">edit</a></td>
    <td><a href="/node/'.$nid.'/submission/'.$sid.'/delete?destination=node/'.$nid.'/manage-event">delete</a></td>
    <td><a href="/node/'.$nid.'/submission/'.$sid.'">view</a></td>
    </tr>
    ';
  }

  // Load queue
  $queue = db_query("SELECT sid FROM {webform_submitted_data} WHERE nid = :nid AND data = :data", array(":nid" => $nid, ":data" => "queue"))->fetchAll();

  // Get first one in the queue
  if (!empty($queue)) {
    $firstQueued = min($queue)->sid;
  }

  // Create link for easy access.
  if (!empty($firstQueued)) {
    $queueMarkup = '<br/><a href="submission/'.$firstQueued.'/edit?destination=node/'.$nid.'/manage-event">View first submission in the queue</a><br/><br/>';
  }

  // Users that have cancelled their participation
  // Check users that have also cancelled status submission(s).
  $userCancel = db_query("SELECT sid FROM {webform_submitted_data} WHERE data = :cancel AND nid = :nid", array(":cancel" => "cancel", ":nid" => $nid))->fetchAll();

  // Loop cancellations
  $cancelMarkup = "";
  foreach ($submissions as $submission) {
    $status = $submission->data[99];
    $uid = $submission->uid;
    if ($status[0] == "cancel") {
      $cancelMarkupTransfer = "";
      $userCancel = user_load($uid);
      // Build markup for each user
      $cancelMarkupTransfer = "<br/><b>User: </b>" . $userCancel->name . ",<br/>has canceled and has the following other submissions:<br/>";
      $cancelMarkup .= _wf_queue_cancel_submissions($nid, $uid, $cancelMarkupTransfer);
    }
  }
  $cancelMarkup = "<h3>Canceled users:</h3>" . $cancelMarkup;

  // Finalize the markup for the page
  $headMarkup .= "<th>Edit</th><th>Delete</th><th>View</th></tr>";
  $finalMarkup = '<table>' . $headMarkup . $markup . "</table>" . $queueMarkup . $cancelMarkup;

  // Finish it!
  $form = array(
    '#suffix' => $finalMarkup,
  );

  // Return built form
  return $form;
}

// This function gets submissions for user that has cancellations

function _wf_queue_cancel_submissions($nid, $uid, $cancelMarkupTransfer) {
  $cancelMarkup = $cancelMarkupTransfer;
  // Get other submissions for canceled user
  $otherSubmissions = db_query("SELECT sid FROM {webform_submissions} WHERE uid = :uid AND nid = :nid", array(":uid" => $uid, ":nid" => $nid))->fetchAll();

  // Loop them
  foreach ($otherSubmissions as $submissionData) {
    // Load submission data
    $data = webform_get_submission($nid, $submissionData->sid);
    // Build markup
    $cancelMarkup .= '<a href="/node/'.$nid.'/submission/'.$submissionData->sid.'">View</a>: ' . ucfirst($data->data[99][0]) . '<br/>';
  }

  $cancelMarkupTransfer = $cancelMarkup;
  // Return markup
  return $cancelMarkupTransfer;
}