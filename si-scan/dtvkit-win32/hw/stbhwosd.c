/*******************************************************************************
 * Copyright (c) 2018 The DTVKit Open Software Foundation Ltd (www.dtvkit.org)
 *
 * This file is part of a DTVKit Software Component
 * You are permitted to copy, modify or distribute this file subject to the terms
 * of the DTVKit 1.0 Licence which can be found in licence.txt or at www.dtvkit.org
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
 * EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR PURPOSE.
 *
 * If you or your organisation is not a member of DTVKit then you have access
 * to this source code outside of the terms of the licence agreement
 * and you are expected to delete this and any associated files immediately.
 * Further information on DTVKit, membership and terms can be found at www.dtvkit.org
 *******************************************************************************/
/**
 * @brief   Set Top Box - Hardware Layer, On Screen Display
 * @file    stbhwosd.c
 * @date    October 2018
 */

//#define OSD_DEBUG
//#define SUBT_DEBUG
//#define MHEG_DEBUG

/*---includes for this file--------------------------------------------------*/
#include <string.h>
#include <math.h>

#include "techtype.h"
#include "dbgfuncs.h"

#include "stbhwdef.h"
#include "stbhwmem.h"
#include "stbhwos.h"
#include "stbhwc.h"
#include "stbhwosd.h"
//#include "stb_osd.h"

#include "cert_log.h"

#define TAG "STBHWOSD_STUB"

/*---constant definitions for this file--------------------------------------*/

/*---macro definitions for this file-----------------------------------------*/

/*---local typedef structs for this file-------------------------------------*/



/*---global variable definitions---------------------------------------------*/

/*---global function definitions---------------------------------------------*/

/**
 * @brief   Initialised the OSD hardware layer functions
 * @param   num_max_regions - number of regions required (not used here)
 */
void STB_OSDInitialise(U8BIT num_max_regions)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func", __FUNCTION__);
}


/**
 * @brief   Reconfigures the OSD for a new screen size
 * @param   scaling - TRUE if osd scaling is required due to MHEG scene
 *          aspect ratio, FALSE otherwise
 * @param   width - width of OSD in pixels
 * @param   height - height of OSD in pixels
 * @param   x_offset - offset of OSD from left of screen, in pixels
 * @param   y_offset - offset of OSD from top of screen, in pixels
 */
void STB_OSDResize(BOOLEAN scaling, U16BIT width, U16BIT height, U16BIT x_offset, U16BIT y_offset)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func", __FUNCTION__);
}


/**
 * @brief   Commit invisible buffer to visible surface and copy back
 */
void STB_OSDUpdate(void)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func", __FUNCTION__);
}


/**
 * @brief   Enable/Disable the OSD
 * @param   enable - TRUE to enable
 * @return  The new state ( i.e. will = param if successful )
 */
BOOLEAN STB_OSDEnable(BOOLEAN enable)
{
   FUNCTION_START(STB_OSDEnable);
   USE_UNWANTED_PARAM(enable);
   FUNCTION_FINISH(STB_OSDEnable);

   return FALSE;
}

/**
 * @brief   Sets the OSD transparency level (0-100%)
 * @param   trans - transparency in percent
 */
void STB_OSDSetTransparency(U8BIT trans)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func", __FUNCTION__);
}


/**
 * @brief   Returns the current OSD transparency level
 * @return  The current transparency in percent
 */
U8BIT STB_OSDGetTransparency(void)
{
   FUNCTION_START(STB_OSDGetTransparency);
   FUNCTION_FINISH(STB_OSDGetTransparency);
   return 0;
}

/**
 * @brief   Sets a range of palette entries to Trans/Red/Grn/Blue levels
 * @param   index - starting number of palette entry to be set
 * @param   num - number of consecutive palette entries to set
 * @param   trgb - the colour value array
 */
void STB_OSDSetPalette(U16BIT index, U16BIT num, U32BIT *trgb)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func", __FUNCTION__);
}


/**
 * @brief   Draw a bitmap into the composition (invisible) buffer
 * @param   x - the x coordinate where to draw
 * @param   y - the x coordinate where to draw
 * @param   width - width of bitmap in pixels
 * @param   height - height of bitmap in pixels
 * @param   bits - bits per pixel of source bitmap
 * @param   data - the bitmap data
 */
