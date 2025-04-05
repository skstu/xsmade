#include "sys.h"
XS_EXTERN void xs_sys_startup(void) {
}
XS_EXTERN void xs_sys_shutdown(void) {
}
XS_EXTERN char *xs_sys_malloc(size_t len) {
  char *result = nullptr;
  do {
    if (len <= 0)
      break;
    result = (char *)malloc(len);
  } while (0);
  return result;
}

XS_EXTERN void xs_sys_free(void **p) {
  if (p) {
    if (*p) {
      free(*p);
      *p = nullptr;
    }
  }
}

XS_EXTERN int xs_sys_image_stream_destroy(xs_image_stream_t **p) {
  if (p && (*p)) {
    xs_sys_free((void **)&(*p)->buffer);
    free(*p);
    *p = nullptr;
  }
  return 0;
}

const std::map<xs_image_type_t, std::vector<std::uint8_t>>
    MAP_IMAGE_SIGNATURES = {
        // PNG	 	Portable Network Graphics file
        {xs_image_type_t::_PNG,
         std::vector<std::uint8_t>{0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A,
                                   0x0A}},
        /*
        FF D8	 	ÿØ
        JPE, JPEG, JPG	 	Generic JPEGimage file
        Trailer: FF D9 (ÿÙ)

        NOTES on JPEG file headers: The proper JPEG header is the two-byte
        sequence, 0xFF-D8, aka Start of Image (SOI) marker. JPEG files end with
        the two-byte sequence, 0xFF-D9, aka End of Image (EOI) marker.

        Between the SOI and EOI, JPEG files are composed of segments. Segments
        start with a two-byte Segment Tag followed by a two-byte Segment Length
        field and then a zero-terminated string identifier (i.e., a character
        string followed by a 0x00), as shown below with the JFIF, Exif, and
        SPIFF segments.

        Segment Tags of the form 0x-FF-Ex (where x = 0..F) are referred to as
        APP0-APP15, and contain application-specific information. The most
        commonly seen APP segments at the beginning of a JPEG file are APP0 and
        APP1 although others are also seen. Some additional tags are shown
        below:

        0xFF-D8-FF-E0 — Standard JPEG/JFIF file, as shown below.
        0xFF-D8-FF-E1 — Standard JPEG file with Exif metadata, as shown below.
        0xFF-D8-FF-E2 — Canon Camera Image File Format (CIFF) JPEG file
        (formerly used by some EOS and Powershot cameras). 0xFF-D8-FF-E8 — Still
        Picture Interchange File Format (SPIFF), as shown below.
*/
        {xs_image_type_t::_JPEG, std::vector<std::uint8_t>{0xFF, 0xD8}},
        /*
        47 49 46 38 37 61 or	 	GIF87a
47 49 46 38 39 61	 	GIF89a
GIF	 	Graphics interchange format file
Trailer: 00 3B (.;)
        */
        {xs_image_type_t::_GIF,
         std::vector<std::uint8_t>{0x47, 0x49, 0x46, 0x38}},
        /*
        00 00 01 00	 	....
ICO	 	Windows icon file
SPL	 	Windows NT/2000/XP printer spool file
        */
        {xs_image_type_t::_ICO,
         std::vector<std::uint8_t>{0x00, 0x00, 0x01, 0x00}},
        /*
        42 4D	 	BM
BMP, DIB	 	Windows (or device-independent) bitmap image
NOTE: Bytes 2-5 contain the file length in little-endian order.
        */
        {xs_image_type_t::_BMP, std::vector<std::uint8_t>{0x42, 0x4D}},
};
int xs_sys_get_image_type(const char *buffer, size_t buffer_size,
                          xs_image_type_t *output_image_type) {
  int r = -1;
  *output_image_type = xs_image_type_t::_Unknown;
  if (buffer && buffer_size > 0) {
    std::string file_buffer(buffer, buffer_size);
    for (const auto &node : MAP_IMAGE_SIGNATURES) {
      if (node.second.empty())
        continue;
      if (file_buffer.size() < node.second.size())
        continue;
      if (0 != memcmp(&node.second[0], file_buffer.data(), node.second.size()))
        continue;
      *output_image_type = node.first;
      r = 0;
      break;
    }
  }
  return 0;
}
void xs_sys_free_buffer(xs_buffer_t **buffer) {
  if (buffer && (*buffer)) {
    free((*buffer)->buffer);
    free((*buffer));
    *buffer = nullptr;
  }
}