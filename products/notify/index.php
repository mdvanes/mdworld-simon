<?php

/* example: 

Build Notify

*/

/* variables */
$FROM_ADDRESS = "x@x.x";
$MONITORING_ADDRESS = $FROM_ADDRESS;
$ID_NN = "NN";
$KEY_CODE = "xyz";

/* functions */
function sendMail()
{
	global $FROM_ADDRESS, $MONITORING_ADDRESS, $ID_NN, $KEY_CODE;
	$key = $_GET['key'];
	$id = $_GET['id'];
	// check password (keycode) and id
	if( true ) // $key == $KEY_CODE && $id == $ID_NN )
	{
		$to = $_GET['to'];
		$subject = $_GET['subject'];
		$message = $_GET['message'] ;
		$trimmedmessage = stripslashes(trim($message));

		// check if the monitoring address is included.
		if( strstr( $to, $MONITORING_ADDRESS ) )
		{
			mail( $to, "BUILD NOTIFY: ".$subject , $trimmedmessage, "From: $FROM_ADDRESS" );
			print "done";
		}
	}
}

/* main entry point */
sendMail();

?>
