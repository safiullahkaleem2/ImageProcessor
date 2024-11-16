#define CATCH_CONFIG_MAIN
#include "util/catch.hpp"
#include <vector>
#include <sys/stat.h>
#include <iostream>
#include "util/PNG.h"
#include "util/HSLAPixel.h"
#include "stats.h"
#include "imgtree.h"

using namespace std;
using namespace util;

// TEST_CASE("Stats::basic RectArea","[weight=1][part=stats]"){

//     PNG data; data.resize(2,2);

//     Stats s(data);
//     pair<unsigned int, unsigned int> ul(0,0);
//     pair<unsigned int, unsigned int> lr(1,1);
//     long result = s.RectArea(ul,lr);

//     REQUIRE(result == 4);
    
// }

// TEST_CASE("Stats::basic getAvg","[weight=1][part=stats]"){
//     PNG data; data.resize(2,2);
//     for (int i = 0; i < 2; i ++){
//         for (int j = 0; j < 2; j++){
//             HSLAPixel * p = data.getPixel(i,j);
//             p->h = (10 +  90*i) % 360;
//             p->s = 1.0;
//             p->l = 0.5;
//             p->a = 1.0;
//         }
//     }
//     Stats s(data);
//     pair<unsigned int, unsigned int> ul(0,0);
//     pair<unsigned int, unsigned int> lr(2,1);
//     HSLAPixel result = s.GetAvg(ul,lr);
//     HSLAPixel expected(112.5,1.0, 0.5);

//     REQUIRE(result == expected);
// }

// TEST_CASE("Stats::basic entropy","[weight=1][part=stats]"){
//     PNG data; data.resize(2,2);
//     for (int i = 0; i < 2; i ++){
//         for (int j = 0; j < 2; j++){
//             HSLAPixel * p = data.getPixel(i,j);
//             p->h = 135*j + i * 90;
//             p->s = 1.0;
//             p->l = 0.5;
//             p->a = 1.0;
//         }
//     }
//     Stats s(data);
//     pair<unsigned int, unsigned int> ul(0,0);
//     pair<unsigned int, unsigned int> lr(1,1);
//     long result = s.Entropy(ul,lr); // simple implicit cast for exact equality testing with known integer value

//     REQUIRE(result == 2);
// }

// TEST_CASE("ImgTree::basic ctor render","[weight=1][part=ImgTree]"){
//     	   PNG img;
//     	cout << "karan is gay2" << endl;
//     img.readFromFile("images-original/tri-640x426.png");
//     	cout << "karan is gay3" << endl;

//     ImgTree t1(img);
//     	cout << "karan is gay4" << endl;

//     PNG out = t1.Render();
//     	cout << "karan is gay5" << endl;

//     REQUIRE(out==img);
// }

// TEST_CASE("ImgTree::basic copy","[weight=1][part=ImgTree]"){
//     PNG img;
//     img.readFromFile("images-original/tri-640x426.png");

//     ImgTree t1(img);
//     ImgTree t1copy(t1);

//     PNG out = t1copy.Render();

//     REQUIRE(out==img);
// }

TEST_CASE("ImgTree::basic prune","[weight=1][part=ImgTree]"){
    PNG img;
    img.readFromFile("images-original/tri-640x426.png");
    
    ImgTree t1(img);

    PNG prePrune = t1.Render();
    cout << t1.CountLeaves() <<endl;

    t1.Prune(0.05);
    cout << t1.CountLeaves() <<endl;
    PNG result = t1.Render();
    PNG expected; expected.readFromFile("images-soln/ex-tri-prune005.png");

    REQUIRE(expected==result);
}

