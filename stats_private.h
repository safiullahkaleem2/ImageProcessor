/**
 * @file stats_private.h
 * @description student declarations of private functions
 *             
 *              THIS FILE WILL BE SUBMITTED.
 *
 *              Simply declare your function prototypes here.
 *              No other scaffolding is necessary.
 */

// begin your declarations below
unsigned int width;
unsigned int height;


void firstFourResizer();
void histResizer();
unsigned int prevfinderX(unsigned int x);
unsigned int prevfinderY(unsigned int x, unsigned int y);
vector<unsigned int> operation(vector<unsigned int>& a1,vector<unsigned int>& a2, vector<unsigned int>& s1);
vector<int>caster(vector<unsigned int>& a1);
vector<unsigned int> operationEnthropy(vector<unsigned int>& a1,vector<unsigned int>& s1, vector<unsigned int>& s2,vector<unsigned int>& a2);

