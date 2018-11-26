var myp5 = new p5 ( function( sketch ) {

  const bela = new BelaWS ( { ip:'192.168.7.2', port:'8888', address:'address'} );

  sketch.setup = function() {

    sketch.createCanvas (sketch.windowWidth, sketch.windowHeight);

  }

  sketch.windowResized = function () {

  }

  bela.onMessage = function (data) {
  
    console.log ('[Bela] Data received:', data);
    test = data;

  }

  var test;

  sketch.draw = function() {

    sketch.background (240);
    drawMsg (msg);

  }
  
  function drawMsg (msg) {
    sketch.text (msg, 0, 0);
  }

}, 'p5div');

