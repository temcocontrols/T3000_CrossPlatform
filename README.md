---

---

# T3000_CrossPlatform [![Language](https://img.shields.io/badge/language-C%23-blue.svg?style=flat-square)](https://github.com/temcocontrols/T3000_CrossPlatform/search?l=C%23)

An Open Source Building Automation System based on the Raspberry Pi featuring a rich hardware and software architecture targeting small and large commercial buildings. Protocols supported include Bacnet and Modbus over both Ethernet IP and RS485. 

![T3000Family](/Documentation/Schematics/T3000Family.jpg)

Branches
========

master (stable)
---------------
| Travic CI(Mono)                          | AppVeyor                                 |
| ---------------------------------------- | ---------------------------------------- |
| [![Build Status](https://api.travis-ci.org/temcocontrols/T3000_CrossPlatform.svg?branch=master)](https://travis-ci.org/temcocontrols/T3000_CrossPlatform) | [![Build status](https://ci.appveyor.com/api/projects/status/9ggbaqrus1tr2ub4/branch/master?svg=true)](https://ci.appveyor.com/project/MauriceDuteau/t3000-crossplatform/branch/master) |

# Requirements
+ msvc14+/mono4.5+/.NET Framework 4.5

# Contacts
* [mail] register3 (at) temcocontrols (dot) com

# Website
* [Temco Controls](http://www.temcocontrols.com/) 

T3000 Building Automation System - for Linux-Win-Android deployment

# Windows

1. Run the .sln file(VS2015 Community Edition) ![](/documentation/run.png)

2. Install the executable project(Right click on T3000 Project and select the "Set as StartUp Project"![](/documentation/startup.png)</details>

3. Start up(F5 or click to Start)

    ![](/documentation/start.png)



# Linux

Preinstall:
```
sudo apt install mono-complete git nuget
```
It's install Mono(libraries), Mono-tools(like xbuild), git(for git clone) and nuget(for nuget restore)

Launch:
```
rm -r -f T3000_CrossPlatform
git clone https://github.com/temcocontrols/T3000_CrossPlatform
nuget restore T3000_CrossPlatform/T3000_CrossPlatform.sln
xbuild T3000_CrossPlatform/T3000_CrossPlatform.sln /p:Configuration=Release
T3000_CrossPlatform/T3000/bin/Release/T3000.exe
```

Comments:
1. Clean directory T3000_CrossPlatform(if exists). It's need for exclude some bugs with reinstall
2. Clone the remote repository to the T3000_CrossPlatform directory
3. Download all require libraries for the solution from Nuget
4. Build project with Configuration=Release
5. Run the obtained exe file

Plan:

1. Gradually merge Windows T3000 project to this repo. 



#### Hardware Description:

Here is an overview of the T3 controller hardware , the main processor is the BCM2837 which is on the Raspberry compute module at Tab1. The compute module has 1G ram and 4G flash which gives plenty of room for the typical building automation application. 

The Pi compute gpio pins are mainly used up with connecting to peripherals like the LCD, clock and communications ports. The few remaining gpio are allocated to the analog and relay outputs which are on the lower PCB at tab 3. The upper PCB is shown at tab2 and is managed by an auxiliary CPU which communicates to the Pi over SPI. The upper PCB has terminals for the universal inputs, the LEDs and hand-off-auto switches. There many peripherals and communications ports including the Ethernet chip and HDMI port on the lower board at Tab4. 

![PiHardwareOverview](/Documentation/Schematics/PiHardwareOverview.png)



# Current Status

We have refactored the 'Control Basic' language interpreter which is used to write the user programming on the T3 controllers and are working on some Pi hardware drivers. 

The control basic language was formally re-created using  ["Extended Backus-Naur form"](https://en.wikipedia.org/wiki/Extended_Backus–Naur_form)  or EBNF which is a way of formally specifying a programming language. This eliminates the ambiguities of a written description and allows us to extend the language in a structured way as the project moves along. Here is a graphical representation of the EBNF file for the user programming language in the controller: 

https://cdn.rawgit.com/temcocontrols/T3000_CrossPlatform/504f6617/Documentation/Grammar%20Definitions/T3000ControlBasicEBNF.xhtml

Clients have asked for a more modern version of the editor including visual programming options, this is on the roadmap once the main project has been ported over from Windows. 

There's plenty of porting and lots of communications drivers to work on still. If you're interested in helping out contributions are welcome. 

Maurice