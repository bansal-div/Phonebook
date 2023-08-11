#include <bits/stdc++.h>

using namespace std;

class node {
	public:
	string name;
  string number;
	int height;
	int diff;
	node *left;
	node *right;

  node(string name, string number) {
    this->name = name;
    this->number = number;
    this->height = 1;
		this->diff = 0;
		this->left = NULL;
		this->right = NULL;
  }
};

int heightfind(node *root) {
  if(root->left == NULL && root->right != NULL) return root->right->height + 1;
	else if(root->left != NULL && root->right == NULL) return root->left->height + 1;
  else if(root->left != NULL && root->right != NULL) return max(root->left->height, root->right->height) + 1;
  else return 1;
}

int difffind(node *root) {
  if(root->left == NULL && root->right != NULL) return root->right->height;
	else if(root->left != NULL && root->right == NULL) return -root->left->height;
	else if(root->left != NULL && root->right != NULL) return root->right->height - root->left->height;
  else return 0;
}

void update(node *root) {
  root->height = heightfind(root);
  root->diff = difffind(root);
}

node *rightrotate(node *root) {
  node *temp = root->left;
  root->left = temp->right;
  update(root);
  temp->right = root;
  root = temp;
  update(root);
  return root;
}

node *leftrotate(node *root) {
  node *temp = root->right;
  root->right = temp->left;
  update(root);
  temp->left = root;
  root = temp;
  update(root);
  return root;
}

node *insert(string n, string p, node *root) {
	if(root == NULL) {
		root = new node(n, p);
		return root;
	}
	else {
		if(n < root->name) {
			root->left = insert(n, p, root->left);
		}
		else {
			root->right = insert(n, p, root->right);
		}
    
    update(root);

    if(root->diff < -1) {
      if(root->left->diff == -1) {
        root = rightrotate(root);
      }
      else {
        root->left = leftrotate(root->left);
        root = rightrotate(root);
      }
    }
    else if(root->diff > 1) {
      if(root->right->diff == 1) {
        root = leftrotate(root);
      }
      else {
        root->right = rightrotate(root->right);
        root = leftrotate(root);
      }
    }
    
		return root;
	}
}

node *remove(string n, node *root) {
  if(root == NULL) return root;
  if(n == root->name) {
    if(root->left == NULL && root->right == NULL) {
      root = NULL;
      return root;
    }
    else if(root->left != NULL && root->right == NULL) {
      root = root->left;
      return root;
    }
    else if(root->left == NULL && root->right != NULL) {
      root = root->right;
      return root;
    }
    else {
      node *ptr = root->right;
      while(ptr->left != NULL) {
        ptr = ptr->left;
      }
      root->name = ptr->name;
      root->right = remove(root->name, root->right);
      return root;
    }
  }
  else if(n < root->name) {
    root->left = remove(n, root->left);
  }
  else {
    root->right = remove(n, root->right);
  }
  
  update(root);

  if(root->diff < -1) {
      if(root->left->diff == -1) {
        root = rightrotate(root);
      }
      else {
        root->left = leftrotate(root->left);
        root = rightrotate(root);
      }
    }
    else if(root->diff > 1) {
      if(root->right->diff == 1) {
        root = leftrotate(root);
      }
      else {
        root->right = rightrotate(root->right);
        root = leftrotate(root);
      }
    }
  return root;
}

void printer(node *root) {
  if(root == NULL) return;
  printer(root->left);
  cout<< root->name << " " << root->number << endl;
  printer(root->right);
}

int main() {
	node *root = NULL;
  while(true) {
    string s;
    cin >> s;
    cout << "commands" << endl;
    if(s == "insert") {
      string n, p;
      cin >> n >> p;
      root = insert(n, p, root);
    }
    else if(s== "remove") {
      string n;
      cin >> n;
      root = remove(n, root);
      
    }
    else if(s == "print") {
      printer(root);
    }
    else if(s == "stop") {
      break;
    }
    else {
      cout << "invalid command" << endl;
    }
  }
}