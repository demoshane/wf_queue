<table class="event-management-table">
<thead>
  <tr>
  <?php
  // Build headers
  foreach($variables['headers'] as $header) {
    print "<th>" . $header . "</th>";
  }
  ?>
  </tr>
</thead>
<tbody>
<?php
// Loop submission result data
foreach($variables['submissions'] as $submission) {
  print "<tr>";
  foreach($submission['fields'] as $field) {
    print "<td>" . $field . "</td>";
  }
  print "</tr>";
}
?>
</tbody>
</table>
<?php
// Build cancellation queue link and header for cancellations
print '<div class="queue-link">' . 
      $variables['queue'] . 
      '</div><h2 class="cancellations-header">' . 
      t('Cancellations') . 
      '</h2><p>' . 
      t('Notice: Delete cancellation last.') . 
      '</p>'
      ;
$submissions = array();

// Loop users that have cancellations
foreach ($variables['cancel'] as $name => $cancelUser) {
  // Build markup
  $uid = $cancelUser['uid'];
  print '<div class="submissions-container"><div class="cancel-user-subheader"><strong>' . 
        t('User ') . 
        l($name, 'user/' . $uid) . ',</strong></div><div class="cancel-submissions">' . 
        ' ' . t('has canceled and has the following submissions:') . 
        '<br/>'
        ;
  $submissions = $cancelUser['submissions'];

  // Loop all submissions for user that has canceled their participation. For easy editing and grouping for admins.
  foreach ($cancelUser['submissions'] as $sub => $submissionData) {
    $sid = $submissionData['sid'];
    $nid = $submissionData['nid'];
    $action = $submissionData['action'];
    // Build markup
    print '<div class="submission-result"><div class="submission-action">' . 
          t('@action', array('@action' => ucfirst($action))) . 
          ':</div><div class="submission-tools"> ' . 
          l(t('Delete'), 'node/' . $nid . '/submission/' . $sid . '/delete', array('query' => drupal_get_destination())) . 
          ' | ' . 
          l(t('View'), 'node/' . $nid . '/submission/' . $sid) . '</div></div>'
          ;
  }
  print '</div></div>';
}
?>