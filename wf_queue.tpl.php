<table class="event-management-table">
<thead><tr>
<?php
// Build headers
foreach($variables['headers'] as $header) {
  echo "<th>" . $header . "</th>";
}
?>
</tr></thead>
<tbody>
<?php
// Loop submission result data
foreach($variables['submissions'] as $submission) {
  echo "<tr>";
  foreach($submission['fields'] as $field) {
    echo "<td>" . $field . "</td>";
  }
  echo "</tr>";
}
?>
</tbody>
</table>
<?php
// Build cancellation queue link and header for cancellations
echo '<div class="queue-link">' . 
     $variables['queue'] . 
     '</div>' . 
     t('<h2 class="cancellations-header">Cancellations</h2>')
     ;
$submissions = array();

// Loop users that have cancellations
foreach ($variables['cancel'] as $cancelUser) {
  $uid = $cancelUser['uid'];
  $user = user_load($uid);
  // Build markup
  echo '<div class="submissions-container"><div class="cancel-user-subheader"><b>' . 
       t('User ') . 
       l($user->name, 'user/' . $uid) . ',</b></div><div class="cancel-submissions">' . 
       ' has canceled and has the following submissions:'
       ;
  $submissions = $cancelUser['submissions'];

  // Loop all submissions for user that has canceled their participation. For easy editing and grouping for admins.
  foreach ($cancelUser['submissions'] as $sub => $submissionData) {
      $sid = $submissionData['sid'];
      $nid = $submissionData['nid'];
      $action = $submissionData['action'];
      // Build markup
      echo '<div class="submission-result"><div class="submission-action">' . 
            t(ucfirst($action)) . 
            ':</div><div class="submission-tools"> ' . 
            l(t('Delete'), 'node/' . $nid . '/submission/' . $sid . '/delete?destination=node/' . $nid . '/manage-event') . 
            ' | ' . 
            l(t('View'), 'node/' . $nid . '/submission/' . $sid) . '</div></div>'
            ;
  }
  echo '</div></div>';
}
?>