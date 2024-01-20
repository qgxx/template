/**
 * @brief 给定一个字符串，逆时针不断的把最后一个字符放在开头
 * （或者顺时针不断地把第一个字符放在最后），所形成的所有字符串集合中字典序最小的一个
 * 
 * O(n)
 */

#include <iostream>
#include <algorithm>

std::string MinS(std::string s) {
    int n = s.length();
    s = "?" + s + s;
    int i = 1, j = 2, k;
    while (i <= n && j <= n) {
        for (k = 0; k < n && s[i + k] == s[j + k]; k++);
        if (k == n) break;
        if (s[i + k] > s[j + k]) {
            i = i + k + 1;
            if (i == j) i++;
        }
        else {
            j = j + k + 1;
            if (j == i) j++;
        }
    }
    return (s.substr(std::min(i, j), n));
}