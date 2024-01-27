/*
* Name: Harnoor Saigal
* Student No.: 28703262
* CWL: hsaigal
* Lab section: L2C
* email: hsaigal@student.ubc.ca
* Purpose: To create Simon Says game. A sequence of colors are shown to the player. 
*          The player should memorize those and reproduce the same sequence by pushing the corresponding switches.
*          The displayed sequence begins with a single colour.
*          If the player follows successfully, another randomly chosen colour is added to the end of the sequence each time
*          and this new sequence is displayed. So the sequence becomes longer each time.
*          The game ends if the player makes a mistake, or if the player wins.
*/

//define constants
#define one_second 1000
#define half_second 500
#define ON HIGH
#define OFF LOW

//symbolic constants for INPUT/OUTPUT pins
int const greenButton = 4;
int const blueButton = 5;
int const yellowButton = 6;
int const redButton = 7;
int const winLED = 8;
int const lostLED = 13;
int const greenLED = 9;
int const blueLED = 10;
int const yellowLED = 11;
int const redLED = 12;

//define functions prototypes
char const test[] = "Game Starting\n";
unsigned long currentMillis; 
unsigned long previousMillis;
int time; //to reset the game
//function to flash green LED after win
void win(void)
{
  for(int j=0;j<3;j++)
  {
    digitalWrite(winLED,ON);
    delay(half_second);
    digitalWrite(winLED,OFF);
    delay(half_second);
  }
}
//function to flash red LED after lost
void lost(void)
{
  for(int j=0;j<3;j++)
  {
    digitalWrite(lostLED,ON);
    delay(half_second);
    digitalWrite(lostLED,OFF);
    delay(half_second);
  }
}

//function to flash any in-game LED
void flashLED(int LED)
{
  digitalWrite(LED,ON);
  delay(half_second);
  digitalWrite(LED,OFF);
  delay(half_second);
}

//function to diplay the random sequence on the in-game LEDs
void displayPattern(int LEDpattern[],int size)
{
  //LEDpattern array is for display pattern of in-game LEDs
  randomSeed(analogRead(0));  //initialises the rng 
  int LEDpins[4]={greenLED,blueLED,yellowLED,redLED};
  //this loop generates a random sequence of the order of the in-game LEDs in which they will turn on
  int num;
  for(int i=0;i<size;i++)
  {
    num = random(3);
    LEDpattern[i] = LEDpins[num];
  }
}

//function to check which LED from the pattern was turned on and return the pin no. of the button that needs to be pressed
int buttonComparison(int LEDpattern[], int size, int j)
{
  int match[][4] = {{greenLED,blueLED,yellowLED,redLED},{greenButton,blueButton,yellowButton,redButton}};
  for(int a=0; a<2; a++)
  {
    for(int b=0; b<4; b++)  //loop to find out which random in-game LED is on
    {
      if(LEDpattern[j]==match[0][b])
      {
        return match[1][b]; //returns the pin no. of corresponding button that needs to be pressed
      }
    }
  }
}
//function to reset the game and display lost if the player doesn't press any button for too long
int overtime(int time)
{
  if(digitalRead(greenButton)==OFF && digitalRead(blueButton)==OFF && digitalRead(yellowButton)==OFF && digitalRead(redButton)==OFF && time>30000)
  {
    //lost();
    //stop = true;
    //delay(2000);  //reset time before the game restarts
    time=0;
    return ON;
  }
  return OFF;
}
//initialization
void setup()
{
  //configure pin modes (inputs, outputs)
  pinMode(greenButton,INPUT);
  pinMode(blueButton,INPUT);
  pinMode(yellowButton,INPUT);
  pinMode(redButton,INPUT);
  pinMode(winLED,OUTPUT);
  pinMode(lostLED,OUTPUT);
  pinMode(greenLED,OUTPUT);
  pinMode(blueLED,OUTPUT);
  pinMode(yellowLED,OUTPUT);
  pinMode(redLED,OUTPUT);
}


//main program loop
void loop()
{
  int score;
  int stop = false;
  int trueButton;
  int pattern[5]={0};
  displayPattern(pattern,5);
  for(score=0; score<5 && stop == false; score++)
  {
    for(int showNext = 0; showNext <= score; showNext++) //This loops displays the next LED in the sequence when the player presses the correct button
    {
      flashLED(pattern[showNext]);
    }
    currentMillis = millis();  //to record time for time out if the player doesn't press any button for a long time
    previousMillis = 0;
    time = currentMillis - previousMillis;
    int correct = 0;
    int tnum = 1;
    while(correct<=score && tnum == 1)
    {
      trueButton = buttonComparison(pattern,5,correct);
      if(digitalRead(trueButton) == ON && overtime(time)==OFF) //if correct button is pressed in the time limit
      {
        flashLED(winLED); //turns on green LED to indicate when correct button is pressed each time
        previousMillis = currentMillis;
        time = currentMillis - previousMillis;;
        correct++;
        if(correct > score)
        {
          tnum = 0;
        }
      }
      else  //condition to check when the player doesn't click the right button or passes the overtime of 30 seconds
      {
        int search = 0;
        while(search == 0)  //checking through all buttons to see if the button pressed by the player is not the true button and then displays lost fucntion
        {
          //repeating conditions to check all buttons
          if(overtime(time= currentMillis - previousMillis)==ON)  
          {
            lost();
            search = 1;
            stop = true;
            delay(2000);  //reset time before the game restarts
            previousMillis = currentMillis;
            time = currentMillis - previousMillis;;
            correct = 100;
          }
          else
          {
            if(digitalRead(greenButton)==ON)
            {
              if(greenButton == trueButton)
              {
                search = 1;
              }
              else
              {
                lost();
                search = 1;
                stop = true;
                delay(2000);  //reset time before the game restarts
                previousMillis = currentMillis;
                time = currentMillis - previousMillis;;
                correct = 100;
              }
            }
            if(digitalRead(blueButton)==ON)
            {
              if(blueButton == trueButton)
              {
                search = 1;
              }
              else
              {
                lost();
                search = 1;
                stop = true;
                delay(2000);  //reset time before the game restarts
                previousMillis = currentMillis;
                time = currentMillis - previousMillis;;
                correct = 100;
              }
            }
            if(digitalRead(yellowButton)==ON)
            {
              if(yellowButton == trueButton)
              {
                search = 1;
              }
              else
              {
                lost();
                search = 1;
                stop = true;
                delay(2000);  //reset time before the game restarts
                previousMillis = currentMillis;
                time = currentMillis - previousMillis;;
                correct = 100;
              }
            }
            if(digitalRead(redButton)==ON)
            {
              if(redButton == trueButton)
              {
                search = 1;
              }
              else
              {
                lost();
                search = 1;
                stop = true;
                delay(2000);  //reset time before the game restarts
                previousMillis = currentMillis;
                time = currentMillis - previousMillis;;
                correct = 100;
              }
            }
          }
        }
      }
    }
  }//for loop for score ends
  if(score==5)  //win displayed if game ends after player presses all the correct buttons
  {
    win();
    delay(2000);
    previousMillis = currentMillis;
    time = currentMillis - previousMillis;
  }
}
