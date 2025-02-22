/*
Copyright (C) 2008 Grame & RTL 2008

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

*/

#ifndef __JackSunAdapter__
#define __JackSunAdapter__

#include <math.h>
#include <limits.h>
#include <assert.h>
#include "JackAudioAdapterInterface.h"
#include "JackPlatformPlug.h"
#include "JackError.h"
#include "jack.h"
#include "jslist.h"

namespace Jack
{

typedef jack_default_audio_sample_t jack_sample_t;

#define SUN_DRIVER_DEF_DEV	"/dev/audio"
#define SUN_DRIVER_DEF_FS	48000
#define SUN_DRIVER_DEF_BLKSIZE	1024
#define SUN_DRIVER_DEF_BITS	16
#define SUN_DRIVER_DEF_INS	2
#define SUN_DRIVER_DEF_OUTS	2

/*!
\brief The Sun adapter.
*/

class JackSunAdapter : public JackAudioAdapterInterface, public JackRunnableInterface
{

    enum { kRead = 1, kWrite = 2, kReadWrite = 3 };

    private:

        JackThread fThread;

        char fCaptureDriverName[JACK_CLIENT_NAME_SIZE+1];
        char fPlaybackDriverName[JACK_CLIENT_NAME_SIZE+1];

        int fInFD;
        int fOutFD;

        int fPrecision;
        int	fRWMode;

        unsigned int fInputBufferSize;
        unsigned int fOutputBufferSize;

        void* fInputBuffer;
        void* fOutputBuffer;

        float** fInputSampleBuffer;
        float** fOutputSampleBuffer;

        int OpenInput();
        int OpenOutput();
        void CloseAux();
        void DisplayDeviceInfo();

    public:

        JackSunAdapter(jack_nframes_t buffer_size, jack_nframes_t sample_rate, const JSList* params);
        ~JackSunAdapter()
        {}

        int Open();
        int Close();

        int Read();
        int Write();

        int SetBufferSize(jack_nframes_t buffer_size);

        bool Execute();
};

}

#ifdef __cplusplus
extern "C"
{
#endif

#include "JackCompilerDeps.h"
#include "driver_interface.h"

SERVER_EXPORT jack_driver_desc_t* jack_get_descriptor();

#ifdef __cplusplus
}
#endif

#endif
