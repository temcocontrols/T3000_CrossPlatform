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
nuget restore T3000_CrossPlatform/T3000_CrossPlatform.sln
xbuild T3000_CrossPlatform/T3000_CrossPlatform.sln /p:Configuration=Release
T3000_CrossPlatform/T3000/bin/Release/T3000.exe
```

# Plan:

1. Support of the program code