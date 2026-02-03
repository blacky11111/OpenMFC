# OpenMFC
This library allows Linux/Mac user to compile cpp program created using Microsoft Foundation Class (MFC) natively, without modifying the source code. This would allow testing MFC program in Linux/Mac.

1. Dependency : 
		wxWidgets 2.8

2. Compiling library :
	
	2.1. Setting up scripts :

		chmod +x compilelib
		chmod +x install_lib
		chmod +x uninstall_lib

	2.2. Compile lib :

		./compilelib

	2.3. Install lib (requires superuser) :

		su
		./install_lib

3. Program compiling example (examples located in folder "tes_program"):

		g++ \`wx-config --cxxflags\` -o "realGUIApp_windows" "realGUIApp_windows.cpp" -lopenMFC \`wx-config --libs\`

4. Run the program :
   
   		./realGUIApp_windows
   
<img width="437" height="459" alt="MFC" src="https://github.com/user-attachments/assets/abfc6fd0-c0f0-4d3f-896c-b3be79a2f188" />
