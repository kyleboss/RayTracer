#include "Color.h"
#include "Sample.h"

// cimg_library::CImg<float> createImg (float width, float height) {
//   cimg_library::CImg<float> img(width,height, 1, 3, 0);
//   return img;
// }

// void editPixel(cimg_library::CImg<float>* img, Sample& sample, Color& color) {
  void editPixel(Magick::Image* img, Sample& sample, Color& color) {
  // (*img)(sample.x, sample.y, 0) = color.r;
  // (*img)(sample.x, sample.y, 1) = color.g;
  // (*img)(sample.x, sample.y, 2) = color.b;
  Magick::ColorRGB magickColor = Magick::ColorRGB(color.r, color.g, color.b);
  (*img).pixelColor(sample.x, sample.y, magickColor);
}

// void saveImg(cimg_library::CImg<float> img) {
  void saveImg(Magick::Image img) {
  // img.normalize(0, 255);
  // img.save("result.png");
  img.write( "result.png" ); 
}
