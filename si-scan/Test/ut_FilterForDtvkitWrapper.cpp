#include <stdio.h>
#include <io.h>
#include <techtype.h>
#include <dbgfuncs.h>
#include <iostream>


#include "stbhwc.h"
#include "stbheap.h"
#include "stbuni.h"

#include "stbsiflt.h"
#include "stbdpc.h"
#include "stbsitab.h"
#include "ap_si.h"

#include "cert_sitbl.h"
#include "cert_sitbl_sgt.h"


#include "FilterForDtvkitWrapper.h"

#include "cert_log.h"

using namespace std;

#define TEST_FILE "D:\\StreamSparkTS\\8669-730\\HD_muxB_010.trp"
#define FILE_DURATION (90*1000)
extern "C" void Integration_TsLoop()
{
    FILE* file = fopen(TEST_FILE, "rb");
    long size = 0;

    if (file)
    {
        size = filelength(fileno(file));
        cout << size << endl;
        fclose(file);
    }

    Wrapper_DMXInitialise(0, 1);

    unsigned int sleep_ms = Wrapper_CalcTsLoopDelay(size, FILE_DURATION);

    Wrapper_SetTsLoopDelayMS(sleep_ms);



#if 1
    Wrapper_SetTsSource(0, TEST_FILE);
    Wrapper_EnableTsLoop();
    Wrapper_StartTsLoop(0);
    Wrapper_DisableTsLoop();
#endif
}