//-----------------Tawkir Aziz Rahman---------------------//

#include <bits/stdc++.h>
#define input(arr, n)          \
    for (ll i = 0; i < n; i++) \
        cin >> arr[i];
#define output(arr, n)             \
    {                              \
        for (ll i = 0; i < n; i++) \
        {                          \
            cout << arr[i] << " "; \
        }                          \
    }
using namespace std;
typedef long long ll;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

typedef __gnu_pbds::tree<int, __gnu_pbds::null_type, less<int>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update> ordered_set;

// for printing normal 1D vector
template <typename T>
void printVector(vector<T> &v, ll st = -1, ll fin = -1)
{
    if (st == -1)
        st = 0;
    if (fin == -1)
        fin = v.size();
    for (ll i = st; i < fin; i++)
    {
        cout << v[i] << " ";
    }
    cout << endl;
    return;
}

template <typename T1, typename T2>
void printVectorPair(vector<pair<T1, T2>> &v, ll st = -1, ll fin = -1)
{
    if (st == -1)
        st = 0;
    if (fin == -1)
        fin = v.size();
    for (ll i = st; i < fin; i++)
    {
        cout << "( " << v[i].first << " , " << v[i].second << " ) ";
    }
    cout << endl;
    return;
}

// for printing 2D vectors (matrix)
template <typename T>
void printMatrix(vector<T> &v, ll st = -1, ll fin = -1)
{
    if (st == -1)
        st = 0;
    if (fin == -1)
        fin = v.size();
    for (ll i = st; i < fin; i++)
    {
        printVector(v[i]);
    }
    // cout << endl;
    return;
}

// for printing other STL structures
template <typename T>
void printStructure(T &t)
{
    for (auto itr = t.begin(); itr != t.end(); itr++)
    {
        cout << *itr << " ";
    }
    cout << endl;
}

// function to convert string to integer number
ll stringToNum(string str)
{
    ll n = 0;
    for (ll i = 0; i < str.size(); i++)
    {
        n = n * 10 + (ll)(str[i] - '0');
    }
    return n;
}

// it is the matrix class to keep the vector matrix and its parent and calculate other distances
class Matrix
{
public:
    vector<vector<string>> mt;             // it is the 2D vector that that stores values as strings
    ll n;                                  // length of the 2D vector
    ll move;                               // how many steps was needed to come to this state
    Matrix *parent;                        // the pointer to the parent matrix class of the matrix
    ll hammingDistance, manhattanDistance; // the distances to calculate
    Matrix(vector<vector<string>> &mat, Matrix *parent = NULL)
    {
        mt = mat;
        n = mt.size();
        this->parent = parent;
        if (parent == NULL)
        {
            move = 0; // if the parent is null that means it is the initial state, and initial state needs 0 steps
        }
        else
        {
            move = parent->move + 1; // otherwise we will need one more step from its parent steps to reach to curernt state
        }
        hammingDistance = -1;   // initializing hamming distance
        manhattanDistance = -1; // iitializing its manhattan distance
    }

    // to run the vector into string with | barriers
    string getAString()
    {
        string str = "|"; // starts
        for (ll i = 0; i < n; i++)
        {
            for (ll j = 0; j < n; j++)
            {
                str.append(mt[i][j]); // appending all the elements of the 2D matrix with the string
                str.append("|");      // using | as a barrier between elements
            }
        }
        return str;
    }

    // to get a one directional vector in row major order
    vector<string> getOneDirectional()
    {
        vector<string> oneDirectionalVector;
        for (ll i = 0; i < n; i++)
        {
            for (ll j = 0; j < n; j++)
            {
                oneDirectionalVector.push_back(this->mt[i][j]); // adding all the elelements to the oneDirectional Vector
            }
        }
        return oneDirectionalVector;
    }

