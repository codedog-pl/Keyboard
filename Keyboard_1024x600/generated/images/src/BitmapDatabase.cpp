// 4.25.0 0x9c6be11e
// Generated by imageconverter. Please, do not edit!

#include <images/BitmapDatabase.hpp>
#include <touchgfx/Bitmap.hpp>

extern const unsigned char image_light_theme_images_backgrounds_1024x600_shattered_rain[]; // BITMAP_LIGHT_THEME_IMAGES_BACKGROUNDS_1024X600_SHATTERED_RAIN_ID = 0, Size: 1024x600 pixels

const touchgfx::Bitmap::BitmapData bitmap_database[] = {
    { image_light_theme_images_backgrounds_1024x600_shattered_rain, 0, 1024, 600, 0, 0, 1024, ((uint8_t)touchgfx::Bitmap::RGB888) >> 3, 600, ((uint8_t)touchgfx::Bitmap::RGB888) & 0x7 }
};

namespace BitmapDatabase
{
const touchgfx::Bitmap::BitmapData* getInstance()
{
    return bitmap_database;
}

uint16_t getInstanceSize()
{
    return (uint16_t)(sizeof(bitmap_database) / sizeof(touchgfx::Bitmap::BitmapData));
}
} // namespace BitmapDatabase
