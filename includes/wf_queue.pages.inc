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
  // Load the Webform module functions for our use.
  // module_load_include('inc', 'webform', 'includes/webform.report');
  // module_load_include('inc', 'webform', 'includes/webform.submissions');

  // Build the form
  $nid = $node->nid;
  // Get submissions for this node
  $submissions = array();
  $submissions = db_query("SELECT DISTINCT sid FROM {webform_submitted_data} WHERE nid = :nid", array(":nid" => $nid))->fetchAll();
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
  foreach ($submissions as $sid) {
    // Row markup
    $markup .= "<tr>";
    // Get submission id
    $sid = $sid->sid;
    // Get user for the submission
    $uid = db_query("SELECT uid FROM {webform_submissions} WHERE sid = :sid", array(":sid" => $sid))->fetchAll();
    $uid = $uid[0]->uid;
    $user = user_load($uid);
    // Get components
    $result = db_query("SELECT * FROM {webform_submitted_data} WHERE sid = :sid", array(":sid" => $sid))->fetchAll();
    // First row shall be the user
    $markup .= '<td><a href="/user/'.$uid.'">'.$user->name.'</a></td>';
    
    // Loop through components
    foreach ($result as $component) {
      // Add component to markup
      $markup .= "<td>";
      $componentName = db_query("SELECT name FROM {webform_component} WHERE cid = :cid AND nid = :nid", array(":cid" => $component->cid, ":nid" => $node->nid))->fetchAll();
      // Get submitted value
      $component = $component->data;
      $markup .= $component;
      $markup .= "</td>";
    }
    
    // Tools
    $markup .= '
    <td><a href="/node/'.$nid.'/submission/'.$sid.'/edit?destination=node/'.$nid.'/manage-event">edit</a></td>
    <td><a href="/node/'.$nid.'/submission/'.$sid.'/delete?destination=node/'.$nid.'/manage-event">delete</a></td>
    <td><a href="/node/'.$nid.'/submission/'.$sid.'">view</a></td>
    </tr>
    ';
  }
  
  // Finalize the markup
  $headMarkup .= "<th>Edit</th><th>Delete</th><th>View</th></tr>";
  $finalMarkup = '<table>';
  $finalMarkup .= $headMarkup;
  $finalMarkup .= $markup;
  $finalMarkup .= "</table>";
  
  // Who is first in the queue?
  $firstQueuedSid = db_query("SELECT sid FROM {webform_submitted_data} WHERE nid = :nid AND data = :data", array(":nid" => $nid, ":data" => "queue"))->fetchAll();
  $firstQueued = array();
  // Get first one
  if (!empty($firstQueuedSid)) {
    $firstQueued = min($firstQueuedSid);
    $firstQueued = $firstQueued->sid;
  }
  // Notify moderator and provide link to first in queue aka the one with lowest sid and status queue.
  if (!empty($firstQueued)) {
    $finalMarkup .= '<br/><a href="submission/'.$firstQueued.'/edit">View first submission in the queue</a>';
  }
  
  // Output it
  $form = array(
    '#suffix' => $finalMarkup,
  );

  return $form;
}
