#!/bin/bash
konsole  -e make 
sleep 1
konsole --hold -e dotnet $(pwd)/Proces4/ConsoleApp2.dll |konsole --hold -e python3 Proces3.py | konsole --hold -e ./proces2 | konsole --hold -e php Proces1.php 


