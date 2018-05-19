<?php
header("Content-type: image/jpeg");

require_once("imageFunctions.inc");
require_once("insig.inc");

// declare $insig here for scope
$insig;

if( isset($_GET["type"]) )
{
	if( $_GET["type"]=="sargeras" )
	{
		$text = array( "i r sargeras avatar and i r lie on ur puny", "infrastructure, causing u all traffic jamz!" );
		$insig = new Insig( "sargeras.jpg", 17, 200, 0, 150, $text );
	}
	elseif( $_GET["type"]=="enterprise" )
	{
		$text = array( "Step on it mister LaForge!", "Klingons on the starboard bough!" );
		$insig = new Insig( "enterprise.jpg", 290, 420, 280, 225, $text );
	}
	elseif( $_GET["type"]=="fluffy" )
	{
		$text = array( "This is Fluffy", "He is the destroyer of worlds." );
		$insig = new Insig( "fluffy.jpg", 10, 410, 10, 120, $text );
	}
}

// if still empty, fallback to default (Vader)
if( $insig == null )
{
	// default: Vader
	$text = array( "Don't be too proud of this technological","terror you've constructed. It is", "insignificant next to the powers of the Force." );
	$insig = new Insig( "vader.jpg", 518, 30, 620, 400, $text );
}

// read the contents of the textarea, if filled, set the custom text in the Insig
if( isset($_GET["text2"]) && strlen($_GET["text2"]) > 0 )
{
	$insig->setText( convertTextarea( $_GET['text2']) );
}

$im = $insig->getImage();

imagejpeg($im);
imagedestroy($im);
?>
