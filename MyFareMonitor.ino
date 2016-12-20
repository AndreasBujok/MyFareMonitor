
/*
	MyFare Monitor Monitor
	(c) 2016
	Andreas Bujok
*/


#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal.h>

#define LCD_RS 7
#define LCD_ENABLE 6
#define LCD_D4 5
#define LCD_D5 4
#define LCD_D6 3
#define LCD_D7 2
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(LCD_RS,LCD_ENABLE,LCD_D4,LCD_D5,LCD_D6,LCD_D7);

// initialize the MFRCS522 library
#define SS_PIN 10 // RFID-RC522 SDA
#define RST_PIN 9 // RFID-RC522 RST
MFRC522 mfrc522(SS_PIN, RST_PIN);
//create a MIFARE_Key struct named 'key',
// which will hold the card information
MFRC522::MIFARE_Key key;
MFRC522::StatusCode status;
byte buffer[18];
byte size = sizeof(buffer);
//This array is used for reading out a block. The MIFARE_Read method requires a buffer 
// that is at least 18 bytes to hold the 16 bytes of a block.
byte readbackblock[18];


String version = "2.0";
String logo = "MyFare Monitor V "+version+"\r\n(c)2016 Andreas Bujok";

int hint;
byte gain;
String gain_str[] ={"18dB","23dB","18dB","23dB","33dB","38dB","43dB","48dB"};

String inputString = ""; // a string to hold incoming data
boolean stringComplete = false; // whether the string is complete
#define para_max 5 //maximum of parameter
String cmd[para_max]; // command parameter buffer

/**============================================
* Write Data "data" to block "blockAddr"
* depend of the value of 'hex' as ASCII or HEX. 
* Start is optinal, set the text startposition (1-16),
* default is 0 => position 1
==============================================*/
void cmd_WriteBlock(byte blockAddr,String data,boolean hex,byte start = 0)
	{
	Serial.print("start: ");
	Serial.println(start);
	// Authenticate using key A
	status = (MFRC522::StatusCode) mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A,blockAddr,&key,&(mfrc522.uid));
	if (status != MFRC522::STATUS_OK)
		{
		Serial.print(F("PCD_Authenticate() failed: "));
		Serial.println(mfrc522.GetStatusCodeName(status));
		return;
		}
	
	// Read block
	status = (MFRC522::StatusCode) mfrc522.MIFARE_Read(blockAddr, buffer, &size);
	if (status != MFRC522::STATUS_OK)
		{
		Serial.print(F("MIFARE_Read() failed: "));
		Serial.println(mfrc522.GetStatusCodeName(status));
		}
	//Fill data -> buffer
	int len = data.length();
	
	if (hex == false)
		{
		if (len > 16){len = 16;}
		}
	else
		{
		if (len > 32){len = 32;}
		}
	
	if (start > 0){start--;}
	
	int XX;
	int Y = start;
	// fill input into buffer
	for (byte i = 0; i < len; i++)
		{
		
		if (hex == false)
			{
			XX = data.charAt(i);
			buffer[Y] = XX;
			}
		else
			{
			String dummy = String(data.substring(i,i+2));
			int hex = (int) strtol(&dummy[0],NULL,16);
			buffer[Y] = hex;
			Serial.print("Buffer #");
			Serial.println(Y);
			i++;
			
			}
		Y++;
		}
	
	Serial.print("Block ");
	Serial.print(blockAddr);
	Serial.println(" now:");
	dump_byte_array(buffer,16,hex);
	Serial.println();
	// Write block
	status = mfrc522.MIFARE_Write(blockAddr, buffer, 16);
	if (status != MFRC522::STATUS_OK)
		{
		Serial.print(F("MIFARE_Write() failed: "));
		Serial.println(mfrc522.GetStatusCodeName(status));
		return;
		}
	
	// Halt PICC
	mfrc522.PICC_HaltA();
	// Stop encryption on PCD
	mfrc522.PCD_StopCrypto1();
	
	return;
	}


void setup()
	{
	Serial.begin(9600);
	SPI.begin();
	mfrc522.PCD_Init();
	
	// reserve bytes for the inputString:
	inputString.reserve(30);
	
	// set Key A to transport Key
	cmd_SetKey("ffffffffffff");
	Serial.println();
	
	// Get the MFRC522 firmware version
	Serial.print("RC522 ");
	mfrc522.PCD_DumpVersionToSerial();
	
	// define LCD to 16 * 2 Characters
	lcd.begin(16, 2);
	lcd.print("RFID RC522 V " + version);
	cmd_Help(logo);
	printReady();
	}