    // to count the number of inversions in the initial matrix
    ll findInversions()
    {
        vector<string> tempString = getOneDirectional(); // getting one directional vector with row major order

        ll inv = 0;
        for (ll i = 0; i < tempString.size(); i++)
        {
            if (tempString[i][0] == '*')
            {
            }
            else
            {
                for (ll j = i + 1; j < tempString.size(); j++)
                {
                    if (tempString[j][0] == '*')
                    {
                        // ignoring inversions for the element where the place is blank space
                    }
                    else if (stringToNum(tempString[i]) > stringToNum(tempString[j]))
                    {
                        inv++; // increasing inversion where the element is lesser than the current eleement is situated after the current values position
                    }
                }
            }
        }
        return inv;
    }

    // to find the blank position
    pair<ll, ll> findBlankPos()
    {
        for (ll i = 0; i < n; i++)
        {
            for (ll j = 0; j < n; j++)
            {
                if (mt[i][j][0] == '*')
                {
                    return make_pair(i, j); // returning the row and column of the blank position
                }
            }
        }
        return make_pair(-1, -1);
    }

    // top copy another matrix
    Matrix *makeAnotherMatrix(Matrix &mat)
    {
        Matrix *mat2 = new Matrix(mat.mt, &mat); // construgting another matrix using the parent matrix
        return mat2;
    }

    // find Rightful place is a function which take input a number and then output a pair of row and
    // column which place in the matrix this number should be on
    pair<ll, ll> findRightfulPlace(ll num)
    {
        num--;
        ll col = num % n; // the rightful position for col is num MOD n
        ll row = num / n; // the rightful position for the row id num DIV n
        return make_pair(row, col);
    }

    // to try to move the blank up and try to insert this into the processed matrices set
    Matrix *moveUp()
    {
        pair<ll, ll> blankPos = findBlankPos();
        if (blankPos.first == 0)
            return NULL; // it is impossible to move blank space up if it is in the first row
        Matrix *matrix = makeAnotherMatrix(*this);
        swap(matrix->mt[blankPos.first - 1][blankPos.second], matrix->mt[blankPos.first][blankPos.second]);

        return matrix;
    }

    // to try to move the blank down and try to insert this into the processed matrices set
    Matrix *moveDown()
    {
        pair<ll, ll> blankPos = findBlankPos();
        if (blankPos.first == n - 1)
            return NULL; // it is impossible to move the blank spaec down if it is in the last row
        Matrix *matrix = makeAnotherMatrix(*this);
        swap(matrix->mt[blankPos.first + 1][blankPos.second], matrix->mt[blankPos.first][blankPos.second]);

        return matrix;
    }

    // to try to move the blank left and try to insert this into the processed matrices set
    Matrix *moveLeft()
    {
        pair<ll, ll> blankPos = findBlankPos();
        if (blankPos.second == 0)
            return NULL; // it is impossible to move the blank space left if it is in the left mst column
        Matrix *matrix = makeAnotherMatrix(*this);
        swap(matrix->mt[blankPos.first][blankPos.second - 1], matrix->mt[blankPos.first][blankPos.second]);

        return matrix;
    }

    // to try to move the blank right and try to insert this into the processed matrices set
    Matrix *moveRight()
    {
        pair<ll, ll> blankPos = findBlankPos();
        if (blankPos.second == n - 1)
            return NULL; // it is impossible to move the blank space to right if it is in the right most column
        Matrix *matrix = makeAnotherMatrix(*this);
        swap(matrix->mt[blankPos.first][blankPos.second + 1], matrix->mt[blankPos.first][blankPos.second]);

        return matrix;
    }

    // this function calculated hamming distance and return it
    ll findHammingDistance()
    {
        if (hammingDistance != -1)
            return hammingDistance; // if hamming distanceis calculated earlier, use that instead of calculating again
        ll distance = 0;
        ll expectedNumber = 1;
        for (ll i = 0; i < n; i++)
        {
            for (ll j = 0; j < n; j++)
            {
                if (mt[i][j][0] == '*')
                {
                }
                else
                {
                    ll temp = stringToNum(mt[i][j]);
                    if (temp != expectedNumber)
                    {
                        // cout << mt[i][j] << endl;
                        distance++;
                    }
                }
                expectedNumber++;
            }
        }
        hammingDistance = distance; // assigning hamming distance so that next time it can return it without calculating
        return distance;
    }