void STB_OSDDrawBitmap(U16BIT x, U16BIT y, U16BIT width, U16BIT height, U8BIT bits, U8BIT *data)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func", __FUNCTION__);
}


/**
 * @brief   Read a bitmap from the composition (invisible) buffer
 * @param   x - the x coordinate where to read
 * @param   y - the x coordinate where to read
 * @param   width - width of bitmap in pixels
 * @param   height - height of bitmap in pixels
 * @param   bits - bits per pixel of destination bitmap
 * @param   data - the resultant bitmap data
 */
void STB_OSDReadBitmap(U16BIT x, U16BIT y, U16BIT width, U16BIT height, U8BIT bits, U8BIT *data)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func", __FUNCTION__);
}


/**
 * @brief   Draw a single pixel in the composition buffer
 * @param   x - x coordinate of pixel
 * @param   y - y coordinate of pixel
 * @param   colour - colour of pixel
 */
void STB_OSDDrawPixel(U16BIT x, U16BIT y, U32BIT colour)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func", __FUNCTION__);
}


/**
 * @brief   Read a single pixel from the composition buffer
 * @param   x - x coordinate of pixel
 * @param   y - y coordinate of pixel
 * @param   colour - colour of pixel
 */
void STB_OSDReadPixel(U16BIT x, U16BIT y, U32BIT *colour)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func", __FUNCTION__);
}


/**
 * @brief   Draw a horizontal line in the composition buffer
 * @param   x - x coordinate of line
 * @param   y - y coordinate of line
 * @param   width - width of line in pixels
 * @param   colour - colour of line
 */
void STB_OSDDrawHLine(U16BIT x, U16BIT y, U16BIT width, U32BIT colour)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func", __FUNCTION__);
}


/**
 * @brief   Draw a vertical line in the composition buffer
 * @param   x - x coordinate of line
 * @param   y - y coordinate of line
 * @param   height - height of line in pixels
 * @param   colour - colour of line
 */
void STB_OSDDrawVLine(U16BIT x, U16BIT y, U16BIT height, U32BIT colour)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func", __FUNCTION__);
}


/**
 * @brief   Draw a rectangle in the composition buffer
 * @param   x - x coordinate of rectangle
 * @param   y - x coordinate of rectangle
 * @param   width - width of rectangle
 * @param   height - height of rectangle
 * @param   colour - colour of rectangle
 * @param   thick - thickness of outline for hollow rectangles
 * @param   fill - TRUE for solid (filled) rectangle
 */
void STB_OSDDrawRectangle(U16BIT x, U16BIT y, U16BIT width, U16BIT height, U32BIT colour,
   U8BIT thick, BOOLEAN fill)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func", __FUNCTION__);
}


/**
 * @brief   Returns the current width and height of the OSD
 * @param   width - width of OSD in pixels
 * @param   height - height of OSD in pixels
 */
void STB_OSDGetSize(U16BIT *width, U16BIT *height)
{
   CERT_LOG_DEBG(TAG, "[%s] Empty Func", __FUNCTION__);
}


/**
 * @brief   Clear the entire composition buffer to a single colour
 * @param   colour - colour to clear to
 */
void STB_OSDClear(U32BIT colour)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func", __FUNCTION__);
}


/**
 * @brief   Clear the user interface layer to the given colour using the given blit op
 * @param   colour - colour to clear to
 * @param   bflg - blit operation
 */
void STB_OSDFill(U32BIT colour, E_BLIT_OP bflg)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func", __FUNCTION__);
}


/**
 * @brief   Register app fn that can be called to redraw OSD
 * @param   func - the callback function
 */
void STB_OSDRegisterRefreshHandler(void (*func)(void))
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func", __FUNCTION__);
}


/**
 * @brief   Can be called by anyone to force redraw of the OSD by the UI
 */
void STB_OSDRefreshDisplayCallback(void)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func", __FUNCTION__);
}


/**
 * @brief   Returns a pointer to the current TRGB palette (clut)
 * @return  Pointer to an array of 32bit trans,red,green,blue values
 */
