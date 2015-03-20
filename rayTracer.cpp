#include <math.h>
#include <iostream>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cmath>
#include <time.h>
#include <opencv2/opencv.hpp>
// #include <Magick++.h> 

int canvasX = 500; //CHANGE THESE!
int canvasY = 500; //CHANGE THESE!
#include "CImg.h"
#include "Camera.h"
#include "Tracer.h"
#include "Canvas.h"
#include "objParse.cpp"
#include "Coord.h"
#include "SaveImg.cpp"
#include "Sphere.h"
#include "Triangle.h"

/*#if !defined(_MSC_VER)
#include <pthread.h>
#endif
#include <omp.h>*/
using namespace cv;
using namespace std;

//************************
// GLOBAL VARIABLES
//************************
	vector<Shape*> all_shapes;
	vector<Triangle> objects; //things to push onto for obj parse
	vector<Light> lights;
	Material last_material = Material(Color(0,0,0), Color(0,0,0), Color(0,0,0), 0, Color(0,0,0)); //intialize to black so there's no garbage
	Coord camEye = Coord(0,0,2);
	Coord camLL = Coord(-1,-1,1);
	Coord camLR = Coord(1,-1,1);
	Coord camUL = Coord(-1,1,1);
	Coord camUR = Coord(1,1,1);
  Matrix transMatrix = Matrix();


// Main render loop
void render() {
	//SET UP CAVAS
	Canvas canvas = Canvas(canvasX, canvasY);

	// //SET UP IMAGE
	// cimg_library::CImg<float> img = createImg(canvasX, canvasY); // Creates Img
  cv::Mat img(canvasX,canvasY,CV_8UC3,Scalar(0,0,0));
  // Magick::Blob blob(&Magick::rgbt[0],(rgbt.size()*sizeof(rgbt[0]));
  // std::string canvasXStr = std::to_string(canvasX);
  // std::string canvasYStr = std::to_string(canvasY);
  // Magick::Image img( canvasYStr + "x" + canvasXStr, "black"); 
	// //SET UP TRACER
	Tracer tracer = Tracer(all_shapes);       

	// //SET UP CAMERA through command line
	Camera camera = Camera(camEye, camLL, camUL, camLR, camUR, canvasX, canvasY);


	//RENDER LOOP FAST
		while (canvas.getSample(&canvas.currSample)) {
		Color color = Color(0,0,0);
		Sample sample = canvas.currSample;
		float u = (sample.x + 0.5) / canvasX ;
		float v = (sample.y + 0.5) / canvasY;
		Ray ray = camera.shootRay(u, v);
		HitRecord hitRecord = tracer.hit(ray);
		if (hitRecord.isHit) {
			color = tracer.trace(hitRecord, lights, hitRecord.ray.direction);
		}
	    //clipping
	    if (color.r > 1)
	    	color.r = 1;
	    if (color.g > 1)
	    	color.g = 1; 
	    if (color.b > 1)
	    	color.b = 1;
	    editPixel(&img, canvas.currSample, color); //writes to the image
	}

/*
	//RENDER LOOP for aliasing   
	while (canvas.getSample(&canvas.currSample)) {
		Color color = Color(0,0,0);
		Sample sample = canvas.currSample;
		int n = 3; //do 3x3 anti-aliasing
		//#pragma omp parallel for 
		for (int p = 0; p < n; p++) {
			for (int q = 0; q < n; q++) {
				float zetta = ((float) rand() / (RAND_MAX));
				float u = (sample.x + (p + zetta)/n) / canvasX ;
  				float v = (sample.y + (q + zetta)/n) / canvasY;
				Ray ray = camera.shootRay(u, v);
				HitRecord hitRecord = tracer.hit(ray);
				if (hitRecord.isHit) {
				    color = color + tracer.trace(hitRecord, lights, ray.direction);
				}  
			}
		}
		float scale = (float) 1/(n*n);
		color = color.scale(scale); //c = c/n^2
	    //clipping
	   if (color.r > 1)
	    	color.r = 1;
	    if (color.g > 1)
	    	color.g = 1; 
	    if (color.b > 1)
	    	color.b = 1;
	    editPixel(&img, canvas.currSample, color); //writes to the image
	} */  

  	// Color color = Color(1,1,1);
  	// editPixel(&img, canvas.currSample, color);
	saveImg(img); // Saving image to file result.png
  	// cimg_library::CImgDisplay main_disp(img, "RayTracer", 3);
 	// img.display(); 

  cv::namedWindow("RayTracer",cv::WINDOW_AUTOSIZE);
  cv::imshow("RayTracer", img);
  waitKey(-1);
  
}; 

