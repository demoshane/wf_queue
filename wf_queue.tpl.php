<table class="event-management-table">
<thead><tr>
<?php
foreach($variables['headers'] as $header) {
  echo "<th>" . $header . "</th>";
}
?>
</tr></thead>
<tbody>
<?php
foreach($variables['submissions'] as $submission) {
  echo "<tr>";
  foreach($submission['fields'] as $field) {
    echo "<td>" . $field . "</td>";
  }
  echo "</tr>";
}
dsm($variables);
?>
</tbody>
</table>
<?php
echo $variables['queue'] . '<br/><br/>' . t('<h2 class="cancellations-header">Cancellations</h2>');
$submissions = array();
foreach ($variables['cancel'] as $cancelUser) {
  $uid = $cancelUser['uid'];
  $user = user_load($uid);
  echo '<div class="cancel-user-subheader"><b>' . t('User ') . l($user->name, 'user/' . $uid) . ',</b></div><div class="cancel-submissions"><br/>' . ' has canceled and has the following submissions:<br/>';
  $submissions = $cancelUser['submissions'];
  foreach ($cancelUser['submissions'] as $sub => $submissionData) {
      $sid = $submissionData['sid'];
      $nid = $submissionData['nid'];
      $action = $submissionData['action'];
      echo '<div class="submission-result">' . 
            t(ucfirst($action)) . 
            ': ' . 
            l(t('Delete'), 'node/' . $nid . '/submission/' . $sid . '/delete?destination=node/' . $nid . '/manage-event') . 
            ' | ' . 
            l(t('View'), 'node/' . $nid . '/submission/' . $sid) . '</div>'
            ;
    
  }
  echo '</div><br/>';
}

?>