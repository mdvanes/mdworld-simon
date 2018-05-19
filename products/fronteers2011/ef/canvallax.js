/**
CanvaLlax - Canvas Parallax Scrolling
*/

// source: http://creativejs.com/tutorials/three-js-part-1-make-a-star-field/
// source: http://www.aerotwist.com/lab/getting-started-with-three-js/
// source: https://github.com/mrdoob/three.js/
// source: http://mrdoob.github.com/three.js/examples/webgl_geometry_shapes.html
// source: http://fhtr.org/BasicsOfThreeJS/#17
// source: https://github.com/mrdoob/three.js/wiki/JSON-Model-format-3.0 // the 3d shape model json spec
// source: http://www.html5canvastutorials.com/webgl/html5-canvas-webgl-directional-lighting-with-three-js/ // directional light
// based on: http://learningthreejs.com/blog/2011/08/06/lets-do-a-cube/
// dropbox url: http://dl.dropbox.com/u/11562983/fronteers2011/ef/ef.html

var canvallax =
{
	mouseX: 0,
	skylineZPosition: -300,
	starAmount: 1800,
	showFps: false,
	parallaxRotate : function()
	{
		return $(window).scrollTop();
	},
	getMouseX : function(event)
	{
		// Thanks to Ryan Artecona on http://stackoverflow.com/a/5932203
		var totalOffsetX = 0;
		var currentElement = document.getElementsByTagName("canvas")[0];

		do{
			totalOffsetX += currentElement.offsetLeft;
		}
		while(currentElement = currentElement.offsetParent)

		return event.pageX - totalOffsetX;
	},
	reset : function()
	{
		$("#canvasWrapper").remove();
		canvallax.bootstrap();

		// Update variable containing the horizontal mouse position that is accessable from the animation function
		$(window).mousemove( function(event){
			canvallax.mouseX = canvallax.getMouseX(event);
		});
	},
	bootstrap : function(debug)
	{
		var startTime = Date.now();
		var container;
		var camera, scene, renderer, stats;
		var morgal, skyline;

		if(debug)
		{
			canvallax.showFps = debug;
		}		

		// Set initial state
		canvallax.init();
		// Loop for animation		
		canvallax.animate();
	},
	screenshot : function(elem)
	{
		var dataUrl = renderer.domElement.toDataURL("image/png");
		elem.src = dataUrl;
	},
	getSkylineMesh : function()
	{
		var extrudeSettings = {	amount: 50, bevelEnabled: false, bevelSegments: 1, steps: 2 };
		var skylineShape = new THREE.Shape();
		var gapWidths = [ 1, 10, 20 ];
		var x = 0, y = 0;
		var windowWidthAtDepth = window.innerWidth * 1.2;
		// Downtown is from 35% - 65%;
		var downtownStart = Math.floor(windowWidthAtDepth * 0.35);
		var downtownEnd = Math.floor(windowWidthAtDepth * 0.65);

		skylineShape.moveTo( 0, 0 );

		while( x < windowWidthAtDepth )
		{
			x += Math.floor(Math.random() * 25) + 50;
			skylineShape.lineTo( x, y );
			y = Math.floor(Math.random() * 40);
			skylineShape.lineTo( x, y );
			var gapWidth = gapWidths[Math.floor(Math.random() * 3)];
			x += gapWidth;
			skylineShape.lineTo( x, y );

			var buildingMinHeight = 100;
			var buildingHeightRange = 100;
			// buildings are heigher at downtown
			if( x > downtownStart && x < downtownEnd ) {
				buildingMinHeight = 200;
				buildingHeightRange = 150
			}
			var buildingHeight = Math.floor(Math.random() * buildingHeightRange) + buildingMinHeight; //x += 50;
			y += buildingHeight;
			skylineShape.lineTo( x, y );
		}

		x += 10;
		skylineShape.lineTo( x, y );
		skylineShape.lineTo( x, -500 );
		skylineShape.lineTo( 0, -500 );
		skylineShape.lineTo( 0, 0 );

		var skyline3d = skylineShape.extrude( extrudeSettings );
		var skyline = new THREE.Mesh(
			skyline3d,
			new THREE.MeshLambertMaterial({color: 0x00ff00, opacity: true, shading: THREE.FlatShading }) );
		return skyline;
	},
	generateStars:
	{
		init: function() {
			// THREE.ParticleCanvasMaterial and THREE.Particle are only supported in THREE.CanvasRenderer
			// THREE.ParticleSystem is only supported in THREE.WebGLRenderer
			if( renderer instanceof THREE.WebGLRenderer )
			{
				canvallax.generateStars.webGLStars();
			} else if ( renderer instanceof THREE.CanvasRenderer )
			{
				canvallax.generateStars.canvasStars();
			} else {
				alert("Can't determine renderer type");
			}
		},
		canvasStars: function() {
			// Only works with Canvas
			// source: http://creativejs.com/tutorials/three-js-part-1-make-a-star-field/
			var particle, material;

			var correctionFactor = 1.4; // correct for z position of stars
			var correctedWindowWidth = (window.innerWidth * correctionFactor);
			var correctedWindowHeight = (window.innerHeight * correctionFactor);
			for( var p = 0; p < canvallax.starAmount; p++ ) {
				material = new THREE.ParticleCanvasMaterial( { color: 0xffffbe, program: canvallax.generateStars.particleRender } );

				particle = new THREE.Particle(material);
				particle.position.x = Math.random() * correctedWindowWidth - (correctedWindowWidth/2);
				particle.position.y = Math.random() * correctedWindowHeight - (correctedWindowHeight/2);
				particle.position.z = Math.random() * 1000 - 1000 + canvallax.skylineZPosition; // from -1300 to -300, if skyline starts at -300

				// add it to the scene
				scene.add( particle );
			}
		},
		particleRender: function( context ) {
			context.beginPath();
			// an arc from 0 to 2Pi radians or 360º = a full circle
			context.arc( 0, 0, 1, 0,  Math.PI * 2, true );
			context.fill();
		},
		webGLStars: function() {
			// Only works with WebGL
			// source: http://aerotwist.com/lab/creating-particles-with-three-js/
			// create the particle variables
			var particles = new THREE.Geometry();

			var pMaterial = new THREE.ParticleBasicMaterial({
				color: 0xFFFFFF,
				size: 20,
				map: THREE.ImageUtils.loadTexture(
				    "../../products/fronteers2011/ef/particle.png"
				),
				blending: THREE.AdditiveBlending,
				transparent: true
			    });

			var correctionFactor = 1.4; // correct for z position of stars
			var correctedWindowWidth = (window.innerWidth * correctionFactor);
			var correctedWindowHeight = (window.innerHeight * correctionFactor);
			for(var p = 0; p < canvallax.starAmount; p++) {
			    var pX = Math.random() * correctedWindowWidth - (correctedWindowWidth/2),
				pY = Math.random() * correctedWindowHeight - (correctedWindowHeight/2),
				pZ = Math.random() * 1000 - 1000 + canvallax.skylineZPosition, // from -1300 to -300, if skyline starts at -300
				particle = new THREE.Vertex(
				    new THREE.Vector3(pX, pY, pZ)
				);
			    
			    // add it to the geometry
			    particles.vertices.push(particle);
			}

			// create the particle system
			var particleSystem = new THREE.ParticleSystem(
			    particles,
			    pMaterial);

			// add it to the scene
			scene.add(particleSystem);
		}
	},
	// ## Initialize everything
	init : function()
	{
		// create the Scene
		scene = new THREE.Scene();

		var VIEW_ANGLE = 45,
		    ASPECT = window.innerWidth / window.innerHeight,
		    NEAR = 0.1,
		    FAR = 10000;

		camera = new THREE.PerspectiveCamera( VIEW_ANGLE, ASPECT, NEAR, FAR );

		// the camera starts at 0,0,0 so pull it back
		camera.position.z = 650;
		scene.add(camera);

		/* 
		Init the renderer and append it to the Dom.
		"Canvas is more widely supported than WebGL, but it's worth noting that WebGL runs on your 
		graphics card's GPU, which means that your CPU can concentrate on other [tasks]... "
		(http://www.aerotwist.com/lab/getting-started-with-three-js/)
		*/
		if( Detector.webgl && $("#webgl").attr("checked") ) {
			// test if webgl is supported
			if ( ! Detector.webgl ) Detector.addGetWebGLMessage();
			renderer = new THREE.WebGLRenderer();
			$("#rendererStatus").removeClass("canvas");
			$("#rendererStatus").addClass("webgl");
			$("#rendererStatus").text("using webgl renderer");
		} else {
			renderer = new THREE.CanvasRenderer();
			$("#rendererStatus").removeClass("webgl");
			$("#rendererStatus").addClass("canvas");
			$("#rendererStatus").text("using canvas renderer");
		}
		renderer.setSize( window.innerWidth, window.innerHeight );

		// create the container element
		container = document.createElement( 'div' );
		container.id = "canvasWrapper";
		var firstDiv = document.getElementsByTagName("div")[0];
		document.body.insertBefore( container, firstDiv );
		container.appendChild( renderer.domElement );

		// Create the Morgal Avatar
		var loader = new THREE.JSONLoader( true );
//		loader.load( "http://mdworld.nl/products/fronteers2011/ef/morgal.js", function( geometry ) {
		loader.load( "../../products/fronteers2011/ef/morgal.js", function( geometry ) {
			morgal = new THREE.Mesh( geometry, 
			new THREE.MeshLambertMaterial({
				color: 0xff0000, 
				opacity: true, 
				shading: THREE.FlatShading }) );
			morgal.scale.set( 3, 3, 3 );
			morgal.position.z = -100;
			scene.add( morgal ); // must be added here, because it guarantees that it is done loading.
		} );

		skyline = canvallax.getSkylineMesh();
		skyline.position.x = -1000;
		skyline.position.z = canvallax.skylineZPosition;

		// add the meshes to the scene
		canvallax.generateStars.init();
		scene.add( skyline );

		// directional lights directly behind the skyline
		var directionalLight = new THREE.DirectionalLight( 0xffffff );
		directionalLight.position.x = 0.5;
		directionalLight.position.z = -3;
		directionalLight.position.normalize();
		var directionalLight2 = new THREE.DirectionalLight( 0xffffff );
		directionalLight2.position.x = -0.5;
		directionalLight2.position.z = -3;
		directionalLight2.position.normalize();

		scene.add( directionalLight );
		scene.add( directionalLight2 );

		// point light at morgal avatar
		var pointLight = new THREE.PointLight( 0xFFFFFF, 0.2 );
		pointLight.position.x = 0;
		pointLight.position.y = 0;
		pointLight.position.z = 0;
		pointLight.position.normalize();
		scene.add(pointLight);
	
		// init the Stats and append it to the Dom - performance vuemeter
		if( canvallax.showFps )
		{
			stats = new Stats();
			stats.domElement.style.height = "100px";
			stats.domElement.style.position = 'absolute';
			stats.domElement.style.top = '0px';
			container.appendChild( stats.domElement );
		}
	},
	// ## Animate and Display the Scene
	animate : function() {
		// relaunch the 'timer' 
		requestAnimationFrame( canvallax.animate );
		// render the 3D scene
		canvallax.render();
		// update the stats
		if( canvallax.showFps )
		{
			stats.update();
		}
	},
	// ## Render the 3D Scene
	render : function() {
		// animate the morgal mesh
		try {
			morgal.rotation.x = (canvallax.parallaxRotate() / 1000 );
			/*
			0 is the default orientation, facing forward.
			Rotation is in ???, so ??? is facing the side forward.
			The var mouseX ranges from 0 to 1920 on a 1920 wide viewport.
			I want the mesh to move slightly to the left and right.
			When mouseX is at 50% of the screen, I want the mesh to be facing forward, so:
			 mouseX = 50% -> y = 0
			 mouseX < 50% -> y < 0 & y > -0.5
			 mouseX > 50% -> y > 0 & y < 0.5
			*/
			morgal.rotation.y = (canvallax.mouseX / window.innerWidth) - 0.5;
		} catch( e ) {
			// Possible that avatar is not done loading in the first couple of milliseconds, just continue
//			console.log( "Still loading morgal.js: " + e );
		}

		skyline.position.y = (canvallax.parallaxRotate() / 100) - 200;
		skyline.rotation.x = -(canvallax.parallaxRotate() / 100000 );

		// actually display the scene in the Dom element
		renderer.render( scene, camera );
	}
}
