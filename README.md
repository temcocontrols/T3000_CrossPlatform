# T3000_CrossPlatform [![Language](https://img.shields.io/badge/language-C%23-blue.svg?style=flat-square)](https://github.com/temcocontrols/T3000_CrossPlatform/search?l=C%23)

Branches
========

master (stable)
---------------
Travic CI(Mono) | AppVeyor
--------------- | -------------
[![Build Status](https://api.travis-ci.org/HavenDV/PRGReaderLibrary.svg?branch=master)](https://travis-ci.org/HavenDV/PRGReaderLibrary) | [![Build status](https://ci.appveyor.com/api/projects/status/dhj18w01i7d753g4/branch/master?svg=true)](https://ci.appveyor.com/project/HavenDV/t3000-crossplatform/branch/master)

# Requirements
+ msvc14+/mono4.6.2+

# Contacts
* [mail](mailto:havendv@gmail.com)

T3000 Building Automation System - for Linux-Win-Android deployment

# Linux

Preinstall:
```
sudo apt install mono-complete git nuget
```

Launch:
```
rm -r -f T3000_CrossPlatform
git clone https://github.com/temcocontrols/T3000_CrossPlatform
nuget restore T3000_CrossPlatform/T3000.sln
xbuild T3000_CrossPlatform/T3000.sln /p:Configuration=Release
T3000_CrossPlatform/T3000/bin/Release/T3000.exe
```