int ledArr[4] = {5, 6, 7, 8};//connection from arduiona to leds
int counterGlobal = 0;//global counter used in functions
boolean first, second;//Variables depending on the state of the button being pressed
int button_id = 2;//the port variable the button is connected to
boolean button = true;//variable holding the high low status of the button
int led_id;//Variable used in founction2 that holds port numbers
boolean flag = true;//In founction2, the variable that controls the lighting of the leds from right to left, then from left to right again
int TIME_LED_COUNTER = 500; //delay time for counter
int TIME_LED_SLIDER = 250; //delay time for slider

int poww(int n, int k)//power calculation function for using function1
{
    int result = 1;
    for (int i = 1; i < k + 1; i++)
    {
        result = result * n;
    }
    return result;
}
void function1(int number)//counter function
{
    digitalWrite(ledArr[0], LOW);
    digitalWrite(ledArr[1], LOW);
    digitalWrite(ledArr[2], LOW);
    digitalWrite(ledArr[3], LOW);
    int power = 3;//Since we have 4 LEDs, it can be 2 ^ 3 at most. 

    while (number > -1 && number != 0)
    {
        int binary_base = poww(2, power);//Determines from which LED it will light

        int tempnum = number - binary_base;// It is the control variable to prevent the LED in the next step.

        if (tempnum >= 0)//If tempnum is greater than or equal to 0, the led that should be lit turns on.
        {
            number = number - binary_base;
            digitalWrite(ledArr[power], HIGH);
        }

        power--;
    }
}

void function2(int counter)//slider function
{
    digitalWrite(ledArr[0], LOW);
    digitalWrite(ledArr[1], LOW);
    digitalWrite(ledArr[2], LOW);
    digitalWrite(ledArr[3], LOW);
    led_id = ledArr[counter];//gives the port of the next led

    if (flag == false)//When flag is false, the leds start flashing in reverse.(from 8th port to 5th port)
    {
        led_id = ledArr[3 - counter];
        digitalWrite((led_id), HIGH);
    }

    else//If flag is true, the leds will start from the 5th port to the 8th port.
    {

        led_id = ledArr[counter];
        digitalWrite(led_id, HIGH);
    }
    if (counter == 3)//When counter is 3, port 8.port works.Then flag false to reverse.
    {
        flag = false;
    }
    if (led_id == 5)//After 5.port is executed, flag will be true again
    {
        flag = true;
    }
}

void setup()
{
    Serial.begin(9600);
    pinMode(ledArr[0], OUTPUT);
    pinMode(ledArr[1], OUTPUT);
    pinMode(ledArr[2], OUTPUT);
    pinMode(ledArr[3], OUTPUT);
    pinMode(button_id, INPUT);
}

void loop()
{

    first = digitalRead(button_id);//reading whether the button is HIHG or LOW
    if (second != first)//The if block runs if the previous value of the button is not equal to its current value
    {
        if (first == HIGH)//If the button is pressed, the if block works.
        {
            button = !button;//The button function, which determines which function will run, is reversed.
            counterGlobal = 0;//With the reset of the counterGlobal function, the counter or slider function starts over when the button is pressed.
            delay(50);
        }
    }
    second = first;//The current state of the button is stored in a variable

    if (button)//When the button variable is true, function1 (counter function) works.
    {
        if (counterGlobal == 16)//When counterGlobal is 16, counterGlobal is reset to return to the beginning.
        {
            counterGlobal = 0;
          
        }
        function1(counterGlobal);
    }
    else
    {
        if (counterGlobal == 4)//When counterGlobal is 4 in function 2, counterGlobal equals 1
        {
            counterGlobal = 1;
        }

        function2(counterGlobal);
    }
    counterGlobal++; // counterGlobal increases by one each time the loop function runs
    if (button)
    {
        delay(TIME_LED_COUNTER);//delay time for function1 (counter function)
    }
    else
    {
        delay(TIME_LED_SLIDER);//delay time for function2 (slider function)
    }
}
