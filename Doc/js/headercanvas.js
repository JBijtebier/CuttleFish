// Canvas

cvs = document.getElementById('headercanvas');
ctx = cvs.getContext("2d");
mousePos = {x: 0, y: 0};

//---------------------------------------------------------------------------

// Points
points = []
amountOfPoints = 500;

// We just place the x,y of our points in [0, 1] because we're going to scale with canvas size anyway.

for (var i = 0; i < amountOfPoints; i++) {
	points.push(
		{
			x: Math.random(),
			y: Math.random(),

			velocity: {
			 	x: (2 * Math.random() - 1) * 0.025,
			 	y: (2 * Math.random() - 1) * 0.025
			},

			alpha: 0.2 + Math.random() * 0.6,
			sizeFactor: 0.75 + Math.random() * 0.5
		}
	);
}

//---------------------------------------------------------------------------

// EventListeners
document.body.addEventListener('mousemove', function(evt) {
	mousePos = getMousePos(cvs, evt);
}, false);

lastScrollY = 0;

document.addEventListener('scroll', function(evt) {
	deltaScroll = window.scrollY - lastScrollY;
	lastScrollY = window.scrollY;

	mousePos.y -= deltaScroll;
}, false);

//---------------------------------------------------------------------------

// Functions

function getMousePos(canvas, evt) {
	var rect = cvs.getBoundingClientRect();
	return {
		x: evt.clientX - rect.left,
		y: cvs.height - (evt.clientY - rect.top)
	};
}

function update(deltaTime) {
	// canvas dimensions
	cvs.width = document.body.clientWidth;
	cvs.height = document.body.clientHeight;

	// Max distance from mouse for drawing lines
	maxDist = distance({x: 0, y: 0}, {x: cvs.width, y: cvs.height}) / 10;

	// Wrapping distance (uses the [0, 1] interval!)
	wrapDist = 0.15;

	// Calculate points positions
	for (var i = 0; i < points.length; i++) {
		d = distance(mousePos,
			{x: points[i].x * cvs.width,
			 y: points[i].y * cvs.height});

		points[i].x += points[i].velocity.x * deltaTime * Math.max(3 - d / 100, 1)
		points[i].y += points[i].velocity.y * deltaTime * Math.max(3 - d / 100, 1)

		// Wrap around screen edges
		if (points[i].x > 1 + wrapDist) { points[i].x = -wrapDist; }
		else if (points[i].x < -wrapDist) { points[i].x = 1 + wrapDist; }
		if (points[i].y > 1 + wrapDist) { points[i].y = -wrapDist; }
		else if (points[i].y < -wrapDist) { points[i].y = 1 + wrapDist; }
	}

	// Draw
	clear();

	for (var i = 0; i < points.length; i++) {
		d = distance(mousePos,
			{x: points[i].x * cvs.width,
			 y: points[i].y * cvs.height});

		// Draw points
		drawPoint(
			{x: points[i].x * cvs.width,
			 y: points[i].y * cvs.height},
			"rgba(255, 255, 255, " + points[i].alpha +  ")",
			Math.max(4 - d / 100, 1) * points[i].sizeFactor
		)

		// Draw lines
		/*
		alpha = (1 - d / maxDist) * 0.5;

		if (alpha < 0) {alpha = 0;}
		if (alpha > 1) {alpha = 1;}

		// Only draw if the line would be visible
		if (alpha > 0) {
			drawLine(
				mousePos,
				{x: points[i].x * cvs.width,
				 y: points[i].y * cvs.height},
				"rgba(255, 255, 255, " + alpha + ")"
			)

		}
		*/
	}
}

function distance(point1, point2) {
	return Math.sqrt(Math.pow(point1.x - point2.x, 2) + Math.pow(point1.y - point2.y, 2));
}

function clear() {
	ctx.clearRect(0, 0, cvs.width, cvs.height);
}

function drawLine(from, to, color) {
	ctx.beginPath();
	ctx.moveTo(from.x, cvs.height - from.y);
	ctx.lineTo(to.x, cvs.height - to.y);
	ctx.strokeStyle = color;
	ctx.stroke();
}

function drawPoint(point, color, width = 2) {
	ctx.fillStyle = color;
	ctx.beginPath();
	ctx.arc(point.x, cvs.height - point.y, width, 0, 2 * Math.PI, false);
	ctx.fill()
	//ctx.fillRect(point.x - width / 2, cvs.height - (point.y + width / 2), width, width);
}

//---------------------------------------------------------------------------

// Loop

var last = Date.now();
setInterval(loop, 0);

function loop() {
    now = Date.now();
    deltaTime = now - last;
    last = now;

    update(deltaTime / 1000);
}
