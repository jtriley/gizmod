    /**
  *********************************************************************
*************************************************************************
*** 
*** \file  actor_gizmod.c
*** \brief Gizmod libvisual plugin
***
*****************************************
  *****************************************
    **/

/*
  
  Copyright (c) 2007, Tim Burrell
  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at 

	http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and 
  limitations under the License. 
  
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <math.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <libvisual/libvisual.h>
#include "GizmodLibVisualCInterface.h"

#if HAVE_CONFIG_H
#include <config.h>
#endif
#define CONFIG_FILE "/config"
#define PRESETS_DIR "/presets"
#define FONTS_DIR "/fonts"

// function headers 
int lv_gizmod_init(VisPluginData *plugin);
int lv_gizmod_cleanup(VisPluginData *plugin);
int lv_gizmod_requisition(VisPluginData *plugin, int *width, int *height);
int lv_gizmod_dimension(VisPluginData *plugin, VisVideo *video, int width, int height);
int lv_gizmod_events(VisPluginData *plugin, VisEventQueue *events);
VisPalette *lv_gizmod_palette(VisPluginData *plugin);
int lv_gizmod_render(VisPluginData *plugin, VisVideo *video, VisAudio *audio);

// validate the version
VISUAL_PLUGIN_API_VERSION_VALIDATOR

/**
 * \brief  Plugin information
 *
 * Main plugin stuff 
 * The get_plugin_info function provides the libvisual plugin registry, and plugin loader
 * with the very basic plugin information 
**/
const VisPluginInfo * get_plugin_info(int *count) {
	/* Initialize the plugin specific data structure
	 * with pointers to the functions that represent
	 * the plugin interface it's implementation, more info:
	 * http://libvisual.sourceforge.net/newdocs/docs/html/struct__VisActorPlugin.html**/
	static VisActorPlugin actor[] = {{
		.requisition = 	lv_gizmod_requisition,
		.palette = 	lv_gizmod_palette,
		.render = 	lv_gizmod_render,
		//.vidoptions.depth = VISUAL_VIDEO_DEPTH_GL /* We want GL clearly**/
	}};

	/* This is the non plugin specific data structure, containing
	 * general informatie about the plugin itself, more info:
	 * http://libvisual.sourceforge.net/newdocs/docs/html/struct__VisPluginInfo.html**/
	static const VisPluginInfo info[] = {{
		.type = 	VISUAL_PLUGIN_TYPE_ACTOR,

		.plugname = 	"gizmod",
		.name = 	"libVisual Gizmo Daemon Visualization Plugin",
		.author = 	"Tim Burrell",
		.version = 	"3.0",
		.about = 	"Gizmo Daemon",
		.help =  	"This plugin is for visualizing music on Gizmo Daemon supported Gizmos\n\t(such as LEDs on certain USB dials, etc)",

		.init = 	lv_gizmod_init,
		.cleanup = 	lv_gizmod_cleanup,
		.events = 	lv_gizmod_events,

		.plugin = (void *) &actor[0]
	}};

	*count = sizeof (info) / sizeof (*info);

	/*
	VISUAL_VIDEO_ATTRIBUTE_OPTIONS_GL_ENTRY(actor[0].vidoptions, VISUAL_GL_ATTRIBUTE_ALPHA_SIZE, 8);
	VISUAL_VIDEO_ATTRIBUTE_OPTIONS_GL_ENTRY(actor[0].vidoptions, VISUAL_GL_ATTRIBUTE_DEPTH_SIZE, 16);
	VISUAL_VIDEO_ATTRIBUTE_OPTIONS_GL_ENTRY(actor[0].vidoptions, VISUAL_GL_ATTRIBUTE_DOUBLEBUFFER, 1);

	VISUAL_VIDEO_ATTRIBUTE_OPTIONS_GL_ENTRY(actor[0].vidoptions, VISUAL_GL_ATTRIBUTE_RED_SIZE, 8);
	VISUAL_VIDEO_ATTRIBUTE_OPTIONS_GL_ENTRY(actor[0].vidoptions, VISUAL_GL_ATTRIBUTE_GREEN_SIZE, 8);
	VISUAL_VIDEO_ATTRIBUTE_OPTIONS_GL_ENTRY(actor[0].vidoptions, VISUAL_GL_ATTRIBUTE_BLUE_SIZE, 8);
	*/

	return info;
}

