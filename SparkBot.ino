/* A Spark function to parse the commands */
int rcCarControl(String command);

/* Globals -------------------------------------------------------------------*/
int leftMotorEnable   = D0;
int leftMotorDir    = D3;
int rightMotorEnable  = D1;
int rightMotorDir   = D4;

int led = D2;                 // a red led for debugging
int rbump = D5;               // rear bumper switch
int IR_PROXIMITY_SENSOR = A1; // Analog input pin that is attached to the sensor
float ADC_REF = 3.3;          // reference voltage of ADC is 3V3
float voltage;                // the sensor voltage, you can calculate or find the distance

/* This function is called once at start up ----------------------------------*/
void setup()
{
  //Register Spark function
  Spark.function("rccar", rcCarControl);

  pinMode(leftMotorDir, OUTPUT);
  pinMode(leftMotorEnable, OUTPUT);
  pinMode(rightMotorDir, OUTPUT);
  pinMode(rightMotorEnable, OUTPUT);
  
  pinMode(led, OUTPUT);
  pinMode(rbump, INPUT);

}

/* This function loops forever --------------------------------------------
void loop()
{
    if (digitalRead(rbump) == HIGH){
      digitalWrite(led, HIGH);
      delay(100);
      digitalWrite(led, LOW);
      delay(100);
    }
    else{
      digitalWrite(led, HIGH);
      stop();
    }
    
}
*/

/* Motor control functions *****************************************************/

void stop()
{
    digitalWrite(leftMotorEnable,LOW);
    digitalWrite(rightMotorEnable,LOW);

    digitalWrite(leftMotorDir,LOW);
    digitalWrite(rightMotorDir,LOW);
}

void back()
{
    digitalWrite(leftMotorDir,LOW);
    digitalWrite(rightMotorDir,LOW);

    analogWrite(leftMotorEnable,127);
    analogWrite(rightMotorEnable,127);
}

void forward()
{
    digitalWrite(leftMotorDir,HIGH);
    digitalWrite(rightMotorDir,HIGH);

    analogWrite(leftMotorEnable,200);
    analogWrite(rightMotorEnable,200);
}

void right()
{
    digitalWrite(leftMotorDir,HIGH);
    digitalWrite(rightMotorDir,HIGH);

    analogWrite(leftMotorEnable,50);
    analogWrite(rightMotorEnable,250);
}

void left()
{
     digitalWrite(leftMotorDir,HIGH);
    digitalWrite(rightMotorDir,HIGH);

    analogWrite(leftMotorEnable,250);
    analogWrite(rightMotorEnable,50);
}

/*****************************************************************************/
/*Function: Get voltage from the sensor pin that is connected with analog pin*/
/*Parameter:-void												        	 */
/*Return:	-float,the voltage of the analog pin						     */

float getVoltage()
{
	int sensor_value;
	int sum;  
	// read the analog in value:
	for (int i = 0;i < 20;i ++) //Continuous sampling 20 times
	{
		sensor_value = analogRead(IR_PROXIMITY_SENSOR); 
		sum += sensor_value;
	}
	sensor_value = sum / 20;
	float voltage;
	voltage = (float)sensor_value*ADC_REF/1024;
	return voltage;
} 

/*******************************************************************************
 * Function Name  : rcCarControl
 * Description    : Parses the incoming API commands and sets the motor control
 * Input          : RC Car commands
                    e.g.: rc,FORWARD
                          rc,BACK
 * Output         : Motor signals
 * Return         : 1 on success and -1 on fail
 *******************************************************************************/
int rcCarControl(String command)
{
  if(command.substring(3,7) == "STOP")
  {
    stop();
    return 1;
  }

  if(command.substring(3,7) == "BACK")
  {
    back();
    return 1;
  }

  if(command.substring(3,10) == "FORWARD")
  {
    forward();
    return 1;
  }

  if(command.substring(3,8) == "RIGHT")
  {
    right();
    return 1;
  }

  if(command.substring(3,7) == "LEFT")
  {
    left();
    return 1;
  }

  // If none of the commands were executed, return false
  return -1;
}
