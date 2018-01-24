// Twelve Dimensional Ranking

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>

using namespace std;

struct Node {
	int index;
	bool deleted;
	double weight;
	Node *left, *right;
	Node (int i) {index = i; deleted = false; weight = 0; left = right = NULL;}
};

void Normalize();
double calcDist(int num1, int num2);
void undelete(Node *T);
Node *findClosest(Node *T, int index, int dim);
void randomizer();
Node *insert(Node *T, int k, int dim);

int N;
int D;
double **P;// holds all of the dimensions at a specific index
double *R; //This is to hold the ranks seperate from the D's for simplicity
int k; // User entered value for number of closest nodes to find
Node *guess;
double bestdist = 999999; // keeping up with the distance without annoying pass throughs

int main(int argc, char *argv[])
{
	if(argc < 3 || argc > 3)
  	{
    	cout << "Please enter the file and K in commandline" << endl;
    	return 0;
  	}

  	k = atoi(argv[2]);

	ifstream fin; // input stuff below here that is all
  	
  	fin.open (argv[1]);

	fin >> N >> D;

	P = new double *[N];

	R = new double [N];

	for(int i = 0; i < N; i++)
	{
		P[i] = new double [D];
	}
 	
	for(int i = 0; i < N; i++)
	{
		fin >> R[i];
		for(int j = 0; j < D; j++)
		{
			fin >> P[i][j];
		}
	}

	fin.close();

	// Now onto the fun stuff

	Normalize();

	randomizer();

	Node *T = NULL;
	for (int i = 0; i < N; i++)
	{
		T = insert(T, i, 0);
	}

	double holders[N]; // this holds distances for after the J index loop

	Node **guessme = new Node *[k]; //holds nodes found from recusive function

	for(int j = 0; j < N; j++)
	{
		bestdist = 9999999;
		guess = findClosest(T, j, 0); // delete myself so I dont find myself
		guess->deleted = true;

		for(int i = 0; i < k; i++)
		{
			bestdist = 9999999;
			guess = findClosest(T, j, 0); // find that closest Node
			guess->deleted = true;
			guessme[i] = guess; // put the node in the array for later
		}

		for(int i = 0; i < k; i++) //for computing weight for neighbor
		{
			double expo = -0.1 * calcDist(guessme[i]->index, j);
			guessme[i]->weight = exp(expo);
		}

		double weighttotal = 0;
		double toptotal = 0;
		for(int i = 0; i < k; i++) //computing the weighted average
		{
			toptotal += guessme[i]->weight * R[guessme[i]->index];
			weighttotal += guessme[i]->weight;
		}

		double hold = toptotal / weighttotal;

		holders[j] = hold;

		undelete(T); // recursive function to find all deleted and reset
	}				 // I was straped for time so this was a necessary evil

	double burger = 0;

	for(int i = 0; i < N; i++)//for output that choose whether it's a good result
	{
		burger += (R[i] - holders[i]) * (R[i] - holders[i]);
	}

	burger *= 1/(double)N;

	cout << burger << endl;

	return 0;
}

void Normalize()
{
	for (int j = 0; j < D; j++) 
	{
	    double mean = 0.0;
	    for (int i = 0; i < N; i++) mean += P[i][j];
	    mean /= N;
	    for (int i = 0; i < N; i++) P[i][j] -= mean;
	    double var = 0.0;
	    for (int i = 0; i < N; i++) var += pow(P[i][j], 2);
	    double stddev = sqrt(var / N);
	    for (int i = 0; i < N; i++) P[i][j] /= stddev;
	}
} 

void undelete(Node *T) // To set the "deleted" nodes back to default
{
  if (T == NULL) return;
  undelete(T->left);
  if(T->deleted == true)
  {
  	T->deleted = false;
  }
  undelete(T->right);
}

double calcDist(int num1, int num2)// calulate distance with all dimensions
{
  double hold = 0.0;
  for(int i = 0; i < D; i++)
  {
  	hold += pow(P[num1][i] - P[num2][i], 2);
  }
  
  return sqrt(hold);
}

Node *findClosest(Node *T, int index, int dim) //recursively find the closest node
{
	Node *result = NULL;
	Node *temp;

	if (T == NULL)
	{
		return NULL;
	}

	if (P[index][dim] < P[T->index][dim]) result = findClosest(T->left, index, (dim + 1) % D);
	else result = findClosest(T->right, index, (dim + 1) % D);

	if (!T->deleted && calcDist(index, T->index) < bestdist) 
	{
		bestdist = calcDist(index, T->index);
		result = T;
	}
	if(result == NULL && !T->deleted)
	{
		result = T;
	}
	if(sqrt(pow(P[index][dim] - P[T->index][dim], 2)) < bestdist) //the prune, saves about 11 seconds
	{
		if(P[index][dim] < P[T->index][dim])
		{
			temp = findClosest(T->right, index, (dim + 1) % D);
			if((result == NULL) || (result != NULL && temp != NULL && !temp->deleted && calcDist(index, temp->index) < calcDist(index, result->index)))
			{
				result = temp;
			}
		}
		else
		{
			temp = findClosest(T->left, index, (dim + 1) % D);
			if((result == NULL) || (result != NULL && temp != NULL && !temp->deleted && calcDist(index, temp->index) < calcDist(index, result->index)))
			{	
				result = temp;
			}
		}
	}

	return result;
}

void randomizer() //To make the dumb insert random insert
{
	for(int i = 0; i < rand() % (N + 1); i++)
	{
		int rando = rand() % (i + 1); // since the R is accessed by index it must line up with the P as well
		swap(R[i], R[rando]);
		swap(P[i], P[rando]);
	}
}

Node *insert(Node *T, int k, int dim)//standard insert
{
  if (T == NULL) return new Node(k);
  if (P[k][dim] < P[T->index][dim]) T->left = insert(T->left, k, (dim + 1) % D);
  else T->right = insert(T->right, k, (dim + 1) % D);
  return T;
}