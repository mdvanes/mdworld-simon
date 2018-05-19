<?php
require_once("imageFunctions.inc");

class Insig
{
	// filename of the source image
	private $mFilename;

	// watermark
	private $mWatermarkText = "http://mdworld.nl/products/insignificant/";
	// start coordinates
	private $mWatermarkX;
	private $mWatermarkY;

	// custom text
	private $mText;
	// custom text start coordinates
	private $mX;
	private $mY;

	// custom font settings?
	// ??

	function __construct( $filename, $x, $y, $watermarkX, $watermarkY, $text )
	{
		$this->mFilename = $filename;
		$this->mX = $x;
		$this->mY = $y;
		$this->mWatermarkX = $watermarkX;
		$this->mWatermarkY = $watermarkY;
		$this->mText = $text;
	}

	function setText( $text )
	{
		$this->mText = $text;
	}

	function getImage()
	{
		$im = imagecreatefromjpeg( $this->mFilename );

		// call function addText here for "string"
		for( $i = 0; $i < sizeof($this->mText); $i++ )
		{
			$strippedtext = stripslashes(stripslashes($this->mText[$i]));
			addText( $im, $strippedtext, 4, $this->mX, $this->mY );
			$this->mY = $this->mY + 20; // go down 20px each line
		}

		// call function addText here for "watermark"
		addText( $im, $this->mWatermarkText, 3, $this->mWatermarkX, $this->mWatermarkY );

		return $im;
	}

	function toString()
	{
		return "Instance of Insig";
	}
}
?>
