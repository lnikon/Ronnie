#pragma once

class ElementArray {
public:
	ElementArray();
	ElementArray(const ElementArray&) = delete;
	ElementArray(ElementArray&&) = delete;
	ElementArray& operator=(const ElementArray&) = delete;
	ElementArray& operator(ElementArray&&) = delete;
	~ElementArray();
};