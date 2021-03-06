/* @(#) $Id: ./src/win32/setup-win.c, 2011/09/08 dcid Exp $
 */

/* Copyright (C) 2009 Trend Micro Inc.
 * All rights reserved.
 *
 * This program is a free software; you can redistribute it
 * and/or modify it under the terms of the GNU General Public
 * License (version 2) as published by the FSF - Free Software
 * Foundation
 */


#include "setup-shared.h"


/* Setup windows after install */
int main(int argc, char **argv)
{
    /* Setting the name */
    OS_SetName(ARGV0);

    if(argc < 2)
    {
        printf("%s: Invalid syntax.\n", argv[0]);
        printf("Try: '%s directory'\n\n", argv[0]);
        return(0);
    }

    /* Trying to chdir to ossec directory. */
    if(chdir(argv[1]) != 0)
    {
        printf("%s: Invalid directory: '%s'.\n", argv[0], argv[1]);
        return(0);
    }


    /* Configure ossec for automatic startup */
    system("sc config OssecSvc start= auto");


    /* Changing permissions. */
    checkVista();


    if(isVista)
    {
        char cmd[OS_MAXSTR +1];

        /* Copy some files to outside */
        snprintf(cmd, OS_MAXSTR, "move os_win32ui.exe ../");
        system(cmd);

        snprintf(cmd, OS_MAXSTR, "move win32ui.exe ../");
        system(cmd);

        snprintf(cmd, OS_MAXSTR, "move uninstall.exe ../");
        system(cmd);

        snprintf(cmd, OS_MAXSTR, "move doc.html ../");
        system(cmd);

        snprintf(cmd, OS_MAXSTR, "move help.txt ../");
        system(cmd);


        /* Changing permissions. */
        system("echo y|cacls * /T /G Administrators:f ");


        /* Copying them back. */
        snprintf(cmd, OS_MAXSTR, "move ..\\os_win32ui.exe .");
        system(cmd);

        snprintf(cmd, OS_MAXSTR, "move ..\\win32ui.exe .");
        system(cmd);

        snprintf(cmd, OS_MAXSTR, "move ..\\uninstall.exe .");
        system(cmd);

        snprintf(cmd, OS_MAXSTR, "move ..\\doc.html .");
        system(cmd);

        snprintf(cmd, OS_MAXSTR, "move ..\\help.txt .");
        system(cmd);
    }
    else
    {
        system("echo y|cacls . /T /G Administrators:f ");
    }

    return(1);
}
