#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif

#include <tchar.h>
#include <windows.h>
#include<bits/stdc++.h>
#include <shlobj.h>
#include <objbase.h>
#include<direct.h>

#define MENU_FILE_NEW    1
#define MENU_FILE_OPEN   2
#define MENU_FILE_EXIT   3
#define HELP_SYNTAX 8

using namespace std;
//HANDLES
HWND textfield,button1,button2,button3,edittxt;
HMENU hMenu;
HANDLE WINAPI file;

TCHAR szBuf[MAX_PATH];

OPENFILENAME ofn ;
char currfiledir[256];
char Filepath[200];
fstream edit;
string editword,tmpword;
/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);
void AddMenu(HWND);

/*  Make the class name into a global variable  */
TCHAR szClassName[ ] = _T("IDE");

int WINAPI WinMain (HINSTANCE hThisInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpszArgument,
                     int nCmdShow)
{
    if(_getcwd(currfiledir,256));
    else strcpy(currfiledir,"");
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH)COLOR_APPWORKSPACE;

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;
    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
           0,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           _T("IDE v3.0.1"),       /* Title Text */
           WS_OVERLAPPEDWINDOW, /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           1366,                 /* The programs width */
           768,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}


/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    LPITEMIDLIST pidl     = NULL;
    BROWSEINFO   bi       = { 0 };
    BOOL         bResult  = FALSE;
    switch (message)                  /* handle the messages */
    {
        case WM_CREATE:
            AddMenu(hwnd);
            MessageBeep(MB_APPLMODAL);
            MessageBox(hwnd,"WELCOME TO IDE V3.0.1","START CODING",MB_OK);
            textfield=CreateWindow("STATIC",
                                   "\n\n\n\tWELCOME!!PLEASE OPEN A TEXT FILE AND ENJOY CODING!!",
                                   WS_VISIBLE|WS_CHILD|WS_BORDER,
                                   20,20,500,500,
                                   hwnd,
                                   NULL,NULL,NULL
                                   );
            /*button1=CreateWindow("BUTTON",
                                "COMPILE",
                                WS_VISIBLE|WS_CHILD|WS_BORDER,
                                700,210,150,40,
                                hwnd,
                                (HMENU)4,NULL,NULL);
            */
            button2=CreateWindow("BUTTON",
                                "EXECUTE",
                                WS_VISIBLE|WS_CHILD|WS_BORDER,
                                700,250,150,40,
                                hwnd,
                                (HMENU)5,NULL,NULL);
           button3=CreateWindow("BUTTON",
                                "EDIT",
                                WS_VISIBLE|WS_CHILD|WS_BORDER,
                                700,350,150,40,
                                hwnd,
                                (HMENU)6,NULL,NULL);
        break;
        case WM_COMMAND:
            switch(wParam){
               case MENU_FILE_EXIT:
                   MessageBeep(MB_OK);
                   DestroyWindow(hwnd);
               break;
               case 5:
                   //cout<<"HI "<<Filepath<<"execute.exe";
                   if(currfiledir){
                   char exe[300];
                   strcpy(exe,currfiledir);
                   strcat(exe,"\\executable\\execute.exe");
                   ShellExecute(hwnd,"open",(LPCSTR)exe,Filepath,NULL,SW_SHOWMAXIMIZED);
                   }
               break;
               case MENU_FILE_NEW:
                   edit.close();
                   MessageBeep(MB_ICONINFORMATION);
                   /*ZeroMemory( &ofn , sizeof( ofn));
                   ofn.lStructSize = sizeof ( ofn );
                   ofn.hwndOwner = hwnd  ;
                   ofn.lpstrFile = Filepath;
                   ofn.lpstrFile[0] = '\0';
                   ofn.nMaxFile = sizeof( Filepath );
                   ofn.lpstrFilter = "FOLDER\0*.FOLDER\0\0";
                   ofn.nFilterIndex =1;
                   ofn.lpstrFileTitle = NULL ;
                   ofn.nMaxFileTitle = 0 ;
                   ofn.lpstrInitialDir=NULL ;
                   ofn.hInstance=(HINSTANCE)OFN_EXPLORER;
                   ofn.Flags = OFN_PATHMUSTEXIST|OFN_FILEMUSTEXIST|OFN_ALLOWMULTISELECT|OFN_EXPLORER;
                   GetOpenFileName( &ofn );*/
                   bi.hwndOwner      = hwnd;
                   bi.pszDisplayName = szBuf;
                   bi.pidlRoot       = NULL;
                   bi.lpszTitle      = "PLEASE CHOOSE A FOLDER:";
                   bi.ulFlags        = BIF_RETURNONLYFSDIRS | BIF_USENEWUI;
                   if ((pidl = SHBrowseForFolder(&bi)) != NULL)
                   {   //cout<<szBuf;
                       bResult = SHGetPathFromIDList(pidl, szBuf);
                       CoTaskMemFree(pidl);
                   }
                   char compName[250];
                   //cout<<bResult;
                   strcpy(compName,szBuf);
                   strcat(compName,"\\UNTITLED.TXT");
                   MessageBox(hwnd,compName,"CONFIRM!!",MB_OK);
                   //file=CreateFile((LPCSTR)compName,GENERIC_READ|GENERIC_WRITE,FILE_SHARE_DELETE|FILE_SHARE_READ|FILE_SHARE_WRITE,NULL,TRUNCATE_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
                   file=CreateFile(
                       (LPCSTR)compName,
                        GENERIC_READ|GENERIC_WRITE,
                        0,
                        NULL,
                        CREATE_NEW,
                        FILE_ATTRIBUTE_NORMAL,
                        NULL);
                   if(file==INVALID_HANDLE_VALUE) {
                       MessageBeep(MB_OKCANCEL);
                       MessageBox(hwnd,"ERROR ATTEMPTING CREATING FILE","ERROR!!",MB_OK|MB_ICONERROR);
                   }
                   else if(bResult==0){
                       MessageBeep(MB_OKCANCEL);
                       MessageBox(hwnd,"ERROR SELECTING FOLDER","ERROR!!",MB_OK|MB_ICONERROR);
                   }
                   else{
                       //strcpy(Filepath,compName);
                       HINSTANCE hin=ShellExecute(hwnd,"open",(LPCSTR)compName,NULL,NULL,SW_SHOWMAXIMIZED);
                       /*edit.open(compName);
                       editword="";
                       while(getline(edit,editword,'\n')){
                           editword+='\n';
                       }
                       edittxt=CreateWindow("STATIC",
                                   (LPSTR)editword.c_str(),
                                   WS_VISIBLE|WS_CHILD|WS_BORDER|WS_VSCROLL|WS_HSCROLL,
                                   20,20,500,500,
                                   hwnd,
                                   NULL,NULL,NULL
                                   );
                                   */
                      MessageBeep(MB_ICONINFORMATION);
                      MessageBox(hwnd,"PLEASE OPEN YOUR RECENTLY CREATED FILE FOR VIEWING,MODIFYING AND EXECUTING","ATTENTION!!",MB_OK|MB_ICONINFORMATION);
                   }
               break;
               case MENU_FILE_OPEN:
                   edit.close();
                   MessageBeep(MB_ICONINFORMATION);
                   ZeroMemory( &ofn , sizeof( ofn));
                   ofn.lStructSize = sizeof ( ofn );
                   ofn.hwndOwner = hwnd  ;
                   ofn.lpstrFile = Filepath;
                   ofn.lpstrFile[0] = '\0';
                   ofn.nMaxFile = sizeof( Filepath );
                   ofn.lpstrFilter = "Text\0*.TXT\0\0";
                   ofn.nFilterIndex =1;
                   ofn.lpstrFileTitle = NULL ;
                   ofn.nMaxFileTitle = 0 ;
                   ofn.lpstrInitialDir=NULL ;
                   ofn.hInstance=(HINSTANCE)OFN_EXPLORER;
                   ofn.Flags = OFN_PATHMUSTEXIST|OFN_FILEMUSTEXIST|OFN_ALLOWMULTISELECT|OFN_EXPLORER;
                   GetOpenFileName( &ofn );
                   //MessageBox ( NULL , ofn.lpstrFile , "File Name:" , MB_OK);
                   SHELLEXECUTEINFO lpExecInfo;
                  lpExecInfo.cbSize  = sizeof(SHELLEXECUTEINFO);
                  lpExecInfo.lpFile =ofn.lpstrFile;
                  lpExecInfo.fMask=SEE_MASK_DOENVSUBST|SEE_MASK_NOCLOSEPROCESS ;
                  lpExecInfo.hwnd = NULL;
                  lpExecInfo.lpVerb = "open"; // to open  program
                  lpExecInfo.lpParameters = "EDITOR"; //  file name as an argument
                  lpExecInfo.lpDirectory = NULL;
                  lpExecInfo.nShow = SW_SHOW ;  // show command prompt with normal window size
                  lpExecInfo.hInstApp = (HINSTANCE) SE_ERR_DDEFAIL ;   //WINSHELLAPI BOOL WINAPI result;
                  lpExecInfo.nShow=SW_SHOWMAXIMIZED;
                  ShellExecuteEx(&lpExecInfo);


                  //wait until a file is finished printing
                  if(lpExecInfo.hProcess !=NULL)
                  {
                    ::WaitForSingleObject(lpExecInfo.hProcess, INFINITE);
                    ::CloseHandle(lpExecInfo.hProcess);
                  }
                   //ShellExecute(hwnd,"open",ofn.lpstrFile,NULL,NULL,SW_SHOWMAXIMIZED);
                   strcpy(Filepath,ofn.lpstrFile);
                   edit.open(ofn.lpstrFile);
                       editword="";
                       while(getline(edit,tmpword,'\n')){
                           editword+=tmpword;
                           editword+="\r\n";
                       }
                       PostMessage(edittxt,WM_CLOSE,0,0);
                       edittxt=CreateWindow("EDIT",
                                   (LPSTR)editword.c_str(),
                                   WS_VISIBLE|WS_CHILD|WS_BORDER|WS_VSCROLL|WS_HSCROLL|ES_AUTOHSCROLL|ES_AUTOVSCROLL|ES_MULTILINE|ES_READONLY|ES_LEFT,
                                   20,20,500,500,
                                   hwnd,
                                   NULL,NULL,NULL
                                   );
               break;
               case 6:
                   edit.close();
                   //HINSTNACE hin=
                   //SHELLEXECUTEINFO lpExecInfo;
                  lpExecInfo.cbSize  = sizeof(SHELLEXECUTEINFO);
                  lpExecInfo.lpFile =ofn.lpstrFile;
                  lpExecInfo.fMask=SEE_MASK_DOENVSUBST|SEE_MASK_NOCLOSEPROCESS ;
                  lpExecInfo.hwnd = NULL;
                  lpExecInfo.lpVerb = "open"; // to open  program
                  lpExecInfo.lpParameters = "EDITOR"; //  file name as an argument
                  lpExecInfo.lpDirectory = NULL;
                  lpExecInfo.nShow = SW_SHOW ;  // show command prompt with normal window size
                  lpExecInfo.hInstApp = (HINSTANCE) SE_ERR_DDEFAIL ;   //WINSHELLAPI BOOL WINAPI result;
                  lpExecInfo.nShow=SW_SHOWMAXIMIZED;
                  ShellExecuteEx(&lpExecInfo);


                  //wait until a file is finished printing
                  if(lpExecInfo.hProcess !=NULL)
                  {
                    ::WaitForSingleObject(lpExecInfo.hProcess, INFINITE);
                    ::CloseHandle(lpExecInfo.hProcess);
                  }
                   //ShellExecute(hwnd,"open",ofn.lpstrFile,NULL,NULL,SW_SHOWMAXIMIZED);
                   edit.open(Filepath);
                       editword="";
                       while(getline(edit,tmpword,'\n')){
                           editword+=tmpword;
                           editword+="\r\n";
                       }
                       PostMessage(edittxt,WM_CLOSE,0,0);
                       edittxt=CreateWindow("EDIT",
                                   (LPSTR)editword.c_str(),
                                   WS_VISIBLE|WS_CHILD|WS_BORDER|WS_VSCROLL|WS_HSCROLL|ES_AUTOHSCROLL|ES_AUTOVSCROLL|ES_MULTILINE|ES_READONLY|ES_LEFT,
                                   20,20,500,500,
                                   hwnd,
                                   NULL,NULL,NULL
                                   );
               break;
               case HELP_SYNTAX:
                   if(currfiledir){
                   char syn[300];
                   strcpy(syn,currfiledir);
                   strcat(syn,"\\readme.txt");
                   ShellExecute(hwnd,"open",(LPCSTR)syn,NULL,NULL,SW_SHOWMAXIMIZED);
                   }
               break;
            }
        break;
        /*case WM_CREATE:
            textfield=CreateWindow("STATIC",
                                   "HELLO WORLD!",
                                   WS_VISIBLE|WS_CHILD|WS_BORDER,
                                   20,20,125,20,
                                   hwnd,
                                   NULL,NULL,NULL
                                   );
            button=CreateWindow("BUTTON",
                                "CLICK HERE!!",
                                WS_VISIBLE|WS_CHILD|WS_BORDER,
                                20,50,150,20,
                                hwnd,
                                (HMENU)1,NULL,NULL);
        break;
        case WM_COMMAND:
            switch(LOWORD(wParam)){
                case 1:
                    ::MessageBeep(MB_ICONERROR);
                    ::MessageBox(hwnd,"BUTTON CLICKED","GOOD",MB_OK);
                break;
            }*/
        case WM_DESTROY:
            PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
            break;
        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}
//FOR ADDING MENU BAR
void AddMenu(HWND hwnd){
    hMenu=CreateMenu();
    HMENU hfilemenu=CreateMenu();
    HMENU Submenu=CreateMenu();
    HMENU hhelpmenu=CreateMenu();

    AppendMenu(hfilemenu,MF_POPUP,(UINT_PTR)Submenu,"NEW");
    AppendMenu(Submenu,MF_STRING,MENU_FILE_NEW,"CHOOSE FOLDER");
    AppendMenu(hfilemenu,MF_STRING,MENU_FILE_OPEN,"OPEN");
    AppendMenu(hfilemenu,MF_SEPARATOR,NULL,NULL);
    AppendMenu(hfilemenu,MF_STRING,MENU_FILE_EXIT,"EXIT");
    AppendMenu(hhelpmenu,MF_STRING,HELP_SYNTAX,"SYNTAX");
    AppendMenu(hMenu,MF_POPUP,(UINT_PTR)hfilemenu,"FILE");
    AppendMenu(hMenu,MF_POPUP,(UINT_PTR)hhelpmenu,"HELP");
    SetMenu(hwnd,hMenu);
}
