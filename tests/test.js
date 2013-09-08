var net = require('net')
 
var connection = net.connect(8085, "localhost", function() { // connect to the server we made
    console.log("client connected");
    setInterval(function () { // every 1000ms,
       connection.write("er-mah-gerd");// write to the connection
    }, 1000);//the 1000 is the delay in between the anon function calls
})
.on('data', function(data) {
   console.log('data ' + data);
})
