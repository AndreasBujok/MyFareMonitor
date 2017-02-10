
/******************************************************************
* decrement value on valueblock
*******************************************************************/
void cmd_DecValue(byte blockAddr,long value)
	{
	// Authenticate using key B
	status = (MFRC522::StatusCode) mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_B,blockAddr,&key,&(mfrc522.uid));
	if (status != MFRC522::STATUS_OK)
		{
		Serial.print(F("PCD_Authenticate() failed: "));
		Serial.println(mfrc522.GetStatusCodeName(status));
		}
	else
		{
		status = mfrc522.MIFARE_Decrement(blockAddr,value);
		mfrc522.MIFARE_Transfer(blockAddr);
		
		Serial.println();
		Serial.print(F("Decrement value on Block "));
		Serial.print(blockAddr);
		Serial.print(F(" --"));
		Serial.println(value);
			
		
		if (status != MFRC522::STATUS_OK)
			{
			Serial.print(F("MIFARE_Increment failed: "));
			Serial.println(mfrc522.GetStatusCodeName(status));
			}
		}
	
	// Halt PICC
	mfrc522.PICC_HaltA();
	// Stop encryption on PCD
	mfrc522.PCD_StopCrypto1();
	
	return;
	}

/******************************************************************
* increment value on valueblock
*******************************************************************/
void cmd_IncValue(byte blockAddr,long value)
	{
	// Authenticate using key B
	status = (MFRC522::StatusCode) mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_B,blockAddr,&key,&(mfrc522.uid));
	if (status != MFRC522::STATUS_OK)
		{
		Serial.print(F("PCD_Authenticate() failed: "));
		Serial.println(mfrc522.GetStatusCodeName(status));
		}
	else
		{
		status = mfrc522.MIFARE_Increment(blockAddr,value);
		mfrc522.MIFARE_Transfer(blockAddr);
		
		Serial.println();
		Serial.print(F("Increment value on Block "));
		Serial.print(blockAddr);
		Serial.print(F(" ++"));
		Serial.println(value);
			
		
		if (status != MFRC522::STATUS_OK)
			{
			Serial.print(F("MIFARE_Increment failed: "));
			Serial.println(mfrc522.GetStatusCodeName(status));
			}
		}
	
	// Halt PICC
	mfrc522.PICC_HaltA();
	// Stop encryption on PCD
	mfrc522.PCD_StopCrypto1();
	
	return;
	}

/******************************************************************
* get value to valueblock
*******************************************************************/
void cmd_GetValue(byte blockAddr)
	{
	// Authenticate using key B
	status = (MFRC522::StatusCode) mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_B,blockAddr,&key,&(mfrc522.uid));
	if (status != MFRC522::STATUS_OK)
		{
		Serial.print(F("PCD_Authenticate() failed: "));
		Serial.println(mfrc522.GetStatusCodeName(status));
		}
	else
		{
		long value;
		status = mfrc522.MIFARE_GetValue(blockAddr,&value);
		
		Serial.println();
		Serial.print("Value on Block ");
		Serial.print(blockAddr);
		Serial.print(" is: ");
		Serial.println(value);
			
		
		if (status != MFRC522::STATUS_OK)
			{
			Serial.print(F("MIFARE_GetValue failed: "));
			Serial.println(mfrc522.GetStatusCodeName(status));
			}
		}
	
	// Halt PICC
	mfrc522.PICC_HaltA();
	// Stop encryption on PCD
	mfrc522.PCD_StopCrypto1();
	
	return;
	}

/******************************************************************
* set value to valueblock
*******************************************************************/
void cmd_SetValue(byte blockAddr,long value)
	{
	// Authenticate using key B
	status = (MFRC522::StatusCode) mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_B,blockAddr,&key,&(mfrc522.uid));
	if (status != MFRC522::STATUS_OK)
		{
		Serial.print(F("PCD_Authenticate() failed: "));
		Serial.println(mfrc522.GetStatusCodeName(status));
		}
	else
		{
		Serial.println();
		Serial.print(F("Write "));
		Serial.print(value);
		Serial.print(F(" to Block "));
		Serial.println(blockAddr);
		status = mfrc522.MIFARE_SetValue(blockAddr, value);
		if (status != MFRC522::STATUS_OK)
			{
			Serial.print(F("MIFARE_SetValue failed: "));
			Serial.println(mfrc522.GetStatusCodeName(status));
			}
		}
	
	// Halt PICC
	mfrc522.PICC_HaltA();
	// Stop encryption on PCD
	mfrc522.PCD_StopCrypto1();
	
	return;
	}

