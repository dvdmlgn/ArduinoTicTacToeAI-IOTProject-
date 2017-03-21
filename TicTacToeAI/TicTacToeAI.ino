void setup() {
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:

  bool isNewMove = false;
  bool finishMove = false;
  bool canMove = false;

  int winner = 0;

  int turnCount = 0;
  int places[9];

  int priority1[] {4};
  int priority2[] {0, 2, 6, 8};
  int priority3[] {1, 3, 5, 7};

  // Write Code here to change "isNewMove" state from wifi data

  // Write Code to Update array on new move


  // This section of Code will determine if there are any available spaces on the grid to make a move
  if(isNewMove)
  {
    for(int i = 0; i < sizeof(places); i++)
    {
      if(places[i] == 0)
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
          if(places[priority1[i]] == 0)
            {
              places[priority1[i]] == 2;
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
          if(places[priority2[i]] == 0)
            {
              places[priority2[i]] == 2;
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
          if(places[priority3[i]] == 0)
            {
              places[priority3[i]] == 2;
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
    if(places[0] == places[1] && places[0] == places[2]
      || places[3] == places[4] && places[3] == places[5]
      || places[6] == places[7] && places[6] == places[8])
    {
      if(places[0] == 1 || places[3] == 1 || places[6] == 1)
      {
        winner = 1;
      }

      else {
        winner = 2;
      }
    }

    // Vertical Checks
    if(places[0] == places[3] && places[0] == places[6]
      || places[1] == places[4] && places[1] == places[7]
      || places[2] == places[5] && places[2] == places[8])
    {
      if(places[0] == 1 || places[1] == 1 || places[2] == 1)
      {
        winner = 1;
      }

      else {
        winner = 2;
      }
    }

    // Diagonal Left Checks
    if(places[0] == places[4] && places[0] == places[8])
    {
      if(places[0] == 1)
      {
        winner = 1;
      }

      else {
        winner = 2;
      }
    }

    // Diagonal Right Checks
    if(places[2] == places[4] && places[2] == places[6])
    {
      if(places[0] == 1)
      {
        winner = 1;
      }

      else {
        winner = 2;
      }
    }
  }

    
}
