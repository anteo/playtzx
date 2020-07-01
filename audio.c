/* 
 * Standard audio related includes
 */

#include <stdio.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include "audio.h"
#include "portaudio.h"

/* Mandatory variables */

PaStream *stream;

void pa_error(PaError err)
{
  fprintf(stderr, "An error occured while using the portaudio stream\n");
  fprintf(stderr, "Error number: %d\n", err);
  fprintf(stderr, "Error message: %s\n", Pa_GetErrorText(err));
  // Print more information about the error.
  if (err == paUnanticipatedHostError)
  {
    const PaHostErrorInfo *hostErrorInfo = Pa_GetLastHostErrorInfo();
    fprintf(stderr, "Host API error = #%ld, hostApiType = %d\n", hostErrorInfo->errorCode, hostErrorInfo->hostApiType);
    fprintf(stderr, "Host API error = %s\n", hostErrorInfo->errorText);
  }
  Pa_Terminate();
  exit(1);
}

void play_buffer(unsigned char *buf, int count)
{
  PaError err;
  err = Pa_WriteStream(stream, buf, count);

  if (err != paNoError)
    pa_error(err);
}

/* note, freq is changed! */

void open_audio(int *freq)
{
  PaError err;
  PaStreamParameters outputParameters;

  err = Pa_Initialize();
  if (err != paNoError)
    pa_error(err);

  outputParameters.device = Pa_GetDefaultOutputDevice(); /* default output device */
  if (outputParameters.device == paNoDevice)
  {
    fprintf(stderr, "Error: No default output device.\n");
    Pa_Terminate();
    exit(1);
  }

  outputParameters.channelCount = 1;
  outputParameters.sampleFormat = paUInt8;
  outputParameters.suggestedLatency = 0.050; // Pa_GetDeviceInfo( outputParameters.device )->defaultLowOutputLatency;
  outputParameters.hostApiSpecificStreamInfo = NULL;

  err = Pa_OpenStream(
      &stream,
      NULL, /* no input */
      &outputParameters,
      *freq,
      paFramesPerBufferUnspecified,
      paClipOff, /* we won't output out of range samples so don't bother clipping them */
      NULL,      /* no callback, use blocking API */
      NULL);     /* no callback, so no callback userData */

  if (err != paNoError)
    pa_error(err);

  err = Pa_StartStream(stream);
  if (err != paNoError)
    pa_error(err);
}

void close_audio()
{
  PaError err;
  err = Pa_CloseStream(stream);
  if (err != paNoError)
    pa_error(err);

  Pa_Terminate();
}
