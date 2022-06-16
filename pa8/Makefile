#------------------------------------------------------------------------------
#  Brandon Hwu, brhwu
#  2022 Spring CSE101 PA8
#  Makefile
#  Makefile for CSE 101 Programming Assignment 8
#
#  make                     makes WordFrequency and Order
#  make DictionaryTest      makes DictionaryTest
#  make clean               removes all binaries
#  make WordFrequencyCheck  runs WordFrequency under valgrind on Gutenberg.txt
#  make OrderCheck          runs Order under valgrind on in5 and junk5
#  make DictionaryCheck     runs DictionaryTest under valgrind
#------------------------------------------------------------------------------

MAIN           = WordFrequency
MAIN1          = Order
ADT            = Dictionary
SOURCE         = $(MAIN).cpp
OBJECT         = $(MAIN).o
SOURCE1        = $(MAIN1).cpp
OBJECT1        = $(MAIN1).o 
ADT_TEST       = $(ADT)Test
ADT_SOURCE     = $(ADT).cpp
ADT_OBJECT     = $(ADT).o
ADT_HEADER     = $(ADT).h
COMPILE        = g++ -std=c++17 -Wall -c
LINK           = g++ -std=c++17 -Wall -o
REMOVE         = rm -f
MEMCHECK       = valgrind --leak-check=full

$(MAIN): $(OBJECT) $(ADT_OBJECT)
	$(LINK) $(MAIN) $(OBJECT) $(ADT_OBJECT)

$(MAIN1): $(OBJECT1) $(ADT_OBJECT)
	$(LINK) $(MAIN1) $(OBJECT1) $(ADT_OBJECT)

$(ADT_TEST): $(ADT_TEST).o $(ADT_OBJECT)
	$(LINK) $(ADT_TEST) $(ADT_TEST).o $(ADT_OBJECT)

$(OBJECT): $(SOURCE) $(ADT_HEADER)
	$(COMPILE) $(SOURCE)

$(OBJECT1): $(SOURCE1) $(ADT_HEADER)
	$(COMPILE) $(SOURCE1)

$(ADT_TEST).o: $(ADT_TEST).cpp $(ADT_HEADER)
	$(COMPILE) $(ADT_TEST).cpp

$(ADT_OBJECT): $(ADT_SOURCE) $(ADT_HEADER)
	$(COMPILE) $(ADT_SOURCE)

clean:
	$(REMOVE) $(MAIN) $(MAIN1) $(ADT_TEST) $(OBJECT) $(OBJECT1) $(ADT_TEST).o $(ADT_OBJECT)

$(MAIN)Check: $(MAIN)
	$(MEMCHECK) $(MAIN) GutenBerg.txt

$(MAIN1)Check: $(MAIN1)
	$(MEMCHECK) $(MAIN1) in5 junk5

$(ADT)Check: $(ADT_TEST)
	$(MEMCHECK) $(ADT_TEST)
