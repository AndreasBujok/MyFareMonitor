# MyFareMonitor

The MyFareMonitor kombines a lot of functions of the Arduino MFCR522 Library (v1.1.8).

__Table of content__

- [Install](#install)
- [Remark](#remark)
- [Usage](#usage)


## Install

Copy all files in subdirectory named MyFareMonitor under your Arduino directory.


## Remark

These Arduino Sketch is based of the deafault MFCR522 Library (v1.1.8). 

You can modify the most things about of a MyFare Classic Card like BlockRead, BlockWrite, etc...

Also exist a few subcommands for the MCFR522Chip byself.

> There are only minimal checking of lengt while setting KEY A or write block commands.
>
> Be carefully. On wrong size of length, the selected block will be blocked for ever!  

Commands are:

- [help](#h)
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

```MyFare Monitor V 2.0
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


## get Card UID


```
Syntax: guid
```


## get CardType

```
Syntax: gct
```

## dump card

```
Syntax: dc
```

## dump sector

```
Syntax: ds,<sector>
Usage: Dumps the blocks of sector 4 'ds,4' 
```


## dump block as ascii

```
Syntax: dba,<block n>
Usage: Dumps 16 Bytes as ASCII of block 3 'dba,3' 
```

## dump block as HEX

```
Syntax: dba,<block n>
Usage: Dumps 16 Bytes as HEX of block 0 'dbh,0' 
```

## write ascii text to block

```
Syntax: wba,<block n>,<ASCII text>,[<start position>]
Usage: Write 'Hello' to block 2, start on position 3 'wba,2,Hello,3' 
```

## write hex values to block

```
Syntax: wbh,<block n>,<2-digit HEX values>,[<start position>]
Usage: Write 'FF06AA' to block 5, start on position 3 'wbh,5,FF06AA,3' 
```

## get Rx Gain

```
Syntax: gg
Usage: Get the Gain (dB) of the receiver 'gg'
```

## set Rx gain

```
Syntax: sg,<0-7>
Usage: Set the Gain of the receiver to 48dB 'sg,7'
```

## dump key A

```
Syntax: dk
Usage: Get the hex values of Key A 'dk'
```

## set key A

```
Syntax: sk,<2-digit HEX values>
Usage: Set the Key A to ff014367ea09 'sk,ff014367ea09'
```




















## Benchmark

Here is the result of readme parse at MB Pro Retina 2013 (2.4 GHz):

```bash
make benchmark-deps
benchmark/benchmark.js readme

Selected samples: (1 of 28)
 > README

Sample: README.md (7774 bytes)
 > commonmark-reference x 1,222 ops/sec ±0.96% (97 runs sampled)
 > current x 743 ops/sec ±0.84% (97 runs sampled)
 > current-commonmark x 1,568 ops/sec ±0.84% (98 runs sampled)
 > marked x 1,587 ops/sec ±4.31% (93 runs sampled)
```
## usage

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
 sk,<KEY A> : set key A (6 hex values)




# (GitHub-Flavored) Markdown Editor

Basic useful feature list:

 * Ctrl+S / Cmd+S to save the filenn
 * Ctrl+Shift+S / Cmd+Shift+S to choose to save as Markdown or HTML
 * Drag anghghghg
kghjhgjhgvgvhvlklj



lknäönöä





I'm no good at writing sample / filler text, so go write something yourself.

Look, a list!

 * foo
 * bar
 * baz

And here's some code! :+1:

```javascript
$(function(){
  $('div').html('I am a div.');
});
```

This is [on GitHub](https://github.com/jbt/markdown-editor) so let me know if I've b0rked it somewhere.


Props to Mr. Doob and his [code editor](http://mrdoob.com/projects/code-editor/), from which
the inspiration to this, and some handy implementation hints, came.

### Stuff used to make this:

 * [markdown-it](https://github.com/markdown-it/markdown-it) for Markdown parsing
 * [CodeMirror](http://codemirror.net/) for the awesome syntax-highlighted editor
 * [highlight.js](http://softwaremaniacs.org/soft/highlight/en/) for syntax highlighting in output code blocks
 * [js-deflate](https://github.com/dankogai/js-deflate) for gzipping of data to make it fit in URLs
