<?php
/*
Converts an invalid snippet into a valid piece of XHTML 1.1 Strict
parameter type The snippet type (plain text, youtube, google maps etc)
parameter source The snippet
returns result The valid snippet
*/
function valificate( $type, $source )
{
	$result = "";
	if ( $type=="plain" )
	{
		$result = htmlentities($source);
	}
	else if ( $type=="youtube" )
	{		
		$source = stripslashes($source);
		/* start extracting parts */
		$object = getTag( $source, "object" );
		$param = getTag( $source, "param" );
		$height = getAttribute( $object, "height" );
		$width = getAttribute( $object, "width" );
		$valueUnescaped = getAttribute( $param, "value" );
		$value = htmlentities($valueUnescaped);
		/* end extracting parts */
		$result = "<object style=\"width: ".$width."px; height: ".$height."px;\" data=\"".$value."\" type=\"application/x-shockwave-flash\">";
		$result .= "\n   <param name=\"movie\" value=\"".$value."\" />";
		$result .= "\n   <span class=\"error\">Can't play flash movie ".$value."</span>";
		$result .= "\n</object>";
	}
	else if ( $type=="gvideo" )
	{
		$source = stripslashes($source);
		/* start extracting parts */
		$embed = getTag( $source, "embed" );
		$style = getAttribute( $embed, "style" );
		$src = htmlentities(getAttribute( $embed, "src" ));
		/* end extracting parts */
		/* start constructing valid code */
		$result = "<object style=\"".$style."\" data=\"".$src."\" type=\"application/x-shockwave-flash\">";
		$result .= "\n   <param name=\"movie\" value=\"".$src."\" />";
		$result .= "\n   <span class=\"error\">Can't play flash movie ".$src."</span>";
		$result .= "\n</object>";
		/* end constructing valid code */
	}
	else if ( $type=="picasaweb" )
	{
		$source = stripslashes($source);
		/* start extracting parts */
		$embed = getTag( $source, "embed" );
		$src = htmlentities(getAttribute( $embed, "src" ));
		$height = getAttribute( $embed, "height" );
		$width = getAttribute( $embed, "width" );
		$flashvars=  htmlentities(getAttribute( $embed, "flashvars" ));
		$pluginspage=  htmlentities(getAttribute( $embed, "pluginspage" ));
		/* end extracting parts */
		/* start constructing valid code */
		$result = "<object style=\"width: ".$width."px; height: ".$height."px;\" data=\"".$src."\" type=\"application/x-shockwave-flash\">";
		$result .= "\n   <param name=\"movie\" value=\"".$src."\" />";
		$result .= "\n   <param name=\"flashvars\" value=\"".$flashvars."\" />";
		$result .= "\n   <param name=\"pluginspage\" value=\"".$pluginspage."\" />";
		$result .= "\n   <span class=\"error\">Can't play flash movie ".$src."</span>";
		$result .= "\n</object>";
		/* end constructing valid code */
	}
	else if ( $type=="gmaps" )
	{
		$source = stripslashes($source);
		/* start extracting parts */
		$iframe = getTag( $source, "iframe" );
		$src = getAttribute( $iframe, "src" );
		$height = getAttribute( $iframe, "height" );
		$width = getAttribute( $iframe, "width" );
		/* end extracting parts */
		/* start constructing valid code */
		$result = "<object style=\"width: ".$width."px; height: ".$height."px; border: none;\" data=\"".$src."\" type=\"text/html\">";
		$result .= "\n</object>";
		$result .= "\n<br/><a href=\"".$src."\">View Larger Map</a>";
		/* end constructing valid code */
	}
	return $result;
}

/*
Extracts the first tag from a string of code
parameter code The code containing the tag
parameter tag The tag to look for
returns the first tag found
*/
function getTag( $code, $tag )
{
	$fromTag = strstr($code, "<".$tag ); /* from the start of the tag to the end of the code */
	$extractedTag = substr( $fromTag, 0, strpos($fromTag,">") + 1 );
	return $extractedTag;
}

/*
Extracts the first attribute from a tag
parameter tag The tag containing the attribute
parameter attribute The attribute to look for
returns the first attribute found
*/
function getAttribute( $tag, $attribute )
{
	$attributeOpener = $attribute."=\"";
	$fromAttributeIncl = strstr($tag, $attributeOpener ); /* from the start of the attribute to the end of the tag */
	$fromAttribute = substr( $fromAttributeIncl, strlen($attributeOpener) );
	$extractedAttribute = substr( $fromAttribute, 0, strpos($fromAttribute,"\"") );
	return $extractedAttribute;
}
?>
