# T3000_CrossPlatform [![Language](https://img.shields.io/badge/language-C%23-blue.svg?style=flat-square)](https://github.com/temcocontrols/T3000_CrossPlatform/search?l=C%23)

Branches
========

master (stable)
---------------
Travic CI(Mono) | AppVeyor
--------------- | -------------
[![Build Status](https://api.travis-ci.org/temcocontrols/T3000_CrossPlatform.svg?branch=master)](https://travis-ci.org/temcocontrols/T3000_CrossPlatform) | [![Build status](https://ci.appveyor.com/api/projects/status/9ggbaqrus1tr2ub4/branch/master?svg=true)](https://ci.appveyor.com/project/MauriceDuteau/t3000-crossplatform/branch/master)

# Requirements
+ msvc14+/mono4.5+/.NET Framework 4.5

# Contacts
* [mail] register3 (at) temcocontrols (dot) com)

# Website
* [Temco Controls](http://www.temcocontrols.com/) 

T3000 Building Automation System - for Linux-Win-Android deployment

# Windows

1. Run the .sln file(VS2015 Community Edition)<details><summary>Image</summary>![](docs/run.png)</details>
2. Install the executable project(Right click on T3000 Project and select the "Set as StartUp Project" option)<details><summary>Image</summary>![](docs/startup.png)</details>
3. Start up(F5 or click to Start)<details><summary>Image</summary>![](docs/start.png)</details>

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

# Plan:

1. Gradually merge Windows T3000 project to this repo. 

# Control Basic Editor
We are currently refactoring the 'Control Basic' language compiler which is used to write the logic of the T3 contollers. EBNF files are a way of accurately representing this control basic language eliminating the ambiguities of a written description. It will also allow us to extend the language in a structured way as the project moves along. Here is a graphical representation of the EBNF file: 


https://cdn.rawgit.com/temcocontrols/T3000_CrossPlatform/504f6617/Documentation/Grammar%20Definitions/T3000ControlBasicEBNF.xhtml

Many clients have asked for a more modern version of the editor, this work will start once the parser and editor are done. 