    // this function calculates manhattan distance and reurns it
    ll findManhattanDistance()
    {
        if (manhattanDistance != -1)
        {
            return manhattanDistance; // if manhattan distance is calculated earlier, use that instead of calculating again
        }
        ll distance = 0;
        for (ll i = 0; i < n; i++)
        {
            for (ll j = 0; j < n; j++)
            {
                if (mt[i][j][0] == '*')
                {
                }
                else
                {
                    ll temp = stringToNum(mt[i][j]);
                    pair<ll, ll> rightfulplace = findRightfulPlace(temp);
                    distance += (llabs(i - rightfulplace.first) + llabs(j - rightfulplace.second));
                }
            }
        }
        manhattanDistance = distance; // assigning hamming distance so that if required again, it can diregt send it instead of calculating
        return distance;
    }

    // this function checks all the the combinations for moving the blank space one move, and then send the vector of all the Matrix pointers
    vector<Matrix *> findAllMoves()
    {
        vector<Matrix *> allMoves; // allMoves is the vector which stores all the Matrix Pointers
        Matrix *movingUp = this->moveUp();
        Matrix *movingDown = this->moveDown();
        Matrix *movingLeft = this->moveLeft();
        Matrix *movingRight = this->moveRight();
        if (movingUp != NULL)
            allMoves.push_back(movingUp); // We will only add this state to the vector if it is not NULL
        if (movingDown != NULL)
            allMoves.push_back(movingDown);
        if (movingLeft != NULL)
            allMoves.push_back(movingLeft);
        if (movingRight != NULL)
            allMoves.push_back(movingRight);
        return allMoves;
    }
};

// function to print the matrix class
void printMatrixClass(Matrix *matrix)
{

    if (matrix == NULL)
    {
        cout << "The matrix is NULL" << endl; // you cannot print a matrix if the matrix pointer is NULL
    }
    else
    {
        printMatrix(matrix->mt); // printing the 2d vector of the matrix pointer
    }
    cout << "" << endl;
}

struct Compare
{
    // this is to custom compare elements of priority queue
    bool operator()(const std::pair<pair<ll, ll>, Matrix *> &a, const std::pair<pair<ll, ll>, Matrix *> &b)
    {
        // comparing only the first long long integer pairs value to determine its position
        // the first value of the first ielement of the pair is total steps
        // this is by using f(n) = g(n) + h(n)
        // if the it is equal for some, then we will compare the second element which is g(n) or heuristic function

        return a.first >= b.first; // Reverse comparison for min-heap
        // comparing the pair<ll,ll> element, firstly with f(n), if tied then with g(n)
    }
};

// function that prints priority queue
// this function copy the previous priority queue and then pops their items one by one and then show them
void printPriorityQueue(priority_queue<pair<pair<ll, ll>, Matrix *>, vector<pair<pair<ll, ll>, Matrix *>>, Compare> p)
{
    // for printing the priority queue
    cout << "THe size =  " << p.size() << endl;
    while (p.size() > 0)
    {
        pair<pair<ll, ll>, Matrix *> poppedElem = p.top();
        p.pop();
        cout << "Val:= " << poppedElem.first.first << endl;
        cout << "dist:= " << poppedElem.first.second << endl;
        cout << "THe matrix:=" << endl;
        printMatrix(poppedElem.second->mt);
        // break;
    }
    cout << endl
         << endl;
}

class starSearchAlgo
{
public:
    Matrix *matrix;           // main matrix with the initial state
    set<Matrix *> closedList; // to store all the matrices that have been added to the priority queue till now

    vector<Matrix *> allMatrices; // to list all the matrices

    ll k, n;

    priority_queue<pair<pair<ll, ll>, Matrix *>, vector<pair<pair<ll, ll>, Matrix *>>, Compare> priorityQueueOfMatricesForHamming, priorityQueueOfMatricesForManhattan;
    // these are the two priority queues of the matrices, one for hamming distance, and the other for Manhattanm distance
    // they will use the value (integer) as the priority value

    starSearchAlgo(Matrix *matrix, ll k)
    {
        this->matrix = matrix;
        this->k = k;
        this->n = k;
        if (solvableOrNot())
        {
            // if the matrix is solvable then we run the algorithms
            cout << "For Hamming distance:--" << endl;
            findStepsUsingHammingDistance(); // for finding steps using Hamming distance
            cout << "For Manhattan Distance:--" << endl;
            findStepsUsingManhattanDistance(); // for finding steps using Manhattan distance
        }
    }

