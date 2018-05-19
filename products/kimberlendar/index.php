<html>
<head>
 <title>KimberleNdar - developed by MD Enterprises</title>
</head>
<body style="background-color: lightpink;">
<table width="300">
<tr>
<td colspan="2" align="center">
<span style="color: white; font-family: Arial; font-size: 180%; font-weight: bold;">KimberleNdar</span><br />
<span style="color: white; font-family: Times; font-size: 80%; font-style: italic;">developed by MD Enterprises</span>
</td>
</tr>

<?php 
function getisomonday($year, $week) {
   $year = min ($year, 2038); $year = max($year, 1970);
   $week = min ($week, 53); $week = max ($week, 1);
   $monday = mktime(1,1,1,1,7*$week, $year);
   while(strftime('%V', $monday)!=$week) {
        $monday -= 60*60*24*7;
   }
   while(strftime('%u', $monday)!=1) {
        $monday -= 60*60*24;
   }
   return $monday;
}

function calc_due_date($date, $interval, $add, $return_date_format='Y-m-d') {
    $date = strtotime($date);
    if ($date != -1) {
       $date = getdate($date);
       switch(strtolower($interval)) {
           case 'month' : $date['mon']  += $add; break;
           case 'day'   : $date['mday'] += $add; break;
           default      : $date['year'] += $add;
       }
       return( date($return_date_format, mktime(0,0,0,$date['mon'],$date['mday'],$date['year'])));
    } else {
       return(false);
    }
}

function week_of_year($nDay, $nMonth, $nYear) {
    $date = getDate(mktime(9,0,0,$nMonth, $nDay, $nYear));
    $weeknr = floor(($date["yday"]+1)/7)+1;
    $weeknr %= 52;
    return $weeknr;
}

if (isset($_GET['verzonden'])) {
  $dag = $_GET['dag'];
  $maand = $_GET['maand'];
  $jaar = $_GET['jaar'];
  $plusweken = $_GET['plusweken'];
  $plusdagen = $plusweken*7;
  
  $startweek = week_of_year($dag, $maand, $jaar);
  $eind_datum = calc_due_date($date, 'day', $plusdagen);
  $eindweek = week_of_year(substr($eind_datum, 8, 2),substr($eind_datum, 5, 2),substr($eind_datum, 0,4));
  // print substr($eind_datum, 8, 2).substr($eind_datum, 5, 2).substr($eind_datum, 0,4);

  // print week_of_year("20","1","2005");
  // echo strtotime("+1 week");
  //print "isomonday ".getisomonday("2005", "03");
  // $date= '2004-03-20';
  $date = $jaar."-".$maand."-".$dag;
  // print_r(getdate($date));
  $due_date = calc_due_date($date, 'month', 3);
  // print "due date for ".$date." is ".$due_date;

  print "<tr><td colspan=2><span style=\"font-weight: bold;\">";
  print "\nIngevoerde datum was: ".$dag."-".$maand."-".$jaar." <br />\n";
  print "\nDat valt in week ".$startweek."<br />\n";
  print "<br />\nNa ".$plusweken." weken is de datum ".$eind_datum." <br />\n";
  print "\nEn dat valt in week ".$eindweek."<br />\n";
  print "</td></tr><tr><td colspan=2 align=\"center\"><input type=\"button\" value=\"terug\" onClick=\"javascript:history.go(-1)\" />";
  print "</span></td></tr>";

} else {
?>
<form method="GET" action="index.php">
  <input type="hidden" name="verzonden" value="ja" />
  <tr>
  <td>dag (2 cijfers)</td><td> <input maxlength="2" size="2" type="text" name="dag" /></td>
  </tr>
  <tr>
  <td>maand (2 cijfers)</td><td> <input maxlength="2" size="2" type="text" name="maand" /></td>
  </tr>
  <tr>
  <td>jaar (4 cijfers)</td><td> <input maxlength="4" size="4" type="text" name="jaar" /></td>
  </tr>
  <tr>
  <td>plus weken</td><td><input type="text" name="plusweken" /></td>
  </tr>
  <tr>
  <td align="center"><input type="submit" value="bereken" /></td><td align="center"><input type="reset"  value="opnieuw" /></td>
</form>


</table>

</body>
<html>
<?php 
}
?>

<?php 
?>
