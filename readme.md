# MyFareMonitor

The MyFareMonitor kombines a lot of functions of the Arduino MFCR522 Library (v1.1.8).

__Table of content__

- [Install](#install)
- [Remark](#Remark)
- [Usage](#Usage)


## Install<a id="install"></a>

Copy all files in subdirectory named MyFareMonitor under your Arduino directory.


## Remark<a id="Remark"></a>

These Arduino Sketch is based of the deafault MFCR522 Library (v1.1.8). 

You can modify the most things about of a MyFare Classic Card like BlockRead, BlockWrite, etc...

Also exist a few subcommands for the MCFR522Chip byself.

> There are only minimal checking of lengt while setting KEY A or write block commands.
>
> BE CAREFULLY. ON WRONG SIZE OF LENGTH, THE INFECTED SECTOR WILL BE BLOCKED FOR EVER! 

## Usage<a id="Usage"></a>

Commands are:

- [help](#help)
- [get Card UID](#guid)
- [get CardType](#gct)
- [dump card](#dc)
- [dump sector](#ds)
- [dump block in ascii](#dba)
- [dump block in HEX](#dbh)
- [write ascii text to block](#wba)
- [write hex values to block](#wbh)
- [get Rx Gain](#gg)
- [set Rx gain](#sg)
- [dump key A](#dk)
- [set key A](#sk)


## help

The command 'h' shows the helpscreen.

```
MyFare Monitor V 2.0
(c)2016 Andreas Bujok
=============
Help:
 h     : print haelp
 guid  : get Card UID
 gct   : get CardType
 dc    : dump card
 ds,<sector> : dump sector <0-n>
 dba,<block>  : dump in ascii of block <0-n>
 dbh,<block>  : dump in HEX of block <0-n>
 wba,<block>,<ascii-data>,[<startpoint>] : write ascii text to block <0-n> (max. 16 char., default start = pos 1)
 wbh,<block>,<hex-data>  ,[<startpoint>] : write hex values to block <0-n> (max. 32 char., default start = pos 1)
 gg    : get Rx Gain
 sg,<gain> : set Rx gain <0-7> (18dB - 48dB)
 dk        : dump key A
```


## get Card UID<a id="guid"></a>

Read the ID of the MyFare Classic Card.

```
Syntax: guid
```


## get CardType<a id="gct"></a>
Get the type of the MyFare Clasic Card.
```
Syntax: gct
```

## dump card<a id="dc"></a>
Dump the full data (sectors and blocks) of the MyFare Classic Card
```
Syntax: dc
```

## dump sector<a id="ds"></a>
Shows the blocks of the given sector.
```
Syntax: ds,<sector>
Usage: Dumps the blocks of sector 4 'ds,4' 
```

## dump block as ascii<a id="dba"></a>
Shows the Bytes of the given block as ASCII characters.
```
Syntax: dba,<block n>
Usage: Dumps 16 Bytes as ASCII of block 2 'dba,2' 
```

## dump block as HEX<a id="dbh"></a>
Shows the Bytes of the given block as HEX digits.
```
Syntax: dba,<block n>
Usage: Dumps 16 Bytes as HEX of block 0 'dbh,0' 
```

## write ascii text to block<a id="wba"></a>
Writes ASCII Text to the given block. Additional the startpoint can be given (0 - 16), the value for the startpoint is not necessary.

The default start is on position one. 

```
Syntax: wba,<block n>,<ASCII text>,[<start position>]
Usage: Write 'Hello' to block 2, start on position 3 'wba,2,Hello,3' 
```

## write hex values to block<a id="wbh"></a>
Writes HEX digits to the given block. Additional the startpoint can be given (0 - 16), the value for the startpoint is not necessary.

The default start is on position one. 
```
Syntax: wbh,<block n>,<2-digit HEX values>,[<start position>]
Usage: Write 'FF06AA' to block 5, start on position 3 'wbh,5,FF06AA,3' 
```

## get Rx Gain<a id="gg"></a>
Shows the current Gain (dB) of the receiver.
```
Syntax: gg
Usage: Get the Gain (dB) of the receiver 'gg'
```

## set Rx gain<a id="sg"></a>
Set the Gain (0-7) of the receiver.

Value | dB
------| ------
0 | 18dB
1 | 23dB
2 | 18dB
3 | 23dB
4 | 33dB
5 | 38dB
6 | 43dB
7 | 48dB


```
Syntax: sg,<0-7>
Usage: Set the Gain of the receiver to 48dB 'sg,7'
```

## dump key A<a id="dk"></a>
Shows the value of Key A in HEX-digits.
```
Syntax: dk
Usage: Get the hex values of Key A 'dk'
```

## set key A<a id="sk"></a>
Set the value of Key A in HEX- digits (max. 6 HEX-pairs).
```
Syntax: sk,<2-digit HEX values>
Usage: Set the Key A to ff014367ea09 'sk,ff014367ea09'
```



