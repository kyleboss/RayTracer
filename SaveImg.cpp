#include <algorithm>
#include "Color.h"
#include "Sample.h"

// cimg_library::CImg<float> createImg (float width, float height) {
//   cimg_library::CImg<float> img(width,height, 1, 3, 0);
//   return img;
// }

void editPixel(cv::Mat* img, Sample& sample, Color& color) {
  // void editPixel(Magick::Image* img, Sample& sample, Color& color) {
  // (*img)(sample.x, sample.y, 0) = color.r;
  // (*img)(sample.x, sample.y, 1) = color.g;
  // (*img)(sample.x, sample.y, 2) = color.b;
  // Magick::ColorRGB magickColor = Magick::ColorRGB(color.r, color.g, color.b);
  // (*img).pixelColor(sample.x, sample.y, magickColor);
  cv::Vec3b oldColor = (*img).at<cv::Vec3b>(cv::Point(sample.x,sample.y));
  oldColor[2] = std::fmax(0, std::fmin(255, color.r*255));
  oldColor[1] = std::fmax(0, std::fmin(255, color.g*255));
  oldColor[0] = std::fmax(0, std::fmin(255, color.b*255));
  (*img).at<cv::Vec3b>(cv::Point(sample.x,sample.y)) = oldColor;
}

void saveImg(cv::Mat img) {
  // void saveImg(Magick::Image img) {
  // img.normalize(0, 255);
  // img.save("result.png");
  // img.write( "result.png" ); 
  vector<int> compression_params;
  compression_params.push_back(cv::IMWRITE_PNG_COMPRESSION);
  compression_params.push_back(9);
  imwrite("result.png", img, compression_params);
}
