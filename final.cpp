#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <queue>
#include <unordered_map>
#include <climits>

using namespace std;

struct Crop
{
    int id;
    string name;
    int health;
};

// Global Data
vector<Crop> crops;
stack<string> irrigationHistory;
queue<string> alerts;
unordered_map<int, string> cropHash;

// ---------------- ADD CROP ----------------
void addCrop()
{
    Crop c;

    cout << "\nEnter Crop ID: ";
    cin >> c.id;

    cout << "Enter Crop Name: ";
    cin >> c.name;

    cout << "Enter Health Score: ";
    cin >> c.health;

    crops.push_back(c);

    cropHash[c.id] = c.name;

    cout << "Crop Added Successfully!\n";
}

// ---------------- DISPLAY ----------------
void displayCrops()
{
    cout << "\nCrop Records\n";

    for (auto c : crops)
    {
        cout << "ID: " << c.id
             << " Name: " << c.name
             << " Health: " << c.health
             << endl;
    }
}

// ---------------- SEARCH ----------------
void searchCrop()
{
    int id;

    cout << "Enter Crop ID: ";
    cin >> id;

    for (auto c : crops)
    {
        if (c.id == id)
        {
            cout << "Crop Found: "
                 << c.name
                 << " Health: "
                 << c.health
                 << endl;
            return;
        }
    }

    cout << "Crop Not Found\n";
}

// ---------------- SORTING ----------------
void sortHealth()
{
    sort(crops.begin(), crops.end(),
         [](Crop a, Crop b)
         {
             return a.health > b.health;
         });

    cout << "Sorted By Health Score\n";
}

// ---------------- STACK ----------------
void irrigateCrop()
{
    string cropName;

    cout << "Enter Crop Name: ";
    cin >> cropName;

    irrigationHistory.push(cropName);

    cout << cropName
         << " Irrigated Successfully\n";
}

void showLastIrrigation()
{
    if (irrigationHistory.empty())
    {
        cout << "No Irrigation History\n";
        return;
    }

    cout << "Last Irrigated Crop: "
         << irrigationHistory.top()
         << endl;
}

// ---------------- QUEUE ----------------
void addAlert()
{
    string msg;

    cin.ignore();

    cout << "Enter Alert: ";
    getline(cin, msg);

    alerts.push(msg);

    cout << "Alert Added\n";
}

void processAlert()
{
    if (alerts.empty())
    {
        cout << "No Alerts Available\n";
        return;
    }

    cout << "Processing Alert: "
         << alerts.front()
         << endl;

    alerts.pop();
}

// ---------------- HASHING ----------------
void hashSearch()
{
    int id;

    cout << "Enter Crop ID: ";
    cin >> id;

    if (cropHash.find(id) != cropHash.end())
    {
        cout << "Crop Found: "
             << cropHash[id]
             << endl;
    }
    else
    {
        cout << "Crop Not Found\n";
    }
}

// ---------------- GRAPH ----------------
vector<int> graph[5];
vector<pair<int, int>> weightedGraph[5];

void createGraph()
{
    graph[0].push_back(1);
    graph[0].push_back(2);

    graph[1].push_back(3);

    graph[2].push_back(4);

    weightedGraph[0].push_back({1, 4});
    weightedGraph[0].push_back({2, 2});

    weightedGraph[1].push_back({3, 5});

    weightedGraph[2].push_back({1, 1});
    weightedGraph[2].push_back({4, 3});

    weightedGraph[4].push_back({3, 2});
}

// ---------------- BFS ----------------
void BFS(int start)
{
    bool visited[5] = {false};

    queue<int> q;

    visited[start] = true;

    q.push(start);

    cout << "BFS: ";

    while (!q.empty())
    {
        int node = q.front();

        q.pop();

        cout << node << " ";

        for (int neighbour : graph[node])
        {
            if (!visited[neighbour])
            {
                visited[neighbour] = true;

                q.push(neighbour);
            }
        }
    }

    cout << endl;
}

// ---------------- DFS ----------------
void DFS(int node, bool visited[])
{
    visited[node] = true;

    cout << node << " ";

    for (int neighbour : graph[node])
    {
        if (!visited[neighbour])
        {
            DFS(neighbour, visited);
        }
    }
}