/**
 * \brief  Initialize
 *
 * This function is called before we really start rendering, it's the init function
**/
int lv_gizmod_init(VisPluginData *plugin) {
	GizmodLibVisual_Init();
	return 0;
}

/**
 * \brief  Cleanup
**/
int lv_gizmod_cleanup(VisPluginData *plugin) {
	GizmodLibVisual_CleanUp();
	return 0;
}

/**
 * \brief  Requisition the plugin to see if it can handle the juice
 *
 * This is used to ask a plugin if it can handle a certain size, and if not, to
 * set the size it wants by putting a value in width, height that represents the
 * required size 
**/
int lv_gizmod_requisition(VisPluginData *plugin, int *width, int *height) {
	*width = 0;
	*height = 0;
	return 0;
}

/**
 * \brief  Get the display dimensions
**/
int lv_gizmod_dimension(VisPluginData *plugin, VisVideo *video, int width, int height) {
	return 0;
}

/**
 * \brief  Main event loop
 *
 * This is the main event loop, where all kind of events can be handled, more information
 * regarding these can be found at:
 * http://libvisual.sourceforge.net/newdocs/docs/html/union__VisEvent.html 
**/
int lv_gizmod_events(VisPluginData *plugin, VisEventQueue *events) {
	return 0;
}

/**
 * \brief  Get the palette
 *
 * Using this function we can update the palette when we're in 8bits mode, which
 * we aren't with gizmod, so just ignore :) 
**/
VisPalette *lv_gizmod_palette(VisPluginData *plugin) {
	return NULL;
}

/**
 * \brief  Render
 *
 * This is where the real rendering happens! This function is what we call, many times
 * a second to get our graphical frames. 
**/
int lv_gizmod_render(VisPluginData *plugin, VisVideo *video, VisAudio *audio) {
	// pcm data
	int lp;
	VisBuffer pcmb;
	float pcm[2][512];
	visual_buffer_set_data_pair (&pcmb, pcm[0], sizeof (pcm[0]));
	visual_audio_get_sample (audio, &pcmb, VISUAL_AUDIO_CHANNEL_LEFT);
	visual_buffer_set_data_pair (&pcmb, pcm[1], sizeof (pcm[1]));
	visual_audio_get_sample (audio, &pcmb, VISUAL_AUDIO_CHANNEL_RIGHT);
	
	float VULeft = 0.0f;
	float VURight = 0.0f;
	float VUCombined = 0.0f;
	for (lp = 0; lp < 512; lp ++) {
		float vall = fabs(pcm[0][lp]);
		float valr = fabs(pcm[1][lp]);
		float valc = (vall + valr) / 2.0f;
		
		if (vall > VULeft)
			VULeft = vall;
		if (valr > VURight)
			VURight = valr;
		if (valc > VUCombined)
			VUCombined = valc;
	}
	
	// send off to the server
	GizmodLibVisual_Render(VULeft, VURight, VUCombined);
	
	/*
	// freq data
	const int BARS = 512; // bars is the number of freqs
	float freq[BARS];
	float freqL[BARS];
	float freqR[BARS];
	float pcm[BARS * 2];
	VisBuffer buffer;
	VisBuffer pcmb;
	visual_buffer_set_data_pair(&buffer, freq, sizeof(freq));
	visual_buffer_set_data_pair(&pcmb, pcm, sizeof(pcm));
	visual_audio_get_sample_mixed_simple(audio, &pcmb, 2, VISUAL_AUDIO_CHANNEL_LEFT, VISUAL_AUDIO_CHANNEL_RIGHT);
	visual_audio_get_spectrum_for_sample(&buffer, &pcmb, TRUE);
	
	visual_buffer_set_data_pair(&buffer, freqL, sizeof(freqL));
	visual_audio_get_sample_simple(audio, &pcmb, 2, VISUAL_AUDIO_CHANNEL_LEFT);
	visual_audio_get_spectrum_for_sample(&buffer, &pcmb, TRUE);
	
	visual_buffer_set_data_pair(&buffer, freqR, sizeof(freqR));
	visual_audio_get_sample_simple(audio, &pcmb, 2, VISUAL_AUDIO_CHANNEL_RIGHT);
	visual_audio_get_spectrum_for_sample(&buffer, &pcmb, TRUE);
	*/
	
	return 0;
}
