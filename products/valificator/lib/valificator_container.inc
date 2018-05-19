<?php

/* on receive, do two things:
1. write source to log
2. valificate!
*/

$VALIFICATOR_SRC = "lib/valificator_function.inc";
$result = "";

include($VALIFICATOR_SRC);

/*
Write a predefined message to the messages file (log)
parameter message Contains the message that is written to the log
returns Void 
*/
function writeLogMessage( $message )
{
	$logpath = "log.inc";
	$message = "\n[".date("Y-m-d H:i:s")."] ".stripslashes($message);
	$filehandle = fopen( $logpath, "a" );
 	fwrite($filehandle, $message);
	fclose($filehandle);	
}

/*
Call the valificator if a request is done
*/
if ( isset($_GET["valificate"]) && isset($_POST["type"]) && isset($_POST["source"]) ) 
{
	$type = $_POST["type"];
	$source = $_POST["source"];
	$result = valificate( $type, $source );
	$logmessage = "\ntype: ".$type."\nsource: ".$source."\nresult: ".$result;
	writeLogMessage($logmessage);
}

?>

<div class="container">

	<p>
	MD Enterprises Softcorp introduces:
	</p>
	<h1>The Valificator</h1>
	<p>
	I'm in ur <img src="http://www.w3.org/Icons/valid-xhtml11" alt="Valid XHTML 1.1" height="31" width="88" /> valificating ur snippitz!
	</p>

	<p>
	Last edited: <?php 
	/* echo date("H:i:s d-m-Y",getlastmod()); */
	$filename = "lib/valificator_container.inc";
	echo " ".date("H:i:s d-m-Y",filemtime($filename));
	 ?>
	</p>
	<hr/>

<?php
if ( $result != "" )
{
	$normalizedResult = htmlspecialchars(stripslashes($result), ENT_QUOTES);
?>
	<h3>Result</h3>	
	<h4>The converted snippet</h4>
	<p>
		<br/>
		<textarea cols="70" rows="10"><?php echo $normalizedResult; ?></textarea>
	</p>

	<h4>Validation</h4>
	<p>
		The following contains the snippet inserted into a bare valid XHTML 1.1 page. You can validate it by clicking the button, too see if the Valificator worked for your snippet.

		<form method="post" enctype="multipart/form-data" action="http://validator.w3.org/check" target="_blank">
			<fieldset>
				<textarea id="fragment" name="fragment" rows="1" cols="70"><?xml version="1.0" encoding="UTF-8"?>
	<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1//EN" "http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd">
	<html xmlns="http://www.w3.org/1999/xhtml"><head><title></title></head><body><div><?php echo $normalizedResult; ?></div></body></html></textarea>
				<input type="hidden" id="direct-doctype" name="doctype" value="Inline"/>
				<input type="hidden" id="direct-ss" name="ss" value="1" />
			</fieldset>
			<input title="Submit for validation" type="submit" value="Validate" />
		</form>
	</p>

	<h4>Demo</h4>
	<p>The actual converted snippet is embedded below, so you can test if it works as expected.</p>
	<div>
		<?php 
			echo stripslashes($result); 
			echo "\n";
		?>
	</div>
	<hr/>
<?php
}
?>

	<p>One day I woke up and decided that it's just not fair. Why should I go trough so much trouble just to make valid XHTML 1.1? Large companies like Youtube and Google don't even take the trouble to provide valid snippits for their embedded code, I'll have to rewrite them every single time.</p>

	<p>That's why I wrote the valificator. It converts Youtube and Google embed snippits to valid XHTML 1.1.</p>

	<h3>Valificate your snippet</h3>
<?php
if ($result != "")
{
?>
	<p>
		<a href="index.php">Validate another snippet</a>
	</p>
<?php
} 
else 
{
?>	
	<form action="index.php?valificate" method="post">
		<fieldset>
			<dl>
				<dt>snippet type</dt>		
				<dd>
					<select name="type">
						<option value="youtube">Youtube</option>
						<option value="gvideo">Google Video Embed</option>
						<option value="gmaps">Google Maps iFrame</option>
						<option value="picasaweb">Picasa Slideshow</option>
						<option value="plain">plain text</option>
					</select>
				</dd>
			</dl>
			<dl>
				<dt>snippet</dt>
				<dd><textarea name="source" cols="40" rows="10"></textarea></dd>
			</dl>
			<br />
			<input type="submit" value="valificate!"/>
		</fieldset>
	</form>
<?php
}
?>
	<p>
		OK, pop your eyes back in after being exposed to this splendor. I can still hear some of you thinking "That's all nice and all, but where do I get these stupid snippets in the first place?". Well, that depends:
	</p>
	<ul>
		<li><a href="http://www.youtube.com">Youtube</a>: go to a Youtube movie, and scroll down to "embed". Then copy the code in the input field following the word Embed. Now paste in in the snippet area up here.</li>
		<li><a href="http://video.google.com">Google Video</a>: go to a Google video. Press the "e-mail - embed HTML" button. Press "embed HTML". Copy and paste the snippet into the area up here.</li>
		<li><a href="http://picasaweb.google.com">Picasa Web Album Slideshow</a> (Google): go to a Picasa Web Album. Click the link Embed Slideshow. Copy and paste the snippet listed under "Embed Slideshow" into the area up here.</li>
		<li><a href="http://maps.google.com">Google Maps</a>: go to a Google map. Click "link to this page". Copy the snippet from the "paste HTML into website" field. Paste it into the area up here.</li>
	</ul>
	<p>Notes:</p>
	<ul>
		<li>Youtube: I've read that the way I convert youtube snippets may result in a problem loading if you view the movie from Internet Explorer. I wouldn't know though, because I don't use IE. So, no guarantees there.</li>
		<li>Google Maps: The valid snippet doesn't appear to work at all in IE. In firefox it works just fine. The reason appears to be that Internet Explorer considers an object-tag that loads an external url (i.e. starting with http://) as possibly harmful, and therefore doesn't load it. It <span style="font-weight: bold">does</span> load local/relative paths into an object-tag. If anyone has a clue how to fix this, you can reach me through the contact button on the top of this page. For now, I just work around it by displaying a link instead of the map when the user agent is IE.</li>
	</ul>

	<h3>Source</h3>
	<p>
		This is open source, distributed under <a href="http://www.gnu.org/licenses/gpl.html">GPL</a>.<br/>
		The source:<br/>
		<textarea cols="70" rows="10"><?php
			$fh = fopen($VALIFICATOR_SRC, 'r');
			$theData = fread($fh, filesize($VALIFICATOR_SRC));
			fclose($fh);
			echo $theData;
		?></textarea>
		<br/>
		Last updated: <?php 
		echo " ".date("H:i:s d-m-Y",filemtime($VALIFICATOR_SRC));
		 ?>	
		<br/>
	</p>
	<h4>Thanks to</h4>
	<ul>
		<li><a href="http://www.alistapart.com/stories/flashsatay/">The Flash Satay Method</a></li>
	</ul>

</div>
<?php
?>

