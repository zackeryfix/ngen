////////////////////////////////////////////////////
  WORKSPACE FILES
////////////////////////////////////////////////////
This folder is the top level directory for all projects related to Ngen Framework.  In this folder you will find several Codeblocks workspace files, and each of them contain a unique permutation of the different projects associated with the framework.  The description for the different workspace files are below.

WORKSPACE FILE  | DESCRIPTION (* = primary project, % = abstract implementation)
--------------------------------------------------------------------------------
\sdk.workspace  | ALL the projects currently under active development.
\core.workspace	| The project(s) associated with the Common Core API
*                        Ngen
*                        Ngen.Reflection
*          		 Ngen.IO
*                        Ngen.Data
*			 Ngen.Math
*                        Ngen.Localization
*			 Ngen.Cryptography
*			 Ngen.Intelligence
\mre.workspace	| The project(s) associated with the Media Rendeirng Engine
                         Ngen
           		 Ngen.IO
*                        Ngen.Audio
*                        Ngen.Drawing
%                        Ngen.Drawing.Gui
%                        Ngen.Drawing.Html
                         Ngen.Math
\cli.workspace	| The project(s) associated with the Common Language Infastructure
                         Ngen
           		 Ngen.IO
                         Ngen.Reflection
*                        Ngen.Reflection.Code
%			 Ngen.Reflection.Code.CCpp
%			 Ngen.Reflection.Code.Cmodulo
%			 Ngen.Reflection.Code.CSharp
\dcf.workspace  | The project(s) associated with the Direct Communication Framework
			 Ngen
           		 Ngen.IO
*                        Ngen.IO.Networking
                         Ngen.Reflection
                         Ngen.Reflection.Code
\wsp.workspace	| The project(s) associated with the Web Services Platform.
			 Ngen
           		 Ngen.IO
                         Ngen.IO.Networking
			 Ngen.Data
			 Ngen.Reflection
                         Ngen.Reflection.Code
*                        Ngen.Web
\iak.workspace	| The project(s) associated with the Interactive Application Kit
 			 Ngen
           		 Ngen.IO
			 Ngen.IO.Networking
                         Ngen.Audio
                         Ngen.Drawing
                         Ngen.Math
*			 Ngen.Scene
*			 Ngen.Scene.Content
-------------------------------------------------------------------------

These are generalized workspaces for the different milestones of the framework.  You are free to create your personal workspace file in this directory.  Just name the file using your GIT username followed by the '.workspace' extension, and document the new addition here using the above descriptions as a guide.

/////////////////////////////////////////////////
  MISC. FILES & SUB-FOLDERS
/////////////////////////////////////////////////

Aside from the obvious folders for each project, you will notice other folders and files in this directory.  Each of these are critical to the development process and it is important that you understand the purpose for each folder/file.  The following is a brief description with each folder having its own 'README.txt' for a more detailed evaluation.

\bin\			
This is the compiler OUTPUT folder for ALL the linked binaries for ALL the projects accross ALL configurations.  This contains one '\Debug\' OUTPUT folder and one '\Release\' OUTPUT folder.

\external\
This is the compiler and linker search directory for ALL external third-party APIs used by the framework.  Each external library being used has their own instructions for getting them setup for the frameworks build process. 

\Codeblocks\
This folder contains various template projects, plugin projects, and other tools developed for the Codeblocks IDE and are there to assist us in development of the framework.

\UnitTest.*\
Each project has its own Unit-testing application.  Currently these are functional tests, but as we develop more features into the Ngen.Diagnostic library these test may eventually be compiled into a single automated testing project.

/////////////////////////////////////////////////////////////////

NOTE:  The organization here contains both future and current projects and is subject to change as the design of our APIs become more developed.