void loop()
	{
	lcd.setCursor(0, 1);
	
	/**=================================
	* commands effected to MFRC522 only
	===================================*/
	if (stringComplete)
		{
		splitString(inputString);
		String command;
		command = cmd[0];
		command.toLowerCase();
		
		// help syntax
		if(command == "h")
			{
			cmd_Help(logo);
			printReady();
			inputString = "";
			stringComplete = false;
			lcd.print("Command: h      ");
			hint = 0;
			return;
			}
		
		// dump key A
		else if(command == "dk")
			{
			cmd_DumpKey();
			Serial.println();
			lcd.print("Command: "+command+"            ");
			printReady();
			inputString = "";
			stringComplete = false;
			hint = 0;
			return;
			}
		
		// get gain of receiver
		else if(command == "gg")
			{
			lcd.print("Command: "+command+"            ");
			gain = (mfrc522.PCD_GetAntennaGain()) >> 4;
			Serial.print("Gain is ");
			Serial.println(gain_str[gain]);
			printReady();
			inputString = "";
			stringComplete = false;
			hint = 0;
			return;
			}
		
		// set gain of receiver
		else if(command == "sg")
			{
			lcd.print("Command: "+command+"            ");
			String dummy = cmd[1];
			gain = dummy.toInt();
			mfrc522.PCD_SetAntennaGain(gain << 4);
			gain = (mfrc522.PCD_GetAntennaGain()) >> 4;
			Serial.print("Gain is now: ");
			Serial.println(gain_str[gain]);
			printReady();
			inputString = "";
			stringComplete = false;
			hint = 0;
			return;
			}
		
		// set key A in hex values
		else if(command == "sk")
			{
			String dummy = cmd[1];
			cmd_SetKey(dummy);
			Serial.println("Setting Key A ready.");
			cmd_DumpKey();
			Serial.println();
			lcd.print("Command: "+command+"            ");
			printReady();
			inputString = "";
			stringComplete = false;
			hint = 0;
			}
		}
	
	if ( ! mfrc522.PICC_IsNewCardPresent())
		{
		if (hint == 1)
			{
			Serial.println("waiting of MyFare Classic Card....");
			hint = 0;
			}
		return;
		}
	
	if ( ! mfrc522.PICC_ReadCardSerial())
		{
		return;
		}
	
	// commands effected to contacless card
	if (stringComplete)
		{
			
		splitString(inputString);
		
		String command;
		command = cmd[0];
		command.trim();
		command.toLowerCase();
		
		// get GUID of card
		if(command == "guid")
			{
			cmd_GetUID();
			lcd.print("Command: "+command+"            ");
			printReady();
			}
		
		// get card type
		else if(command== "gct")
			{
			cmd_GetCardType();
			lcd.print("Command: "+command+"            ");
			printReady();
			}
		
		// dump all blocks of card
		else if(command == "dc")
			{
			cmd_DumpCard();
			lcd.print("Command: "+command+"            ");
			printReady();
			}
		
		// dump ector 0-n
		else if(command == "ds")
			{
			String dummy = cmd[1];
			byte sector = dummy.toInt();
			cmd_DumpSector(sector);
			lcd.print("Command: "+command+"            ");
			printReady();
			}
		
		// dump block n in hex or ASCII values
		else if(command == "dbh" || command == "dba")
			{
			String dummy = cmd[1];
			byte blockAddr = dummy.toInt();
			// set ASCII or HEX for output
			boolean output = (command == "dbh")?true:false;
			cmd_DumpBlock(blockAddr,output);
			lcd.print("Command: "+command+"            ");
			printReady();
			}
		
		// write ASCII or HEX data to block n
		else if(command == "wbh" || command == "wba")
			{
			String dummy = cmd[1];
			byte blockAddr = dummy.toInt();
			String value = cmd[2];
			dummy = cmd[3];
			int go = dummy.toInt();
			boolean output = (command == "wbh")?true:false;
			cmd_WriteBlock(blockAddr,value,output,go);
			lcd.print("Command: "+command+"            ");
			printReady();
			}
		
		// unknown order, syntax error
		else
			{
			Serial.println("??? '"+cmd[0]+"' unknown command.");
			Serial.println("type h for help.");
			}
		
		// clear all about inputbuffer
		GarbageCollection();
		}
	}