U32BIT* STB_OSDGetCurrentPalette(void)
{
   FUNCTION_START(STB_OSDGetCurrentPalette);
   FUNCTION_FINISH(STB_OSDGetCurrentPalette);
   return(NULL);
}


/**
 * @brief   Enables (makes visible) the OSD
 * @return  TRUE if succesful, FALSE otherwise
 */
BOOLEAN STB_OSDEnableUIRegion(void)
{
   FUNCTION_START(STB_OSDEnableUIRegion);
   FUNCTION_FINISH(STB_OSDEnableUIRegion);

   return FALSE;
}

/**
 * @brief   Disables (makes invisible) the OSD
 * @return  TRUE if succesful, FALSE otherwise
 */
BOOLEAN STB_OSDDisableUIRegion(void)
{
   FUNCTION_START(STB_OSDDisableUIRegion);
   FUNCTION_FINISH(STB_OSDDisableUIRegion);

   return FALSE;
}

/**
 * @brief   Creates a new OSD region (for subtitling)
 * @param   width - width of new region
 * @param   height - height of new region
 * @param   depth - bits per pixel of new region
 * @return  handle (pointer to) new region
 */
void* STB_OSDCreateRegion(U16BIT width, U16BIT height, U8BIT depth)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func", __FUNCTION__);
}


/**
 * @brief   Destroys (free the resources used by) a region
 * @param   handle - handle of (pointer to) the region
 */
void STB_OSDDestroyRegion(void* handle)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func", __FUNCTION__);
}


/**
 * @brief   Sets a regions entire palette to a T,Y,CR,CB clut
 * @param   handle - handle (pointer to) the region to configure
 * @param   tycrcb - pointer to the CLUT entries
 */
void STB_OSDSetYCrCbPalette(void *handle, U32BIT *tycrcb)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func", __FUNCTION__);
}


/**
 * @brief   Move a region to new coordinates
 * @param   handle - handle of (pointer to) the region
 * @param   x - new x coordinate of region
 * @param   y - new y coordinate of region
 */
void STB_OSDMoveRegion(void *handle, U16BIT x, U16BIT y)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func", __FUNCTION__);
}


/**
 * @brief   Makes a region invisible
 * @param   handle - handle of (pointer to) the region
 */
void STB_OSDHideRegion(void* handle)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func", __FUNCTION__);
}


/**
 * @brief   Makes a region visible
 * @param   handle - handle of (pointer to) the region
 */
void STB_OSDShowRegion(void* handle)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func", __FUNCTION__);
}


/**
 * @brief   Updates the display of all subtitle regions
 */
void STB_OSDUpdateRegions(void)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func", __FUNCTION__);
}


/**
 * @brief   Draw a bitmap in a specified region
 * @param   handle - handle of (pointer to) the region
 * @param   x - x coordinate to draw bitmap
 * @param   y - y coordinate to draw bitmap
 * @param   w - width of bitmap
 * @param   h - height of bitmap
 * @param   bitmap - the bitmap data
 * @param   non_modifying_colour - not used
 */
void STB_OSDDrawBitmapInRegion(void* handle, U16BIT x, U16BIT y, U16BIT w, U16BIT h,
      U8BIT* bitmap, BOOLEAN non_modifying_colour)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func", __FUNCTION__);
}


/**
 * @brief   Copy a region to another region, including palette
 * @param   handle_new - handle of (pointer to) new (destination) region
 * @param   handle_old - handle of (pointer to) old (source) region
 */
void STB_OSDRegionToRegionCopy(void *handle_new, void *handle_orig)
{
  CERT_LOG_DEBG(TAG, "[%s] Empty Func", __FUNCTION__);
}


/**
 * @brief   Fill a region with a colour
 * @param   handle - handle of (pointer to) the region
 * @param   colour - the colour index to fill with
 */
void STB_OSDFillRegion(void *handle, U8BIT colour)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func", __FUNCTION__);
}


/**
 * @brief   Should be called to set the size of the display so that SD subtitles
 *          can be scaled correctly for an HD display, or vice versa.
 * @param   width - display width defined by the subtitle DDS
 * @param   height - display height defined by the subtitle DDS
 */
void STB_OSDSetRegionDisplaySize(U16BIT width, U16BIT height)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func", __FUNCTION__);
}


