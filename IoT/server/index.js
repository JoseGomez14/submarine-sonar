import { ReadlineParser, SerialPort } from "serialport";

import { io } from "socket.io-client";

// Load environment variables from the .env file
const CONNECTION_SERVER = process.env.CONNECTION_SERVER;
const CONNECTION_EVENT = process.env.CONNECTION_EVENT;
const ARDUINO_PORT = process.env.ARDUINO_PORT || "COM3";

const socket = io(CONNECTION_SERVER);

// Create a new serial port instance to connect to the Arduino and read data from it
const port = new SerialPort({
  path: ARDUINO_PORT,
  baudRate: 9600,
});

// Create a new parser instance to read data from the serial port
const parser = port.pipe(new ReadlineParser({ delimiter: "\n" }));

// Add event listener for open event
port.on("open", () => {
  console.log("serial port open");
});

// TODO: Add event listener for error or close event

// Add event listener for data event to read data from the serial port and emit it to the server
parser.on("data", (data) => {
  let temp = data.replace("\r", "").split(",");
  let IoTData = {
    position: temp[0],
    direction: temp[1],
    distance: temp[2],
  };
  socket.emit(CONNECTION_EVENT, IoTData);
});
