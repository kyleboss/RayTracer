#include "Color.h"
#include "Sample.h"

cimg_library::CImg<float> createImg (float width, float height) {
  cimg_library::CImg<float> img(width,height, 1, 3, 0);
  return img;
}

void editPixel(cimg_library::CImg<float>* img, Sample& sample, Color& color) {
  (*img)(sample.x, sample.y, 0) = color.r;
  (*img)(sample.x, sample.y, 1) = color.g;
  (*img)(sample.x, sample.y, 2) = color.b;
}

void saveImg(cimg_library::CImg<float> img) {
  img.save("result.png");
}
