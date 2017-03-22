/*
  Arduino Yún Bridge example

  This example for the YunShield/Yún shows how 
  to use the Bridge library to access the digital and
  analog pins on the board through REST calls.
  It demonstrates how you can create your own API when
  using REST style calls through the browser.

  Possible commands created in this shetch:

  "/arduino/digital/13"     -> digitalRead(13)
  "/arduino/digital/13/1"   -> digitalWrite(13, HIGH)
  "/arduino/analog/2/123"   -> analogWrite(2, 123)
  "/arduino/analog/2"       -> analogRead(2)
  "/arduino/mode/13/input"  -> pinMode(13, INPUT)
  "/arduino/mode/13/output" -> pinMode(13, OUTPUT)

  This example code is part of the public domain

  http://www.arduino.cc/en/Tutorial/Bridge

*/

#include <Bridge.h>
#include <BridgeServer.h>
#include <BridgeClient.h>

// Listen to the default port 5555, the Yún webserver
// will forward there all the HTTP requests you send
BridgeServer server;

void setup() {
  // Bridge startup
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  Bridge.begin();
  digitalWrite(13, HIGH);

  // Listen for incoming connection only from localhost
  // (no one from the external network could connect)
  server.listenOnLocalhost();
  server.begin();

}

void loop() {
  // Get clients coming from server
  BridgeClient client = server.accept();

  // There is a new client?
  if (client) {
    // Process request
    process(client);

    // Close connection and free resources.
    client.stop();
  }

  delay(50); // Poll every 50ms
}

void process(BridgeClient client) {
  // read the command
  String command = client.readStringUntil('/');

  // is "digital" command?
  if (command == "digital") {
    digitalCommand(client);
  }

  // is "analog" command?
  if (command == "analog") {
   // analogCommand(client);
  }

  // is "mode" command?
  if (command == "mode") {
   // modeCommand(client);
  }
}

void digitalCommand(BridgeClient client) {
  int pin, value;

  // Read pin number
  pin = client.parseInt();

  // If the next character is a '/' it means we have an URL
  // with a value like: "/digital/13/1"
  if (client.read() == '/') {
    value = client.parseInt();
    digitalWrite(pin, value);
  } else {
    value = digitalRead(pin);
  }

  // Send feedback to client
  client.print(F("Pin D"));
  client.print(pin);
  client.print(F(" set to "));
  client.println(value);

  client.println();

  int grid[9];

  client.println(sizeof(grid));

  for(int i = 0; i < 9; i++)
  {
    client.println(grid[i]);
  
  }

// Tic Tac Toe AI & Game Logic

  bool isNewMove = false;
  bool finishMove = false;
  bool canMove = false;
  
  int winner = 0;

  int turnCount = 0;

  int priority1[] {4}; // middle position
  int priority2[] {0, 2, 6, 8}; // corner positions
  int priority3[] {1, 3, 5, 7}; // remaining positions

  // This section of Code will determine if there are any available spaces on the grid to make a move
  if(isNewMove)
  {
    for(int i = 0; i < sizeof(grid); i++)
    {
      if(grid[i] == 0)
      {
        canMove = true;
      }
    }
  }

  // this section of Code will detmine which space the Arduino will choose the place their mark
  while(isNewMove && canMove)
    {
      for(int i = 0; i < sizeof(priority1); i++)
        {
          if(grid[priority1[i]] == 0)
            {
              grid[priority1[i]] == 2;
              break;
              finishMove = true;
            }
        }

        if(finishMove)
        {
          break;
        }

        for(int i = 0; i < sizeof(priority2); i++)
        {
          if(grid[priority2[i]] == 0)
            {
              grid[priority2[i]] == 2;
              break;
              finishMove = true;
            }
        }

        if(finishMove)
        {
          break;
        }

        for(int i = 0; i < sizeof(priority3); i++)
        {
          if(grid[priority3[i]] == 0)
            {
              grid[priority3[i]] == 2;
              break;
              finishMove = true;
            }
        }

      
      }

 if(finishMove)
  {
    turnCount += 2;
  }

if(!canMove && turnCount > 0)
  {
    // Horizontal Checks
    if(grid[0] == grid[1] && grid[0] == grid[2]
      || grid[3] == grid[4] && grid[3] == grid[5]
      || grid[6] == grid[7] && grid[6] == grid[8])
    {
      if(grid[0] == 1 || grid[3] == 1 || grid[6] == 1)
      {
        winner = 1;
      }

      else {
        winner = 2;
      }
    }

    // Vertical Checks
    if(grid[0] == grid[3] && grid[0] == grid[6]
      || grid[1] == grid[4] && grid[1] == grid[7]
      || grid[2] == grid[5] && grid[2] == grid[8])
    {
      if(grid[0] == 1 || grid[1] == 1 || grid[2] == 1)
      {
        winner = 1;
      }

      else {
        winner = 2;
      }
    }

    // Diagonal Left Checks
    if(grid[0] == grid[4] && grid[0] == grid[8])
    {
      if(grid[0] == 1)
      {
        winner = 1;
      }

      else {
        winner = 2;
      }
    }

    // Diagonal Right Checks
    if(grid[2] == grid[4] && grid[2] == grid[6])
    {
      if(grid[0] == 1)
      {
        winner = 1;
      }

      else {
        winner = 2;
      }
    }
  }

    
  
  
  // Update datastore key with the current pin value
  String key = "D";
//  key += pin;
//  Bridge.put(key, String(value));
}

void analogCommand(BridgeClient client) {
  int pin, value;

  // Read pin number
  pin = client.parseInt();

  // If the next character is a '/' it means we have an URL
  // with a value like: "/analog/5/120"
  if (client.read() == '/') {
    // Read value and execute command
    value = client.parseInt();
    analogWrite(pin, value);

    // Send feedback to client
    client.print(F("Pin D"));
    client.print(pin);
    client.print(F(" set to analog "));
    client.println(value);

    // Update datastore key with the current pin value
    String key = "D";
    key += pin;
    Bridge.put(key, String(value));
  } else {
    // Read analog pin
    value = analogRead(pin);

    // Send feedback to client
    client.print(F("Pin A"));
    client.print(pin);
    client.print(F(" reads analog "));
    client.println(value);

    // Update datastore key with the current pin value
    String key = "A";
    key += pin;
    Bridge.put(key, String(value));
  }
}

void modeCommand(BridgeClient client) {
  int pin;

  // Read pin number
  pin = client.parseInt();

  // If the next character is not a '/' we have a malformed URL
  if (client.read() != '/') {
    client.println(F("error"));
    return;
  }

  String mode = client.readStringUntil('\r');

  if (mode == "input") {
    pinMode(pin, INPUT);
    // Send feedback to client
    client.print(F("Pin D"));
    client.print(pin);
    client.print(F(" configured as INPUT!"));
    return;
  }

  if (mode == "output") {
    pinMode(pin, OUTPUT);
    // Send feedback to client
    client.print(F("Pin D"));
    client.print(pin);
    client.print(F(" configured as OUTPUT!"));
    return;
  }

  client.print(F("error: invalid mode "));
  client.print(mode);
}
