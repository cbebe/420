/*
Header for the Lab 4 IO functions
Need "-lm" tag when include this header
*/
#ifndef LAB4_H_INCLUDE
#define LAB4_H_INCLUDE

//===========
// Mandatory included functions
int Lab4_saveoutput(double *R, int nodecount, double Time);

//===========
// Supporting structures and reference functions for serialtester
// math functions
#ifdef LAB4_EXTEND
// the relative between vec r and vec t with respect to t, i.e., it returns norm(r-t)/norm(t)
double rel_error(double *r, double *t, int size);
// cp r to t
int vec_cp(double *r, double *t, int size);

// Structure to store the node info
struct node {
    int *inlinks;
    int num_in_links;
    int num_out_links;
};
// Load the input data for index within a range. Including the start but not including the end!
int node_init(struct node **nodehead, int start, int end);
int node_destroy(struct node *nodehead, int num_nodes);
#endif // LAB4_EXTEND
#endif // LAB4_H_INCLUDE
