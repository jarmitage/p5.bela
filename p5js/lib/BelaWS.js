class BelaWS {

  constructor ( {ip='192.168.7.2', port=8888, address='address'} ) {
  
    this.ws = new WebSocket (`ws://${ip}:${port}/${address}`);

    this.ws.onopen = function() {
      // this.ws.binaryType = 'arraybuffer';
      console.log ('[WS] Connected');
      // this.ws.onclose = ws_onerror;
      // this.ws.onerror = undefined;
    };

    this.ws.onerror = event => {
      setTimeout(() => {
        this.ws = new WebSocket (`ws://${ip}:${port}/${address}`);
        // how to get this to loop as before?
        // this.ws.onerror = this.ws.onerror;
        // this.ws.onopen    = ws_onopen;
        // this.ws.onmessage = ws_onmessage;
      }, 500);
    };

    this.ws.onmessage = event => {
      if ('data' in event) {
        this.onMessage (JSON.parse (event.data));
      }
    }
  }
  
  onMessage (data) {
    // User override...
  };

  send (msg) {
    if (this.ws.readyState === 1) this.ws.send (JSON.stringify (msg));
  }

}
