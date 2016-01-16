#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(int i = a;i < b; i++)
#define rrep(i,a,b) for(int i = a; i > b; i--)
#define fastIO std::ios_base::sync_with_stdio(false)

/* Program to calculate Conjunctive Normal Form of an expression */

class expr
{
	expr *left, *right; /* left and right pointers to store the expression*/
	char op;			/* op at the root level*/
	bool isLiteral;		/* a boolean to check whether the expression is a literal or not*/

	//functions
	expr* CNF(expr *A);	
	expr* DISTR(expr *l, expr *r);
	expr* NNF(expr *A);
	expr* IMPL_FREE(expr *A);
	expr* constructUtil(string & S, vector<int> & x,int l,int r); /*helper function for constructing
																	the expression from string */
	void print(expr* A);  		/* Recursive Function for printing the expression */
	expr* copyExpr(expr* e);	/* helper function for copy constructor, for Deep Copy */

public:

	//Constructors
	expr(): left(NULL),right(NULL){}
	
	//Overloaded Constructors
	expr(char c):op(c),left(NULL),right(NULL),isLiteral(true){}
	expr(expr* l, expr* r, char c);
	expr(string & S);

	//Overloaded Copy Constructor
	expr(const expr & e);
	
	//Overloaded Assignment operator
	void operator=(const expr & e);

	// Destructor
	~expr()					
	{					
		delete left;		
		delete right;		
	}

	//Accesor functions
	expr calcCNF();	
	expr calcImplFree();
	expr calcNNF();
	void printExpr();
};

expr* expr::copyExpr(expr* e)
{
	if(e == NULL)
		return NULL;
	expr* newExpr = new expr;
	newExpr->op = e->op;
	newExpr->isLiteral = e->isLiteral;
	newExpr->left = copyExpr(e->left);
	newExpr->right = copyExpr(e->right);
	return newExpr;
}

void expr::operator=(const expr & e)
{
	left = copyExpr(e.left);
	right = copyExpr(e.right);
	op = e.op;
	isLiteral = e.isLiteral;
}

expr::expr(const expr & e)
{
	left = copyExpr(e.left);
	right = copyExpr(e.right);
	op = e.op;
	isLiteral = e.isLiteral;
}

//Overloaded constructor
expr::expr(expr* l, expr* r, char c)
{
	left = copyExpr(l);
	right = copyExpr(r);
	op = c;
	if(right == NULL && ((left == NULL) || (left->isLiteral && op == '!')) )
		isLiteral = true;
	else
		isLiteral = false;
}

/* precondition: A implication free and in NNF */
/* postcondition: CNF (A) computes an equivalent CNF for A */
expr* expr::CNF(expr* A)
{
	if(A == NULL || A->isLiteral)
		return A;
	else if(A->op == '^')
	{
		return new expr(CNF(A->left),CNF(A->right),'^');
	}
	else if(A->op == 'v')
	{
		return DISTR(CNF(A->left),CNF(A->right));
	}

}

/* precondition: l and r are in CNF */
/* postcondition: DISTR (l, r) computes a CNF for l ∨ r */
expr* expr::DISTR(expr* l, expr *r)
{

	bool lConj = false,rConj = false;
	if(!l->isLiteral && l->op == '^')
		lConj = true;
	if(!r->isLiteral && r->op == '^')
		rConj = true;

	if(lConj && !rConj)
		return new expr(DISTR(l->left,r), DISTR(l->right,r),'^');
	
	else if(!lConj && rConj)
		return new expr(DISTR(l,r->left),DISTR(l,r->right),'^');
	
	else if(lConj && rConj)
		return new expr(new expr(DISTR(l->left,r), DISTR(l->right,r),'^'),
			 			new expr(DISTR(l,r->left),DISTR(l,r->right),'^'),'^');
	else
		return new expr(l,r,'v');
}

/* precondition: A is implication free */
/* postcondition: NNF (A) computes a NNF for A */
expr* expr::NNF(expr* A)
{
	if(A == NULL)
		return NULL;
	if(A->isLiteral){
		if(A->op == '!' && A->left->op == '!')
			return NNF(A->left->left);
		else
			return A;
	}
	if(A->op != '!')
		return new expr(NNF(A->left),NNF(A->right),A->op);
	else if(A->right == NULL)
	{
		char opr = A->left->op;
		if(opr != '!')
			return new expr(NNF(new expr(A->left->left,NULL,'!')),
					NNF(new expr(A->left->right,NULL,'!')),(opr=='v')?'^':'v');
	}
}

expr* expr::IMPL_FREE(expr* A)
{
	if(A == NULL || A->isLiteral)
		return A;
	else if(A->op != '>')
		return new expr(IMPL_FREE(A->left),IMPL_FREE(A->right),A->op);
	else
		return new expr(IMPL_FREE(new expr(A->left,NULL,'!')),IMPL_FREE(A->right),'v');
}

void expr::print(expr* A)
{
	if(A == NULL)
		return;
	else if(A->isLiteral){

		if(A->op == '!'){
			cout << '(' << '!';
			print(A->left);
			cout << ')';
		}
		else
		    cout << A->op;
	}
	else{
		cout << '(';
		if(A->op == '!'){
			cout << '!';
			print(A->left);
		}
		else{
			print(A->left);
			cout << A->op;
			print(A->right);
		}
		cout << ')';
	}
}

expr::expr(string & S)
{
	stack<int> y;
	int l = S.length()-1;
	vector<int> x(l+1,-1);
	rrep(i,l,-1)
	{
		if(S[i] == ')')
			y.push(i);
		else if(S[i] == '('){
			x[i] = y.top();
			y.pop();
		}
	}

	*this = *(constructUtil(S,x,0,l));	//Assignment operator
}

expr* expr::constructUtil(string & S,vector<int> & x,int l,int r)
{
	if(r-l <= 1){
		if(r < l)
			return NULL;
		if(r == l)
			return new expr(S[l]);
		else{
			expr* A = new expr(new expr(S[r]),NULL,S[l]);
			A->isLiteral = true;
			return A;
		}
	}
	expr* A = new expr();
	if(S[l] == '('){
		if(x[l] == r)
			A = constructUtil(S,x,l+1,r-1);
		else{
			 A->left = constructUtil(S,x,l+1,x[l]-1);
			 A->right = constructUtil(S,x,x[l]+2,r);
			 A->op = S[x[l] + 1];
			 A->isLiteral = false; 
		}
	}
	else{
		A->isLiteral = false;
		if(S[l] == '!'){
			A->left = constructUtil(S,x,l+1,r);
			A->right = NULL;
			A->op = '!';
			if(A->left->isLiteral)
				A->isLiteral = true;
		}
		else
		{
			A->left = new expr(S[l]);
			A->op = S[l+1];
			A->right = constructUtil(S,x,l+2,r);
		}
	}

	return A;
}

expr expr::calcCNF()
{
	return *CNF(NNF(IMPL_FREE(this)));
}

expr expr::calcImplFree()
{
	return *IMPL_FREE(this);
}

expr expr::calcNNF()
{
	return *NNF(this);
}

void expr::printExpr()
{
	print(this);
	cout << endl; 
}

int main()
{
	fastIO;
	int t,k;
	int a;
	expr B;
	string S;
	cin >> t;
	rep(i,0,t)
	{
		cin >> S;
		expr A(S);
		B = A.calcCNF(); //Assignment operator
		B.printExpr();
	}
	return 0;
}