/******************************************************************
* set access bits on trailerblock
* http://www.akafugu.jp/posts/blog/2015_09_01-MIFARE-Classic-1K-Access-Bits-Calculator
* (windows-only): http://www.sendspace.com/file/o3frc9 (pass: mifcalc10)
* http://tutorials.boecker-systemelektronik.de/MFRC522-Programmierung_mit_Arduino/PdM_12.html
* http://tutorials.boecker-systemelektronik.de/Mifare_S50-Chip/S50_1.html
*******************************************************************/
void cmd_AccessBits2Hex(byte block_0,byte block_1,byte block_2,byte block_3)
	{
	byte TrailerBuffer[3];
	mfrc522.MIFARE_SetAccessBits(&TrailerBuffer[0],block_0,block_1,block_2,block_3);
	Serial.print(F("Access bits value:"));
	dump_byte_array(TrailerBuffer,3,true);
	
	return;
	}


/******************************************************************
* set Hex to access bits on trailerblock
* Calculates the bit pattern needed for the specified access bits. In the [C1 C2 C3] tuples C1 is MSB (=4) and C3 is LSB (=1).
*******************************************************************/
void cmd_Hex2AccessBits(byte Byte0,byte Byte1,byte Byte2)
	{
	byte b0 = ((Byte2 & 16) >> 4) | ((Byte2 & 1) << 1) | ((Byte1 & 16) >> 2);
	byte b1 = ((Byte2 & 32) >> 5) | ((Byte2 & 2) << 0) | ((Byte1 & 32) >> 3);
	byte b2 = ((Byte2 & 64) >> 6) | ((Byte2 & 4) >> 1) | ((Byte1 & 64) >> 4);
	byte b3 = ((Byte2 & 128) >> 7) | ((Byte2 & 8) >> 2) | ((Byte1 & 128) >> 5);
	
	Serial.print(F("Block0: "));
	Serial.println(b0,HEX);
	Serial.print(F("Block1: "));
	Serial.println(b1,HEX);
	Serial.print(F("Block2: "));
	Serial.println(b2,HEX);
	Serial.print(F("Block3: "));
	Serial.println(b3,HEX);
	return;
	}




/******************************************************************
* command dump sector n
*******************************************************************/
void cmd_DumpSector(byte sector)
	{
	Serial.println();
	Serial.print(F("Sector "));
	Serial.print(sector);
	Serial.println(F(":"));
	
	mfrc522.PICC_DumpMifareClassicSectorToSerial(&(mfrc522.uid),&(key),sector);
	// Halt the PICC before stopping the encrypted session.
	mfrc522.PICC_HaltA();
	// Stop encryption on PCD
	mfrc522.PCD_StopCrypto1();
	
	return;
	}

/******************************************************************
* command get UID
*******************************************************************/
void cmd_GetUID()
	{
	String TAGID;
	Serial.print(F("\r\nUID: "));
	for (byte i = 0; i < mfrc522.uid.size; i++)
		{
		int uid = mfrc522.uid.uidByte[i];
		Serial.print(norm_hex(uid));
		}
	Serial.println();
	
	return;
	}

/******************************************************************
* command get cardtype
*******************************************************************/
void cmd_GetCardType()
	{
	Serial.print(F("\r\nCardType: "));
	MFRC522::PICC_Type piccType = mfrc522.PICC_GetType(mfrc522.uid.sak);
	Serial.println(mfrc522.PICC_GetTypeName(piccType));
	return;
	}

/******************************************************************
* command dump full card
*******************************************************************/
void cmd_DumpCard()
	{
	Serial.println();
	mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
	return;
	}

