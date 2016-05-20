//IMHO using Class for this task is an overkill
//So I am using just one struct and a few functions to operate with it

//NOTE: The input must start with ( and the first digit of the root must be at position 1 !!!
//Example: (5{...
#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <algorithm>

struct Node
{
	int val;
	Node* parent;
	std::vector<Node*> children;
	Node() {}
	Node(int _val, Node* _parent) : val(_val), parent(_parent) {}
};

void deleteTree(Node* root)
{
	if (root->children.size() == 0) {
		delete root;
		return;
	}
	for (auto& a : root->children) {
		a->children.clear();
		deleteTree(a);
	}
	if (!root->parent) delete root;
}

int extract_int(const std::string& line, int& pos)
{
	int start = pos, end = pos;
	while (isdigit(line[end++]));

	//-1 so we don't jump over the element after the number
	pos = end - 1;
	return std::stoi(line.substr(start, end));
}

/*
* Use the AHU algorithm with cannonical names
* Source of the paper: http://logic.pdmi.ras.ru/~smal/files/smal_jass08_slides.pdf
*/
std::string rootCannonicalName(Node* const root)
{
	if (root->children.size() == 0)
	{
		//The Knuth tuple is (0) for a leaf
		//With the cannonical names we replace '(' and ')' with 1 and 0 respectively 
		//ignoring the 0
		return "10";
	}
	else
	{
		//we make a new cannonical name by concatenating the cannonical names of the children (sorted)
		//and put the result between 1 and 0
		//which is equivalent of putting it into brackets

		std::vector<std::string> children;
		Node* tmp = new Node();
		for (auto& a : root->children) {
			children.emplace_back(rootCannonicalName(a));
		}
		std::sort(children.begin(), children.end());
		//The default comparison is alphabetical
		//With lambda redefine it for comparing the lengths
		//This way we ignore the mirroring (?!? could use a better word here)
		//Stable so we do not mess with the previous alphabetical sort
		std::stable_sort(children.begin(), children.end(),
			[](std::string l, std::string r) { return l.length() > r.length(); }
		);
		std::string res = "1";
		for (auto& a : children) {
			res += a;
		}
		res += "0";

		return res;
	}
}

/*
 * Not optimised. + gluposti :(
 * TODO: Rewrite it better
 */
void buildTreeWrapper(std::string& line, int _pos, Node* root, std::stack<char>& bracketsHolder)
{
	Node* last = root;				//<!-- Could I do it without this node???
	for (int pos = _pos; pos < line.length(); pos++)
	{
		char c = line[pos];
		if (line[pos] == ' ' || line[pos] == '(' || line[pos] == ')')
			continue;
		if (line[pos] == '{'){
			if (line[pos + 1] == '}') { pos++; continue; }

			bracketsHolder.push(line[pos]);
			root = last;
			continue;
		}
		if (line[pos] == '}'){
			bracketsHolder.pop();
			if (root->parent)
				root = root->parent;
			continue;
		}

		if (isdigit(line[pos])){
			Node* new_child = new Node(extract_int(line, pos), root);
			root->children.push_back(new_child);
			last = new_child;

			//Hack: If there's no white space after the number
			//Pos jumps to a bracket and after pos++ is calculated we miss a bracket in the next iteration
			if (line[pos] == '{') pos--;
		}
	}
}

Node* buildTree(std::string& line)
{
	//Const : Precation for accidently changing where the root points
	Node* const root = new Node(0, nullptr);
	//Take the root
	std::stack<char> s;
	s.push('(');
	int pos = 1;
	root->val = extract_int(line, pos);
	buildTreeWrapper(line, pos, root, s);

	return root;
}

int main()
{
	std::string t1, t2;
	std::getline(std::cin, t1);
	std::getline(std::cin, t2);
	Node* t1_root = buildTree(t1);
	Node* t2_root = buildTree(t2);
	std::string t1_canonicalName = rootCannonicalName(t1_root);
	std::string t2_canonicalName = rootCannonicalName(t2_root);

	std::string equal = (t1_canonicalName.compare(t2_canonicalName) == 0) ? "YES" : "NO";
	std::cout << equal << std::endl;

	deleteTree(t1_root);
	deleteTree(t2_root);
	return 0;
}