// ---------------- DIJKSTRA ----------------
void dijkstra(int start)
{
    vector<int> dist(5, INT_MAX);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty())
    {
        int distance = pq.top().first;
        int node = pq.top().second;
        pq.pop();

        if (distance > dist[node])
        {
            continue;
        }

        for (auto edge : weightedGraph[node])
        {
            int neighbour = edge.first;
            int weight = edge.second;

            if (dist[node] + weight < dist[neighbour])
            {
                dist[neighbour] = dist[node] + weight;
                pq.push({dist[neighbour], neighbour});
            }
        }
    }

    cout << "Shortest Distance From Node " << start << ":\n";

    for (int i = 0; i < 5; i++)
    {
        cout << "Node " << i << " = " << dist[i] << endl;
    }
}

// ---------------- AVL TREE ----------------
struct AVLNode
{
    int data;
    int height;
    AVLNode *left;
    AVLNode *right;
};

int height(AVLNode *node)
{
    if (node == NULL)
    {
        return 0;
    }

    return node->height;
}

int getBalance(AVLNode *node)
{
    if (node == NULL)
    {
        return 0;
    }

    return height(node->left) - height(node->right);
}

AVLNode *newAVLNode(int data)
{
    AVLNode *node = new AVLNode();
    node->data = data;
    node->height = 1;
    node->left = NULL;
    node->right = NULL;

    return node;
}

AVLNode *rightRotate(AVLNode *y)
{
    AVLNode *x = y->left;
    AVLNode *temp = x->right;

    x->right = y;
    y->left = temp;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

AVLNode *leftRotate(AVLNode *x)
{
    AVLNode *y = x->right;
    AVLNode *temp = y->left;

    y->left = x;
    x->right = temp;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

AVLNode *insertAVL(AVLNode *node, int data)
{
    if (node == NULL)
    {
        return newAVLNode(data);
    }

    if (data < node->data)
    {
        node->left = insertAVL(node->left, data);
    }
    else if (data > node->data)
    {
        node->right = insertAVL(node->right, data);
    }
    else
    {
        return node;
    }

    node->height = max(height(node->left), height(node->right)) + 1;

    int balance = getBalance(node);

    if (balance > 1 && data < node->left->data)
    {
        return rightRotate(node);
    }

    if (balance < -1 && data > node->right->data)
    {
        return leftRotate(node);
    }

    if (balance > 1 && data > node->left->data)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && data < node->right->data)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

void avlDemo()
{
    AVLNode *root = NULL;
    int values[] = {30, 20, 40, 10, 25, 50};

    for (int value : values)
    {
        root = insertAVL(root, value);
    }

    cout << root->data << " (Root)\n";
    cout << "       /  \\\n";
    cout << "     " << root->left->data << "    " << root->right->data << endl;
    cout << "    /  \\     \\\n";
    cout << "  " << root->left->left->data
         << "    " << root->left->right->data
         << "    " << root->right->right->data
         << endl;
}

// ---------------- MAIN ----------------
int main()
{
    createGraph();

    int choice;

    do
    {
        cout << "\n===== SMART FARMING SYSTEM =====\n";

        cout << "1. Add Crop\n";
        cout << "2. Display Crops\n";
        cout << "3. Search Crop\n";
        cout << "4. Sort By Health\n";
        cout << "5. Irrigate Crop\n";
        cout << "6. Show Last Irrigation\n";
        cout << "7. Add Alert\n";
        cout << "8. Process Alert\n";
        cout << "9. Hash Search\n";
        cout << "10. BFS Traversal\n";
        cout << "11. DFS Traversal\n";
        cout << "12. Dijkstra Algorithm\n";
        cout << "13. AVL Tree\n";
        cout << "14. Exit\n";

        cout << "Enter Choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                addCrop();
                break;

            case 2:
                displayCrops();
                break;

            case 3:
                searchCrop();
                break;

            case 4:
                sortHealth();
                break;

            case 5:
                irrigateCrop();
                break;

            case 6:
                showLastIrrigation();
                break;

            case 7:
                addAlert();
                break;

            case 8:
                processAlert();
                break;

            case 9:
                hashSearch();
                break;

            case 10:
                BFS(0);
                break;

            case 11:
            {
                bool visited[5] = {false};

                cout << "DFS: ";

                DFS(0, visited);

                cout << endl;

                break;
            }

            case 12:
                dijkstra(0);
                break;

            case 13:
                avlDemo();
                break;

            case 14:
                cout << "Thank You\n";
                break;

            default:
                cout << "Invalid Choice\n";
        }

    } while (choice != 14);

    return 0;
}
