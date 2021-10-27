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
Download [Visual Studio Community 2017](https://visualstudio.microsoft.com/it/free-developer-offers/) .NET and C++ applications development should be selected during installation.

To clone the project:

`File -> Open -> Open from source control`

![File>Open>Open from source](/Documentation/open_from_source.png)

Then on the right bar `Local Git Repository` click on Clone, and fill the field `Enter the URL of a Git repo to clone` with project URL `https://github.com/temcocontrols/T3000_CrossPlatform` and into `Enter a path for the cloned Git repo` insert your project directory (i.e. `My Documents\Source\T3000_CrossPlatform`). Then click `Clone`.

![Clone Repository](/Documentation/clone_git.png)

Wait for clone completion, then open 'T3000_CrossPlatform.sln'. When the project is opened the first time there will be a warning in the Nuget Package Manager Console about missing packages - click 'Restore'.

![Restore Nuget Packages](/Documentation/restore_nuget_packages.png)

Then select Build > Clean, and then Build > Batch Build, select all, and click 'Build'.

Executable can be found in the `T3000_CrossPlatform\ReleaseFiles\LastCompilation\T3000.exe` directory.


# Linux

Preinstall:
Import [Mono](https://en.wikipedia.org/wiki/Mono_(software)) repository following official distro instructions from [Mono-Project](https://www.mono-project.com/download/stable/#download-lin) website. Then install the mono-complete, git and curl packages using the following command

```
sudo apt install mono-complete git curl
```
Install `nuget`
```
sudo apt install nuget
```
Check `nuget`
```
sudo nuget update -self
```
To install the MonoDevelop IDE
```
sudo apt install monodevelop
```
Execute the following commands to clone the repo
```
rm -r -f T3000_CrossPlatform
git clone https://github.com/temcocontrols/T3000_CrossPlatform
nuget restore T3000_CrossPlatform/T3000_CrossPlatform.sln
```
And to build from command line
```
msbuild T3000_CrossPlatform/T3000_CrossPlatform.sln /p:Configuration=Release
chmod +x T3000_CrossPlatform/T3000/bin/Release/T3000.exe
```
Run the application
```
mono ./T3000_CrossPlatform/T3000/bin/Release/T3000.exe
```

Comments:
1. Clean directory T3000_CrossPlatform(if exists). It's need for exclude some bugs with reinstall
2. Clone the remote repository to the T3000_CrossPlatform directory
3. Download all require libraries for the solution from Nuget
4. Build project with Configuration=Release
5. Run the obtained exe file
6. This Software only demonstrat the reading and writing of program file of T3000 on other operating systems like linux . Sample Program File can be load from the Path T3000_CrossPlatform\Documentation\ExampleProgFiles 
7. Device Discovery or Connection is not currenlty available in this version
8. The turminal you are using in case on linux it should support X server. otherwise on running the EXE it will give error.
At the moment editing programs with Linux version return an error.

# Plan:

1. Support of the program code
