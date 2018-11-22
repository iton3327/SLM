#include <Arduino.h>
#include <iostream> 
#include <vector>
/* @file CustomKeypad.pde
|| @version 1.0
|| @author Alexander Brevig
|| @contact alexanderbrevig@gmail.com
||
|| @description
|| | Demonstrates changing the keypad size and key values.
|| #
*/
#include <Keypad.h>
using namespace std;

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {17, 5, 18, 19}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {2, 0, 4, 16}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

void stateStart (){
  Serial.println("-> Ready");
  Serial.println("-> Input your service key");
  Serial.println("'*':Delete or '#':Enter");
  Serial.print("-> ");
}

void stateInvalid(){
  Serial.println("-> Invalid service key!");
  Serial.println("-> Press any key to try again");
  char key = NULL;
  while(!key){
    key = customKeypad.getKey();
  }
  Serial.println();
}

void stateConfirm(String username){
  Serial.println("-> Confirm to start?");
  Serial.println("-> '*':Yes or '#':No");
  char key = NULL;
  while((key != '*')&&(key != '#')){
    key = customKeypad.getKey();
  }
  if(key == '*'){
    Serial.println();
    Serial.println("-> Washing");
    Serial.print("-> ");
    Serial.println(username);
  }
  Serial.println();
}

// void stateRunning(String username){
//   Serial.println("-> Washing");
//   Serial.print("-> ");
//   Serial.println(username);
// }

void setup(){
  Serial.begin(921600);
}

vector<string> q = {"111111","222222"};

void loop(){

  stateStart();
  char customKey = NULL;

  auto itr = q.begin();
  string service_key = *itr;  //Test reference service key
  string pressed = "";

  for (int i=0 ; i<6 ; i++){
    while(!customKey){
      customKey = customKeypad.getKey();
    }
    pressed += customKey;
    Serial.print(customKey);
    customKey = NULL;
  }
  
  Serial.println("\r\n");
  // Serial.print("Pressed : ");
  // Serial.println(pressed);

  if(pressed != service_key){
    stateInvalid();
  }else{
    q.erase(q.begin());
    stateConfirm("FakeCustomer");
    delay(2000);
  }

}