//+-----------------------------------------------------------------------------
//
//  File:       minheap.h
//
//  Synopsis:   Implemented a minimal MinHeap
//
//  Author:     Qirong Ma, 10/12/2015
//
//------------------------------------------------------------------------------
#pragma once
#ifndef nullptr
#define nullptr 0
#endif

template<class T>
class MinHeap {
private:
	T* _array;
	int _currentSize;
	int _maxSize;
	bool _outsideData;

	void SiftUp(int pos) {
		T temp = _array[pos];
		while (pos > 0 && _array[parent(pos)] > temp) {
			_array[pos] = _array[parent(pos)];
			pos = parent(pos);
		}
		_array[pos] = temp;
	}

	void SiftDown(int pos) {
		int i = pos;
		int j = 2*pos+1;
		T temp = _array[i];

		while (j < _currentSize) {
			if (j < _currentSize-1 && _array[j] > _array[j+1])
				j++;
			if (temp > _array[j]) {
				_array[i] = _array[j];
				i = j;
				j = 2*j+1;
			}
			else
				break;
		}
		_array[i] = temp;
	}

public:
	MinHeap(const int n) : _array(nullptr), _currentSize(0), _maxSize(n), _outsideData(false) {
		_array = new T[n];
	}
	MinHeap(T* data, const int n): _array(data), _currentSize(n), _maxSize(n), _outsideData(true)
	{
		for (int i = _currentSize / 2; i >= 0; i--)
			SiftDown(i);
	}
	virtual ~MinHeap() {
		if (!_outsideData)
			delete[] _array;
	}

	int size() const {return _currentSize;}
	int maxSize() const {return _maxSize;}
	bool isLeaf(int pos) const {return (2*pos+1 >= _currentSize);}
	int leftchild(int pos) const {return 2*pos+1;}
	int rightChild(int pos) const {return 2*pos+2;}
	int parent(int pos) const {return (pos-1)/2;}

	bool Insert(T node) {
		if (_currentSize == _maxSize)
			return false;
		_array[_currentSize++] = node;
		SiftUp(_currentSize-1);
		return true;
	}

	bool Remove(int pos, T& node) {
		if (pos<0 || pos>=_currentSize)
			return false;
		T temp = _array[pos];
		_array[pos] = _array[_currentSize-1];
		_array[--_currentSize] = temp;
		if (pos > 0 && _array[parent(pos)] > _array[pos])
			SiftUp(pos);
		else
			SiftDown(pos);
		node = temp;
		return true;
	}

	T RemoveMin() {
		T temp;
		Remove(0, temp);
		return temp;
	}
};
