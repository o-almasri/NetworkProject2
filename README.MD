to get the project working 

works only on Release x64

go to cBaseDAO.cpp and change the following 

const std::string SCHEMA = "authserver"; to "your schema Name " 
const std::string USER = "root"; to " your DB user Name " 
const std::string PWD = "root"; to your DB Password 


Launch sequence 

-Auth Server 
-Server 
-Client

For first Time build you need to build all projects including the NetworkUtils which 
have a script to copy google protobuf dlls to $(OutDir) 
