/**
 * @file imgtree.cpp
 * @description implementation of ImgTree class used for storing image data
 *              
 *
 *              SUBMIT THIS FILE WITH YOUR MODIFICATIONS
 */

#include "imgtree.h"
#define COUNT 20

/* ImgTree constructor */
ImgTree::ImgTree(const PNG &imIn)
{
	height = imIn.height();
	width = imIn.width();
	pair<unsigned int, unsigned int> ul = pair<unsigned int, unsigned int>(0, 0);
	pair<unsigned int, unsigned int> lr = pair<unsigned int, unsigned int>(width - 1, height - 1);
	Stats s = Stats(imIn);
	root = BuildTree(s, ul, lr);
}

/* BuildTree helper for ImgTree constructor */

Node *ImgTree::BuildTree(Stats &s, pair<unsigned int, unsigned int> ul, pair<unsigned int, unsigned int> lr)
{	
	unsigned int x1 = ul.first;
	unsigned int x2 = lr.first;
	unsigned int y1 = ul.second;
	unsigned int y2 = lr.second;

	if (x1 == x2 && y1 == y2)
	{
		Node *n = new Node(ul, lr, s.GetAvg(ul, lr));
		n->LT = nullptr;
		n->RB = nullptr;
		return n;
	}

	unsigned int h = y2 - y1 + 1;
	unsigned int w = x2 - x1 + 1;
	pair<unsigned int, unsigned int> ul3;
	pair<unsigned int, unsigned int> Entropymin;
	Node *n = new Node(ul, lr, s.GetAvg(ul, lr));


	if (w >= h)
	{

		
		double minEntropy = 10000;
		for (unsigned int i = 1; i <= w - 1; i++)
		{
				pair<unsigned int, unsigned int> ul1 = ul;
			pair<unsigned int, unsigned int> lr1(x1 + i - 1, y2);
			pair<unsigned int, unsigned int> ul2(x1 + i, y1);
			pair<unsigned int, unsigned int> lr2 = lr;

			double area1a = s.RectArea(ul1, lr1);
			double area2b = s.RectArea(ul2, lr2);
			double totalArea = area1a + area2b;
			double area1 = area1a / totalArea;
			double area2 = area2b / totalArea;

			double entropy = (area1 * s.Entropy(ul1, lr1)) + area2 * s.Entropy(ul2, lr2);
				if (entropy < minEntropy)
			{
				minEntropy = entropy;
				Entropymin = lr1;
			}
			
		}

	
		ul3 = pair<unsigned int, unsigned int> (Entropymin.first + 1, y1);
	
		
	}
	else
	{
				double minEntropy = 10000;

		for (unsigned int i = 1; i <= h - 1; i++)
		{
	
			pair<unsigned int, unsigned int> ul1 = ul;
			pair<unsigned int, unsigned int> lr1(x2, y1 + i - 1);
			pair<unsigned int, unsigned int> ul2(x1, y1 + i);
			pair<unsigned int, unsigned int> lr2 = lr;

			double area1a = s.RectArea(ul1, lr1);
			double area2b = s.RectArea(ul2, lr2);
			double totalArea = area1a + area2b;
			double area1 = area1a / totalArea;
			double area2 = area2b / totalArea;

			double entropy = (area1 * s.Entropy(ul1, lr1)) + area2 * s.Entropy(ul2, lr2);
	
			if (entropy < minEntropy)
			{
				minEntropy = entropy;
				Entropymin = lr1;
			}
	

		}
		
		ul3 = pair<unsigned int, unsigned int>(x1, Entropymin.second + 1);
		
	}


	n->LT = BuildTree(s, ul, Entropymin);
	n->RB = BuildTree(s, ul3, lr);
	return n;
}

/* Render your ImgTree into a png */
PNG ImgTree::Render() const
{
	// replace the stub below with your own implementation
	PNG image = PNG(width, height);
	Helper(image, root);
	return image;
}

/* Prune function modifies tree by cutting off
 * subtrees whose leaves are all within tol of
 * the average pixel value contained in the root
 * of the subtree
 */
void ImgTree::Prune(double tol)
{
	// complete your implementation below
	Prune(root,tol,false);
}

void ImgTree::Prune(Node* node, double tol, bool b)
{
	if (node == NULL) {
		return;
	}

	else if (b) {
		Prune(node->LT,tol, true);
		Prune(node->RB,tol, true);
		node->LT = NULL;
		node->RB = NULL;
		delete node;
	}

	else if (node ->LT == NULL && node ->RB == NULL) {
		return;
	}

	else if	(Prune(node,node,tol)) {
		Prune(node->LT,tol, true);
		Prune(node->RB,tol, true);
		node->LT = NULL;
		node->RB = NULL;
	}

	else {
		Prune(node->LT,tol, false);
		Prune(node->RB,tol, false);
	}
}



