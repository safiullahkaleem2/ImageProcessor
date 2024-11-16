/**
 * @file imgtree.cpp
 * @description implementation of ImgTree class used for storing image data
 *              
 *
 *              
 */

#include "imgtree.h"
#include "float.h"

/* ImgTree constructor */
ImgTree::ImgTree(const PNG& imIn){ 
	// complete your implementation below
    
    unsigned int width = imIn.width();
    unsigned int height = imIn.height();

    pair<unsigned int, unsigned int> ul(0, 0);
    pair<unsigned int, unsigned int> lr(width - 1, height - 1);

    Stats s(imIn);

    root = BuildTree(s, ul, lr);
    
}

/* BuildTree helper for ImgTree constructor */
Node* ImgTree::BuildTree(Stats& s, pair<unsigned int, unsigned int> ul, pair<unsigned int, unsigned int> lr) {
	// replace the stub below with your own implementation

    if (ul == lr) {
        // cout<<"Hit if"<<endl;

        return new Node(ul, lr, s.GetAvg(ul,lr));
    } else {
        // cout<<"Hit else";

        Node* currNode = new Node(ul, lr, s.GetAvg(ul,lr));

        // split w/ minimum entropy
        double minEntropy = DBL_MAX;
        pair<unsigned int, unsigned int> lineT;
        pair<unsigned int, unsigned int> lineB;
        pair<unsigned int, unsigned int> lineL;
        pair<unsigned int, unsigned int> lineR;

        if (lr.first - ul.first > lr.second - ul.second) {
            // Split by vertical line

            // cout<<" vertical line split"<<endl;
            for (unsigned int x = ul.first + 1; x < lr.first; x++) {
                pair<unsigned int, unsigned int> lineTop(x,ul.second);
                pair<unsigned int, unsigned int> lineBottom(x,lr.second);

                double deltaEntropy = abs(s.Entropy(ul,lineBottom) - s.Entropy(lineTop,lr));
                if (deltaEntropy < minEntropy) {
                    minEntropy = deltaEntropy;
                    lineT = lineTop;
                    lineB = lineBottom;
                }
            }

            currNode->LT = BuildTree(s, ul, lineB);
            currNode->RB = BuildTree(s, lineT, lr);
        } else {
            // Split by horizontal line

        // cout<<" horizontal line split"<<endl;
            for (unsigned int y = ul.second + 1; y < lr.second; y++) {
                pair<unsigned int, unsigned int> lineLeft(ul.first, y);
                pair<unsigned int, unsigned int> lineRight(lr.first, y);

                double deltaEntropy = abs(s.Entropy(ul,lineRight) - s.Entropy(lineLeft,lr));
                if (deltaEntropy < minEntropy) {
                    minEntropy = deltaEntropy;
                    lineL = lineLeft;
                    lineR = lineRight;
                }
            }

            currNode->LT = BuildTree(s, ul, lineR);
            currNode->RB = BuildTree(s, lineL, lr);
        }
        return currNode;
    }
}
