
/******************************************************************
* Helper routine to dump a byte array as hex values to Serial.
*******************************************************************/
void dump_byte_array(byte *buffer, byte bufferSize,boolean show_hex)
	{
	for (byte i = 0; i < bufferSize; i++)
		{
		if (show_hex == true)
			{
			Serial.print(buffer[i] < 0x10 ? " 0" : " ");
			Serial.print(buffer[i], HEX);
			}
		else
			{
			if (isAlphaNumeric(buffer[i]))
				{
				Serial.print(char(buffer[i]));
				}
			else
				{
				Serial.print(".");
				}
			}
		}
	}

/******************************************************************
* Split the string s into cmd[] array, seperater is ','
*******************************************************************/
String splitString(String s)
	{
	int index = 0;
	int found = 0;
	int flag = 0;
	String dummy;
		
	//loop until no comma found
	while (s.indexOf(",",found)> -1)
		{
		flag = 1;
		//find first comma
		found = s.indexOf(",",found);
		dummy = s.substring(0,found);
				
		cmd[index] = dummy;
		if (index < para_max)
			{
			index++;
			}
		else
			{
			}
		
		
		//reonfigure inputstring
		s = s.substring(found+1);
		
		// set found to the beginning of the string
		found = 0;
		}
	dummy = s;
	cmd[index] = dummy;
	return "";
	}

/******************************************************************
* clear all about input buffer
*******************************************************************/
void GarbageCollection()
	{
	// clear Input stuff
	for(int i=0;i < para_max;i++)
		{
		cmd[i] = "";
		}
	inputString = "";
	stringComplete = false;
	
	return;
	}

/******************************************************************
* normalize a value to ttwo hex digit
*******************************************************************/
String norm_hex(int chr)
	{
	String txt;
	if (chr == 0)
		{
		txt = "00";
		}
	else if (chr < 10 )
		{
		txt = "0" + String(chr,HEX);
		}
	else
		{
		txt = String(chr,HEX);
		}
	txt.toUpperCase();
	return txt;
	}

/******************************************************************
* serial input via interrupt
* add all incoming chars into inputbuffer
* hint; all incoming whitespaces will be deleted
*******************************************************************/
void serialEvent()
	{
	while (Serial.available())
		{
		// get the new byte:
		char inChar = (char)Serial.read();
		// add it to the inputString:
		inputString += inChar;
		//inputString.toLowerCase();
		inputString.trim();
				
		// if the incoming character is a newline, set a flag
		// so the main loop can do something about it:
		if (inChar == '\n')
			{
			stringComplete = true;
			hint = 1;
			}
		}
	}



