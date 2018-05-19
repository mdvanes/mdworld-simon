<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1//EN" "http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
	<?php
	$PATH = "../..";
	include($PATH.'/templates/generic_head.inc');	
	?>
	<body>
		<div id="mainContainer">
		<?php
		include($PATH.'/templates/generic_top.inc');
		include($PATH.'/templates/generic_menu.inc');
		?>
			<div id="centerRailWide">
			<?php
			include('lib/valificator_container.inc');
			?>
			</div>
		</div>
		<div class="clear_both"/>
	</body>
</html>
