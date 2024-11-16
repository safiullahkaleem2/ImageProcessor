/**
 * @file imgtree_private.h
 * @description student declarations of private functions
 *              for ImgTree, 
 *
 *              THIS FILE WILL BE SUBMITTED.
 *
 *              Simply declare your function prototypes here.
 *              No other scaffolding is necessary.
 */

// begin your declarations below

void Helper2(Node* n);
void Helper(PNG &output, Node *curr) const;
Node* Helper3(Node* orig);
void FlipHorizontal(Node* node);
// void  print2DUtil(Node* root, int space);
void Prune(Node* node, double tol, bool b);
bool Prune(Node*& node, Node*& r, double tol);