    // function to find  out if the initial state given as input is solvable or not
    bool solvableOrNot()
    {
        ll inv = matrix->findInversions();              // couting the number of inversions
        pair<ll, ll> blankPos = matrix->findBlankPos(); // getting the row and column number of the blank position

        if (k % 2 == 1)
        {
            if (inv % 2 == 1)
            {
                cout << "Sorry, it is not solvable." << endl;
                cout << "Because inversion number is odd" << endl; // if both k and the inversions are odd, then the matrix is unsolvable
                return false;
            }
            else
            {
                return true; // if k is odd and the inversion count is even, then the matrix is solvable
            }
        }
        if (((n - blankPos.first) % 2) != (inv % 2))
        {
            return true; // if both inversion count and the blank's row position from bottom have  different parity then it is solvable
        }
        else
        {
            cout << "Sorry, the matrix is not solvable." << endl;
            cout << "Because, its inversions number is " << inv << " , and its row no from below is " << (n - blankPos.first) << endl;
            return false; // inversion count and the row position of the blank from bottom have same parity, so it is unsolvable
        }
    }

    // this function frees the space for all the matrices except the initial state
    void freeMatrices()
    {
        for (ll i = 0; i < allMatrices.size(); i++)
        {
            delete allMatrices[i]; // deleting all the matrix pointers in the vector to free their spaces
        }
        allMatrices.clear(); // clearing the vecor
    }

    //  this function print all the necessary elements and matrices
    void printAnswers(string str, Matrix *answerMatrix, ll expandedNodes, ll exploredNodes)
    {
        Matrix *cur = answerMatrix;
        stack<Matrix *> stackOfMatrices;
        ll processed = 0;
        while (cur != NULL)
        {
            // we will find parents until parent state in NULL meaning it is the initial state
            stackOfMatrices.push(cur); // pushing it into the stack
            cur = cur->parent;
            processed++;
        }
        cout << "Steps needed using " << str << " distance:= " << processed - 1 << endl; // total steps
        cout << "Total expanded Nodes:= " << expandedNodes << endl;                      // total expanded nodes
        cout << "Total explored Nodes:= " << exploredNodes << endl;                      // total explored nodes
        while (stackOfMatrices.size() > 0)
        {
            Matrix *tempMatrix = stackOfMatrices.top();
            stackOfMatrices.pop();       // popping stack elements one by one
            printMatrix(tempMatrix->mt); // printing the matrix
            cout << endl;
        }
        freeMatrices(); // free the space for all the matrices except the initial state
        closedList.clear();
    }

    // function for determining steps using Hamming distance
    void findStepsUsingHammingDistance()
    {
        unordered_map<string, bool> map; // to keep track of states
        string initialString = matrix->getAString();
        map[initialString] = true;
        priorityQueueOfMatricesForHamming.push(make_pair(make_pair(matrix->findHammingDistance(), 0), matrix)); // adding the initial state into the priority queue

        ll expandedNodes = 0, exploredNodes = 1;
        Matrix *answerMatrix; // to store the answer matrix
        while (true)
        {
            // printPriorityQueue(priorityQueueOfMatricesForHamming);
            if (priorityQueueOfMatricesForHamming.size() == 0)
                break;                                                                         // there is no more elements in queue to pop()
            pair<pair<ll, ll>, Matrix *> poppedPair = priorityQueueOfMatricesForHamming.top(); // getting the matrix with the lowest distance
            priorityQueueOfMatricesForHamming.pop();
            closedList.insert(poppedPair.second); // removing the element from the priority queue

            if (poppedPair.second->findHammingDistance() == 0)
            {
                // we have found our answer state
                answerMatrix = poppedPair.second; // storing the answer
                break;
            }
            expandedNodes++; // we need to expand a node
            Matrix *currentMatrix = poppedPair.second;
            vector<Matrix *> allMoves = currentMatrix->findAllMoves(); // getting all the possible moves for the current matrix
            for (ll i = 0; i < allMoves.size(); i++)
            {
                Matrix *mat = allMoves[i];
                string temp = mat->getAString();
                if (!map[temp])
                {
                    // there is no state till noe like the newest state
                    map[temp] = true;                                                                                                     // setting we have found this state
                    priorityQueueOfMatricesForHamming.push(make_pair(make_pair(mat->findHammingDistance() + mat->move, mat->move), mat)); // adding the new state into the priority queue
                    exploredNodes++;                                                                                                      // we have explored a new node state
                    allMatrices.push_back(mat);                                                                                           // adding the new node into the list of all matrices
                }
                else
                {
                    // there is already a instance of this state
                    delete mat; // deleting the space needed for that matrix
                }
            }
        }
        printAnswers(" Hamming ", answerMatrix, expandedNodes, exploredNodes); // printing the answer
    }

