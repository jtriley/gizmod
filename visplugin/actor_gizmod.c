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

void debugPrint(const char * text) {
	FILE * f = fopen("/tmp/actor_gizmod.log", "a");
	fprintf(f, text);
	fclose(f);
}

// validate the version
VISUAL_PLUGIN_API_VERSION_VALIDATOR

/**
 * \brief  Plugin information
 *
 * Main plugin stuff 
 * The get_plugin_info function provides the libvisual plugin registry, and plugin loader
 * with the very basic plugin information 
 */
const VisPluginInfo * get_plugin_info(int *count) {
	debugPrint("plugin info\n");
	
	/* Initialize the plugin specific data structure
	 * with pointers to the functions that represent
	 * the plugin interface it's implementation, more info:
	 * http://libvisual.sourceforge.net/newdocs/docs/html/struct__VisActorPlugin.html */
	static VisActorPlugin actor[] = {{
		.requisition = 	lv_gizmod_requisition,
		.palette = 	lv_gizmod_palette,
		.render = 	lv_gizmod_render,
		//.vidoptions.depth = VISUAL_VIDEO_DEPTH_GL /* We want GL clearly */
	}};

	/* This is the non plugin specific data structure, containing
	 * general informatie about the plugin itself, more info:
	 * http://libvisual.sourceforge.net/newdocs/docs/html/struct__VisPluginInfo.html */
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
 */
int lv_gizmod_init(VisPluginData *plugin) {
	// initialize
	GizmodLibVisual_Init();
	return 0;
}

/**
 * \brief  Cleanup
 */
int lv_gizmod_cleanup(VisPluginData *plugin) {
	// Cleanup, and thus also free our private 
	debugPrint("cleanup\n");
	return 0;
}

/**
 * \brief  Requisition the plugin to see if it can handle the juice
 *
 * This is used to ask a plugin if it can handle a certain size, and if not, to
 * set the size it wants by putting a value in width, height that represents the
 * required size 
 */
int lv_gizmod_requisition(VisPluginData *plugin, int *width, int *height) {
	debugPrint("requisition\n");
	
	*width = 0;
	*height = 0;

	return 0;
}

/**
 * \brief  Get the display dimensions
 */
int lv_gizmod_dimension(VisPluginData *plugin, VisVideo *video, int width, int height) {
	debugPrint("dimension\n");
		
	return 0;
}

/**
 * \brief  Main event loop
 *
 * This is the main event loop, where all kind of events can be handled, more information
 * regarding these can be found at:
 * http://libvisual.sourceforge.net/newdocs/docs/html/union__VisEvent.html 
 */
int lv_gizmod_events(VisPluginData *plugin, VisEventQueue *events) {
	debugPrint("events\n");
	return 0;
}

/**
 * \brief  Get the palette
 *
 * Using this function we can update the palette when we're in 8bits mode, which
 * we aren't with gizmod, so just ignore :) 
 */
VisPalette *lv_gizmod_palette(VisPluginData *plugin) {
	return NULL;
}

/**
 * \brief  Render
 *
 * This is where the real rendering happens! This function is what we call, many times
 * a second to get our graphical frames. 
 */
int lv_gizmod_render(VisPluginData *plugin, VisVideo *video, VisAudio *audio) {
	debugPrint("render\n");
	return 0;
}
