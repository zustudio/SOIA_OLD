# SOIA

## About
SOIA, or Self-reflecting Object Interaction Analysis is a tool for dynamically analyzing different data sets.

## Structure
The code base is divided into following folders:
```
 /Source
   /"Namespace"
     /"Project"
	   /Header
	     /(subfolder)
	   /Public
	     /(subfolder)
	   /Source
	     /(subfolder)
```

## Naming Conventions
 - [namespace/class/struct names, function names, (class-) global variable names]: ThisIsAnExample
 - [child classes of RElement]: RChild
 - [child classes of TTool]: TChild
 - [functions to be executed from console]: cmd_thisisafunction
 - [functions to be used for pipes]: pipe_anotherfunction
 - [function local variable names]: thisIsAnExample

## Dependencies
programs:
 - cmake
command line utilities:
 - bash
 - unzip
 - make
 - grep
 - curl
