<?php
if (isset($_GET["debug"]))
{
 $_POST=array("bla"=>"blie","foo"=>"bar","fuzz"=>"burr","i'm"=>"in","ur"=>"medieval","village"=>"burnanating","urr"=>"villagers");
}
?>
<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
	<head>
		<title>PostSnitch | MD Enterprises</title>
		<style type="text/css" media="screen">
html,body
{
	background: #242424; /* charcoal */
	color: #e2e3a6; /* yella */
	font-family: sans-serif;
}
div.results, p, h1
{
	background-color: #242424; /* charcoal */
	border: 1px solid #8db11f; /* olive green */
	margin-bottom: 30px;
	margin-top: 30px;
	padding: 5px;
}
table
{
	width: 500px;
}
td
{
	border: 1px solid #8db11f; /* olive green */
}
a
{
	color: #8db11f; /* olive green */
}
		</style>
	</head>
	<body>
                <h1>MD SoftCorp PostSnitch</h1>
		<p>A request debugging page. There are many like this, but this one is mine...</p>
		<!-- debugging POST variables: <?php echo print_r($_POST); ?>-->
		<div class="results">
			<?php
			if (isset($_POST) && sizeof($_POST) > 0)
			{
			?>
			<table>
				<caption>POST Variables</caption>
				<thead>
					<tr>
						<th>key</th>
						<th>value</th>
					</tr>
				</thead>
				<tbody>
<?php
foreach($_POST as $key => $value)
{
 echo "\n<tr><td>".$key."</td><td>".$value."</td></tr>";
}
?>
				</tbody>
			</table>
			<?php
			} 
			else
			{
				echo "\nNo POST Variables Found";
			}
			?>
		</div>
		<!-- debugging GET variables: <?php echo print_r($_GET); ?> -->
		<div class="results">
			<?php
			if (isset($_GET) && sizeof($_GET) > 0)
			{
			?>
			<table>
				<caption>GET Variables</caption>
				<thead>
					<tr>
						<th>key</th>
						<th>value</th>
					</tr>
				</thead>
				<tbody>
<?php
foreach($_GET as $key => $value)
{
 echo "\n<tr><td>".$key."</td><td>".$value."</td></tr>";
}
?>
				</tbody>
			</table>
			<?php
			} 
			else
			{
				echo "\nNo GET Variables Found";
			}
			?>
		</div>
		<p>MD Enterprises <a href="http://creativecommons.org/licenses/by-nc-sa/3.0/" title="Creative Commons Attribution-Noncommercial-Share Alike 3.0 Unported">(cc)</a> 2007-2010 <a href="http://www.mdworld.nl/cms/contact">For source contact me</a></p>
	</body>
</html>
<?php
?>
