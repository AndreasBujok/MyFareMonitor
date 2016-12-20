
/******************************************************************
* command dump sector n
*******************************************************************/
void cmd_DumpSector(byte sector)
	{
	Serial.println();
	Serial.print("Sector ");
	Serial.print(sector);
	Serial.println(":");
	
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
	Serial.print("\r\nUID: ");
	for (byte i = 0; i < mfrc522.uid.size; i++)
		{
		int uid = mfrc522.uid.uidByte[i];
		Serial.print(norm_hex(uid));
		}
	Serial.println("");
	
	return;
	}

/******************************************************************
* command get cardtype
*******************************************************************/
void cmd_GetCardType()
	{
	Serial.print("\r\nCardType: ");
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
*******************************************************************/
void cmd_DumpBlock(byte blockAddr,boolean showhex)
	{
	// Authenticate using key A
	status = (MFRC522::StatusCode) mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A,blockAddr,&key,&(mfrc522.uid));
	if (status != MFRC522::STATUS_OK)
		{
		Serial.print(F("PCD_Authenticate() failed: "));
		Serial.println(mfrc522.GetStatusCodeName(status));
		}
	
	Serial.println();
	Serial.print("Block :");
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
	
	// Halt PICC
	mfrc522.PICC_HaltA();
	// Stop encryption on PCD
	mfrc522.PCD_StopCrypto1();
	
	return;
	}

/******************************************************************
* command dump KEY A
*******************************************************************/
void cmd_DumpKey()
	{
	Serial.println();
	Serial.print("Key A: ");
	dump_byte_array(key.keyByte,6,true);
	
	return;
	}

/******************************************************************
* command set KEY A
*******************************************************************/
void cmd_SetKey(String myKey)
	{
	
	int y = 0;
	for (byte i = 0; i < myKey.length(); i=i+2)
		{
		String XX = myKey.substring(i,i+2);
		int hex = (int) strtol(&XX[0],NULL,16);
		key.keyByte[y] = hex;
		y++;
		}
	
	return;
	}

/******************************************************************
* command help syntax
*******************************************************************/
void cmd_Help(String txt)
	{
	Serial.println("\r\n"+txt);
	Serial.println("=============");
	Serial.println("Help:");
	Serial.println(" h     : print haelp");
	Serial.println(" guid  : get Card UID");
	Serial.println(" gct   : get CardType");
	Serial.println(" dc    : dump card");
	Serial.println(" ds,<sector> : dump sector <0-n>");
	Serial.println(" dba,<block>  : dump in ascii of block <0-n>");
	Serial.println(" dbh,<block>  : dump in HEX of block <0-n>");
	Serial.println(" wba,<block>,<ascii-data>,[<startpoint>] : write ascii text to block <0-n> (max. 16 char., default start = pos 1)");
	Serial.println(" wbh,<block>,<hex-data>  ,[<startpoint>] : write hex values to block <0-n> (max. 32 char., default start = pos 1)");
	Serial.println(" gg    : get Rx Gain");
	Serial.println(" sg,<gain> : set Rx gain <0-7> (18dB - 48dB)");
	Serial.println(" dk        : dump key A");
	Serial.println(" sk,<KEY A> : set key A (6 hex values)");
	
	return;
	}

/******************************************************************
* command print "ready."
*******************************************************************/
void printReady()
	{
	Serial.println("ready.\r\n");
	return;
	}


