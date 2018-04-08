#include "ftime.h"
#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <chrono>
#include <ctime>

using namespace std;

TimeNode::TimeNode() {
	children = vector<TimeNode>();
}

TimeNodeStack::TimeNodeStack()
{
	start = std::chrono::high_resolution_clock::now();
}


void TimeNodeStack::push(string name)
{
	TimeNode t_node;
	t_node.name = name;
	t_node.begin = std::chrono::high_resolution_clock::now();
	stack.push_back(t_node);
}

void TimeNodeStack::pop()
{
	if (stack.size() > 1) {
		TimeNode t_node = stack[stack.size() - 1];
		stack.pop_back();
		t_node.end = std::chrono::high_resolution_clock::now();
		stack[stack.size() - 1].children.push_back(t_node);
	} else if (stack.size() == 1) {
		stack[0].end = std::chrono::high_resolution_clock::now();
                if(print_flag){
                        print_recursive(stack[0], string(""));
                        stack.pop_back();
                } else {
                        print_stack.push_back(stack[0]);
                        stack.pop_back();
                }
                //print();
                //stack.pop_back();
	} else {
		throw runtime_error("error");
	}
}

void TimeNodeStack::print_recursive(const TimeNode& x, const string& arrow)
{
	cout << setw(70) << left << arrow + x.name << setw(20) << left << 
                std::chrono::duration_cast<std::chrono::microseconds>(x.begin - start).count() << 
                setw(20) << left << std::chrono::duration_cast<std::chrono::microseconds>(x.end - x.begin).count() << 
                '\n';

	for (TimeNode child : x.children) {
		if (arrow.length() == 0) {
			print_recursive(child, " \\_");
		} else {
			print_recursive(child, arrow.substr(0, arrow.length() - 2) + "    " + "\\_");
		}
	}
}

void TimeNodeStack::print()
{
        //User should be allowed to put more than one function at top level of tree, e.g. processInput and actonInput
        //if (stack.size() != 1) {
	//	throw runtime_error("Error: not finished visiting the call stack.");
	//}
        //if (!printed) {
        cout << setw(70) << left << "namespace/function name" << setw(20) << 
                left << "unix begin time" << setw(20) << left << "time elapsed" <<'\n';
        cout << string(102, '-') << '\n';
        //cout << "stack size: " << stack.size() << '\n';
	for(TimeNode node: print_stack){
                //auto node = stack[0];
	        print_recursive(node, string(""));
	        //stack.pop_back();
        }
}

TimeNodeStack t_stack = TimeNodeStack();