//To put command line parsings here
void commandLine(int argc, char *argv[]) {
	for (int i = 1; i < argc; ++i) {
	    if (i < argc && strcmp(argv[i], "cam") == 0) {
	      //cam ex ey ez llx lly llz lrx lry lrz ulx uly ulz urx ury urz
	      camEye = Coord(strtof(argv[i+1], NULL), strtof(argv[i+2], NULL), strtof(argv[i+3], NULL));
	      camLL = Coord(strtof(argv[i+4], NULL), strtof(argv[i+5], NULL), strtof(argv[i+6], NULL));
	      camLR = Coord(strtof(argv[i+7], NULL), strtof(argv[i+8], NULL), strtof(argv[i+9], NULL));
	      camUL = Coord(strtof(argv[i+10], NULL), strtof(argv[i+11], NULL), strtof(argv[i+12], NULL));
	      camUR = Coord(strtof(argv[i+13], NULL), strtof(argv[i+14], NULL), strtof(argv[i+15], NULL));
	      camEye = Transform::performTransform(camEye, transMatrix);
	      camLL = Transform::performTransform(camLL, transMatrix);
	      camLR = Transform::performTransform(camLR, transMatrix);
	      camUL = Transform::performTransform(camUL, transMatrix);
	      camUR = Transform::performTransform(camUR, transMatrix);
	      i += 15;
	    }
	    else if (i < argc && strcmp(argv[i], "sph") == 0) {
	      Coord c = Coord(strtof(argv[i+1], NULL), strtof(argv[i+2], NULL), strtof(argv[i+3], NULL));
	      // c = Transform::performTransform(c, transMatrix);
        Sphere * sph = new Sphere(c, strtof(argv[i+4], NULL), last_material, transMatrix);
	      all_shapes.push_back(sph);
	      i += 4;
	    }
	    else if (i < argc && strcmp(argv[i], "tri") == 0) {
	      Coord a = Coord(strtof(argv[i+1], NULL), strtof(argv[i+2], NULL), strtof(argv[i+3], NULL));
	      Coord b = Coord(strtof(argv[i+4], NULL), strtof(argv[i+5], NULL), strtof(argv[i+6], NULL));
	      Coord c = Coord(strtof(argv[i+7], NULL), strtof(argv[i+8], NULL), strtof(argv[i+9], NULL));
	      // a = Transform::performTransform(a, transMatrix);
	      // b = Transform::performTransform(b, transMatrix);
	      // c = Transform::performTransform(c, transMatrix);
	      Triangle * tri = new Triangle(a, b, c, last_material, transMatrix);
	      all_shapes.push_back(tri);
	      i += 9;
	    }  
	    else if (i < argc && strcmp(argv[i], "obj") == 0) {
	    	objParse(argv[i+1], &objects, &transMatrix);
	    	for (int i = 0; i < objects.size(); i++) {
	    		Triangle * objtri;
	    		if (objects[i].hasNormal) { //w defined normals
		    		objtri = new Triangle(objects[i].point1, objects[i].point2, objects[i].point3, objects[i].vn1, objects[i].vn2, objects[i].vn3, last_material, transMatrix);
	    		} 
	    		else {  
		    		objtri = new Triangle(objects[i].point1, objects[i].point2, objects[i].point3, last_material, transMatrix);
	    		}
	    		all_shapes.push_back(objtri);
	    	} 
	    	//hacky fix to deal w/ shape class, if slow fix later ^
	      i += 1; 
	    }
	    else if (i < argc && strcmp(argv[i], "ltp") == 0) {
	    	//ltp px py pz r g b falloff
	      Coord pl = Coord(strtof(argv[i+1], NULL), strtof(argv[i+2], NULL), strtof(argv[i+3], NULL));
	      Color pl_c = Color(strtof(argv[i+4], NULL), strtof(argv[i+5], NULL), strtof(argv[i+6], NULL));
	      pl = Transform::performTransform(pl, transMatrix);
	      if ((strcmp(argv[i+7], "0") == 0) || (strcmp(argv[i+7], "1") == 0) || (strcmp(argv[i+7], "2") == 0)) {
	      	//if they specified falloff
	      	lights.push_back(Light(pl, pl_c, 2, strtof(argv[i+7], NULL)));
	      	i += 7;
	      }
	      else {
	      	lights.push_back(Light(pl, pl_c, 2, 0));
	      	i+= 6;
	      }
	    }
	    else if (i < argc && strcmp(argv[i], "ltd") == 0) {
	      Coord dl = Coord(strtof(argv[i+1], NULL), strtof(argv[i+2], NULL), strtof(argv[i+3], NULL));
	      Color dl_c = Color(strtof(argv[i+4], NULL), strtof(argv[i+5], NULL), strtof(argv[i+6], NULL));
	      dl = Transform::performTransform(dl, transMatrix);
	      lights.push_back(Light(dl, dl_c, 1));
	      i += 6;
	    }
	    else if (i < argc && strcmp(argv[i], "lta") == 0) {
	      Coord al = Coord(0,0,0); //lol
	      Color al_c = Color(strtof(argv[i+1], NULL), strtof(argv[i+2], NULL), strtof(argv[i+3], NULL));
	      al = Transform::performTransform(al, transMatrix);
	      lights.push_back(Light(al, al_c, 0));
	      i += 3;
	    }
	    else if (i < argc && strcmp(argv[i], "mat") == 0) {
	      Color ka = Color(strtof(argv[i+1], NULL), strtof(argv[i+2], NULL), strtof(argv[i+3], NULL));
	      Color kd = Color(strtof(argv[i+4], NULL), strtof(argv[i+6], NULL), strtof(argv[i+6], NULL));
	      Color ks = Color(strtof(argv[i+7], NULL), strtof(argv[i+8], NULL), strtof(argv[i+9], NULL));
	      Color kr = Color(strtof(argv[i+11], NULL), strtof(argv[i+12], NULL), strtof(argv[i+13], NULL));
	      last_material = Material(ka, kd, ks, strtof(argv[i+10], NULL), kr);
	      i += 13;
	    }
	    else if (i < argc && strcmp(argv[i], "xft") == 0) {
	 			Transform(TRANSLATION, strtof(argv[i+1], NULL),strtof(argv[i+2], NULL),strtof(argv[i+3], NULL));
	      transMatrix = Transform::calcTransMatrix();
        i += 3;
	    }
	    else if (i < argc && strcmp(argv[i], "xfr") == 0) {
	 			Transform(ROTATION, strtof(argv[i+1], NULL),strtof(argv[i+2], NULL),strtof(argv[i+3], NULL));
	      transMatrix = Transform::calcTransMatrix();
        i += 3;
	    }
	    else if (i < argc && strcmp(argv[i], "xfs") == 0) {
	 			Transform(SCALE, strtof(argv[i+1], NULL),strtof(argv[i+2], NULL),strtof(argv[i+3], NULL));
	      transMatrix = Transform::calcTransMatrix();
        i += 3;
	    }
	    else if (i < argc && strcmp(argv[i], "xfz") == 0) {
	 			transMatrix = Matrix();
	      i += 1;
	    }
	    else { //error handling per last pg in spec
	    	cerr << "Bad command line input" << endl;
	    }
	}
}

int main (int argc, char *argv[]) {
  commandLine(argc, argv);     
  render();
  return 0;
}
