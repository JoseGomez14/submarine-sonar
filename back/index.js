import { Server } from "socket.io";
import { createServer } from "node:http";

// Load environment variables from .env file
const PORT = process.env.PORT || 3000;
const { CONNECTION_IOT_EVENT, CONNECTION_USER_EVENT } = process.env;

// Create a http server and attach the socket.io server to it for real-time communication
const server = createServer();
const io = new Server(server, {
  cors: {
    origin: "*",
  },
});

// Listen for incoming connections from clients and local IoT devices
io.on("connection", (socket) => {
  console.log("A user connected!");

  socket.on("disconnect", () => {
    console.log("A user disconnected!");
  });

  // Forward the data from IoT devices to the connected clients
  socket.on(CONNECTION_IOT_EVENT, (data) => {
    io.emit(CONNECTION_USER_EVENT, data);
  });
});

// Start the server on the specified port
server.listen(PORT, () => {
  if (process.env.NODE_ENV !== "production") {
    console.log(`Server is running on http://localhost:${PORT}`);
  }
});
