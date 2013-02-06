<?php
echo "<pre>";
print_r($variables);
echo "</pre>";
?>

<table>
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
?>
</tbody>



</table>