bool ImgTree::Prune(Node*& node, Node*& r, double tol)
{
	if (node ->LT == NULL && node ->RB == NULL) {
		if (r->avg.distanceTo(node->avg) > tol) {
		return false;
	}
		return true;
	}

	else {
		return Prune(node->LT,r,tol) && Prune(node->RB,r,tol);
	}

}


/* Modifies node contents so that the rendered tree
 * will appear to be flipped horizontally across
 * a vertical axis
 */
void ImgTree::FlipHorizontal()
{
	// complete your implementation below

	FlipHorizontal(root);
}

void ImgTree::FlipHorizontal(Node *node)
{
	// complete your implementation below
	if (node->LT == nullptr && node->RB == nullptr)
	{
		return;
	}

	else
	{
		if (node->LT->upLeft.second == node->RB->upLeft.second)
		{
			FlipHorizontal(node->LT);
			FlipHorizontal(node->RB);
			/* code */
			pair<unsigned int, unsigned int> left = node->LT->upLeft;
			pair<unsigned int, unsigned int> right = node->RB->upLeft;
			Node *left1 = node->LT;
			Node *right2 = node->RB;
			node->LT->upLeft.first = width - 1 - node->LT->lowRight.first;
			node->LT->lowRight.first = width - 1 - left.first;
			node->RB->upLeft.first = width - 1 - node->RB->lowRight.first;
			node->RB->lowRight.first = width - 1 - right.first;
			node->LT = right2;
			node->RB = left1;
		}

		else
		{
			FlipHorizontal(node->LT);
			FlipHorizontal(node->RB);
			pair<unsigned int, unsigned int>left = node->LT->upLeft;
			pair<unsigned int, unsigned int>right = node->RB->upLeft;
			
			node->LT->upLeft.first = width - 1 - node->LT->lowRight.first;
			node->LT->lowRight.first = width - 1 - left.first;
			node->RB->upLeft.first = width - 1 - node->RB->lowRight.first;
			node->RB->lowRight.first = width - 1 - right.first;
	
		}
	}
}

/* helper function for destructor and op= */
/* frees dynamic memory associated w the ImgTree */
void ImgTree::Clear()
{
	Helper2(root);
	height = 0;
	width = 0;
	root = NULL;
}

/* helper function for copy constructor and op= */
void ImgTree::Copy(const ImgTree &orig)
{
	// complete your implementation below
	height = 0;
	width = 0;
	root = NULL;
	height = orig.height;
	width = orig.width;
	root = Helper3(orig.root);
}

/**
 * Add your private ImgTree function implementations below
 */
void ImgTree::Helper(PNG &output, Node *curr) const
{
	if (curr->LT == nullptr && curr->RB == nullptr)
    {
        for (unsigned int y = curr->upLeft.second; y <= curr->lowRight.second; y++)
        {
            for (unsigned int x = curr->upLeft.first; x <= curr->lowRight.first; x++)
            {
                *output.getPixel(x, y) = curr->avg;
            }
        }
    }
    else
    {
        Helper( output,curr->LT);
        Helper( output,curr->RB);
    }
}

void ImgTree::Helper2(Node *n)
{
	if (n == NULL)
	{
		return;
	}

	Helper2(n->LT);
	Helper2(n->RB);
	n->LT = NULL;
	n->RB = NULL;
	delete n;
}

// void ImgTree::Helpera() {
	
//    print2DUtil(root, 0);
   
// }

// void ImgTree:: print2DUtil(Node* root, int space)
// {
//     // Base case
//     if (root == NULL)
//         return;
 
//     // Increase distance between levels
//     space += COUNT;
 
//     // Process right child first
//     print2DUtil(root->RB, space);
 
//     // Print current node after space
//     // count
//     cout << endl;
//     for (int i = COUNT; i < space; i++)
//         cout << " ";
//     	cout << root->upLeft.first <<" " << root->upLeft.second << " " << root->lowRight.first <<" " << root->lowRight.second << "\n";
	
 
//     // Process left child
//     print2DUtil(root->LT, space);
// }
 

Node *ImgTree::Helper3(Node *orig)
{
	if (orig == NULL)
	{
		return NULL;
	}
	pair<unsigned int, unsigned int> ul = pair<unsigned int, unsigned int>(orig->upLeft.first, orig->upLeft.second);
	pair<unsigned int, unsigned int> rb = pair<unsigned int, unsigned int>(orig->lowRight.first, orig->lowRight.second);
	HSLAPixel pixel = orig->avg;
	Node *node = new Node(ul, rb, pixel);

	node->LT = Helper3(orig->LT);
	node->RB = Helper3(orig->RB);
	return node;
}
