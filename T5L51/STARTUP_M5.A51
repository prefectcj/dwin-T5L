$NOMOD51
;------------------------------------------------------------------------------
;  This file is part of the C51 Compiler package
;  Startup Code for the Capital Micro AS1E5 device
;  Copyright (c) 2001-2005 Keil Elektronik GmbH and Keil Software, Inc.
;  Version 1.00
;
;  *** <<< Use Configuration Wizard in Context Menu >>> ***
;------------------------------------------------------------------------------
;  STARTUP_AS1E5.A51:  This code is executed after processor reset.
;
;  To translate this file use A51 with the following invocation:
;
;     A51 STARTUP_CME3000.A51
;
;  To link the modified STARTUP_CME3000.OBJ file to your application use the following
;  Lx51 invocation:
;
;     Lx51 your object file list, STARTUP_CME3000.OBJ  controls
;
;------------------------------------------------------------------------------

                CSEG    AT  0F8H
                DB  0FFH,0FFH
                DB  'DWINT5'

                EXTRN CODE (?C_START)

                LJMP    ?C_START

                END
