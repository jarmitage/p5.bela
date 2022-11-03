# Connecting Bela to p5.js via WebSockets (i.e. no OSC or Node.js)

OBSOLETE! This work was integrated into the Bela project: https://learn.bela.io/the-ide/crafting-guis/

This (not thoroughly tested...) example demonstrates connecting [Bela](http://bela.io) to [p5.js](http://p5js.org) via a WebSocket.

This eliminates the need for either OSC or Node.js as intermediaries between Bela and `p5.js` and in theory would support higher throughput communication, similar to how the Bela Oscilloscope works.

It uses work currently existing in the `dev-websocket-rebased` branch of the main Bela repository.

It uses `p5.js` in "instance mode" since you might want multiple p5 widgets in your GUI.

#### TODO

- Cleanup!
- Make a better example