    // function for determining steps using manhattan distance
    void findStepsUsingManhattanDistance()
    {
        unordered_map<string, bool> map; // to keep track of states
        string initialString = matrix->getAString();
        map[initialString] = true;
        priorityQueueOfMatricesForManhattan.push(make_pair(make_pair(matrix->findManhattanDistance(), 0), matrix)); // adding the initial state to the priority queue

        ll expandedNodes = 0, exploredNodes = 1;
        Matrix *answerMatrix; // to store the answer matrix
        while (true)
        {
            // printPriorityQueue(priorityQueueOfMatricesForManhattan);
            if (priorityQueueOfMatricesForManhattan.size() == 0)
            {
                break; // there is no more elements to pop()
            }
            pair<pair<ll, ll>, Matrix *> poppedPair = priorityQueueOfMatricesForManhattan.top(); //  getting the state with the lowest distance
            priorityQueueOfMatricesForManhattan.pop();                                           // removing that value
            closedList.insert(poppedPair.second);

            if (poppedPair.second->findManhattanDistance() == 0)
            {
                // we have found our answer
                answerMatrix = poppedPair.second; // assigning the answer matrix
                break;
            }
            expandedNodes++; // another node expanding is required
            Matrix *currentMatrix = poppedPair.second;
            vector<Matrix *> allMoves = currentMatrix->findAllMoves(); // stroing all the possible moves inside allMoves vector
            for (ll i = 0; i < allMoves.size(); i++)
            {
                Matrix *mat = allMoves[i];
                string temp = mat->getAString();
                if (!map[temp])
                {
                    // there is no other state in all the matrices like mat matrix pointer
                    map[temp] = true;                                                                                                         // setting we have found that state
                    priorityQueueOfMatricesForManhattan.push(make_pair(make_pair(mat->findManhattanDistance() + mat->move, mat->move), mat)); // adding them into priority queue
                    exploredNodes++;                                                                                                          // exploring another new node matrix
                    allMatrices.push_back(mat);                                                                                               // adding this new state to the vector of all kind of states
                }
                else
                {
                    delete mat; // deleting the space needed for the pointer
                }
            }
        }
        printAnswers(" Manhattan ", answerMatrix, expandedNodes, exploredNodes); // printing the matrix
    }
};

void solve()
{
    ll k;
    cin >> k;
    vector<vector<string>> matrix; // to input the initial positions

    // freopen("output.txt", "w", stdout);
    // this is to output the answer to a text file instead of a console

    for (ll i = 0; i < k; i++)
    {
        vector<string> tempString;
        for (ll j = 0; j < k; j++)
        {
            string temp;
            cin >> temp; // to input all the initial states
            tempString.push_back(temp);
        }
        matrix.push_back(tempString);
    }

    Matrix *mt = new Matrix(matrix, NULL);          // to make a matrix class
    starSearchAlgo *st = new starSearchAlgo(mt, k); // starting the algorithm class
    // cout << mt->findManhattanDistance() << endl;

    delete st; // deleting the pointer of the algo class
    delete mt; // deleting the initial matrix
}

int main()
{
    // cin.tie(0);
    // cin.sync_with_stdio(0);
    // cout.tie(0);
    // cout.sync_with_stdio(0);
    int t = 1;
    // cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}