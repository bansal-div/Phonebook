#include <bits/stdc++.h>

using namespace std;

class node {
	public:
	int value;
	int height;
	int diff;
	node *left;
	node *right;
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

node *insert(int n, node *root) {
	if(root == NULL) {
		root = new node;
		root->value = n;
		root->height = 1;
		root->diff = 0;
		root->left = NULL;
		root->right = NULL;
		return root;
	}
	else {
		if(n < root->value) {
			root->left = insert(n, root->left);
		}
		else {
			root->right = insert(n, root->right);
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

node *remove(int n, node *root) {
  if(root == NULL) return root;
  if(n == root->value) {
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
      root->value = ptr->value;
      root->right = remove(root->value, root->right);
      return root;
    }
  }
  else if(n < root->value) {
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
  cout<< root->value << " " << root->height << endl;
  printer(root->left);
  printer(root->right);
}

int main() {
	node *root = NULL;
	root = insert(1, root);
  root = insert(2, root);
	root = insert(3, root);
  root = insert(4, root);
  root = insert(5, root);
  //root = remove(1, root);
  
  printer(root);
}