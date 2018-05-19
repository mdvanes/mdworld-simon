<?php
error_reporting(E_ALL);
ini_set("display_errors", 1);

require_once("imageFunctions.inc");
require_once("insig.inc");
?>
<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE html>
<html xmlns="http://www.w3.org/1999/xhtml">
	<head>
		<title>Insignificant! by MD Enterprises</title>
	</head>
	<body>
		<div id="mainContainer">
			<div id="centerRail" class="container" style="width: 920px;">
				<h1>Insignificant!</h1>
				<a href="/">home</a>
				<p>The tool with working title "Insignificant!", to prove you are insignificant next to powers of the Force!</p>

<?php
$type = "";
if( isset($_POST["type"]) )
{
	$type = $_POST["type"];
}
$text2 = "";
if( isset($_POST["text2"]) )
{
	$text2 = $_POST["text2"];
}
?>

				<div><img alt="generated image" src="image.php?type=<?php echo $type; ?>&amp;text2=<?php echo $text2; ?>"/>
</div>

				<form action="index.php" method="post">
					<fieldset>
						<select name="type">
							<option value="vader">Darth Vader</option>
							<option value="sargeras" <?php 
			if( $type=="sargeras")
			{ echo "selected=\"selected\""; } 
			?>>Sargeras</option>
							<option value="enterprise" <?php 
			if( $type=="enterprise")
			{ echo "selected=\"selected\""; } 
			?>>Enterprise</option>
							<option value="fluffy" <?php 
			if( $type=="fluffy")
			{ echo "selected=\"selected\""; } 
			?>>Fluffy</option>
						</select>
						<br/>
<textarea name="text2" cols="50" rows="10"><?php 
if( isset($_POST['text2']) && strlen($_POST['text2']) > 0)
{
	echo stripslashes( implode("",convertTextarea($_POST['text2'])) );
} ?></textarea>
						<br/>
						<input type="submit" value="generate image"/>
					</fieldset>
				</form>
				<input type="button" onclick="javascript: document.location='index.php'" value="clear"/>

				<p>date: 01-01-2011 version 1.4: separate input lines replaced by single textarea. Text is limited to 46 characters per line, 7 lines total.<br/>
Added Fluffy.<br/>
Refactored to be Object Oriented.</p>
				<p>date: 11-12-2010 version 1.3: updated watermark.</p>
				<p>date: 04-02-2009 version 1.2</p>
			</div>
		</div>
	</body>
</html>
