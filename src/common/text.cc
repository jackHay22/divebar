/*
 * Dive Bar
 * (C) Jack Hay, 2021
 * All rights reserved
 */

#include "text.h"
#include "texture_builder.h"
#include "font.h"

namespace common {

  /**
   * Generate an image from text
   * @param str      the text
   * @param renderer the sdl renderer
   * @param r        color channel r
   * @param g        color channel g
   * @param b        color channel b
   */
  std::shared_ptr<common::image_t> image_from_text(const std::string& str,
                                                   SDL_Renderer& renderer,
                                                   unsigned int r,
                                                   unsigned int g,
                                                   unsigned int b) {
    texture_builder_t builder(FONT_WIDTH * str.size(), FONT_HEIGHT);

    for (size_t c=0; c<str.size(); c++) {

      unsigned char *glyph = (unsigned char *)&FONT + (str[c] * FONT_BPG);

      for (int i=0; i<FONT_HEIGHT; i++) {
        for (int j=0; j<FONT_WIDTH; j++) {

          //check glyph to see if pixel set
          if (*glyph & (1 << j)) {
            //draw the pixel
            builder.set_px_color(j + (c * FONT_WIDTH),i,r,g,b);
          }
        }
        glyph += FONT_BPL;
      }
    }

    return builder.to_image(renderer);
  }

}
