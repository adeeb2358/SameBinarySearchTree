//
//  main.cpp
//  SameBinarySearchTree
//
//  Created by adeeb mohammed on 19/04/20.
//  Copyright © 2020 adeeb mohammed. All rights reserved.
//
// program to find two arrays gives the same bst
// optimal solution o(n*2) time and o(d) space
// non optimal solution gives o(n*2) time and space

#include <iostream>
#include <vector>

std::vector<int> getSmaller(std::vector<int> array){
    std::vector<int> smallerArray;
    for(int i = 1; i < array.size(); i++){
        if(array.at(i) < array.at(0)){
            smallerArray.push_back(array.at(i));
        }
    }
    return smallerArray;
}

std::vector<int> getBiggerOrEqual(std::vector<int> array){
    std::vector<int> biggerArray;
    for(int i = 1; i < array.size(); i++){
        if(array.at(i) > array.at(0)){
            biggerArray.push_back(array.at(i));
        }
    }
    return biggerArray;
}


bool sameBstsOrg(std::vector<int> arrayOne, std::vector<int> arrayTwo) {
    if(arrayOne.size() != arrayTwo.size()){
        return false;
    }
    
    if(arrayOne.size() == 0 && arrayTwo.size() == 0){
        return true;
    }
    
    if(arrayOne[0] != arrayTwo[0]){
        return false;
    }
    
    std::vector<int> smallerOne = getSmaller(arrayOne);
    std::vector<int> smallerTwo = getSmaller(arrayTwo);
    std::vector<int> biggerOne  = getBiggerOrEqual(arrayOne);
    std::vector<int> biggerTwo  = getBiggerOrEqual(arrayTwo);
    
    return sameBstsOrg(smallerOne, smallerTwo) && sameBstsOrg(biggerOne, biggerTwo);
}
/* **************************************************************************  */


int getIdxOfFirstSmaller(std::vector<int> array, int startingIdx, int minVal){
    for(int i = startingIdx + 1; i < array.size();i++){
        if(array[i] < array[startingIdx] && array[i] >= minVal){
            return i;
        }
    }
    return -1;
}

int getIdxOfFirstBiggerOrEqual(std::vector<int> array,int startingIdx,int maxVal){
    for (int i = startingIdx+1; i < array.size(); i++) {
        if(array[i] >= array[startingIdx] && array[i] < maxVal){
            return i;
        }
    }
    return -1;
}


bool areSameBsts(std::vector<int> arrayOne,
                 std::vector<int> arrayTwo,
                 int rootIdxOne,
                 int rootIdxTwo,
                 int minVal,
                 int maxVal){
    
    if(rootIdxOne == -1 || rootIdxTwo == -1){
        return rootIdxOne == rootIdxTwo;
    }
    if(arrayOne.at(rootIdxOne) != arrayTwo.at(rootIdxTwo)){
        return false;
    }
    
    int leftRootIdxOne = getIdxOfFirstSmaller(arrayOne, rootIdxOne, minVal);
    int leftRootIdxTwo = getIdxOfFirstSmaller(arrayTwo, rootIdxTwo, minVal);
    int rightRootIdxOne = getIdxOfFirstBiggerOrEqual(arrayOne,rootIdxOne, maxVal);
    int rightRootIdxTwo = getIdxOfFirstBiggerOrEqual(arrayTwo, rootIdxTwo, maxVal);
    
    int currentValue = arrayOne.at(rootIdxOne);
    bool isLeftSubTreeSame = areSameBsts(arrayOne, arrayTwo, leftRootIdxOne, leftRootIdxTwo,minVal, currentValue);
    bool isRightSubTreeSame = areSameBsts(arrayOne, arrayTwo, rightRootIdxOne, rightRootIdxTwo,currentValue, maxVal);
    return isLeftSubTreeSame && isRightSubTreeSame;
}




bool sameBsts(std::vector<int> arrayOne, std::vector<int> arrayTwo){
    return areSameBsts(arrayOne,arrayTwo,0,0,INT_MIN,INT_MAX);
}


int main(int argc, const char * argv[]) {
    std::cout << "function to check whether two arrays form same binary trees." << std::endl;
    std::cout << sameBsts({10,24,23,12,12,5,6}, {10,12,23,12,24,5,6});
    return 0;
}