/**
 * @brief   Fill the rectangle within the given region with the given colour
 * @param   handle - region handle
 * @param   left - x position of rectangle within the region
 * @param   top - y position of rectangle within the region
 * @param   width - rectangle width
 * @param   height rectangle height
 * @param   colour - fill colour
 */
void STB_OSDRegionFillRect(void *handle, U16BIT left, U16BIT top, U16BIT width,
   U16BIT height, U8BIT colour)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func", __FUNCTION__);
}


/**
 * @brief   Sets the palette for the given region based on a set of RGB values
 * @param   handle region handle
 * @param   trgb array of TRGB palette entries, the size of which is defined
 *               by the colour depth of the region
 */
void STB_OSDSetRGBPalette(void *handle, U32BIT *trgb)
{
   CERT_LOG_DEBG(TAG, "[%s] Empty Func", __FUNCTION__);
}


/**
 * @brief   Sets Colour Palette array of up to 256 values, for single byte colour depth.
 *          This palette being an array of 'U32BIT' (8 Alpha, 8 Red, 8 Green, 8 Blue).
 * @param   index
 * @param   number   Size of palette array
 * @param   argb     pointer to palette array
 */
void STB_OSDMhegSetPalette(U16BIT index, U16BIT number, const U32BIT *argb)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func", __FUNCTION__);
}


/**
 * @brief   Sets the size of the OSD to be used by MHEG engine.
 *          The return must be a surface handle for the entire screen back-buffer.
 *          The Engine will draw to the surface using STB_OSDMhegBlitStretch, which
 *          would be equivalent to it using STB_OSDMhegBlitBitmap() without stretching.
 * @param   width   Width of MHEG OSD resolution
 * @param   height  Height of MHEG OSD resolution
 * @param   bits    Number of bits per pixel
 * @return  Surface handle of MHEG OSD layer
 */
void* STB_OSDMhegSetResolution(U16BIT width, U16BIT height, U8BIT bits)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func", __FUNCTION__);

    return NULL;
}



/**
 * @brief   Creates a hardware surface on which MHEG5 engine will draw an individual
 *          MHEG object.
 *          At its basic the function can just allocate the buffer to be returned by
 *          STB_OSDMhegLockBuffer(). It's size being: (width * height * bytes_per_pixel)
 *          Also, when 'init' is TRUE, function initialises surface buffer to the
 *          specified colour. For pixel colour format of less than four bytes, use
 *          least significant bits of 'colour'.
 * @param   width Width of requested surface in pixels
 * @param   height Height of requested surface in pixels
 * @param   init If TRUE, initialise buffer with colour.
 * @param   colour colour for all pixels in buffer.
 * @return  void*    Success  -  Handle to surface.
 *          Failure  -  NULL (or zero)
 */
void* STB_OSDMhegCreateSurface(U16BIT width, U16BIT height, BOOLEAN init, U32BIT colour)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func", __FUNCTION__);

    return NULL;
}


/**
 * @brief   Converts hardware surface handle returned by STB_OSDMhegCreateSurface()
 *          to buffer address that the engine needs in order to draw the MHEG object.
 *          This function can inform HW that the engine needs write access to buffer.
 *          MHEG5 will use the return address and 'pitch' (or stride) value to
 *          locate pixel data.
 *          Before calling this function, 'pitch' is  initialised to width as given
 *          by STB_OSDMhegCreateSurface(), but platform can alter this here.
 * @param   surface Handle of surface returned by STB_OSDMhegCreateSurface
 * @param   pitch width in bytes of one line of pixel data in buffer
 * @return  void*    Address of the buffer
 */
void* STB_OSDMhegLockBuffer( void *surface, U32BIT *pPitch )
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func", __FUNCTION__);

    return NULL;
}


/**
 * @brief   This function informs HW that MHEG5 is finished writing to the buffer.
 * @param   surface Handle of surface returned by STB_OSDMhegCreateSurface
 * @return  void
 */
void STB_OSDMhegUnlockBuffer( void *surface )
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func", __FUNCTION__);

}


/**
 * @brief   This function destroys surface and all data allocated by
 *          STB_OSDMhegCreateSurface()
 * @param   surface Handle of surface returned by STB_OSDMhegCreateSurface
 * @return  void
 */