/******************************************************************
* command block n in ASCII or in HEX
* keytype: 0->KEY-A, 1->KEY-B
*******************************************************************/
void cmd_DumpBlock(byte blockAddr,boolean showhex,boolean keytype)
	{
	if (keytype == true)
		{
		// Authenticate using key B
		status = (MFRC522::StatusCode) mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_B,blockAddr,&key,&(mfrc522.uid));
		Serial.println("Use key as auth B");
		}
	else
		{
		// Authenticate using key A
		status = (MFRC522::StatusCode) mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A,blockAddr,&key,&(mfrc522.uid));
		Serial.println("Use key as auth A");
		}
	
	// Authenticate using key A
	//status = (MFRC522::StatusCode) mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A,blockAddr,&key,&(mfrc522.uid));
	if (status != MFRC522::STATUS_OK)
		{
		Serial.print(F("PCD_Authenticate() failed: "));
		Serial.println(mfrc522.GetStatusCodeName(status));
		}
	else
		{
		Serial.println();
		Serial.print(F("Block :"));
		Serial.println(blockAddr);
		status = (MFRC522::StatusCode) mfrc522.MIFARE_Read(blockAddr, buffer, &size);
		if (status != MFRC522::STATUS_OK)
			{
			Serial.print(F("MIFARE_Read() failed: "));
			Serial.println(mfrc522.GetStatusCodeName(status));
			
			}
		else
			{
			dump_byte_array(buffer,16,showhex);
			}
		Serial.println();
		}
	
	// Halt PICC
	mfrc522.PICC_HaltA();
	// Stop encryption on PCD
	mfrc522.PCD_StopCrypto1();
	
	return;
	}

/******************************************************************
* command dump KEY
*******************************************************************/
void cmd_DumpKey()
	{
	Serial.println();
	Serial.print(F("Key: "));
	dump_byte_array(key.keyByte,6,true);
	
	return;
	}

/******************************************************************
* command set KEY,
* if no key given, set key to transport key
*******************************************************************/
void cmd_SetKey(String myKey)
	{
	if (myKey.length() == 0)
		{
		Serial.println(F("Set key to transport value."));
		for (byte i = 0; i < 6; i++)
			{
			key.keyByte[i] = 0xff;
			}
		}
	else
		{
		int y = 0;
		for (byte i = 0; i < myKey.length(); i=i+2)
			{
			String XX = myKey.substring(i,i+2);
			int hex = (int) strtol(&XX[0],NULL,16);
			key.keyByte[y] = hex;
			y++;
			}
		}
	
	return;
	}

/******************************************************************
* command help syntax
*******************************************************************/
void cmd_Help(String txt)
	{
	Serial.println("\r\n"+txt);
	Serial.println(F("============="));
	Serial.println(F("Help:"));
	Serial.println(F(" h     : print help"));
	Serial.println();
	Serial.println(F(" guid  : get Card UID"));
	Serial.println(F(" gct   : get CardType"));
	Serial.println(F(" gg    : get Rx Gain"));
	Serial.println(F(" sg,<gain> : set Rx gain <0-7> (18dB - 48dB)"));
	Serial.println(F(" dk        : dump key"));
	Serial.println(F(" sk,<KEY> : set key (6 hex values). Has <KEY> no value, key will be set to transport key."));
	Serial.println(F(" ab2hex,<value block 0>,<value block 1>,<value block 2>,<value block 3> : convert access bits to hex values for trailerblock"));
	Serial.println(F(" hex2ab,<value 0>,<value 1>,<value 2> : convert hex values to access bits for trailerblock"));
	Serial.println();
	Serial.println(F(" dc    : dump card, use fix the transportkey."));
	Serial.println(F(" ds,<sector> : dump sector <0-n>, use key as auth A."));
	Serial.println(F(" dba,<block>,[<'a'|'b'>] : dump in ascii of block <0-n> with KEY A|B (default is A)"));
	Serial.println(F(" dbh,<block>,[<'a'|'b'>] : dump in HEX of block <0-n> with KEY A|B (default is A)"));
	Serial.println(F(" wba,<block>,<ascii-data>,[<'a'|'b'>],[<startpoint>] : write ascii text to block <0-n> (max. 16 char.), with key A|B (default is A), start position (default is 1)"));
	Serial.println(F(" wbh,<block>,<hex-data>  ,[<'a'|'b'>],[<startpoint>] : write hex values to block <0-n> (max. 32 char.), with key A|B (default is A), start position (default is 1)"));
	Serial.println();
	Serial.println(F(" sv,<block>,<val> : set value to valueblock <n>"));
	Serial.println(F(" gv,<block> : get value of valueblock <n>"));
	Serial.println(F(" iv,<block>,<val> : increment valueblock <n> with value <val>"));
	Serial.println(F(" dv,<block>,<val> : decrement valueblock <n> with value <val>"));
	
	return;
	}

/******************************************************************
* command print "ready."
*******************************************************************/
void printReady()
	{
	Serial.println(F("ready.\r\n"));
	return;
	}


