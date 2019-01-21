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
* [mail](mailto:register3@temcocontrols.com)

T3000 Building Automation System - for Linux-Win deployment

# Windows

Preinstall:
Download [Visual Studio Community 2017](https://visualstudio.microsoft.com/it/free-developer-offers/). .NET and C++ applications development should be selected during installation.

To clone the project:

`File -> Open -> Open from source control`

Then on the right bar `Local Git Repository` fill the field `Enter the URL of a Git repo to clone` with project URL `https://github.com/temcocontrols/T3000_CrossPlatform` and into `Enter a path for the cloned Git repo` insert your project directory (i.e. `My Documents/T3000_CrossPlatform`)

Wait for clone completion, then open `T3000_CrossPlatform.sln` and build the project with `Build -> Build Solution`

Executable can be find into `T3000_CrossPlatform\ReleaseFiles\LastCompilation\T3000.exe`


# Linux

Preinstall:
Import [Mono](https://en.wikipedia.org/wiki/Mono_(software)) repository following official distro instructions from [Mono-Project](https://www.mono-project.com/) website. Then install the packages:

```
mono-complete git curl
```
Get `nuget`
```
sudo curl -o /usr/local/bin/nuget.exe https://dist.nuget.org/win-x86-commandline/latest/nuget.exe
```
Create an alias for nuget adding the following line in `.bash_aliases` (a logout can be required)
```
alias nuget="mono /usr/local/bin/nuget.exe"
```
Check `nuget`
```
nuget update -self
```
Then execute the following commands:
```
rm -r -f T3000_CrossPlatform
git clone https://github.com/temcocontrols/T3000_CrossPlatform
nuget restore T3000_CrossPlatform/T3000_CrossPlatform.sln
msbuild T3000_CrossPlatform/T3000_CrossPlatform.sln /p:Configuration=Release
chmod +x T3000_CrossPlatform/T3000/bin/Release/T3000.exe
./T3000_CrossPlatform/T3000/bin/Release/T3000.exe
```

Comments:
1. Clean directory T3000_CrossPlatform(if exists). It's need for exclude some bugs with reinstall
2. Clone the remote repository to the T3000_CrossPlatform directory
3. Download all require libraries for the solution from Nuget
4. Build project with Configuration=Release
5. Run the obtained exe file

At the moment editing programs with Linux version return an error.

# Plan:

1. Support of the program code