void STB_OSDMhegDestroySurface(void *surface)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func", __FUNCTION__);

}



/**
 * @brief   Render bitmap on OSD back buffer in the given screen location, with given
 *          operation.
 *          The bitmap is referenced 'surface' - a handle returned by
 *          STB_OSDMhegCreateSurface()
 *          1. It is a one-to-one mapping between surface pixels and screen pixels, so
 *          rect.width and rect.height give size of rectangle on the screen as well.
 *          2. (rect.top + rect.height) is guarenteed to be less than or equal to height
 *          given to STB_OSDMhegCreateSurface()
 * @param   surface Handle of surface returned by STB_OSDMhegCreateSurface
 * @param   rect source rectangle within surface - top/left is offset into
 *          bitmap referenced by 'surface', width/height gives size.
 * @param   pitch Width of line of source bitmap data - as returned by
 *          STB_OSDMhegLockBuffer()
 * @param   screen_x Left or X position on screen to draw bitmap
 * @param   screen_y Top or Y position on screen to draw bitmap
 * @param   bflg Operation - COPY or ALPHA BLEND
 * @return  void
 */
void STB_OSDMhegBlitBitmap( void *surface, S_RECTANGLE *pRect, U32BIT pitch,
   U16BIT screen_x, U16BIT screen_y, E_BLIT_OP bflg )
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func", __FUNCTION__);

}


/**
 * @brief   Draw a filled rectangle on OSD back buffer in the location given.
 *          Where pixel colour is less than four bytes, use least significant bits
 *          in 'colour'.
 *          'rect' can be part of the screen or the entire screen.
 * @param   rect rectangle on screen - with top,left starting position
 * @param   colour colour for all pixels in rectangle.
 * @param   bflg Operation - COPY or ALPHA BLEND
 * @return  void
 */
void STB_OSDMhegFillRectangle( S_RECTANGLE *pRect, U32BIT colour, E_BLIT_OP bflg )
{
   CERT_LOG_DEBG(TAG, "[%s] Empty Func", __FUNCTION__);

}


/**
 * @brief   Stretch blit bitmap data from source surface to destination surface
 *          using source and destination rectangles. When 'dst_surf' is handle
 *          returned by STB_OSDMhegSetResolution(), and rectangles are same size,
 *          this function is equivalent to STB_OSDMhegBlitBitmap.
 * @param   pSrcRect rectangle for bitmap data
 * @param   src_surf handle returned by STB_OSDMhegCreateSurface
 * @param   pDstRect rectangle for destination on surface
 * @param   dst_surf handle returned by STB_OSDMhegCreateSurface or
 *          STB_OSDMhegSetResolution
 * @param   bflg Operation - COPY or ALPHA BLEND
 * @return  void
 */
void STB_OSDMhegBlitStretch( S_RECTANGLE *pSrcRect, void *src_surf,
   S_RECTANGLE *pDstRect, void *dst_surf, E_BLIT_OP bflg )
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func", __FUNCTION__);

}


/**
 * @brief   Draw a filled rectangle on surface in the location given.
 *          Where pixel colour is less than four bytes, use least significant bits
 *          in 'colour'.
 * @param   surface handle returned by STB_OSDMhegCreateSurface
 * @param   rect rectangle on screen - with top,left starting position
 * @param   colour colour for all pixels in rectangle.
 * @param   bflg Operation - COPY or ALPHA BLEND
 * @return  void
 */
void STB_OSDMhegFillSurface( void *surface, S_RECTANGLE *pRect, U32BIT colour, E_BLIT_OP bflg )
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func", __FUNCTION__);

}


/**
 * @brief   Commit OSD changes to the screen - changes given by previous calls to
 *          STB_OSDMhegDrawRectangle() and STB_OSDMhegDrawBitmap().
 * @return  void
 */
void STB_OSDMhegUpdate(void)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func", __FUNCTION__);

}


/**
 * @brief   Clear MHEG's entire OSD
 */
void STB_OSDMhegClear(void)
{
    CERT_LOG_DEBG(TAG, "[%s] Empty Func", __FUNCTION__);

}




