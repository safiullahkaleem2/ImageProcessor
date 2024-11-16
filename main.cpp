/**
 * @file main.cpp
 * @description 
 */

#include "util/HSLAPixel.h"
#include "util/PNG.h"
#include "imgtree.h"

using namespace util;
using namespace std;

/**
 * Test function declarations
 */
// void TestBuild();
// void TestCopy();
// void TestFlipHorizontal();
void TestPrune();
void TestPruneFlip();

int main()
{
	// TestBuild();
	// cout << "Exited TestBuild." << endl;

	// // TestCopy();
	// // cout << "Exited TestCopy." << endl;

	// TestFlipHorizontal();
	// cout << "Exited TestFlipHorizontal" << endl;

	TestPrune();
	cout << "Exited TestPrune" << endl;

	TestPruneFlip();
	cout << "Exited TestPruneFlip" << endl;

  return 0;
}

// void TestBuild() {
// 	cout << "Entered TestBuild..." << endl;

// 	// read in an image
// 	PNG origimg;
// 	origimg.readFromFile("images-original/colours-8x6.png");

// 	// use it to build a ImgTree
// 	ImgTree t1(origimg);

// 	// render to file
// 	PNG outimg = t1.Render();

// 	// write the rendered PNG to file
// 	outimg.writeToFile("images-output/colours-8x6-render.png");
// }


// void TestBuild() {
// 	cout << "Entered TestBuild..." << endl;

// 	// read in an image
// 	PNG origimg;
// 	origimg.readFromFile("images-original/Untitled2.png");

// 	// use it to build a ImgTree
// 	ImgTree t1(origimg);
// 	// t1.Helpera();
// 	// // render to file
// 	PNG outimg = t1.Render();

// 	// write the rendered PNG to file
// 	outimg.writeToFile("images-output/test.png");
// }

// void TestCopy() {
// 	cout << "Entered TestCopy..." << endl;

// 	// read in two images
// 	PNG img1, img2;
// 	img1.readFromFile("images-original/bc-257x240.png");
// 	img2.readFromFile("images-original/Untitled2.png");

// 	// build three trees
// 	ImgTree t1(img1); // first tree from img1
// 	ImgTree t2(t1);   // second tree as copy of t1
// 	ImgTree t3(img2); // third tree from img2

// 	// reassign t1 to check that t1 and t2 contents are separate
// 	t1 = t3;

// 	// render t1 and t2 to files
// 	// t1 should contain "colours" data, t2 should contain "bc" data
// 	PNG outimg1 = t1.Render();
// 	t1.Helpera();
// 	PNG outimg2 = t2.Render();

// 	// write the rendered PNGs to files
// 	outimg1.writeToFile("images-output/lulli.png");
// 	outimg2.writeToFile("images-output/bc-copyconstructor.png");
// }

// void TestFlipHorizontal() {
// 	cout << "Entered TestFlipHorizontal..." << endl;

// 	// read in an image
// 	PNG origimg;
// 	origimg.readFromFile("images-original/Untitled2.png");

// 	// use it to build a ImgTree
// 	ImgTree t1(origimg);
// 	t1.Helpera();

// 	// flip the tree
// 	t1.FlipHorizontal();
	
// cout << "Flipped tree" << endl;
// cout << "Flipped tree" << endl;
// cout << "Flipped tree" << endl;
// cout << "Flipped tree" << endl;
// cout << "Flipped tree" << endl;
// cout << "Flipped tree" << endl;
// cout << "Flipped tree" << endl;
// 	t1.Helpera();

// 	// render the ImgTree
// 	PNG outimg = t1.Render();

// 	// write the PNG to file
// 	outimg.writeToFile("images-output/fnr-flip2.png");
// }

// void TestPrune() {
// 	cout << "Entered TestPrune..." << endl;

// 	// read in an image
// 	PNG origimg;
// 	origimg.readFromFile("images-original/tri-640x426.png");

// 	// use it to build a ImgTree
// 	ImgTree t1(origimg);

// 	// it might be useful to find out how many total nodes
// 	// and how many leaves there are before and after pruning

// 	// prune the tree
// 	t1.Prune(0.05);

// 	// render the ImgTree
// 	PNG outimg = t1.Render();

// 	// write the PNG to file
// 	outimg.writeToFile("images-output/tri-prune005.png");
// }

void TestPrune() {
	cout << "Entered TestPrune..." << endl;

	// read in an image
	PNG origimg;
	origimg.readFromFile("images-original/Untitled2.png");

	// use it to build a ImgTree
	ImgTree t1(origimg);
// 	t1.Helpera();
// cout << "Prune tree" << endl;
	// it might be useful to find out how many total nodes
	// and how many leaves there are before and after pruning

cout << t1.CountLeaves() << endl;

	// prune the tree
	t1.Prune(0.1);
cout << t1.CountLeaves() << endl;

	// t1.Helpera();

	// render the ImgTree
	PNG outimg = t1.Render();

	// write the PNG to file
	outimg.writeToFile("images-output/tri-prune005.png");
}

void TestPruneFlip() {
	cout << "Entered TestPruneFlip..." << endl;

	// read in an image
	PNG origimg;
	origimg.readFromFile("images-original/kkkk-kmnn-480x270.png");

	// use it to build a ImgTree
	ImgTree t1(origimg);

	// prune the tree, followed by a flip
	cout << t1.CountLeaves() << endl;
	t1.Prune(0.01);
	cout << t1.CountLeaves() << endl;
	t1.FlipHorizontal();

	// render the ImgTree
	PNG outimg = t1.Render();

	// write the PNG to file
	outimg.writeToFile("images-output/kkkk-prune01-flip.png");
}