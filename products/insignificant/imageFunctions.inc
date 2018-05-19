<?php

function addText( $image, $text, $fontsize, $x, $y )
{
	$black = imagecolorallocate( $image, 0, 0, 0 );
	imagestring( $image, $fontsize, $x, $y, $text, $black );
}

/*
Convert the content of the textarea to separate lines
*/
function convertTextarea( $value )
{
	$resultArray = array( "", "", "", "", "", "", "" );	
	$values = explode( " ", $value );
	$j = 0;
	for( $i = 0; $i < sizeof($values); $i++ )
	{
		$lineIfNextWordAdded = $resultArray[$j].$values[$i]." ";
		if( strlen($lineIfNextWordAdded) > 46 )
		{
			// line would become too long horizontally, break to new line
			$j++;
		}
		if( $j > 6 )
		{
			// entire text would become too long vertically, return first 7 lines (starts at 0)
			return $resultArray;
		}
		$resultArray[$j] .= $values[$i]." ";
	}
	return $resultArray;
}

?>
